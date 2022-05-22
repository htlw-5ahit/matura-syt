#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout above
#define RST_PIN         8
#define SS_PIN          10

#define LED_0           5
#define LED_1           6

#define LED_SHINE       2000

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  // Initialize serial communications with the PC
  Serial.begin(115200);
  // Do nothing if no serial port is opened
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

  // Set LED Pins to Output
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
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

  /* readNFC(LED_0, 0x9C, 0x82, 0xBC, 0xB2);
  readNFC(LED_1, 0xA5, 0xE0, 0xE3, 0xBB); */

  // Serial.println(mfrc522.uid.size);

  // TODO: auf gleiner gleich länge 4 einschränken

  unsigned long id = mfrc522.uid.uidByte[0];
  for (int i = 1; i < mfrc522.uid.size; i++) {
    id *= 256;
    id += mfrc522.uid.uidByte[i];
  }

  Serial.println(id, 16);

  if (id == 0x9C82BCB2) {
    digitalWrite(LED_0, HIGH);
    delay(LED_SHINE);
    digitalWrite(LED_0, LOW);
  } else if (id == 0xA5E0E3BB) {
    digitalWrite(LED_1, HIGH);
    delay(LED_SHINE);
    digitalWrite(LED_1, LOW);
  }

  
}
