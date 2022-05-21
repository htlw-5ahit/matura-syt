#include <Stepper.h>
#include <Encoder.h>

#define CLK 2
#define DREHGEBER A2

// change this to fit the number of steps per revolution
const int stepsPerRevolution = 20;

// fiktive "alte" Position um die Logik in Gang zu setzen (!= 0)
long altePosition = -999;
long zaehler = altePosition;

Encoder meinEncoder(DREHGEBER, CLK);
Stepper myStepper1(stepsPerRevolution, 3, 6, 5, 4);


void setup()
{
  Serial.begin(115200);
  myStepper1.setSpeed(10);
}

void loop()
{
  long neuePosition = meinEncoder.read();

  // Ist die neue Position ungleich der alten (-999) und ein Vielfaches von 4?
  if (neuePosition != altePosition && neuePosition % 4 == 0) {

    // setze alte auf neue Position
    altePosition = neuePosition;

    // Zaehler wird neue Position
    zaehler = neuePosition;

    // um mehr Resultat am Schrittmotor zu sehen,
    // mulitplizieren wir den Zähler mit 100
    zaehler = zaehler * 100;

    // aktuelle Position im seriellen Monitor ausgeben.
    Serial.println(zaehler);
  }

  // Schritte gehen
  myStepper1.step(zaehler);
  
  delay(10);
}
