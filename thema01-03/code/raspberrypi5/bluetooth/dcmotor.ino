//  Auto Generated Code for Arduino IDE
//  Created using keuwlsofts Bluetooth Electronics App
//  www.keuwl.com

//  Steps: 
//  1) Upload code and power your Arduino project 
//  2) Run Bluetooth Electronics App and connect to your device 
//  3) Press the reset button on your Arduino 

//  This auto generated code template is only a suggestion to get you started.
//  It is incomplete and will need modification specific to your project.

#define PWM_MOT_1 3
#define PWM_MOT_2 5
#define PWM_FWD 6
#define PWM_BWD 4

int update_interval=100; // time interval in ms for updating panel indicators 
unsigned long last_time=0; // time of last update
char data_in; // data received from serial link
int slider_value; // Received Slider Values

void setup() {

  Serial.begin(115200);
  
  pinMode(PWM_MOT_1, OUTPUT);
  pinMode(PWM_MOT_2, OUTPUT);
  pinMode(PWM_FWD, OUTPUT);
  pinMode(PWM_BWD, OUTPUT);

///////////// Build panel in app

Serial.println(F("*.kwl"));
delay(10);
Serial.println(F("clear_panel()"));
delay(10);
Serial.print(F("set_grid_size(17,8)"));
delay(10);
Serial.println(F(""));
delay(10);
Serial.print(F("add_text_box(1,1,4,L"));
delay(10);
Serial.print(F(",Richtung,245,240,24"));
delay(10);
Serial.println(F("5,)"));
delay(10);
Serial.print(F("add_text_box(6,1,4,L"));
delay(10);
Serial.print(F(",Geschwindigkeit,245"));
delay(10);
Serial.println(F(",240,245,)"));
delay(10);
Serial.print(F("add_switch(1,2,3,C,c"));
delay(10);
Serial.println(F(",0,0)"));
delay(10);
Serial.print(F("add_slider(6,2,7,0,2"));
delay(10);
Serial.println(F("55,0,A,A,0)"));
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

    if(data_in=='C'){ //Switch On
      //<--- Insert code for switch on here 
      Serial.println("direction forward");
      digitalWrite(PWM_FWD, HIGH);
      digitalWrite(PWM_BWD, LOW);
    }
    if(data_in=='c'){ // Switch Off 
      //<--- Insert code for when switch turned off here
      Serial.println("direction backwards");
      digitalWrite(PWM_FWD, HIGH);
      digitalWrite(PWM_BWD, LOW);
    }

    if(data_in=='A'){ //  Slider
      slider_value=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
      Serial.println("move");
      Serial.println(slider_value);
      if (slider_value != 0) {
        analogWrite(PWM_MOT_1, slider_value);
      }
    }
  }
  /////////////  Send Data to Android device

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

  }

}
