#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/lcd_i2c.h"

#include <wiringPi.h>

#define LCD_I2C_BACKLIGHT_ON(lcd_p) lcd_i2c_backlight(lcd_p, 1)
#define LCD_I2C_BACKLIGHT_OFF(lcd_p) lcd_i2c_backlight(lcd_p, 0)

// option flags
int8_t opt_address = 0x27;
int8_t opt_cols = 16;
int8_t opt_rows = 2;

FILE *temperatureFile;
double temperature;
char formatedText[30];

int main() {
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

    // open file
    temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");

    // check if file could be opened
    if (temperatureFile != NULL) {
        // read temeperature
        fscanf (temperatureFile, "%lf", &temperature);

        // process temperature
        temperature /= 1000;

        // close file stream
        fclose (temperatureFile);
    }

    // format temp into string
    sprintf(formatedText, "Temp: %.2f °C", temperature);

    // set string on display
    lcd_i2c_puts(&lcd, formatedText);

    return 0;
}