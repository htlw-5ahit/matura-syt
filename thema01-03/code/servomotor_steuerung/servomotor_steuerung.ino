#include <Servo.h>

#define SLIDER A0
#define SERVO 9

Servo servo1;

float sliderValue = 0;

void setup() {
  pinMode(SLIDER, INPUT);
  servo1.attach(SERVO);
}

void loop() {
  sliderValue = analogRead(SLIDER);
  //slider Value max = 1023 -> /6 max 170,5
  servo1.write(sliderValue / 6);
  delay(1000);
}
