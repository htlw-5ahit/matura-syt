#include<Wire.h>

#define LEDS_I2C_ADDR 4           // I2C address of LED, LDR, and tactile switch slave

#define PIN_LED    4
#define PIN_SWITCH 2
#define PIN_LDR    A1

#define LED_OFF     0x01
#define LED_ON      0x02
#define READ_SWITCH 0x03
#define READ_LDR    0x04
#define MOTOR       0x05
#define NO_ACTION   0xFF

volatile byte received;
volatile boolean jobAvailable;
volatile byte unsentData[2];
volatile int unsentCount;           // initialized to 0 to indicate no data belonging to previous command is unsent

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);               // setting LED pin as OUTPUT

  setupI2cComm();

  printInfo();                            // print usage message onto device connected to HW Serial
}

void loop() {
  if (jobAvailable) {                     // react to command received from master
    noInterrupts();
    jobAvailable = false;                 // indicate no message to process
    interrupts();

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
      writeI2cByte(digitalRead(PIN_SWITCH) ? LED_ON : LED_OFF);
      break;
    case READ_LDR:
      //Serial.println(F("Slave: read LDR"));
      ldrValue = analogRead(PIN_LDR);
      Serial.print(F("Slave: LDR: "));
      Serial.print('('); Serial.print((ldrValue >> 8) & 0xFF);
      Serial.print(' '); Serial.print(ldrValue & 0xFF);
      Serial.print(") ");
      Serial.println(ldrValue);
      writeI2cInt(ldrValue);
      break;
    case NO_ACTION:                           // with SPI: will be sent from master following READ_SWITCH to get button state
      break;
    default:
      Serial.print(F("Slave: undefined command 0x"));
      Serial.println(received, HEX);
  }
}

void printInfo() {
  Serial.println(F("I2C communication between two Arduino UNO (Master and slave)"));
  Serial.println(F("Master: tactile switch on pin 2, LED on pin 3"));
  Serial.println(F("Slave: tactile swich on pin 2, LED on pin 4, LDR on pin A1"));
  Serial.println(F("Connection: SDA<->SDA, SCL<->SCL (SDA/A4, SCL/A5 on UNO)"));
  Serial.println(F("Slave switches LED on/off according to command received (LED_ON, LED_OFF)"));
  Serial.println(F("       reads own switch if requested and prepares result for next transfer (READ_SWITCH)"));
  Serial.println(F("       reads LDR if requested, prepares 2 result bytes (MSB first) for next transfers (READ_LDR)"));
  Serial.println(F("       prints LDR value sent to master (2 bytes, MSB folowed by LSB) onto Serial"));
}

void setupI2cComm() {
  jobAvailable = false;                   // nothing received yet -> nothing to do
  Wire.begin(LEDS_I2C_ADDR);              // join i2c bus with address #4
  Wire.onReceive(receiveEvent);           // register event handler for receiving data
  Wire.onRequest(requestEvent);           // register event handler for answering requests
}

void writeI2cByte(byte value) {
  noInterrupts();
  unsentData[0] = value; // send the button state on next transfer to master
  unsentCount = 1;                                            // remember count of unsent bytes
  interrupts();
}

void writeI2cInt(int value) {
  noInterrupts();
  unsentData[0] = value & 0xFF;        // preserve low byte of LDR value in unsent data at index 0 (MSB first!)
  unsentData[1] = (value >> 8) & 0xFF; // send the high byte of the LDR value on next transfer to master
  unsentCount = 2;                        // remember count of unsent bytes
  interrupts();
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  static byte receiveMultipleBytes = 0x00;
  static int receiveMultipleBytesAmount = 0;
  static byte receiveInt[2];
  
  if (Wire.available() > 0) // fetch received command
  {
    received = Wire.read(); // receive byte as a character

    // check if command is 'motor' ==> receiving bytes
    if (received == MOTOR) {
      receiveMultipleBytes = MOTOR; 
      
    } else {

      // check if multiple bytes are incoming
      if (receiveMultipleBytes != 0x00) {

        // save byte to array and inrement counter
        receiveInt[receiveMultipleBytesAmount] = received;
        receiveMultipleBytesAmount++;

        // check if all bytes are received
        if (receiveMultipleBytesAmount == 2) {
          
          // reset
          receiveMultipleBytes = 0x00;
          receiveMultipleBytesAmount = 0;

          // build bytes to int
          int ldr = receiveInt[0] + receiveInt[1] * 256;
    
          Serial.print("MY LDR: ");
          Serial.println(ldr);   
        }
      
      } else {
          // only one byte ==> no command attributes
          jobAvailable = true;                  // trigger loop as new command to be processed is available
      }
    }
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  while (unsentCount > 0) {
    Wire.write(unsentData[--unsentCount]);
  }
}
