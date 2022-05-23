//  Auto Generated Code for Arduino IDE
//  Created using keuwlsofts Bluetooth Electronics App
//  www.keuwl.com

//  Steps: 
//  1) Upload code and power your Arduino project 
//  2) Run Bluetooth Electronics App and connect to your device 
//  3) Press the reset button on your Arduino 

//  This auto generated code template is only a suggestion to get you started.
//  It is incomplete and will need modification specific to your project.

int update_interval=100; // time interval in ms for updating panel indicators 
unsigned long last_time=0; // time of last update
char data_in; // data received from serial link
int slider_value; // Received Slider Values
String text; // String for text elements

#define LED_R 3
#define LED_G 5
#define LED_B 6

void setup() {

  Serial.begin(115200); //Change baud rate as required!

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  

///////////// Build panel in app

Serial.println(F("*.kwl"));
delay(2);
Serial.println(F("clear_panel()"));
delay(2);
Serial.print(F("set_grid_size(17,8)"));
delay(2);
Serial.println(F(""));
delay(2);
Serial.print(F("add_text(3,2,xlarge,"));
delay(2);
Serial.print(F("R,Red LED,250,115,11"));
delay(2);
Serial.println(F("0,0)"));
delay(2);
Serial.print(F("add_text(3,3,xlarge,"));
delay(2);
Serial.print(F("R,Green LED,110,245,"));
delay(2);
Serial.println(F("110,0)"));
delay(2);
Serial.print(F("add_text(3,4,xlarge,"));
delay(2);
Serial.print(F("R,Blue LED,90,110,24"));
delay(2);
Serial.println(F("5,0)"));
delay(2);
Serial.print(F("add_text(1,0,xlarge,"));
delay(2);
Serial.print(F("L,Led Brightness Con"));
delay(2);
Serial.print(F("troller,250,245,240,"));
delay(2);
Serial.println(F("0)"));
delay(2);
Serial.print(F("add_slider(4,3,1,0,2"));
delay(2);
Serial.println(F("55,0,G,A,0)"));
delay(2);
Serial.print(F("add_slider(4,4,1,0,2"));
delay(2);
Serial.println(F("55,0,B,A,0)"));
delay(2);
Serial.print(F("add_slider(4,2,1,0,2"));
delay(2);
Serial.println(F("55,0,R,A,0)"));
delay(2);
Serial.print(F("set_panel_notes(LED "));
delay(2);
Serial.print(F("Brightness,Control t"));
delay(2);
Serial.print(F("he Red, Green and Bl"));
delay(2);
Serial.print(F("ue Brightness,with S"));
delay(2);
Serial.print(F("liders that adjust t"));
delay(2);
Serial.print(F("he PWM.,Requires: Ar"));
delay(2);
Serial.print(F("udino, HC-06, LEDs, "));
delay(2);
Serial.println(F("Resistors)"));
delay(2);
Serial.println(F("run()"));
delay(2);
Serial.println(F("*"));
delay(2);

}

void loop() {

  /////////////   Receive and Process Data

  if (Serial.available()){
    data_in=Serial.read();  //Get next character 

    if(data_in=='G'){ //  Slider
      slider_value=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
      analogWrite(LED_G, slider_value);
    }

    if(data_in=='B'){ //  Slider
      slider_value=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
      analogWrite(LED_B, slider_value);
    }

    if(data_in=='R'){ //  Slider
      slider_value=Serial.parseInt();
      //<--- Perhaps do something with slider_value here
      analogWrite(LED_R, slider_value);
    }

  }

  /////////////  Send Data to Android device

  unsigned long t=millis();
  if ((t-last_time)>update_interval){
    last_time=t;

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("0"+text+"");
delay(2);

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("0"+text+"");
delay(2);

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("0"+text+"");
delay(2);

    // Update Text Element 
    text="abc"; // <--- Set text to send here 
    Serial.print("0"+text+"");
delay(2);

  }

}
