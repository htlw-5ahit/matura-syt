#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout above
#define RST_PIN 8
#define SS_PIN 10

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // Initialize serial communications with the PC
  Serial.begin(115200);
  // Do nothing if no serial port is opened
  // (added for Arduinos based on ATMEGA32U4)
  while (!Serial);

  // Init SPI bus
  SPI.begin();
  // Init MFRC522
  mfrc522.PCD_Init();
  // Optional delay. Some board do need more time after init to be ready
  delay(4);

  // Show details of PCD - MFRC522 Card Reader details
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader.
  // This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
