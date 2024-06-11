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
  Serial.println("clockwise");
  //myStepper.step(stepsPerRevolution);
  myStepper.step(val - previous);
  // remember the previous value of the sensor
  previous = val;
  //delay(500);

  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  //myStepper.step(-stepsPerRevolution);
  //delay(500);
  
}
