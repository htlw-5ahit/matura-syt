/**
   Example sketch for the SteinhartHart library.
*/

#include "SteinhartHartSimple.h"

// second resistor in voltage divider
#define OTHER_RESISTOR 10000

// analog pin connected to voltage divider
#define NTC_PIN A2

// SteinhartHart calculation instance
SteinhartHartSimple sh(OTHER_RESISTOR);

void setup(void)
{
  Serial.begin(115200);
}

void loop(void)
{
  // read raw value from NTC voltage divider
  int ntcVal = analogRead(NTC_PIN);

  Serial.print(" Raw ADC reading: ");
  Serial.print(ntcVal);

  // raw reading must not be zero (0 Ohm at NTC, nearly impossible)
  if (ntcVal != 0) {
    // calculate temperature in Celsius, Fahrenheit, Kelvin
    // for scheme 5V - NTC - Ax - fixed resistor - GND:
    //double tempCels = sh.getTempCelsius(ntcVal);
    // for scheme 5V - fixed resistor - Ax - NTC - GND (as on HTL-Wels board):
    double tempCels = sh.getTempCelsius(1023 - ntcVal);
    Serial.print(" ");
    Serial.print(" Temperature in C: ");
    Serial.print(tempCels);
  }
  Serial.println();

  delay(1000);
}

/*
  float calcTemp(int tempReading, float *tempC, float *tempF) {
  double tempK = log(10000.0 * ((1023.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK ))
                 tempK );
   tempC = tempK - 273.15;
   tempF = (*tempC * 9.0) / 5.0 + 32.0;
  }
*/
