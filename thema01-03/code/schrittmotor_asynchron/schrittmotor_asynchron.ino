/*
  Stepper Motor Control - in parallel to other logic

  This program drives a unipolar or bipolar stepper motor
  in parallel to other logic.
  The motor is attached to digital pins 2 - 5 of the Arduino.

  After a button press the motor should revolve one revolution
  in one direction.
  After another button press the motor should revolve one revolution
  in the other direction.

  Created 17 Apr. 2016

  by Ferdinand Hell
*/

#include <StepperAsync.h>

// digital output lines used for unipolar stepper motor 28BYJ-48 on ULN2003
#define IN1 4 // 13
#define IN2 6 // 12
#define IN3 5 // 11
#define IN4 3 // 10

// digital input pin for start/direction switch
#define SWTCH 2

// analog pin for light dependent resistor (LDR)
#define LDR A1

// analog read cycle time in millis
#define ANALOG_CYCLE 512

// time of next analog read
unsigned long nextAnalogRead = 0;

// change this to fit the number of steps per revolution for your motor
const int stepsPerRevolution = (360 / 5.625); // * 64;  // angle: 5.625; gear ratio: 64

// direction factor (1 forward, -1 backward)
int direction = 1;

// initialize the asynchronous stepper library on pins 2 through 5:
//the 28BYJ-48 on ULN2003 needs this order: IN4, IN2, IN1, IN3
StepperAsync myStepper(stepsPerRevolution, IN4, IN2, IN1, IN3);

void resetStepper() {
  digitalWrite(IN4, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN1, 0);
  digitalWrite(IN3, 0);
  delay(10);
}

void setup() {
  resetStepper();
  // set the speed to number of revolutions per minute
  // highest speed tested successfully: 420
  myStepper.setSpeed(120);
  
  // initialize the serial port @ 115200 baud:
  Serial.begin(115200);
  Serial.print("Steps per Revolution: ");
  Serial.println(stepsPerRevolution);
}

void loop() {
  // show parallel processing by reading analog input from A3
  unsigned long now = millis();
  if (now >= nextAnalogRead) {
    Serial.println(analogRead(LDR));
    nextAnalogRead = now + ANALOG_CYCLE;
  }

  // do the next step repeatedly until required steps are completed
  if (myStepper.stepsLeft()) {
    myStepper.doStep();
  } else {
    resetStepper();
  }
  
  // check switch repeatedly to start motor or to change
  // direction and restart motor
  if (digitalRead(SWTCH) && !myStepper.stepsLeft()) {
    direction = -direction;
    
    // step one revolution  in one direction:
    myStepper.step(direction * stepsPerRevolution * 32);
    
    if (direction > 0) {
      Serial.println("clockwise");
    } else {
      Serial.println("counterclockwise");
    }
  }
}
