#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout above
#define RST_PIN       8
#define SS_PIN        10

// led configuration
#define LED_0         5     // led green
#define LED_1         3     // led red
#define LED_SHINE     2000  // led shine time

// button configuration
#define BUTTON        2

// master uid
unsigned long masterUid = 0;

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

  // set pin modes for leds and buttons
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(BUTTON, INPUT);
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

  // set new master
  if (digitalRead(BUTTON) == HIGH) {
    masterUid = readUid();
    Serial.println(masterUid);

  } else {
    // default routine
    if (readUid() == masterUid) {
      controlLed(LED_0);
    } else {
      controlLed(LED_1);
    }
  }

}

// read uid
unsigned long readUid() {
  unsigned long id = mfrc522.uid.uidByte[0];
  for (int i = 1; i < mfrc522.uid.size; i++) {
    id *= 256;
    id += mfrc522.uid.uidByte[i];
  }
  return id;
}

// switch led on and off with above defined delay
void controlLed(int led) {
  digitalWrite(led, HIGH);
  delay(LED_SHINE);
  digitalWrite(led, LOW);
}
