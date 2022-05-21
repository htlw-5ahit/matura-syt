#include "DHT.h"
#include <Servo.h>

// Define Servo motor
Servo servo1;

// Digital pin connected to the DHT sensor
#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// variables for delay
unsigned long previousMillis = 0;
const long interval = 1100;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // attach pin to servo
  servo1.attach(9);
}

void loop() {
  int temperature = dht.readTemperature();

  // constain tmeperature between 20 to 30
  int constainTemperature = constrain(temperature, 20, 30);

  // map value from 20-30 to 20-160
  int mappedValue = map(constainTemperature, 20, 30, 20, 160);

  // print to serial console  
  Serial.print(temperature);
  Serial.print(" --> ");
  Serial.println(mappedValue);

  // write mapped value to servo motor
  servo1.write(mappedValue);

  // delay 0.3 sec
  delay(300);
}
