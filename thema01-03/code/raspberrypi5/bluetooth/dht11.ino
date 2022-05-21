#include "DHT.h"

#define DHTPIN A0     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE); // create dht

float humidity, temperature = 0;

int update_interval=2000; // update every 1 sec
unsigned long last_time=0; // time of last update
char data_in; // data received from serial link
char text[10]; // String for text elements

void setup() {

  Serial.begin(115200); //Change baud rate as required!

///////////// Build panel in app

Serial.println(F("*.kwl"));
delay(10);
Serial.println(F("clear_panel()"));
delay(10);
Serial.print(F("set_grid_size(17,8)"));
delay(10);
Serial.println(F(""));
delay(10);
Serial.print(F("add_text_box(1,1,3,L"));
delay(10);
Serial.print(F(",DHT11,245,240,245,)"));
delay(10);
Serial.println(F(""));
delay(10);
Serial.print(F("add_text_box(6,3,3,L"));
delay(10);
Serial.print(F(",,245,240,245,A)"));
delay(10);
Serial.println(F(""));
delay(10);
Serial.print(F("add_text_box(6,5,3,L"));
delay(10);
Serial.print(F(",,245,240,245,B)"));
delay(10);
Serial.println(F(""));
delay(10);
Serial.print(F("add_text_box(1,3,3,L"));
delay(10);
Serial.print(F(",Temperatur:,245,240"));
delay(10);
Serial.println(F(",245,)"));
delay(10);
Serial.print(F("add_text_box(1,5,4,L"));
delay(10);
Serial.print(F(",Luftfeuchtigkeit:,2"));
delay(10);
Serial.println(F("45,240,245,)"));
delay(10);
Serial.print(F("set_panel_notes(-,,,"));
delay(10);
Serial.println(F(")"));
delay(10);
Serial.println(F("run()"));
delay(10);
Serial.println(F("*"));
delay(10);

}

void loop() {

  /////////////   Receive and Process Data

  if (Serial.available()){
    data_in=Serial.read();  //Get next character 

  }

  /////////////  Send Data to Android device

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

    // read sensor value
    read_sensor();

    // Update Text Element 
    sprintf(text, "*A%d.%02d", (int)temperature, (int)(temperature*100)%100);
    Serial.print(text);
    delay(10);

    // Update Text Element 
    sprintf(text, "*B%d.%02d", (int)humidity, (int)(humidity*100)%100);
    Serial.print(text);
    delay(10);

  }

}

void read_sensor() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  if (!(isnan(h) || isnan(t))) {
    humidity = h;
    temperature = t;
  }
  
}
