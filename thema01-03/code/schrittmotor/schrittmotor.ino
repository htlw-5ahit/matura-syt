#include <Stepper.h>

#define SLIDER A0
#define BUTTON_FORW 02
#define BUTTON_BACK 12

// change this to fit the number of steps per revolution for your motor
const int stepsPerRevolution = 20;

// initialize the stepper library on pins 8 through 11:
Stepper stepper(stepsPerRevolution, 3, 6, 5, 4); //P1, P2, P3, P4

float sliderValue = 0;
float stepValue = 0;
boolean directionForward = true;

void setup()
{
  pinMode(SLIDER, INPUT);
  pinMode(BUTTON_FORW, INPUT);
  pinMode(BUTTON_BACK, INPUT);
  stepper.setSpeed(5.0);
}

void loop()
{
  // read slider value
  sliderValue = analogRead(SLIDER);

  // button forwrts
  if (digitalRead(BUTTON_FORW) == HIGH) {
    directionForward = true;
  }

  // button rückwärts
  if (digitalRead(BUTTON_BACK) == HIGH) {
    directionForward = false;
  }

  // set slider speed mit slider wert
  stepper.setSpeed(sliderValue / 2);

  // steps vorwärts oder rückwärts
  if (directionForward) {
    stepValue = stepsPerRevolution;
  } else {
    stepValue = -stepsPerRevolution;
  }

  stepper.step(stepValue);
}
