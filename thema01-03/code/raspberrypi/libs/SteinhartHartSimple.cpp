/**
 * SteinhartHart.cpp - Library for interacting with NTC thermistors
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "SteinhartHartSimple.h"
#include <math.h>	

	
/**
 * Returns the temperature in kelvin for the given resistance value
 * using the Steinhart-Hart polynom.
 */
double SteinhartHartSimple::steinhartHart(double resistance)
{
	double log_r  = log(resistance);
	double log_r3 = log_r * log_r * log_r;

	return 1.0 / (_a + _b * log_r + _c * log_r3);
}


double SteinhartHartSimple::getTempKelvin(int adcRaw) 
{
	double voltage = adcRaw / 1023.0 * V_IN;
	double resistance = ((1023.0 * _resistance / adcRaw) - _resistance);
	
	// Account for dissipation factor K
	return steinhartHart(resistance) - voltage * voltage / (K * _resistance);
}


double SteinhartHartSimple::getTempCelsius(int adcRaw) 
{
	return getTempKelvin(adcRaw) - 273.15;
}


double SteinhartHartSimple::getTempFahrenheit(int adcRaw)
{
	return getTempCelsius(adcRaw) * 9/5 + 32;
}

