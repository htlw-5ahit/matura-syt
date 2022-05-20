// constants won't change. They're used here to set pin numbers:
const int buttonPin = 8;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);
}

void loop() {
  delay(50);
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.println("Sensor ausgelöst.");
  } else {
    Serial.println("Sensor kann keine Bewegung feststellen.");
  }
}
