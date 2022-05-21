#include <stdio.h>
#include <wiringPi.h>

#define STEPPER_PIN_1 38 //32
#define STEPPER_PIN_2 35 //33
#define STEPPER_PIN_3 40 //16
#define STEPPER_PIN_4 36 //18
#define STEPPER_SPEED 1

const int stepperPins[4] = {STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4};

const int stepperSteps[8][4] = {
        {HIGH, LOW, LOW, LOW},
        {HIGH, HIGH, LOW, LOW},
        {LOW, HIGH, LOW, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, LOW, HIGH, LOW},
        {LOW, LOW, HIGH, HIGH},
        {LOW, LOW, LOW, HIGH},
        {HIGH, LOW, LOW, HIGH},
};

void setupStepper() {
    //set Pins to OUTPUT
    for (int i = 0; i < 4; i++) {
        pinMode(stepperPins[i], OUTPUT);
        digitalWrite(stepperPins[i], 0);
    }
}


void doStepper(int amount) {
    for (int i = 0; i <= amount; i++)
        for (int step = 0; step < 8; step++)
            for (int pin = 0; pin < 4; pin++) {
                digitalWrite(stepperPins[pin], stepperSteps[step][pin]);
                printf("Stepper moving! (%d)\n", i);
                delay(STEPPER_SPEED);
            }
}

int main() {
    wiringPiSetupPhys();
    setupStepper();

    doStepper(512);
    return 0;
}