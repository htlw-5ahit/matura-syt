#define SLIDER A0
#define BUTTON 2
#define MOTOR_DIR 04
#define MOTOR_PWM 03

Servo servo1;

float sliderValue = 0;
boolean directionForward = true;

void setup() {
  pinMode(SLIDER, INPUT);
  pinMode(BUTTON, INPUT);

  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
}

void loop() {
  sliderValue = analogRead(SLIDER);

  // forwaerts / rueckwaerts schalten des motors via button
  if (digitalRead(BUTTON) == HIGH) {
    directionForward = !directionForward;
    delay(100);
  }

  analogWrite(MOTOR_PWM, sliderValue / 4);
  digitalWrite(MOTOR_DIR, directionForward);
}
