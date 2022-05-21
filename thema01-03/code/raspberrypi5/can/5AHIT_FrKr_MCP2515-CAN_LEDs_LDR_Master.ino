#include <stdlib.h>
#include <SPI.h>
#include <mcp2515.h>

#define PIN_LED       3           // LED on pin 3
#define PIN_SWITCH    2           // tactile switch on pin 2
#define PIN_LDR       A1

#define LED_OFF     0x01          // switch LED off command
#define LED_ON      0x02          // switch LED on command
#define READ_SWITCH 0x03          // read switch state command
#define READ_LDR    0x04
#define WRITE_LDR   0x05
#define NO_ACTION   0xFF          // dummy command for 'do nothing'

#define WRITE_LDR_DELAY   2000    // delay between 2 write LDR commands
#define READ_SWITCH_DELAY 1000    // delay between 2 read switch commands
#define READ_LDR_DELAY    2500    // delay between 2 read LDR commands

#define COMM_WRITE_READ_DELAY 5   // delay between write command and read back result

MCP2515 mcp2515(7);
struct can_frame canMsg[3];

unsigned long now = 0;
unsigned long lastWrite = 2000L;

void setup(void) {
  Serial.begin(115200);                   // start Serial Communication at Baud Rate 115200
  pinMode(PIN_LED, OUTPUT);               // set LED pin as output

  setupCanComm();
  buildCanMsgs();

  printInfo();                            // print usage message onto device connected to HW Serial
  //delay(1000);                            // wait a moment to avoid unwanted flooding log at the beginning
}

void loop(void) {
  /*doSwitch();
  readSlaveSwitch();
  readSlaveLDR();*/

  now = millis();
  //If time is over, send value again
  if(now - WRITE_LDR_DELAY > lastWrite){
    int sensValue = analogRead(PIN_LDR);
    writeCanLDR(sensValue);
    lastWrite = now;
 }
}

void readSlaveSwitch() {
  static unsigned long prevReadSwitchCmd = 2000L; // time of most recent read switch command
  byte received = 0;                               // byte received upon read switch command
  unsigned long now = millis();                // milliseconds from power up

  if (now - READ_SWITCH_DELAY > prevReadSwitchCmd) {
    prevReadSwitchCmd = now;
    //Serial.println(F("Master: read switch"));
    if (requestCanByte(READ_SWITCH, &received)) {                // slave may send less than requested
      doCommand(received);
    }
  }
  //delay(10);
}

void readSlaveLDR() {
  static unsigned long prevReadLDRCmd = 2000L;   // time of most recent read switch command
  byte received[2];                           // byte received upon read switch command
  unsigned int ldrValue;
  unsigned long now = millis();               // milliseconds from power up

  if (now - READ_LDR_DELAY > prevReadLDRCmd) {
    prevReadLDRCmd = now;
    //Serial.println(F("Master: read LDR"));
    if (requestCanInt(READ_LDR, &ldrValue)) {                // slave may send less than requested
      Serial.println(ldrValue);
    }
  }
  //delay(10);
}

void doSwitch() {
  static boolean prevSwitchState = false;      // previous state of tactile switch (to reduce repeating messages)
  boolean switchState = digitalRead(PIN_SWITCH);
  if (switchState != prevSwitchState) {
    prevSwitchState = switchState;
    writeCanByte(switchState ? LED_ON : LED_OFF);
  }
}

void doCommand(byte received) {
  static boolean prevLedState = false;       // previous state of LED to reduce dig.Write and Serial.print
  switch (received) {
    case LED_ON:                             // set the LED state depending upon command received from slave
      if (!prevLedState) {
        digitalWrite(PIN_LED, HIGH);         //Sets LED pin HIGH
        Serial.println(F("Master: LED on"));
        prevLedState = true;
      }
      break;
    case LED_OFF:
      if (prevLedState) {
        digitalWrite(PIN_LED, LOW);          //Sets LED pin LOW
        Serial.println(F("Master: LED off"));
        prevLedState = false;
      }
      break;
    case NO_ACTION:
      break;
    default:
      Serial.print(F("Master: undefined command 0x"));
      Serial.println(received, HEX);
  }
}

void printInfo() {
  Serial.println(F("CAN communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: MCP2515 CAN-Connector, CS/SS 10, 125KBPS"));
  Serial.println(F("Master eagerly reads own tactile switch and sends changes to slave (LED_ON, LED_OFF)"));
  Serial.println(F("       requests tactile switch of slave every second (READ_SWITCH)"));
  Serial.println(F("       requests LDR value of slave every 2 and a half second (READ_LDR)"));
  Serial.println(F("       fetches values from slave (>= 1 byte) by sending according number of NO_ACTION commands"));
  Serial.println(F("       builds result from multiple byte responses (MSB first) (LDR)"));
  Serial.println(F("       switches own LED according to slaves answer (LED_ON, LED_OFF)"));
  Serial.println(F("       prints LDR value received from slave (2 bytes, MSB followed by LSB) onto Serial"));
}

void setupCanComm() {
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}

void writeCanByte(byte value) {
  canMsg[1].data[0] = value;
  mcp2515.sendMessage(&canMsg[1]); // sends command byte LED_ON or LED_OFF to slave
}

boolean requestCanByte(byte command, byte *value) {
  boolean success = false;
  canMsg[0].data[0] = command;
  mcp2515.sendMessage(&canMsg[0]);          // send read switch request READ_SWITCH to slave
  delay(COMM_WRITE_READ_DELAY);                                 // give slave time to accomplish work
  success = mcp2515.readMessage(&canMsg[2]) == MCP2515::ERROR_OK;
  if (success) {                // slave may send less than requested
    *value = canMsg[2].data[0];           // receive 1 byte from slave
  }
  return success;
}

boolean requestCanInt(byte command, int *value) {
  boolean success = false;
  canMsg[0].data[0] = command;
  mcp2515.sendMessage(&canMsg[0]);          // send read switch request READ_LDR to slave
  delay(COMM_WRITE_READ_DELAY);             // give slave time to accomplish work (1 is not enough)
  success = mcp2515.readMessage(&canMsg[2]) == MCP2515::ERROR_OK;
  if (success) {              // slave may send less than requested
    *value = canMsg[2].data[0] * 256 + canMsg[2].data[1]; // build int from 2 bytes (MSB @ 0, LSB @ 1
    Serial.print(F("Master: LDR: "));
    Serial.print('('); Serial.print(canMsg[2].data[0]);
    Serial.print(' '); Serial.print(canMsg[2].data[1]);
    Serial.print(") ");
  }
  return success;
}

void buildCanMsgs() {
  // lowest can_id (0x00) has highest priority / is dominant
  // highest can_id (0xFF) has lowest priority / is recessive
  // Request switch state / LDR value command
  canMsg[0].can_id  = 0x0F6;
  canMsg[0].can_dlc = 8;
  canMsg[0].data[0] = 0x8E;
  canMsg[0].data[1] = 0x87;
  canMsg[0].data[2] = 0x32;
  canMsg[0].data[3] = 0xFA;
  canMsg[0].data[4] = 0x26;
  canMsg[0].data[5] = 0x8E;
  canMsg[0].data[6] = 0xBE;
  canMsg[0].data[7] = 0x86;

  // switch LED on/off command
  canMsg[1].can_id  = 0x036;
  canMsg[1].can_dlc = 8;
  canMsg[1].data[0] = 0x0E;
  canMsg[1].data[1] = 0x00;
  canMsg[1].data[2] = 0x00;
  canMsg[1].data[3] = 0x08;
  canMsg[1].data[4] = 0x01;
  canMsg[1].data[5] = 0x00;
  canMsg[1].data[6] = 0x00;
  canMsg[1].data[7] = 0xA0;

  //Send LDR Value to Slave
  canMsg[2].can_id = 0x01;
  canMsg[2].can_dlc = 3;
  canMsg[2].data[0] = 0x0E;
  canMsg[2].data[1] = 0x00;
  canMsg[2].data[2] = 0xA0;
}

void writeCanLDR(int value){
  Serial.println(value);
  
  canMsg[2].data[0] = WRITE_LDR;
  canMsg[2].data[1] = (value >> 8) & 0xFF; // send the high byte of the LDR value to master first
  canMsg[2].data[2] = value & 0xFF;        // send low byte of LDR value to master second (MSB first!)           
  mcp2515.sendMessage(&canMsg[2]); // send the LDR value to master
}
