/*
紅綠燈
紅常暗，綠常亮
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPinR = 12;     // the number of the pushbutton pin
const int buttonPinW = 11;     // the number of the pushbutton pin
const int LIGHT = 0;     // the number of the pushbutton pin
const int THOLD = 300;     // the threshold of yellow light



const int ledPin =  13;      // the number of the LED pin
const int ledPinR =  4;      // the number of the LED pin
const int ledPinY =  3;      // the number of the LED pin
const int ledPinG =  2;      // the number of the LED pin


// variables will change:
int buttonStateR = 0;         // variable for reading the pushbutton status
int buttonStateW = 0;         // variable for reading the pushbutton status


void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinR, INPUT);
  pinMode(buttonPinW, INPUT);
}

void loop() {
  Serial.println(analogRead(LIGHT));
  
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
  //==================
  if(analogRead(LIGHT)<=THOLD)
  {
    digitalWrite(ledPinY, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPinY, LOW);
  }
  delay(1000);
}
