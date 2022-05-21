# UART - Universal Asynchronous Receiver / Transmitter

| Aufbau | Bitversand |
|---|---|
| ![Aufbau](https://cdn.rohde-schwarz.com/pws/solution/research___education_1/educational_resources_/oscilloscope_and_probe_fundamentals/05_Understanding-UART_01_w1280_hX.png) | ![Bitversand](https://cdn.rohde-schwarz.com/pws/solution/research___education_1/educational_resources_/oscilloscope_and_probe_fundamentals/05_Understanding-UART_04_w1280_hX.png) |



- Austausch von seriellen Daten zwischen zwei Geräten
- Zwei Drähte zwischen Sender und Empfänger, um in beiden Richtungen zu senden und zu empfangen
- Fünf bis maximal neun Datenbits
- Kommunikation:
	- Simplex-Betrieb: die Daten werden nur in eine Richtung gesendet
	-  Halbduplex-Betrieb: jede Seite sendet, aber nicht zur selben Zeit
	-  Vollduplex-Betrieb: beide Seiten können gleichzeitig senden
-  Arbeitet asynchron - kein gemeinsames Taktsignal, daher:
	-  Startbit signalisiert das Senden von Nutzdatenbits
	-  Stoppbit kennzeichnet das Ende der Nutzdaten
	-  Versand von Nutzdaten: normalerweise mit dem niedrigstwertigen Bit zuerst (Least Significant Bit, LSB)

Quelle: https://www.rohde-schwarz.com/at/produkte/messtechnik/oszilloskope/educational-content/uart-verstehen_254524.html

## Code

### Write

```c
void writeSerialByte(byte value) {
  softSerial.write(value);
}

void writeSerialInt(int value) {
  softSerial.write((value >> 8) & 0xFF); // send the high byte of the LDR value
  softSerial.write(value & 0xFF);  // send low byte of LDR value to master second
}
```

### Request

```c
boolean requestSerialByte(byte command, byte *value) {
  boolean success = false;
  softSerial.write(command);        // send read switch request READ_SWITCH to slave
  delay(COMM_WRITE_READ_DELAY);             // give slave time to accomplish work
  success = softSerial.available() >= 1;
  if (success) {                // slave may send less than requested
    *value = softSerial.read();                 // receive 1 byte from slave
  }
  return success;
}

boolean requestSerialInt(byte command, int *value) {
  boolean success = false;
  byte received[2];
  softSerial.write(command);       // send read switch request READ_LDR to slave
  delay(COMM_WRITE_READ_DELAY);   // give slave time to accomplish work (1 not enough)
  success = softSerial.available() >= 2;
  if (success) {              // slave may send less than requested
    received[0] = softSerial.read();  // receive MSB byte of LDR value from slave
    received[1] = softSerial.read();  // receive LSB byte of LDR value from slave
    *value = received[0] * 256 + received[1]; // build int from 2 bytes
    Serial.print(F("Master: LDR: "));
    Serial.print('('); Serial.print(received[0]);
    Serial.print(' '); Serial.print(received[1]);
    Serial.print(") ");
  }
  return success;
}
```

### Read
```c
boolean readSerialInt(int *value) {
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
```
