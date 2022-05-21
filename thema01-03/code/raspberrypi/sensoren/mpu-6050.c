#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdint-gcc.h>

#define MPU6050_ADDRESS (0x69)
#define MPU6050_REG_PWR_MGMT_1 (0x6b)
#define MPU6050_REG_DATA_START (0x3b)
#define MPU6050_A_SCALE (16384.0)
#define MPU6050_ANG_SCALE (131.0)

void setupMPU(int *fd) {
    wiringPiSetup();

    // Open an I2C connection
    *fd = wiringPiI2CSetup(MPU6050_ADDRESS);
    if (fd >= 0) {
        // Perform I2C work
        wiringPiI2CWriteReg8(*fd, MPU6050_REG_PWR_MGMT_1, 0);
    }
}

void readMPU(const int *fd, int *accelX, int *accelY, int *accelZ, int *temp, int *gyroX, int *gyroY, int *gyroZ) {
    uint8_t msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START);
    uint8_t lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 1);
    *accelX = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 2);
    lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 3);
    *accelY = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 4);
    lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 5);
    *accelZ = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 6);
    lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 7);
    *temp = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 8);
    lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 9);
    *gyroX = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 10);
    lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 11);
    *gyroY = msb << 8 | lsb;

    msb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 12);
    lsb = wiringPiI2CReadReg8(*fd, MPU6050_REG_DATA_START + 13);
    *gyroZ = msb << 8 | lsb;
}

int main() {
    int fd = 0, accelX = 0, accelY = 0, accelZ = 0, temp = 0, gyroX = 0, gyroY = 0, gyroZ = 0;

    setupMPU(&fd);

    printf("MPU-6050:\n");
    if (fd > 0) {
        readMPU(&fd, &accelX, &accelY, &accelZ, &temp, &gyroX, &gyroY, &gyroZ);
        printf("\taccelX=%f\n\taccelY=%f\n\taccelZ=%f\n\tgyroX=%f\n\tgyroY=%f\n\tgyroZ=%f\n",
               accelX / MPU6050_A_SCALE,
               accelY / MPU6050_A_SCALE,
               accelZ / MPU6050_A_SCALE,
               gyroX / MPU6050_ANG_SCALE,
               gyroY / MPU6050_ANG_SCALE,
               gyroZ / MPU6050_ANG_SCALE
       );
    } else
        printf("An error occurred!\n");
}