#include <Stepper.h>

const int stepsPerRevolution = 2048;  
// change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int previous = 0;
void setup() {
  // set the speed rpm:
  myStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  int val = analogRead(0);
  //myStepper.step(stepsPerRevolution);
  myStepper.step(val - previous);
  //Serial.println(val - previous);
  previous = val;
  
}
