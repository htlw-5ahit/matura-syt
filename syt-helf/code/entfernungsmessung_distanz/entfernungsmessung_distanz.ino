// include h files from libraries
#include <NewPing.h>
#include <Encoder.h>

// distance sensor port defintion
#define TRIGGER_PIN  7
#define ECHO_PIN     7

// rotary encoder delay
#define CLK     2      // Definition der Pins: CLK an D2, DT an A2.
#define DT      A2
#define BUTTON  A1

// 
long oldPosition = -999;  // fiktive "alte" Position um die Logik in Gang zu setzen (!= 0)
long counter = oldPosition;

// create objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN);
Encoder meinEncoder(DT, CLK);

// variables for delay
unsigned long previousMillis = 0;
const long interval = 750;

boolean buttonPressed = false;

void setup() {
  // Open serial monitor at 115200 baud to see ping results.
  Serial.begin(115200);
  pinMode(BUTTON, INPUT);
}

void loop() {
  triggerRotaryEncoder();

  if (digitalRead(BUTTON) == HIGH) {
      buttonPressed = !buttonPressed;
  }
  
  if (buttonPressed == true) {
    triggerDistanceSensor();
  }
  
}

void triggerRotaryEncoder() {
  // Die "neue" Position des Encoders wird eingelesen und übernommen.
  long newPosition = meinEncoder.read();

  // Ist die neue Position ungleich der alten (-999) und ein Vielfaches von 4?
  if (newPosition != oldPosition && newPosition % 4 == 0) {
    oldPosition = newPosition;
    counter = newPosition / 4;
    // aktuelle Position im seriellen Monitor ausgeben.
    Serial.println(counter);
  }
}

void triggerDistanceSensor() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
     Serial.print("Ping: ");
    // Send ping, get distance in cm and print result
    //(0 = outside set distance range)
    Serial.print(sonar.ping_cm(counter));
    Serial.println("cm");
  }
}
