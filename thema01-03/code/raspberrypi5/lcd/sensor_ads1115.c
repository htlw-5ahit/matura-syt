#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <math.h>

#include "../libs/lcd_i2c.h"

// option flags
int8_t opt_address = 0x27;
int8_t opt_cols = 16;
int8_t opt_rows = 2;

#define LCD_I2C_BACKLIGHT_ON(lcd_p) lcd_i2c_backlight(lcd_p, 1)
#define LCD_I2C_BACKLIGHT_OFF(lcd_p) lcd_i2c_backlight(lcd_p, 0)

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
    double light = 0, temperature = 0;
    char formatedText[30];

    // setup wiring pi
    wiringPiSetupPhys();

    // init i2c
    lcd_i2c_t lcd = {0};
    if (lcd_i2c_setup(&lcd, opt_address) == -1)
        fprintf(stderr, "Error intialising PCF8574 at address i2c 0x%02x: %s\n", opt_address, strerror(errno));

    // init lcd
    lcd_i2c_init(&lcd);

    // geometry
    lcd.rows = opt_rows;
    lcd.cols = opt_cols;

    // turn backlight on
    LCD_I2C_BACKLIGHT_ON(&lcd);

    // read ads1115 for 20 seconds
    int i = 0;
    while (i++ < 20) {
        // read sensor
        readADS(&light, &temperature);

        // clear lcd
        lcd_i2c_clear(&lcd);

        // print line 1 of lcd
        lcd_i2c_gotoxy(&lcd, 0, 0);
        sprintf(formatedText, "Light: %.2f", light);
        lcd_i2c_puts(&lcd, formatedText);

        // print line 2 of lcd
        lcd_i2c_gotoxy(&lcd, 0, 1);
        sprintf(formatedText, "Temp: %.2f", temperature);
        lcd_i2c_puts(&lcd, formatedText);

        // wait a second
        delay(1000);
    }

    // write finish msg
    lcd_i2c_clear(&lcd);
    lcd_i2c_gotoxy(&lcd, 0, 0);
    lcd_i2c_puts(&lcd, "finished!");

    return 0;
}