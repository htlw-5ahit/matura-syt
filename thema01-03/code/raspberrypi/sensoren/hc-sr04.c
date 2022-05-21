#include <stdio.h>
#include <wiringPi.h>

#define HCPIN 15

void readHC(int *distance) {
    int counter = 0;
    long startTime, travelTime;

    wiringPiSetupPhys();
    pinMode(HCPIN, OUTPUT);
    digitalWrite(HCPIN, LOW);
    delay(30);

    while (*distance == 0 && counter < 5) {
        pinMode(HCPIN, OUTPUT);

        // send trigger pulse
        digitalWrite(HCPIN, HIGH);
        delay(20);
        digitalWrite(HCPIN, LOW);

        pinMode(HCPIN, INPUT);

        // wait for echo (echo = low)
        while (digitalRead(HCPIN) == LOW);

        // wait for echo end long
        startTime = micros();
        while (digitalRead(HCPIN) == HIGH);
        travelTime = micros() - startTime;

        // read distance in cm and write into variable
        *distance = travelTime / 58;

        delay(1000);
        counter++;
    }
}

int main() {
    int distance = 0;

    readHC(&distance);

    printf("HC-SR04:\nDistance: %d cm", distance);
}