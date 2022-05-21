/**
 * SteinhartHart.h - Library for interacting with NTC thermistors
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

#define V_IN 5.0	// Input voltage
#define K 9.5		// Dissipation factor (mW/°C)


class SteinhartHartSimple {
	private:
		double steinhartHart(double);
		
		// Value of the resistor put in serial
		double _resistance;	

		// Manufacturing constants
		double _a;
		double _b;
		double _c;
		
	public:	
		/**
		 * The reading pin has to be specified.
		 * If no other parameters are given default values will be used.
		 * These values are for a NTC 10k thermistor with a 10k resistor
		 * put in parallel.
		 */
		SteinhartHartSimple(double resistance, double a, double b, double c) {
			_resistance = resistance; 
			_a = a;
			_b = b;
			_c = c;
		};

		SteinhartHartSimple(double resistance) { 
			_resistance = resistance;
			_a = 1.129148e-3;
			_b = 2.34125e-4;
			_c = 8.76741e-8;
		};
		
		double getTempKelvin(int adcRaw);
		double getTempCelsius(int adcRaw);
		double getTempFahrenheit(int adcRaw);
};
