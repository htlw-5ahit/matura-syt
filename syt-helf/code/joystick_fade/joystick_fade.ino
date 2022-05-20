// read joystick y axis
#define JOY_Y A2

// write green led
#define LED_GREEN 11

// define temporary variables
int yVal;
int ledVal;

void setup() {
  // sets the baud rate for the serial transmission
  Serial.begin(115200); 
  // set led pin to output
  pinMode(LED_GREEN, OUTPUT);
}

void loop() {
  // read analog
  yVal = analogRead(JOY_Y); 
  // device output through 4
  ledVal = yVal / 4;
  
  // write value to the led
  analogWrite(LED_GREEN, ledVal);

  // print values over serial connection
  Serial.print(yVal);
  Serial.print("\n");
  Serial.println(ledVal);
}
