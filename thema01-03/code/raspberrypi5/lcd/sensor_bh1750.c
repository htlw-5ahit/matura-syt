#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/lcd_i2c.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

#define LCD_I2C_BACKLIGHT_ON(lcd_p) lcd_i2c_backlight(lcd_p, 1)
#define LCD_I2C_BACKLIGHT_OFF(lcd_p) lcd_i2c_backlight(lcd_p, 0)

// option flags
int8_t opt_address = 0x27;
int8_t opt_cols = 16;
int8_t opt_rows = 2;

void readBH(double *lux) {
    int handle = wiringPiI2CSetup(0x5C);

    wiringPiI2CWrite(handle, 0x10);
    delay(1000);

    int word = wiringPiI2CReadReg16(handle, 0x00);

    *lux = ((word & 0xff00) >> 8) | ((word & 0x00ff) << 8);
}

int main() {
    double lux = 0;
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

    // read bh1750 for 20 seconds
    int i = 0;
    while (i++ < 20) {
        // read sensor
        readBH(&lux);

        // format output
        sprintf(formatedText, "BH1750: %.2f lx", lux);

        // clear text and write to lcd
        lcd_i2c_clear(&lcd);
        lcd_i2c_puts(&lcd, formatedText);

        // wait a second
        delay(1000);
    }

    // write finish msg
    lcd_i2c_clear(&lcd);
    lcd_i2c_puts(&lcd, "finished!");

    return 0;
}