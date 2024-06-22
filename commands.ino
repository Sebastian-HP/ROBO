#include <Servo.h>

Servo top_right;
Servo top_left;
Servo bottom_right;
Servo bottom_left;  


// create servo object to control a servo
                // 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 


void setup() {
  top_right.attach(6);
  top_left.attach(11);
  bottom_right.attach(9);
  bottom_left.attach(10);
     // attaches the servo on pin 18 to the servo object
                              // using default min/max of 1000us and 2000us
                              // different servos may require different min/max settings
                              // for an accurate 0 to 180 sweep
}

void loop() {
  int command = 0;
  if (command = 0){
    top_right.write(90);
    top_left.write(90);
    bottom_right.write(90);
    bottom_left.write(90);  
    Serial.print(0);           
  }

  if (command = 1){
    top_right.write(180);
    top_left.write(180);
    bottom_right.write(180);
    bottom_left.write(180);  
    Serial.print(1);              
  }

   if (command = 2){
    top_right.write(0);
    top_left.write(180);
    bottom_right.write(0);
    bottom_left.write(180);    
    Serial.print(2);            
  }

    if (command = 3){
    top_right.write(0);
    top_left.write(0);
    bottom_right.write(0);
    bottom_left.write(0);       
    Serial.print(3);         
  }
    if (command = 4){
    top_right.write(180);
    top_left.write(0);
    bottom_right.write(180);
    bottom_left.write(0);  
    Serial.print(4); 
  
  }
}