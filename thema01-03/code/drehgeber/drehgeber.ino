// Quelle: https://funduino.de/nr-32-der-rotary-encoder-ky-040
// Taster aus Code entfernt
// für Elegoo-Drehgeber: Modulo 4 und Division durch 4 ergänzt

#include <Encoder.h>    // Verwendung der <Encoder.h> Bibliothek 

#define CLK 2      // Definition der Pins: CLK an D2, DT an A2.
#define  DT A2
//#define SW A1

// fiktive "alte" Position um die Logik in Gang zu setzen (!= 0)
long altePosition = -999; 
long zaehler = altePosition;

// neues Encoder Objekt erstellt (Pins: DT auf A2, CLK auf 2)
Encoder meinEncoder(DT, CLK);


void setup()
{
  Serial.begin(115200);
  //  pinMode(SW, INPUT);
}


void loop()
{
  // Die "neue" Position des Encoders wird eingelesen und übernommen.
  long neuePosition = meinEncoder.read();

  // Ist die neue Position ungleich der alten (-999) und ein Vielfaches von 4?
  if (neuePosition != altePosition && neuePosition % 4 == 0) {
    altePosition = neuePosition;
    zaehler = neuePosition / 4;
    Serial.println(zaehler);       // alt. Position im ser. Monitor ausgeben.
  }
}
