#include <Wire.h>
#include <rgb_lcd.h>
#include <BlynkSimpleEsp32.h>
rgb_lcd lcd;
int myalarm=0;
int lcd_on=1;
#include "time.h"
#include "myblynk.h"
#include "mytimer.h"

void sendSensor()
{
  Blynk.virtualWrite(V6, myalarm);
}

void setup_pinMode()
{
  pinMode(LED_BUILTIN,OUTPUT);
}
void setup() {
    Serial.begin(115200);
    lcd.begin(16,2);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    printLocalTime();
    setup_pinMode();
    setup_Wifi();  
    Blynk.begin("9PYDD7BujqynzfqQ4GC4ySMRcioalJBt", ssid, password);
    timer.setInterval(1000L, sendSensor);// Setup a function to be called every second
}

void loop() 
{
    Blynk.run();
    timer.run();
    printLocalTime();
}
