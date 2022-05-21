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

#define LDR_READ    0xA0

#define READ_SWITCH_DELAY 1000    // delay between 2 read switch commands
#define READ_LDR_DELAY    2500    // delay between 2 read LDR commands

#define COMM_WRITE_READ_DELAY 2   // delay between write command and read back result

#define PWM_MOT_1 3
#define PWM_MOT_2 5
#define PWM_FWD 6
#define PWM_BWD 4

volatile byte received;

SoftwareSerial softSerial(PIN_RX, PIN_TX);

void setup()
{
  pinMode(PWM_MOT_1, OUTPUT);
  pinMode(PWM_MOT_2, OUTPUT);
  pinMode(PWM_FWD, OUTPUT);
  pinMode(PWM_BWD, OUTPUT);
  
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT);               // setting LED pin as OUTPUT

  setupSerialComm();

  printInfo();                            // print usage message onto device connected to HW Serial
}

void loop() {
  if (softSerial.available() > 0) // fetch received command
  {
    received = softSerial.read(); // receive byte as a character

    doCommand();                          // process command received from master
  }

  readMasterLDR();
}

void readMasterLDR() {
  static unsigned long prevReadLDRCmd = 2000L;   // time of most recent read switch command
  byte received[2];                           // byte received upon read switch command
  unsigned int ldrValue;
  unsigned long now = millis();               // milliseconds from power up

  if (now - READ_LDR_DELAY > prevReadLDRCmd) {
    prevReadLDRCmd = now;
    Serial.println(F("clemen test: read LDR"));
    if (requestSerialInt(LDR_READ, &ldrValue)) {                // slave may send less than requested
      Serial.print("clemens test: ");
      Serial.println(ldrValue);
    }
  }
  //delay(10);
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
      writeSerialByte(digitalRead(PIN_SWITCH) ? LED_ON : LED_OFF); // send the button state to master
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
    case NO_ACTION:                           // with SPI: will be sent from master following READ_SWITCH to get button state
      break;
    default:
      Serial.print(F("Slave: undefined command 0x"));
      Serial.println(received, HEX);
  }
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
