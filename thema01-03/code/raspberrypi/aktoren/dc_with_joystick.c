#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <ads1115.h>

#define DC_FORWARD_PIN 36
#define DC_BACKWARDS_PIN 40
#define DC_PWM_MOT_1 38
#define DC_PWM_MOT_2 35

#define ADS_PHYSICAL (0x49)
#define ADS_PIN 120

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void moveMotor(int power, int forward) {
    digitalWrite(DC_FORWARD_PIN, forward);
    digitalWrite(DC_BACKWARDS_PIN, !forward);
    softPwmWrite(DC_PWM_MOT_1, power);
}

void driveTestMotor() {
    for (int i = 0; i < 100; i++) {
        delay(25);
        moveMotor(i, HIGH);
    }
    delay(750);
    for (int i = 100; i > 0; i--) {
        delay(25);
        moveMotor(i, LOW);
    }
}

void driveByJoystick() {
    int i = 1000, joystickX, mappedValue;
    while (i-- > 0) {
        joystickX = analogRead(ADS_PIN + 1);

        mappedValue = map(joystickX, 40, 32767, 1, 100);

        printf("joystick: %d\tmapped value: %d\n", joystickX, mappedValue);

        if (mappedValue > 65) { // move forward
            mappedValue = map(mappedValue, 65, 100, 1, 100);
            moveMotor(mappedValue, HIGH);
            printf("move forward: %d\n", mappedValue);

        } else if (mappedValue < 55) { // move backwards
            mappedValue = map(mappedValue, 1, 55, 100, 1);
            moveMotor(mappedValue, LOW);
            printf("move backwards: %d\n", mappedValue);

        } else { // stand still
            moveMotor(0, HIGH);
        }

        delay(100);
    }
}

void closeMotor() {
    softPwmStop(DC_PWM_MOT_1);
    digitalWrite(DC_FORWARD_PIN, 0);
    digitalWrite(DC_BACKWARDS_PIN, 0);
}

int main() {
    wiringPiSetupPhys();
    ads1115Setup(ADS_PIN, ADS_PHYSICAL);
    softPwmCreate(DC_PWM_MOT_1, 0, 100);

    pinMode(DC_FORWARD_PIN, OUTPUT);
    pinMode(DC_BACKWARDS_PIN, OUTPUT);

    driveByJoystick();

    closeMotor();
    return 0;
}