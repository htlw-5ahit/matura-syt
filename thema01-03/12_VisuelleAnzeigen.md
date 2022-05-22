# Visuelle Anzeigen

- [LED](#led)
- [LCD](#lcd)

## LED

* LED … Light Emitting Diodes
* LEDs sind Leuchtdioden, die in vielen verschiedenen Farben erhältlich sind.
* Die LEDs können nicht direkt auf das Board angehängt werden, da sie eine Platine benötigt wird, um diese dort aufzustecken.

```c
// constants won't change. They're used here to set pin numbers:
const int led = 4;

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin as an output.
    pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(led, HIGH);    // turn the LED on (HIGH is the voltage level)
    delay(1000);                // wait for a second
    digitalWrite(led, LOW);     // turn the LED off by making the voltage LOW
    delay(1000);                // wait for a second
}
```

## LCD

| Befehl | Beschreibung |
|---|---|
| `lcd_i2c_t lcd = {0};` | Vorinitialisieren der Variable |
| `int8_t opt_address = 0x27;`<br>`lcd_i2c_setup(&lcd, opt_address);` | Initalisierung des I2C Busses und LCD Displays<br> Rückgabewert -1, beim Auftritt von Fehlern |
| `lcd_i2c_init(&lcd);` | Software-Reset, Bereinigung des Cursors, Cursor in Home-Position setzen |
| `lcd.rows = 2;`<br>`lcd.cols = 16;` | Sitzen der LCD Dimension |
| `lcd_i2c_backlight(&lcd, 1);` | LCD Hintergrundslicht einschalten |
| `char formatedText[30];`<br>`sprintf(formatedText, "Temp: %.2f °C", temperature);` | Ausgabe vorbereiten mit sprintf |
| `lcd_i2c_gotoxy(&lcd, 0, 0);` | Display-Cursor setzen |
| `lcd_i2c_puts(&lcd, formatedText);` | Schreiben des vorbereiteten Textes auf das LCD Display |

Beispiele:
- [Arduino: LCD Display mit DHT11](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/lcd_dht11)
- [Raspberry Pi: LCD Projekte](https://github.com/htlw-5ahit/matura-syt/tree/main/thema01-03/code/raspberrypi5/lcd)