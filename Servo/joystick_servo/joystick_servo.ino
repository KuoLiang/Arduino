//www.youtube.com/Electronics is Fun//
//www.facebook.com/Electronics  is Fun//
//copyright by MOHD SOHAIL//


#include <Servo.h>

//Servo  objects created to control the servos
Servo myServo1;
Servo myServo2;

int  servo1 = 3; //Digital PWM pin used by the servo 1
int servo2 = 5; //Digital PWM  pin used by the servo 2
int joyX = 0;   //Analog pin to which the joystick (X)  is connected
int joyY = 1;   //Analog pin to which the joystick (Y) is connected

void  setup(){
  Serial.begin(9600);
  myServo1.attach(servo1);
  myServo2.attach(servo2);
}

void  loop(){
  
  int valX = analogRead(joyX); //Read the joystick X value (value  between 0 and 1023)
  int valY = analogRead(joyY); //Read the joystick Y value  (value between 0 and 1023)
  Serial.println(valX);
  valX = map(valX, 0, 1023, 10, 170); //Scale  the joystick X value to use it with the servo
  valY = map(valY, 0, 1023, 10,  170); //Scale the joystick X value to use it with the servo

  //Sets the  servo position according to the scaled values.
  myServo1.write(valX);   
  myServo2.write(valY);

  delay(5);

}
