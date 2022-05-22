#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <DS3231.h>
#include <LightDependentResistor.h>

#define SDCARD_PIN 10
#define SENSOR_PIN A1
#define BUTTON_PIN 2

#define OTHER_RESISTOR 3300 //ohms
#define USED_PHOTOCELL LightDependentResistor::GL5528

LightDependentResistor photocell(SENSOR_PIN, OTHER_RESISTOR, USED_PHOTOCELL);

DS3231 clock;
RTCDateTime dt;

File myFile;
char formatedString[50];
float sensorValue;

bool doing = 1;

unsigned long delayTime = 0;
unsigned long lastTime = 1500;

void sdCardSetup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("Initializing SD card...");
  if (!SD.begin(SDCARD_PIN)) {
    Serial.println("Initialization failed!");
    while (1);
  }
  Serial.println("Initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("syt.csv", FILE_WRITE);
  Serial.println("Open File succeeded.");
}

void setup() {
  // setup sd card
  sdCardSetup();

  // set csv header
  myFile.println("Timestamp;Lux");

  // begin clock
  clock.begin();
}

void loop() {

  if (digitalRead(BUTTON_PIN)) {
      myFile.close();
      Serial.println("Eject SD Card...");
      doing = 0;
  }

  if(doing == 1) {
    if ((millis() - lastTime) > delayTime) {
      sensorValue = photocell.getCurrentLux();
      dt = clock.getDateTime();
    
      sprintf(formatedString, "%04d-%02d-%02d %02d-%02d-%02d;%i.%i",
        dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second, (int)sensorValue, (int)((sensorValue - (int)sensorValue) * 10)
      );
    
      Serial.println(formatedString);
      myFile.println(formatedString);
  
      lastTime = millis();
    }
  }
}

/*
Initializing SD card...
Initialization done.
Open File succeeded.
2021-11-04 11-07-33;73.2
2021-11-04 11-07-35;64.7
2021-11-04 11-07-36;71.5
2021-11-04 11-07-38;3.5
2021-11-04 11-07-39;3.8
2021-11-04 11-07-41;58.9
2021-11-04 11-07-42;34.2
2021-11-04 11-07-44;71.5
*/
