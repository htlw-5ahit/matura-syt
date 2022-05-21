# Analog & Digital

## analogRead()

* Liest den Wert vom angegebenen analogen Pin ein. Die Arduino-Boards enthalten einen 10-Bit-Analog-zu-Digital-Konverter. Dieser mappt Eingangsspannungen zwischen 0 und 5 V auf Integer-Werte zwischen 0 und 1023.
* A0 bis A5 sind auf dem Board benannt, A6 bis A11 sind auf den Pins 4, 6, 8, 9, 10, und 12 verfügbar.

Syntax:

* `analogRead(pin)`
* `pin`: Der Pinname, von der gelesen werden soll 

Rückgabewert:

* Den analog gelesenen Wert auf dem Pin (int).
* Allerdings ist der Wert limitiert durch die Auflösung des Digital-Konverters (0-1023 für 10 Bit und 0-4095 für 12 Bit).

Code:

```c
int analogPin = A3; // Pin, der gelesen werden soll: Pin A3
int val = 0; // Variable, die den gelesenen Wert speichert

void setup() {
  Serial.begin(115200); // Setup der seriellen Verbindung
}

void loop() {
  val = analogRead(analogPin); // Pin einlesen
  Serial.println(val); // Wert ausgeben
}
```
[Arduino Projekt: analog_read](./code/analog_read/analog_read.ino)

## analogWrite()

* Schreibt einen Analogwert auf einen Pin.
* Kann z.B. benutzt werden, um eine LED mit verschiedener Helligkeit leuchten zu lassen oder einen Motor mit unterschiedlicher Geschwindigkeit laufen zu lassen.

Syntax: 

* `analogWrite(pin, value)`
* `pin`: Der Arduino-Pin auf den geschrieben werden soll. Erlaubte Datentypen: int.
* `value`: Die Zykluszeit. Werte zwischen 0 (immer aus) und 255 (immer an).
* Erlaubte Datentypen: int.

Code:

```c
int ledPin = 9; // LED auf Digitalpin 9 verbunden
int analogPin = 3; // Potentiometer auf Pin 3 verbunden
int val = 0; // Variable, um den gelesenen Wert zu speichern

void setup() {
  pinMode(ledPin, OUTPUT); // Setzt den Pin als output.
}

void loop() {
  val = analogRead(analogPin); // Liest den Wert vom Pin ein
  analogWrite(ledPin, val / 4); // analogRead: Werte von 0 bis 1023, analogWrite: Werte von 0 bis 255
}
```
[Arduino Projekt: analog_write](./code/analog_write/analog_write.ino)

## digitalRead()

* Liest einen Wert von einem vorgegebenen Digitalpin ein, entweder HIGH oder LOW.

Syntax: 

* `digitalRead(pin)`
* `pin`: Die Nummer des Arduino-Digitalpins, welcher gelesen werden soll.

Rückgabewert:

* `HIGH` oder `LOW`

```c
int ledPin = 13; // LED verbunden mit Digitalpin 13
int inPin = 7;   // Button verbunden mit Digitalpin 7
int val = 0;     // Variable, um den gelesenen Wert zu speichern

void setup() {
  pinMode(ledPin, OUTPUT); // Setzt den Digitalpin 13 als Outputpin
  pinMode(inPin, INPUT);   // Setzt den Digitalpin 7 als Intputpin
}

void loop() {
  val = digitalRead(inPin);  // Liest den Inputpin
  digitalWrite(ledPin, val); // Setzt die LED auf den Wert des Buttons
}
```
[Arduino Projekt: digital_read](./code/digital_read/digital_read.ino)

## digitalWrite()

* Schreibt einen HIGH- oder LOW-Wert auf einen Digitalpin.
* Wenn der Pin mit pinMode() als Outputpin gesetzt wird, wird die Spannung auf den Wert 5V (oder 3,3V) für HIGH gesetzt, 0V für LOW. Es wird empfohlen, den Pin mit pinMode() auf INPUT_PULLUP zu setzen, um den internen Pull-Up-Widerstand zu nutzen.
* Wenn du pinMode() nicht auf OUTPUT setzt, aber eine LED auf den Pin anschließt, kann die LED mit digitalWrite(HIGH) gedimmt erscheinen. Wenn pinMode() nicht explicit gesetzt wird, verwendet digitalWrite() den Pull-Up-Widerstand, der als eine Art großer spannungslimitierender Widerstand wirkt.

Syntax:

* `digitalWrite(pin, value)`
* `pin`: Die Arduino-Pinnummer.
* `value`: HIGH oder LOW.

Code:

```c
void setup() {
  pinMode(13, OUTPUT); // Setzt den Digitalpin 13 als Outputpin
}

void loop() {
  digitalWrite(13, HIGH); // Setzt den Digitalpin 13 auf HIGH = "Ein"
  delay(1000);            // Wartet eine Sekunde
  digitalWrite(13, LOW);  // Setzt den Digitalpin 13 auf LOW = "Aus"
  delay(1000);            // Wartet eine Sekunde
}
```
[Arduino Projekt: digital_write](./code/digital_write/digital_write.ino)