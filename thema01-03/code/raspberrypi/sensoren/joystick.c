#include <wiringPi.h>
#include <stdio.h>
#include <ads1115.h>

#define ADS_PHYSICAL (0x49)
#define ADS_PIN 120


int main() {
    wiringPiSetupPhys();
    ads1115Setup(ADS_PIN, ADS_PHYSICAL);
    int x, y, i = 25;

    while (i-- > 0) {
        x = analogRead(ADS_PIN + 1);
        y = analogRead(ADS_PIN + 2);

        printf("%d: x: %d, y; %d\n", i, x, y);
        delay(100);
    }

    return 1;
}