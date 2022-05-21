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
