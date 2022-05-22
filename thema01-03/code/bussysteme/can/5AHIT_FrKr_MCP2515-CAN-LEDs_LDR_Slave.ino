#include <SPI.h>
#include <mcp2515.h>

#define PIN_LED    4
#define PIN_SWITCH 2
#define PIN_LDR    A1

#define LED_OFF     0x01
#define LED_ON      0x02
#define READ_SWITCH 0x03
#define READ_LDR    0x04
#define WRITE_LDR   0x05
#define NO_ACTION   0xFF

#define MOT_A 3 //10 (beide PWM)
#define MOT_B 5 //11 (beide PWM)
#define FWD 6 //12 (digital)
#define BWD 4 //13 (digital)

volatile byte received;

MCP2515 mcp2515(7);
struct can_frame canMsg;

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);               // setting LED pin as OUTPUT

  setupCanComm();

  pinMode(MOT_A, OUTPUT);
  pinMode(MOT_B, OUTPUT);
  pinMode(FWD, OUTPUT);
  pinMode(BWD, OUTPUT);
  //forward
  digitalWrite(FWD, HIGH);
}

void loop() {  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) // fetch received command
  {
    received = canMsg.data[0];            // receive byte as a character
    Serial.println("Test: " + canMsg.data[0]);
    //    switch (canMsg.can_id) {
    //      case 0x0F6:
    //        break;
    //      case 0x036:
    //        break;
    //    } // switch

    doCommand();                          // process command received from master
  }
}

void doCommand() {
  static boolean prevLedState = false;
  int ldrValue;
  switch (received) {                           // distinquish command received
    case LED_ON:
      if (!prevLedState) {
        digitalWrite(PIN_LED, HIGH);            // sets LED pin HIGH to switch LED on
        Serial.println(F("Slave: LED on"));
        prevLedState = true;
      }
      break;
    case LED_OFF:
      if (prevLedState) {
        digitalWrite(PIN_LED, LOW);             // sets LED pin LOW to switch LED off
        Serial.println(F("Slave: LED off"));
        prevLedState = false;
      }
      break;
    case READ_SWITCH:
      //Serial.println(F("Slave: read switch"));
      writeCanByte(digitalRead(PIN_SWITCH) ? LED_ON : LED_OFF);
      break;
    case READ_LDR:
      //Serial.println(F("Slave: read LDR"));
      ldrValue = analogRead(PIN_LDR);
      Serial.print(F("Slave: LDR: "));
      Serial.print('('); Serial.print((ldrValue >> 8) & 0xFF);
      Serial.print(' '); Serial.print(ldrValue & 0xFF);
      Serial.print(") ");
      Serial.println(ldrValue);
      writeCanInt(ldrValue);
      break;
    case WRITE_LDR:
      int senseVal = 0;
      receiveCanInt(&senseVal);
      Serial.println("From Master: WRITE_LDR");
      setMotVal(senseVal);
      break;
    case NO_ACTION:                           // with SPI: will be sent from master following READ_SWITCH to get button state
      break;
    default:
      Serial.print(F("Slave: undefined command 0x"));
      Serial.println(received, HEX);
  }
}

void printInfo() {
  Serial.println(F("CAN communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: MCP2515 CAN-Connector, CS/SS 10, 125KBPS"));
  Serial.println(F("Slave switches LED on/off according to command received (LED_ON, LED_OFF)"));
  Serial.println(F("       reads own switch if requested and prepares result for next transfer (READ_SWITCH)"));
  Serial.println(F("       reads LDR if requested, prepares 2 result bytes (MSB first) for next transfers (READ_LDR)"));
  Serial.println(F("       prints LDR value sent to master (2 bytes, MSB folowed by LSB) onto Serial"));
}

void setupCanComm() {
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}

void writeCanByte(byte value) {
  canMsg.can_id = 0x06F;
  canMsg.can_dlc = 1;
  canMsg.data[0] = value;
  mcp2515.sendMessage(&canMsg); // send the button state to master
}

void writeCanInt(int value) {
  canMsg.can_id = 0x06F;
  canMsg.can_dlc = 2;
  canMsg.data[0] = (value >> 8) & 0xFF; // send the high byte of the LDR value to master first
  canMsg.data[1] = value & 0xFF;        // send low byte of LDR value to master second (MSB first!)
  mcp2515.sendMessage(&canMsg);            // send the LDR value to master
}

boolean receiveCanInt(int *value) {
  boolean success = true;
  delay(5);             // give slave time to accomplish work (1 is not enough)
  if (success) {              // slave may send less than requested
    *value = canMsg.data[1] * 256 + canMsg.data[2]; // build int from 2 bytes (MSB @ 0, LSB @ 1
    Serial.print(F("Master: LDR: "));
    Serial.print('('); Serial.print(*value);
    Serial.println(") ");
  }
  return success;
}

void setMotVal(int senseVal){
    int adjustedSensVal = map(senseVal, 40, 1024, 0, 255);
    int motVal = adjustedSensVal;
    moveMotor(motVal);
}

void moveMotor(int motVal){
    analogWrite(MOT_A, motVal);
}
