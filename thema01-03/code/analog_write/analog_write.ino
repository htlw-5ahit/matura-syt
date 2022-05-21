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
