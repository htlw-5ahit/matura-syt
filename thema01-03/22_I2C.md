# I²C - Inter-Integrated Circuit

![Aufbau](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3e/I2C.svg/1920px-I2C.svg.png)

- Master-Slave-Bus
- Serieller 2-Draht-Bus
	- SDA ... Serial Data
	- SCL ... Serial Clock
- Bidirektionale Daten- und Taktleitung verwendet
- Mindestens einen Master sowie bis zu 127 Slaves (mehrere Master => "Multi-Master-Bus")
	- Slaves müssen alle mit einer individuellen Adresse codiert werden
	- Broadcastkanal, um alle Slaves anzusprechen
- Adressierung
	- Master sprechen die Slaves jeweils aktiv => Slaves können nie selbstständig beginnen
	- Kommunikation
		- Durch Start-Signal des Master übernimmt der Master den Bus
		- Dieser gibt anschließend Adresse des Slaves aus, mit welchen es kommunizieren möchte
		-  Abhängig vom R/W-Bit werden nun Daten byteweise geschrieben (Daten an Slave) oder gelesen (Daten vom Slave)
		- Anschließend werden die Daten auf den Bus geschrieben
		- Nach dem Lese- bzw. Schreibvorgang: Slave sendet ein Acknowledge (`ACK`) - Master quittiert diesen anschließend (außer beim Broadcast)
	- `Repeated-Start` kann vorkommen, um die erneute Übertragung zu triggern
	- Alle Bytes werden dabei „Most Significant Bit First“ übertragen.

Quellen:
- https://www.mikrocontroller.net/articles/I²C
- https://de.wikipedia.org/wiki/I²C

## Code

### Slave

- Slave hat Interrupts & Events

```c
void writeI2cByte(byte value) {
  noInterrupts();
  unsentData[0] = value; // send the button state on next transfer to master
  unsentCount = 1;                             // remember count of unsent bytes
  interrupts();
}

void writeI2cInt(int value) {
  noInterrupts();
  // preserve low byte of LDR value in unsent data at index 0 (MSB first!)
  unsentData[0] = value & 0xFF;
  // send the high byte of the LDR value on next transfer to master       
  unsentData[1] = (value >> 8) & 0xFF;
  unsentCount = 2;        // remember count of unsent bytes
  interrupts();
}
```

```c
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
	   // trigger loop as new command to be processed is available
          jobAvailable = true;
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
```

### Master

```c
void writeI2cByte(byte value) {
  Wire.beginTransmission(LEDS_I2C_ADDR); //Starts communication with to device number LEDS_I2C_ADDR
  Wire.write(value);       // sends command byte LED_ON or LED_OFF to slave
  Wire.endTransmission();          // stop transmitting -> transfer data
}

boolean requestI2cByte(byte command, byte *value) {
  boolean success = false;
  Wire.beginTransmission(LEDS_I2C_ADDR);
  Wire.write(command);           // send read switch request READ_SWITCH to slave
  Wire.endTransmission();
  delay(COMM_WRITE_READ_DELAY);            // give slave time to accomplish work
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
  Wire.requestFrom(LEDS_I2C_ADDR, 2);  // request 2 byte from slave device (10 bit LDR)
  success = Wire.available() >= 2;
  if (success) {              // slave may send less than requested
    received[0] = Wire.read();       // receive MSB byte of LDR value from slave
    received[1] = Wire.read();       // receive LSB byte of LDR value from slave
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
