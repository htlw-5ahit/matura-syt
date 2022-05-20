#include <NewPing.h>

// Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN  7

// Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN     7

// Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_DISTANCE 300

// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  // Open serial monitor at 115200 baud to see ping results.
  Serial.begin(115200);
}

void loop() {
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  delay(50);
  Serial.print("Ping: ");
  // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
}
