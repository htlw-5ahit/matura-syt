# SPI - Serial Peripheral Interface

| Master & Slave | Master & Multi-Slave |
|---|---|
| ![Master & Slave](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ed/SPI_single_slave.svg/1920px-SPI_single_slave.svg.png) | ![Master & Multi-Slave](https://upload.wikimedia.org/wikipedia/commons/thumb/9/97/SPI_three_slaves_daisy_chained.svg/1920px-SPI_three_slaves_daisy_chained.svg.png) |

- Drei Leitungen für eine serielle synchrone Datenübertragung
	- MOSI (Master Out -> Slave In) auch SDO (Serial Data Out) oder DO
	- MISO (Master In <- Slave Out) auch SDI (Serial Data In) oder DI
	- SCK (Serial Clock) - Schiebetakt
	- Zusätzlich wird für jeden Slave eine Slave Select (SS) oder auch Chip Select (CS) genannte Leitung benötigt, durch die der Master den Slave zur aktuellen Kommunikation selektiert
- Übertragungsprinzip
	- gleichzeitig 1 Bit vom Master zum Slave und 1 Bit vom Slave zum Master übertragen => "Austausch von Bits"
	- Master als auch Slave jederzeit sowohl Sender als auch Empfänger
	- jegliche Kommunikation geht immer vom Master aus
	- erstes Byte ist das Kommando, anschließend Daten

Quellen:
- https://www.mikrocontroller.net/articles/Serial_Peripheral_Interface
- https://de.wikipedia.org/wiki/Serial_Peripheral_Interface

## Code

### Slave

```c
void writeSpiByte(byte value) {
  noInterrupts();
  SPDR = value; // send the button state on next transfer to master via SPDR
  interrupts();
}

void writeSpiInt(int value) {
  noInterrupts();
  unsentData[0] = value & 0xFF;    // preserve low byte of LDR value in unsent data at index 0
  unsentCount = 1;                          // remember count of unsent bytes
  SPDR = (value >> 8) & 0xFF; // send the low byte of the LDR value on next transfer to master via SPDR
  interrupts();
}

ISR (SPI_STC_vect) {    // interrupt service routine function
  if (unreceived == 0) {
    received = SPDR;     // value received from master is store in variable received
    if (received == WRITE_LDR){
      unreceived = 2;
      SPDR = NO_ACTION; 
    } else if (unsentCount > 0) {
      SPDR = unsentData[--unsentCount]; // send first unsent byte and reduce counter of unsent bytes
    } else {
      SPDR = NO_ACTION;  // indicate nothing to be done on master (will be sent at next transfer)
      jobAvailable = true;  // trigger loop as new command to be processed is available
    }

  } else {
    if(unreceived == 2){
      receivedInt[0] = SPDR;
    } else{
      receivedInt[1] = SPDR;
      jobAvailable = true;   // trigger loop as new command to be processed is available
    }
    SPDR = NO_ACTION;  // indicate nothing to be done on master
    unreceived--; 
   }
}
```

### Master

```c
void writeSpiByte(byte value) {
  digitalWrite(SS, LOW);    //Starts communication with Slave connected to master
  /*value = */
   SPI.transfer(value); //Send the button state to slave, ignore synchronous response
  digitalWrite(SS, HIGH); //Ends communication with Slave connected to master
}

void writeSPIInt(int value) {
  writeSpiByte(WRITE_LDR);
  writeSpiByte((value >> 8) & 0xFF);
  writeSpiByte((value & 0xFF));
}
```

```c
void requestSpiByte(byte command, byte *value) {
  digitalWrite(SS, LOW);        // start communication to Slave connected to SS pin
  /* var = */SPI.transfer(command); // send read switch request to slave (
  digitalWrite(SS, HIGH);         // end communication with Slave connected to SS pin
  delay(1);                                 // give slave time to accomplish work
  digitalWrite(SS, LOW);                    // start communication with same Slave
  *value = SPI.transfer(NO_ACTION);       // get button state from same Slave
  digitalWrite(SS, HIGH);                   // end communication to same Slave
}

void requestSpiInt(byte command, int *value) {
  byte received[2];
  digitalWrite(SS, LOW);          // start communication to Slave connected to SS pin
  /* var = */SPI.transfer(command);    // send read LDR request to slave
  digitalWrite(SS, HIGH);          // end communication with Slave connected to SS pin
  delay(COMM_WRITE_READ_DELAY);                // give slave time to accomplish work
  digitalWrite(SS, LOW);                    // start communication with same Slave
  received[0] = SPI.transfer(NO_ACTION);  // get high byte of LDR value from same Slave
  delay(COMM_WRITE_READ_DELAY);
  received[1] = SPI.transfer(NO_ACTION);    // get low byte of LDR value from same Slave
  digitalWrite(SS, HIGH);                   // end communication to same Slave
  *value = received[0] * 256 + received[1]; // build int from 2 bytes
  Serial.print(F("Master: LDR: "));
  Serial.print('('); Serial.print(received[0]);
  Serial.print(' '); Serial.print(received[1]);
  Serial.print(") ");
}
```
