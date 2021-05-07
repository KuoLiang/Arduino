#include <NewPing.h>
#define TRIGGER_PIN 3 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN 4 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigger_pin = TRIGGER_PIN;
const int echo_pin = ECHO_PIN;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()
{
  pinMode(trigger_pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo_pin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);
}
void loop()
{  
      Serial.println(sonar.ping_cm());  
      delay(50);
}
