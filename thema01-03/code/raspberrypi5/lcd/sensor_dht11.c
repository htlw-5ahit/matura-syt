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

#define DHTMAXTIMINGS 85
#define DHTPIN 11

void readDHT(double *temperature, double *humidity, int *worked) {
    int dht11_dat[5] = {0, 0, 0, 0, 0};
    int dhtCounter = 0;

    while (*humidity == 0 && *temperature == 0 && dhtCounter < 5) {
        // predefine values
        uint8_t laststate = HIGH, counter, j = 0, i;
        dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

        // set pin mode
        pinMode(DHTPIN, OUTPUT);
        digitalWrite(DHTPIN, LOW);
        delay(18);
        digitalWrite(DHTPIN, HIGH);
        delayMicroseconds(40);
        pinMode(DHTPIN, INPUT);

        // digital read
        for (i = 0; i < DHTMAXTIMINGS; i++) {
            counter = 0;
            while (digitalRead(DHTPIN) == laststate) {
                counter++;
                delayMicroseconds(1);
                if (counter == 255) { break; }
            }
            laststate = digitalRead(DHTPIN);

            if (counter == 255) break;

            if ((i >= 4) && (i % 2 == 0)) {
                dht11_dat[j / 8] <<= 1;
                if (counter > 50)
                    dht11_dat[j / 8] |= 1;
                j++;
            }
        }

        // calculate values
        if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF))) {
            *temperature = dht11_dat[0] + (dht11_dat[1] / 10);
            *humidity = dht11_dat[2] + (dht11_dat[3] / 10);
            *worked = HIGH;
        } else
            *worked = LOW;

        dhtCounter++;
    }
}

int main() {
    char formatedText[30];
    int worked = 0;
    double temperature = 0, humidity = 0;

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
        readDHT(&temperature, &humidity, &worked);

        lcd_i2c_clear(&lcd);

        if (worked == 1) {
            lcd_i2c_gotoxy(&lcd, 0, 0);
            sprintf(formatedText, "Temp: %.2f", temperature);
            lcd_i2c_puts(&lcd, formatedText);

            lcd_i2c_gotoxy(&lcd, 0, 1);
            sprintf(formatedText, "Humi: %.2f", humidity);
            lcd_i2c_puts(&lcd, formatedText);
        } else
            lcd_i2c_puts(&lcd, "not working...");

        // wait a second
        delay(1000);
    }

    // write finish msg
    lcd_i2c_clear(&lcd);
    lcd_i2c_puts(&lcd, "finished!");

    return 0;
}