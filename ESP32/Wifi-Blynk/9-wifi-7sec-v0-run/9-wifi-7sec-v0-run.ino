#include <BlynkSimpleEsp32.h>
int start =0;
int stop_LED=26;
int LED[6]={23,16,17,25,33,32};
int money = 100;
int bet[6]={0,0,0,0,0,0};
BlynkTimer timer;

#include "mywifi.h"
//#include "run_7sec.h"
#include "run_7sec_random.h"
#include "myblynk.h"


void sendSensor() //run at every second
{
  Blynk.virtualWrite(V6, money);
}


void setup_pinMode()
{
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(stop_LED,OUTPUT);
  for(int i=0;i<6;i++)
    pinMode(LED[i],OUTPUT); //declare the pinMode for all the 7-sec
}
//==============
void setup()
{
  Serial.begin(115200);
  setup_pinMode();
  setup_Wifi();  
  timer.setInterval(1000L, sendSensor);// Setup a function to be called every second
}
void loop()
{
  Blynk.run();
  timer.run();
  if(start==1)
  {
    run_7sec();
  }
  start=0;
  Blynk.virtualWrite(V7, start); //clear the start button
}
