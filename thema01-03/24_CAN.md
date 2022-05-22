# CAN - Controller Area Network

| Aufbau | Topologie |
|---|---|
| ![Aufbau](https://www.me-systeme.de/website/var/tmp/image-thumbnails/0/5269/thumb__auto_065914de213e279c63fe37dad9bf21e5/canbus.png) | ![Verkabelung](https://upload.wikimedia.org/wikipedia/commons/thumb/9/9e/CAN-Bus_Elektrische_Zweidrahtleitung.svg/1920px-CAN-Bus_Elektrische_Zweidrahtleitung.svg.png) |

- Zweck: Kabelbäume reduzieren und hiermit Kosten und Gewicht zu spare
- Übertragungsverfahren
	- Multi-Master-Prinzip => Verbindung von mehrere gleichberechtigte Steuergeräten
	- CSMA/CR-Verfahren löst Kollisionen (gleichzeitiger Buszugriff) auf
	- Kupferleitungen: CAN-Bus arbeitet mit zwei verdrillten Adern, CAN_HIGH und CAN_LOW (symmetrische Signalübertragung)
- Datenaustausch
	- Beim CAN-Bus werden keine Knoten adressiert, sondern der Inhalt einer Nachricht  wird durch einen eindeutigen Identifier gekennzeichnet
	- Identifier legt gleichzeitig auch die Priorität der Nachricht fest (um so niedriger die ID, umso wichtiger die Nachricht)
	- Bei Kollision, niedrigste ID kommt durch
- Anwendungsbeispiel: Kraftfahrzeug

Quellen:
- https://de.wikipedia.org/wiki/Controller_Area_Network 
- https://www.me-systeme.de/de/technik-zuerst/elektronik/can-bus-grundlagen 

## Code

### Slave

```c
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
```


### Master

```c
void writeCanByte(byte value) {
  canMsg[1].data[0] = value;
  mcp2515.sendMessage(&canMsg[1]); // sends command byte LED_ON or LED_OFF to slave
}

boolean requestCanByte(byte command, byte *value) {
  boolean success = false;
  canMsg[0].data[0] = command;
  mcp2515.sendMessage(&canMsg[0]);   // send read switch request READ_SWITCH to slave
  delay(COMM_WRITE_READ_DELAY);                // give slave time to accomplish work
  success = mcp2515.readMessage(&canMsg[2]) == MCP2515::ERROR_OK;
  if (success) {                // slave may send less than requested
    *value = canMsg[2].data[0];           // receive 1 byte from slave
  }
  return success;
}

boolean requestCanInt(byte command, int *value) {
  boolean success = false;
  canMsg[0].data[0] = command;
  mcp2515.sendMessage(&canMsg[0]);     // send read switch request READ_LDR to slave
  delay(COMM_WRITE_READ_DELAY);  // give slave time to accomplish work (1 is not enough)
  success = mcp2515.readMessage(&canMsg[2]) == MCP2515::ERROR_OK;
  if (success) {              // slave may send less than requested
    *value = canMsg[2].data[0] * 256 + canMsg[2].data[1]; // build int from 2 bytes
    Serial.print(F("Master: LDR: "));
    Serial.print('('); Serial.print(canMsg[2].data[0]);
    Serial.print(' '); Serial.print(canMsg[2].data[1]);
    Serial.print(") ");
  }
  return success;
}

void writeCanLDR(int value){
  Serial.println(value);
  
  canMsg[2].data[0] = WRITE_LDR;
  canMsg[2].data[1] = (value >> 8) & 0xFF; // send the high byte of the LDR value to master first
  canMsg[2].data[2] = value & 0xFF;      // send low byte of LDR value to master second (MSB first!)           
  mcp2515.sendMessage(&canMsg[2]); // send the LDR value to master
}
```
