#include <NewPing.h>

// define sensor pins
const int DISTANCE_SENSOR = 7;
const int MOTION_SENSOR = 8;

// set maximal distance for distance sensor library
const int MOTION_MAX_DISTANCE = 300;

// define variable for previous time millis and the interval
unsigned long previousMillis = 0;
const long interval = 5000; // 5 sec

// NewPing setup of pins and maximum distance.
NewPing sonar(DISTANCE_SENSOR, DISTANCE_SENSOR, MOTION_MAX_DISTANCE);

void setup() {
  // initialise pin
  pinMode(DISTANCE_SENSOR, INPUT);
  pinMode(MOTION_SENSOR, INPUT);

  // sets the baud rate for the serial transmission
  Serial.begin(115200);
}

void loop() {
  // set current millis
  triggerSensor();
}

void triggerSensor() {
  unsigned long currentMillis = millis();

  // check if the interval time is over
  if (currentMillis - previousMillis >= interval) {
    // check if the motion sensor is triggered
    if (digitalRead(MOTION_SENSOR) == HIGH) {
      
      // print distance and text to serial interface
      Serial.print("Abstand: ");
      Serial.print(sonar.ping_cm());
      Serial.println(" cm");
      
      // set current millis to pervious millis
      previousMillis = currentMillis;
    }
  }
}
