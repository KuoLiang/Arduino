#include <Servo.h>  
const int trigPin = 8;  
const int echoPin = 9;  
long duration; //declare time duration  
int distance;  //declare distance  
Servo myServo; // Object servo  
  
void setup() {  
  pinMode(trigPin, OUTPUT); // trigPin as an output  
  pinMode(echoPin, INPUT); // echoPin as an input  
  Serial.begin(9600);  
  myServo.attach(10); // pin connected to Servo  
}  
  
void loop() {  
  // rotating servo i++ depicts increment of one degree  
  for(int i=0;i<=180;i++){    
  myServo.write(i);  
  delay(30);  
  distance = calculateDistance();  
  Serial.print(i);   
  Serial.print(",");   
  Serial.print(distance);   
  Serial.print(".");  
  }  
  // Repeats the previous lines from 180 to 0 degrees  
  for(int i=180;i>0;i--){    
  myServo.write(i);  
  delay(30);  
  distance = calculateDistance();  
  Serial.print(i);  
  Serial.print(",");  
  Serial.print(distance);  
  Serial.print(".");  
  }  
}  
  
int calculateDistance(){   
  digitalWrite(trigPin, LOW);   
  delayMicroseconds(2);  
  // Sets the trigPin on HIGH state for 10 micro seconds  
  digitalWrite(trigPin, HIGH);   
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);   
  distance= duration*0.034/2;  
  return distance;  
}  
