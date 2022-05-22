/*
  DS3231: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <DS3231.h>

#define LEN_STR 100

DS3231 clock;
RTCDateTime dt;

char timeStr[LEN_STR];

void setup()
{
  Serial.begin(112500);

  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();

  // Set date and time
  // clock.setDateTime(2020-09-29, 09-00-00-00);
}

void loop()
{
  dt = clock.getDateTime();

  sprintf(timeStr, „%04d-%02d-%02d %02d-%02d-%02d",
    dt.year, dt.month, dt.day, dt.hour, dt.minute, dt.second
  );

  Serial.println(timeStr);
  
  delay(1000);
}