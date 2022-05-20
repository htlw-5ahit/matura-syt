void setup() {
  pinMode(13, OUTPUT); // Setzt den Digitalpin 13 als Outputpin
}

void loop() {
  digitalWrite(13, HIGH); // Setzt den Digitalpin 13 auf HIGH = "Ein"
  delay(1000);            // Wartet eine Sekunde
  digitalWrite(13, LOW);  // Setzt den Digitalpin 13 auf LOW = "Aus"
  delay(1000);            // Wartet eine Sekunde
}
