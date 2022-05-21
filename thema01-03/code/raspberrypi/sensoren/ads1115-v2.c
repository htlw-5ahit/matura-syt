// LDR (A1) und NTC (A2) am ADS1115 bzw PCF8591

#include <stdio.h>
#include <wiringPi.h>
#include <ads1115.h>
#include <math.h>

#define ADSPIN 120
#define SHH_V_IN 5.0
#define SSH_K 9.5
#define ADS_MAX (1 < 14)
const double SHH_A = 1.129148e-3;
const double SHH_B = 2.34125e-4;
const double SHH_C = 8.76741e-8;

double steinhartHart(double resistance) {
    double log_r  = log(resistance);
    double log_r3 = log_r * log_r * log_r;
    return 1.0 / (SHH_A + SHH_B * log_r + SHH_C * log_r3);
}

double getTempKelvin(double adcRaw, double _resistance) {
    double voltage = adcRaw / ADS_MAX * SHH_V_IN;
    double resistance = ((ADS_MAX * _resistance / adcRaw) - _resistance);
    // Account for dissipation factor K
    return steinhartHart(resistance) - voltage * voltage / (SSH_K * _resistance);
}

double getTempCelsius(double adcRaw, double _resistance) {
    return getTempKelvin(adcRaw, _resistance) - 273.15;
}

void readADS(double *light, double *temperature) {
    double sensorLight = analogRead(ADSPIN + 2), sensorTemperature = analogRead(ADSPIN + 1);
    *temperature = sensorTemperature / 1000;
    *light = sensorLight / 100;
}

void readSteinhartHart(double *temperature, double _resistance) {
    *temperature = getTempCelsius(analogRead(ADSPIN + 1), _resistance);
}

int main() {
    double light = 0.0, temperature = 0.0, temperature2 = 0.0;

    wiringPiSetupPhys();
    ads1115Setup(ADSPIN, 0x49);

    readADS(&light, &temperature);
    readSteinhartHart(&temperature2, 10000);

    printf("ADS1115:\n");
    printf("Temperature: %.2f °C\nLight: %.2f lx\n", temperature, light);
    printf("Steinharthart: %.2f °C\n", temperature2);
}