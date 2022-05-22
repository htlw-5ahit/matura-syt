# Peripherie

## Echtzeituhr

* Wir verwenden folgende Echtzeituhr: DS3231
* Der DS3231 zwei einstellbare Alarme mit dem über zwei Ausgängen Interrupts eines Mikrocontrollers zu einem bestimmten Zeitpunkt oder periodisch ausgelöst werden können.
* Der DS3231 ist über den I2C Bus angeschlossen. Zusätzlich kann über die I2C Adresse und Registern zugegriﬀen werden. Zusätzlich hat der DS3231 einen Ausgang für ein 32kHz Signal, was über ein Register ein- oder ausgeschaltet werden kann.
* Es ﬁndet auch alle 64 Sekunden eine Temperaturmessung innerhalb des DS3231 statt, welche dann den Oscillator des Uhr der Umgebungstemperatur zu Korrekturzwecken anpasst. Die Temperatur kann über zwei Register ausgelesen werden und auch eine manuelles Anstossen der Messung ist möglich.

```c
#include <Wire.h>
#include <DS3231.h>

#define LEN_STR 100

DS3231 clock;
RTCDateTime dt;

char timeStr[LEN_STR];

void setup() {
  Serial.begin(112500);

  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();

  // Set date and time
  // clock.setDateTime(2020-09-29, 09-00-00-00);
}

void loop() {
  dt = clock.getDateTime();

  sprintf(timeStr, „%04d-%02d-%02d %02d-%02d-%02d",
    dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second
  );
  Serial.println(timeStr);
  
  delay(1000);
}
```

## NFC-Kartenleser

* Folgenden Baustein haben wir verwendet: MFRC-522. Die dafür verwendete Library heißt „MFRC522“ und wird von der Github Community bereitgestellt.
* Der RFID („radio-frequency identiﬁcation“) Reader wird verwendet, um von RFID Sendern (auch „RFID Tags“ genannt) per Funk einen bestimmten Code auszulesen. Jeder Sender hat dabei nur einen einmaligen ganz individuellen Code.

```c
#include <SPI.h>
#include <MFRC522.h>

// Configurable, see typical pin layout above
#define RST_PIN 8
#define SS_PIN 10

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  
  Serial.begin(115200); // Initialize serial communications with the PC
  while (!Serial); // Do nothing if no serial port is opened

  
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  delay(4); // Optional delay. Some board do need more time after init to be ready

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
```

Beispiele:
- [Arduino: NFC-Kartenleser mit LED Steuerung](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/nfc_led)
- [Arduino: NFC-Kartenleser mit LED und Taster Steuerung](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/nfc_led_taster)