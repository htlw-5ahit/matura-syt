// ----------------------------------------------------------------
// Copyright Stephen Stebbing 2014
// $Id: $
// ----------------------------------------------------------------
#include <ctype.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lcd_i2c.h"

// option flags
int8_t opt_cursor = 0; // 0 off, 1 on , 2 blink
int8_t opt_address = LCD_I2C_PCF8574_ADDRESS_DEFAULT;
int8_t opt_backlight = -1; // -1 do nothing, 0 turn off, 1 turn on
int8_t opt_clear;
int8_t opt_cols = 16;
int8_t opt_help;
int8_t opt_init;
int8_t opt_rows = 2;
int8_t opt_x = -1;
int8_t opt_y = -1;

// forward declarations
static void usage(char *argv0);

//! process command line options, set the opt_xxx variables
//! returns 0 on success, on failure it displays an error message and returns non-zero
static int process_options(int argc, char **argv);

//! display values of the options variables
static void print_options();

int main(int argc, char **argv) {

    if (process_options(argc, argv)) {
        usage(argv[0]);
        return 1;
    }
    if (opt_help || argc == 1) {
        usage(argv[0]);
        return 0;
    }

//    print_options();

    // init i2c
    lcd_i2c_t lcd = {0};
    if (lcd_i2c_setup(&lcd, opt_address) == -1) {
        fprintf(stderr, "Error intialising PCF8574 at address i2c 0x%02x: %s\n", opt_address, strerror(errno));
    }

    // init lcd
    if (opt_init)
        lcd_i2c_init(&lcd);

    // backlight
    if (opt_backlight == 0) {
        LCD_I2C_BACKLIGHT_OFF(&lcd);
    } else if (opt_backlight == 1) {
        LCD_I2C_BACKLIGHT_ON(&lcd);
    }

    // clear
    if (opt_clear)
        lcd_i2c_clear(&lcd);

    // geometry
    lcd.rows = opt_rows;
    lcd.cols = opt_cols;

    // x and y
    // note: if only one is specified, the other is set to 0
    if (opt_x != -1) {
        lcd.x = opt_x;
        if (opt_y == -1) {
            lcd.y = 0;
        }
    }
    if (opt_y != -1) {
        lcd.y = opt_y;
        if (opt_x == -1) {
            lcd.x = 0;
        }
    }
    if (opt_x != -1) {
        lcd_i2c_gotoxy(&lcd, lcd.x, lcd.y);
    }


    // cursor


    // display text
    for (int index = optind; index < argc; index++) {
        lcd_i2c_puts(&lcd, argv[index]);
        if (index != argc - 1)
            lcd_i2c_putc(&lcd, ' ');
    }

    return 0;
}

static void usage(char *argv0) {
    fprintf(stderr, "Usage:  %s [options] \"string to display\"\n", basename(argv0));
    char msg[] = "Display string on a HD44780 LCD which is connected by the i2c bus via a PCF8574 port expander\n\
Options:\n\
\t-a address\t- use this i2c (hexidecimal) address (default 0x27)\n\
\t-i\t\t- initialise (reset) the lcd\n\
\t-r rows\t\t- set the number of rows (default 2)\n\
\t-c cols\t\t- set the number of columns (default 16)\n\
\t-x col\t\t- move cursor to this column (default 0)\n\
\t-y row\t\t- move cursor to this row (default 0)\n\
\t-b [01]\t\t- turn backlight on (1) or off (0) (default off)\n\
\t-l\t\t- clear the screen\n\
\t-s [012]\t- turn cursor off (0), on (1), or blink (2) (default off)\n\
\t-h\t\t- display this help message\n\
\n";
    fprintf(stderr, msg);
}

//! convert passed string to int8_t using base 10, return <0 on error
//! string must contain a number >=0 and <=127
//! argchar is the argument character, base is the base to use for conversion
static int8_t str2int8(char argchar, char *str, int base, int8_t min, int8_t max) {
    char *endp;
    int8_t r = strtol(str, &endp, base);
    if (*endp != '\x0') {
        // conversion failed
        fprintf(stderr, "Option -%c requires a numeric argument\n", argchar);
        return -1;
    }
    if (r < min || r > max) {
        // out of range
        fprintf(stderr, "Option -%c argument is out of range (%i to %i)\n", argchar, min, max);
        return -2;
    }
    return r;
}

static int process_options(int argc, char **argv) {

    int option;

    opterr = 0; // no error message printing by getopt()
    while ((option = getopt(argc, argv, "ilha:r:c:x:y:b:s:")) != -1) {
        switch (option) {
            case 'h' :
                opt_help = 1;
                break;
            case 'l':
                opt_clear = 1;
                break;
            case 'i':
                opt_init = 1;
                break;
            case 'c':
                opt_cols = str2int8('c', optarg, 10, 0, 20);
                if (opt_cols < 0) return -1;
                break;
            case 'r':
                opt_rows = str2int8('r', optarg, 10, 0, 4);
                if (opt_rows < 0) return -1;
                break;
            case 'a':
                opt_address = str2int8('a', optarg, 16, 0, 127);
                if (opt_address < 0) return -1;
                break;
            case 'x':
                opt_x = str2int8('x', optarg, 10, 0, 19);
                if (opt_x < 0) return -1;
                break;
            case 'y':
                opt_y = str2int8('y', optarg, 10, 0, 3);
                if (opt_y < 0) return -1;
                break;
            case 'b':
                opt_backlight = str2int8('b', optarg, 10, 0, 2);
                if (opt_backlight < 0) return -1;
                break;
            case 's':
                opt_cursor = str2int8('c', optarg, 10, 0, 3);
                if (opt_cursor < 0) return -1;
                break;


            case '?':
                if (strchr("arcxybs", optopt))
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
            default:
                return -1;
        }
    }
    // success
    return 0;
}

static void print_options() {
    fprintf(stderr, "%15s: %i\n", "opt_cursor", opt_cursor);
    fprintf(stderr, "%15s: 0x%02x\n", "opt_address", opt_address);
    fprintf(stderr, "%15s: %i\n", "opt_backlight", opt_backlight);
    fprintf(stderr, "%15s: %i\n", "opt_clear", opt_clear);
    fprintf(stderr, "%15s: %i\n", "opt_cols", opt_cols);
    fprintf(stderr, "%15s: %i\n", "opt_help", opt_help);
    fprintf(stderr, "%15s: %i\n", "opt_init", opt_init);
    fprintf(stderr, "%15s: %i\n", "opt_rows", opt_rows);
    fprintf(stderr, "%15s: %i\n", "opt_x", opt_x);
    fprintf(stderr, "%15s: %i\n", "opt_y", opt_y);

}
