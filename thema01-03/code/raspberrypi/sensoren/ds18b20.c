#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

#define DSB_SIZE 1
#define DSB_NUMELEM 74

// setup the raspberry pi with following commands:
// - sudo modprobe w1-gpio
// - sudo modprobe w1-therm

FILE *fp = NULL;

void openFile() {
    char path[50];
    sprintf(path,"/sys/bus/w1/devices/%s/w1_slave", device);
    fp = fopen(path, "r");
}

void closeFile () {
    fclose(fp);
}

void readDSB(char device[20], double *temperature) {
    char buff[100];
    char temp_raw[6];
    int counter = 0;

    while (*temperature == 0 && counter < 20) {
        // read file
        if (DSB_SIZE * DSB_NUMELEM != fread(buff, DSB_SIZE, DSB_NUMELEM, fp)) {
            printf("\n fread() failed\n");
            return;
        }

        // write raw data into buffer
        temp_raw[0] = buff[69];
        temp_raw[1] = buff[70];
        temp_raw[2] = buff[71];
        temp_raw[3] = buff[72];
        temp_raw[4] = buff[73];
        temp_raw[5] = buff[74];

        *temperature = strtod(temp_raw, NULL) / 1000;
        counter++;
    }

    // close file
    fclose(fp);
}

int main() {
    double temperature = 0.0;

    wiringPiSetupPhys();
    setupDSB();

    openFile();

    if (fp == NULL) { // check if file could be opened
        printf("\n fopen Error!!!\n\n");
    } else {
        readDSB("28-01144feb1aaa", &temperature);

        printf("DS18B20:\nTemperature = %.2f °C", temperature);

        closeFile();
    }
}