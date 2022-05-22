#include <SoftwareSerial.h>

#define PIN_RX     7
#define PIN_TX     8
#define PIN_LED    4
#define PIN_SWITCH 2
#define PIN_LDR    A1

#define LED_OFF     0x01
#define LED_ON      0x02
#define READ_SWITCH 0x03
#define READ_LDR    0x04
#define NO_ACTION   0xFF
#define WRITE_LDR   0x05

#define MOTOR_A     10
#define MOTOR_B     11
#define MOTOR_FWD   12
#define MOTOR_BWD   13

volatile byte received;
int motorValue = 0;

SoftwareSerial softSerial(PIN_RX, PIN_TX);

void setup()
{
  Serial.begin(115200);

  // setting LED pin as OUTPUT
  pinMode(PIN_LED, OUTPUT);               

  setupSerialComm();
  
  // set output mode on motor
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  pinMode(MOTOR_FWD, OUTPUT);
  pinMode(MOTOR_BWD, OUTPUT);

  // set default motor rotation to forward
  digitalWrite(MOTOR_FWD, HIGH);

  // print usage message onto device connected to HW Serial
  printInfo();
}

void loop() {
  // fetch received command
  if (softSerial.available() > 0) {
    // receive byte as a character
    received = softSerial.read();
    // process command received from master
    doCommand();                          
  }
}

void doCommand() {
  static boolean prevLedState = false;
  int ldrValue;

  // distinquish command received
  switch (received) {
    case LED_ON:
      if (!prevLedState) {
        // sets LED pin HIGH to switch LED on
        digitalWrite(PIN_LED, HIGH);
        Serial.println(F("Slave: LED on"));
        prevLedState = true;
      }
      break;
    case LED_OFF:
      if (prevLedState) {
        // sets LED pin LOW to switch LED off
        digitalWrite(PIN_LED, LOW);
        Serial.println(F("Slave: LED off"));
        prevLedState = false;
      }
      break;
    case READ_SWITCH:
      //Serial.println(F("Slave: read switch"));
      // send the button state to master
      writeSerialByte(digitalRead(PIN_SWITCH) ? LED_ON : LED_OFF);
      break;
    case READ_LDR:
      //Serial.println(F("Slave: read LDR"));
      ldrValue = analogRead(PIN_LDR);
      Serial.print(F("Slave: LDR: "));
      Serial.print('('); Serial.print((ldrValue >> 8) & 0xFF);
      Serial.print(' '); Serial.print(ldrValue & 0xFF);
      Serial.print(") ");
      Serial.println(ldrValue);
      writeSerialInt(ldrValue);
      break;
    case WRITE_LDR:
      int sensorValue = 0;
      // read sensor
      requestSerialInt(&sensorValue);
      // debug logging
      Serial.print("WRITE LDR ");
      Serial.println(sensorValue);
      // map values for motor
      motorValue = map(sensorValue, 45, 1024, 0, 255);
      break;
    case NO_ACTION:
      // with SPI: will be sent from master following READ_SWITCH to get button state
      break;
    default:
      Serial.print(F("Slave: undefined command 0x"));
      Serial.println(received, HEX);
  }
  
  // move motor a
  analogWrite(MOTOR_A, motorValue);
}

void printInfo() {
  Serial.println(F("UART communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: 8 -> 7, 9600 BAUD"));
  Serial.println(F("Slave switches LED on/off according to command received (LED_ON, LED_OFF)"));
  Serial.println(F("       reads own switch if requested and prepares result for next transfer (READ_SWITCH)"));
  Serial.println(F("       reads LDR if requested, prepares 2 result bytes (MSB first) for next transfers (READ_LDR)"));
  Serial.println(F("       prints LDR value sent to master (2 bytes, MSB folowed by LSB) onto Serial"));
}

void setupSerialComm() {
  softSerial.begin(9600);
}

void writeSerialByte(byte value) {
  softSerial.write(value);
}

void writeSerialInt(int value) {
  softSerial.write((value >> 8) & 0xFF); // send the high byte of the LDR value to master first
  softSerial.write(value & 0xFF);        // send low byte of LDR value to master second (MSB first!)
}

boolean requestSerialInt(int *value) {
  boolean success = false;
  byte received[2];
  delay(2);                   // give slave time to accomplish work (1 is not enough)
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