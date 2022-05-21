#include <stdio.h>
#include <wiringPi.h>

#define SERVO_NR 7

/*
pi@raspi-it-08:~ $ sudo /home/pi/PiBits/ServoBlaster/user/servod --pcm

Board model:                    2B
GPIO configuration:            P1 (40 pins)
Using hardware:                PCM
Using DMA channel:              14
Idle timeout:             Disabled
Number of servos:                8
Servo cycle time:            20000us
Pulse increment step size:      10us
Minimum width value:            50 (500us)
Maximum width value:           250 (2500us)
Output levels:              Normal

Using P1 pins:               7,11,12,13,15,16,18,22

Servo mapping:
     0 on P1-7           GPIO-4
     1 on P1-11          GPIO-17
     2 on P1-12          GPIO-18
     3 on P1-13          GPIO-27
     4 on P1-15          GPIO-22
     5 on P1-16          GPIO-23
     6 on P1-18          GPIO-24
     7 on P1-22          GPIO-25
*/

FILE *fp = NULL;

void openFile() {
    fp = fopen("/dev/servoblaster", "w");
}

void closeFile () {
    fclose(fp);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void driveServo(int degree) {
    if (degree < 0)
        degree = 0;
    else if (degree > 180)
        degree = 180;

    // map degree to microseconds
    degree = map(degree, 0, 180, 50, 250);

    //creat command that system should execute
    char cmd[10];
    sprintf(cmd, "%d=%d\n", SERVO_NR, degree);
    printf(cmd);
    fputs(cmd, fp);
    fflush(fp);
}

void test(int phases) {
    int count = 250 / phases;
    for (int i = 1; i <= phases; ++i) {
        driveServo(count);
        count = count + 250 / phases;
        delay(2000);
    }
}

int main() {
    wiringPiSetupPhys();
    openFile();

    if (fp != NULL) {
        test(20);

        closeFile();
    } else {
        printf("Cannot open device file! Please contact your raspi admin! :)");
    }


}