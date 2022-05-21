#include <stdint-gcc.h>
#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

#define DHTMAXTIMINGS 85
#define DHTPIN 11

FILE *logFile;

void setup() {
    // setup wiring pi
    wiringPiSetupPhys();
}

void openLogFile() {
    // open file in a (append) mode
    // => append text to file; when not exists, create file
    logFile = fopen ("/media/sd0/rumpfhuber.log", "a");
}

void closeLogFile() {
    fclose(logFile);
}

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

void writeSensorDataToFile(unsigned int amount, unsigned int delayTime) {
    char formatedText[60], timeText[24];
    int worked = 0, i = 0;
    double temperature = 0, humidity = 0;

    while (i++ < amount) {
        // read sensor
        readDHT(&temperature, &humidity, &worked);

        // format time string
        time_t current_time = time(NULL);
        struct tm tm = *localtime(&current_time);
        strftime(timeText, sizeof timeText, "%Y-%d-%m %H:%M:%S:", &tm);

        // check if dht11 is working
        if (worked)
            sprintf(formatedText, "%s Temperature: %.2f Humidity: %.2f\n", timeText, temperature, humidity);
        else
            sprintf(formatedText, "%s Sensor not working...\n", timeText);

        // write string into file
        fputs(formatedText, logFile);

        // delay
        delay(delayTime);
    }
}

int main() {
    setup();
    openLogFile();

    // check if file stream is successfully open
    if (logFile != NULL) {
        // write 12x sensor data and wait 10 sec between
        writeSensorDataToFile(12, 10000);
        
        // close log file
        closeLogFile();
    }
}
