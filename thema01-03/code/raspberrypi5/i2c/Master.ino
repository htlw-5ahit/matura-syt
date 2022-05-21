#include<Wire.h>                   // Library for SPI einbinden

#define LEDS_I2C_ADDR 4           // I2C address of LED, LDR, and tactile switch slave

#define PIN_LED       3           // LED on pin 3
#define PIN_SWITCH    2           // tactile switch on pin 2
#define PIN_LDR    A1

#define LED_OFF     0x01          // switch LED off command
#define LED_ON      0x02          // switch LED on command
#define READ_SWITCH 0x03          // read switch state command
#define READ_LDR    0x04
#define MOTOR       0x05
#define NO_ACTION   0xFF          // dummy command for 'do nothing'

#define READ_SWITCH_DELAY 1000    // delay between 2 read switch commands
#define READ_LDR_DELAY    2500    // delay between 2 read LDR commands

#define COMM_WRITE_READ_DELAY 1   // delay between write command and read back result

unsigned long previousMillis = 0;
const long interval = 1000;

volatile byte unsentData[2];
volatile int unsentCount;           // initialized to 0 to indicate no data belonging to previous command is unsent

void setup(void) {
  Serial.begin(115200);                   // start Serial Communication at Baud Rate 115200
  pinMode(PIN_LED, OUTPUT);               // set LED pin as output

  setupI2cComm();

  printInfo();                            // print usage message onto device connected to HW Serial
  //delay(1000);                            // wait a moment to avoid unwanted flooding log at the beginning
}

void loop(void) {
  doSwitch();
  readSlaveSwitch();
  readSlaveLDR();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    writeLDR();
  }
  
}

void readSlaveSwitch() {
  static unsigned long prevReadSwitchCmd = 2000L; // time of most recent read switch command
  byte received = 0;                               // byte received upon read switch command
  unsigned long now = millis();                // milliseconds from power up

  if (now - READ_SWITCH_DELAY > prevReadSwitchCmd) {
    prevReadSwitchCmd = now;
    //Serial.println(F("Master: read switch"));
    if (requestI2cByte(READ_SWITCH, &received)) {                // slave may send less than requested
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
    if (requestI2cInt(READ_LDR, &ldrValue)) {                // slave may send less than requested
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
    writeI2cByte(switchState ? LED_ON : LED_OFF);
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
  Serial.println(F("I2C communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: SDA<->SDA, SCL<->SCL (SDA/A4, SCL/A5 on UNO)"));
  Serial.println(F("Master eagerly reads own tactile switch and sends changes to slave (LED_ON, LED_OFF)"));
  Serial.println(F("       requests tactile switch of slave every second (READ_SWITCH)"));
  Serial.println(F("       requests LDR value of slave every 2 and a half second (READ_LDR)"));
  Serial.println(F("       fetches values from slave (>= 1 byte) by sending according number of NO_ACTION commands"));
  Serial.println(F("       builds result from multiple byte responses (MSB first) (LDR)"));
  Serial.println(F("       switches own LED according to slaves answer (LED_ON, LED_OFF)"));
  Serial.println(F("       prints LDR value received from slave (2 bytes, MSB followed by LSB) onto Serial"));
}

void setupI2cComm() {
  Wire.begin();                            // begin the I2C commnuication
}

void writeI2cByte(byte value) {
  Wire.beginTransmission(LEDS_I2C_ADDR);            //Starts communication with to device number LEDS_I2C_ADDR
  Wire.write(value);       // sends command byte LED_ON or LED_OFF to slave
  Wire.endTransmission();                           // stop transmitting -> transfer data
}

boolean requestI2cByte(byte command, byte *value) {
  boolean success = false;
  Wire.beginTransmission(LEDS_I2C_ADDR);
  Wire.write(command);                   // send read switch request READ_SWITCH to slave
  Wire.endTransmission();
  delay(COMM_WRITE_READ_DELAY);                                 // give slave time to accomplish work
  Wire.requestFrom(LEDS_I2C_ADDR, 1);     // request 1 byte from slave device (tactile switch state LED_ON or LED_OFF)
  success = Wire.available() >= 1;
  if (success) {                // slave may send less than requested
    *value = Wire.read();                 // receive 1 byte from slave
  }
  return success;
}

boolean requestI2cInt(byte command, int *value) {
  boolean success = false;
  byte received[2];
  Wire.beginTransmission(LEDS_I2C_ADDR);
  Wire.write(command);                     // send read switch request READ_LDR to slave
  Wire.endTransmission();
  delay(COMM_WRITE_READ_DELAY);             // give slave time to accomplish work
  Wire.requestFrom(LEDS_I2C_ADDR, 2);       // request 2 byte from slave device (10 bit LDR value)
  success = Wire.available() >= 2;
  if (success) {              // slave may send less than requested
    received[0] = Wire.read();                 // receive MSB byte of LDR value from slave
    received[1] = Wire.read();                 // receive LSB byte of LDR value from slave
    *value = received[0] * 256 + received[1]; // build int from 2 bytes
    Serial.print(F("Master: LDR: "));
    Serial.print('('); Serial.print(received[0]);
    Serial.print(' '); Serial.print(received[1]);
    Serial.print(") ");
  }
  return success;
}

void writeI2cInt1(int value) {
  unsentData[0] = value & 0xFF;        // preserve low byte of LDR value in unsent data at index 0 (MSB first!)
  unsentData[1] = (value >> 8) & 0xFF; // send the high byte of the LDR value on next transfer to master
  unsentCount = 2;                   // remember count of unsent bytes

  writeI2cByte(unsentData[0]);
  writeI2cByte(unsentData[1]);
}

void writeLDR() {
    int ldrValue = analogRead(PIN_LDR);
    Serial.println(ldrValue);
    writeI2cByte(MOTOR);
    writeI2cInt1(ldrValue);
}
