#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

void readBH(double *lux) {
    int handle = wiringPiI2CSetup(0x5C);

    wiringPiI2CWrite(handle, 0x10);
    delay(1000);

    int word = wiringPiI2CReadReg16(handle, 0x00);

    *lux = ((word & 0xff00) >> 8) | ((word & 0x00ff) << 8);
}

int main() {
    double lux = 0;

    wiringPiSetupPhys();

    readBH(&lux);
    printf("BH1750:\nLight: %.2f lx", lux);
}