int analogPin = A3; // Pin, der gelesen werden soll: Pin A3
int val = 0; // Variable, die den gelesenen Wert speichert

void setup() {
  Serial.begin(115200); // Setup der seriellen Verbindung
}

void loop() {
  val = analogRead(analogPin); // Pin einlesen
  Serial.println(val); // Wert ausgeben
}
