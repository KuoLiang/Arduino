// open source if you improve this please share with me and others
int min_sweep = 0;
int max_sweep = 180;
int sweep_rate = 40;
float correct;
int k = 0;

// ----------------------------------U/S Ranging-----------------------------------------
#include <NewPing.h>
#define TRIGGER_PIN 3 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN 4 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigger_pin = TRIGGER_PIN;
const int echo_pin = ECHO_PIN;
// Variables for the duration and the distance
long duration;
int distance;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int pingSpeed = 50; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer; // Holds the next ping time.
// ---------------------------------------------------------------------------
char val; // Data received from the serial port

void setup()
{
  // ----------------------------------U/S Ranging-----------------------------------------
  pingTimer = millis(); // Start now.
  // ---------------------------------------------------------------------------
  pinMode(trigger_pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echo_pin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200);

}
void loop()
{//format to serial port : angle,distance.
 
    for (int i = min_sweep; i <= max_sweep; i++) {
  
      Serial.print(i); // Sends the current degree into the Serial Port
      Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      //Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Sends the distance value into the Serial Port
      //unsigned int us=sonar.ping_median();     //傳回 5 次偵測的回應時間中數 (微秒)
      //Serial.print(sonar.convert_cm(us));   
      Serial.print(sonar.ping_cm());  
      Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      delay(pingSpeed);
    }
}

///////////////////////////////////////////////////////////////
