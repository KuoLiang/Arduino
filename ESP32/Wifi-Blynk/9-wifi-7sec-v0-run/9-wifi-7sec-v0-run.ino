#include <BlynkSimpleEsp32.h>
const char* ssid = "RyanRoy";
const char* password = "3838383838";

BlynkTimer timer;
int money = 100;
int start =0;
int bet[6]={0,0,0,0,0,0};
int LED[6]={23,16,17,25,33,32};
int stop_LED=26;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  Blynk.virtualWrite(V6, money);
}
BLYNK_WRITE(V7)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  start=pinValue;
  Serial.println(start);
}
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[0]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[0]=pinValue;
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[1]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[1]=pinValue;
}
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[2]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[2]=pinValue;
}
BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[3]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[3]=pinValue;
}
BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[4]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[4]=pinValue;
}
BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(bet[5]!=pinValue)
  {
    if(pinValue == 1)
      money--;
    else
      money++;
  }
  bet[5]=pinValue;
}

//==============
void setup_pinMode()
{
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(stop_LED,OUTPUT);
  for(int i=0;i<6;i++)
    pinMode(LED[i],OUTPUT); //declare the pinMode for all the 7-sec
}
//==============
void setup_Wifi()
{
    Serial.println("Trying");
    digitalWrite(LED_BUILTIN,LOW);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      digitalWrite(LED_BUILTIN,HIGH);
      delay(200);
      Serial.print(".");
      digitalWrite(LED_BUILTIN,LOW);
      delay(200);
    }
    Serial.println("WiFi connected");
    digitalWrite(LED_BUILTIN,HIGH);
}
//==============
//==============
void setup(){
  Serial.begin(115200);
  setup_pinMode();
  setup_Wifi();  
  Blynk.begin("9PYDD7BujqynzfqQ4GC4ySMRcioalJBt", ssid, password);
    // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
void loop()
{
  Blynk.run();
  timer.run();
  if(start==1)
  {
    digitalWrite(stop_LED,LOW);
    for(int i=0;i<6;i++)
    {
      for(int j=0;j<6;j++)
      {
        digitalWrite(LED[j],LOW); //clear all
      }
      digitalWrite(LED[i],HIGH);
      Serial.println(LED[i]);
      delay(500);
    }
  }
  start=0;
  digitalWrite(stop_LED,HIGH);
}
