#include <SoftwareSerial.h>

#define PIN_RX        7
#define PIN_TX        8
#define PIN_LED       4           // LED on pin 4
#define PIN_SWITCH    2           // tactile switch on pin 2
#define PIN_LDR       A1

#define LED_OFF     0x01          // switch LED off command
#define LED_ON      0x02          // switch LED on command
#define READ_SWITCH 0x03          // read switch state command
#define READ_LDR    0x04
#define WRITE_LDR   0x05          //write ldr value to slave
#define NO_ACTION   0xFF          // dummy command for 'do nothing'
#define WRITE_LDR   0x05

#define READ_SWITCH_DELAY 1000    // delay between 2 read switch commands
#define READ_LDR_DELAY    2500    // delay between 2 read LDR commands
#define WRITE_LDR_DELAY   2000

#define COMM_WRITE_READ_DELAY 2   // delay between write command and read back result

SoftwareSerial softSerial(PIN_RX, PIN_TX);
unsigned long now = 0;
unsigned long ldrTime = 2000L;
int currentLdrValue = 0;

void setup(void) {
  Serial.begin(115200);                   // start Serial Communication at Baud Rate 115200
  pinMode(PIN_LED, OUTPUT);               // set LED pin as output

  setupSerialComm();

  printInfo();                            // print usage message onto device connected to HW Serial
  //delay(1000);                            // wait a moment to avoid unwanted flooding log at the beginning
}

void loop(void) {
  /*
  doSwitch();
  readSlaveSwitch();
  readSlaveLDR();
  */
  
  // ldr send every 2 seconds
  now = millis();
  if (now - WRITE_LDR_DELAY > ldrTime){
    currentLdrValue = analogRead(PIN_LDR);
    writeSerialInt(WRITE_LDR, currentLdrValue);
    ldrTime = now;
  }
}

void readSlaveSwitch() {
  static unsigned long prevReadSwitchCmd = 2000L;   // time of most recent read switch command
  byte received = 0;               // byte received upon read switch command
  unsigned long now = millis();      // milliseconds from power up

  if (now - READ_SWITCH_DELAY > prevReadSwitchCmd) {
    prevReadSwitchCmd = now;
    //Serial.println(F("Master: read switch"));
    if (requestSerialByte(READ_SWITCH, &received)) {                // slave may send less than requested
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
    if (requestSerialInt(READ_LDR, &ldrValue)) {                // slave may send less than requested
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
    writeSerialByte(switchState ? LED_ON : LED_OFF);
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
  Serial.println(F("UART communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: 5 -> 3, 9600 BAUD"));
  Serial.println(F("Master eagerly reads own tactile switch and sends changes to slave (LED_ON, LED_OFF)"));
  Serial.println(F("       requests tactile switch of slave every second (READ_SWITCH)"));
  Serial.println(F("       requests LDR value of slave every 2 and a half second (READ_LDR)"));
  Serial.println(F("       fetches values from slave (>= 1 byte) by sending according number of NO_ACTION commands"));
  Serial.println(F("       builds result from multiple byte responses (MSB first) (LDR)"));
  Serial.println(F("       switches own LED according to slaves answer (LED_ON, LED_OFF)"));
  Serial.println(F("       prints LDR value received from slave (2 bytes, MSB followed by LSB) onto Serial"));
}

void setupSerialComm() {
  softSerial.begin(9600);
}

void writeSerialByte(byte value) {
  softSerial.write(value);       // sends command byte LED_ON or LED_OFF to slave
}

boolean requestSerialByte(byte command, byte *value) {
  boolean success = false;
  softSerial.write(command);                   // send read switch request READ_SWITCH to slave
  delay(COMM_WRITE_READ_DELAY);                                 // give slave time to accomplish work
  success = softSerial.available() >= 1;
  if (success) {                // slave may send less than requested
    *value = softSerial.read();                 // receive 1 byte from slave
  }
  return success;
}

boolean requestSerialInt(byte command, int *value) {
  boolean success = false;
  byte received[2];
  softSerial.write(command);                     // send read switch request READ_LDR to slave
  delay(COMM_WRITE_READ_DELAY);                   // give slave time to accomplish work (1 is not enough)
  success = softSerial.available() >= 2;
  if (success) {              // slave may send less than requested
    received[0] = softSerial.read();                 // receive MSB byte of LDR value from slave
    received[1] = softSerial.read();                 // receive LSB byte of LDR value from slave
    *value = received[0] * 256 + received[1]; // build int from 2 bytes
    Serial.print(F("Master: LDR: "));
    Serial.print('('); Serial.print(received[0]);
    Serial.print(' '); Serial.print(received[1]);
    Serial.print(") ");
  }
  return success;
}

void writeSerialInt(byte command, int value) {
    softSerial.write(command); 
    softSerial.write((value >> 8) & 0xFF);
    softSerial.write(value & 0xFF);
}
