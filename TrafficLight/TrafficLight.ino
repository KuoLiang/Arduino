/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPinR = 12;     // the number of the pushbutton pin
const int buttonPinW = 11;     // the number of the pushbutton pin

const int ledPin =  13;      // the number of the LED pin
const int ledPinR =  4;      // the number of the LED pin
const int ledPinY =  3;      // the number of the LED pin
const int ledPinG =  2;      // the number of the LED pin


// variables will change:
int buttonStateR = 0;         // variable for reading the pushbutton status
int buttonStateW = 0;         // variable for reading the pushbutton status


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinR, INPUT);
  pinMode(buttonPinW, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonStateR = digitalRead(buttonPinR);
  buttonStateW = digitalRead(buttonPinW);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateR == HIGH) {
    // turn LED on:
    digitalWrite(ledPinR, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPinR, LOW);
  }
  //==================
    if (buttonStateW == HIGH) {
    // turn LED on:
    digitalWrite(ledPinG, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPinG, LOW);
  }
}
