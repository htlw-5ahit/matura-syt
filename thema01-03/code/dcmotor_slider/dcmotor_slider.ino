#define SLIDER A0
#define MOTOR_DIR 04
#define MOTOR_PWM 03

float sliderValue = 0;
float motorSpeed = 0;
boolean directionForward = true;

void setup() {
  pinMode(SLIDER, INPUT);
  pinMode(MOTOR_DIR, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);
}

void loop() {
  sliderValue = analogRead(SLIDER);

  // stop wertebereich
  // 500-520 bleibt motor stehen, sonst drehen
  if (sliderValue < 500 || sliderValue > 520) {

    // setze richtung
    // true --> vorwärts
    // false --> rückwärts
    directionForward = (sliderValue < 512);

    if (directionForward) {
      motorSpeed = (500 - sliderValue) / 2;
    } else {
      motorSpeed = (sliderValue - 520) / 2;
    }

    digitalWrite(MOTOR_DIR, directionForward);
    analogWrite(MOTOR_PWM, motorSpeed);

  }
}
