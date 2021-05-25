#include<analogWrite.h>
void setup () 
{ 
  pinMode(36,INPUT);
  pinMode(4,OUTPUT); 
} 
void loop() 
{ 
      analogWrite(4,analogRead(36)/4);    
} 
