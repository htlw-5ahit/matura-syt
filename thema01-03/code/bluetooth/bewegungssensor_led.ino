#define LED 6
#define SENSOR 8

int update_interval=500; // time interval in ms for updating panel indicators 
unsigned long last_time=0; // time of last update
char data_in; // data received from serial link
int red,green,blue; // RGB color

unsigned int force_led_on = 0;
unsigned int button_state = 0;

void setup() {

  // set pin modes for led and sensor
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);

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
Serial.print(F("add_text_box(0,1,6,L"));
delay(10);
Serial.print(F(",Lichtsteuerung,245,"));
delay(10);
Serial.println(F("240,245,)"));
delay(10);
Serial.print(F("add_switch(4,2,4,D,d"));
delay(10);
Serial.println(F(",0,0)"));
delay(10);
Serial.print(F("add_led(7,2,2,L,0,0,"));
delay(10);
Serial.println(F("0)"));
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

  if (Serial.available()){
    data_in=Serial.read();  //Get next character 

    if(data_in=='D'){ //Switch On
      led_switch(1);
      force_led_on = 1;
    }
    if(data_in=='d'){ // Switch Off 
      led_switch(0);
      force_led_on = 0;
    }

  }

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

    // check if led is set on by phone
    if (force_led_on == 0) {
      
      // read button state
      button_state = digitalRead(SENSOR);
  
      // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
      if (button_state == HIGH) {
        led_switch(1);
      } else {
        led_switch(0);
      }
      
    }

  }
}

void led_switch(int state) {
  // arduino led
  analogWrite(LED, state == 1 ? 250 : 0);

  // smartphone led
  red = state == 1 ? 255 : 0;
  green = state == 1 ? 255 : 0;
  blue = 0;
  Serial.print("*LR"+String(red)+"G"+String(green)+"B"+String(blue)+"");
  delay(10);
}
