#include <EEPROM.h>
#include <Wire.h>
#include <rgb_lcd.h>
#include <BlynkSimpleEsp32.h>
#include <DFRobotDFPlayerMini.h>
#include <TimeLib.h>

#define EEPROM_SIZE 8

rgb_lcd lcd;
int myalarm=0;
int lcd_on=1;
int play=0;
int lastplay=0;

struct tm timeinfo;
long wakeup_time_long=25200; //am 7:00 as default
String wakeup_time_str;
long currentTime;
long currentDate;

DFRobotDFPlayerMini myDFPlayer;

#include "time.h"
#include "myblynk.h"
#include "mytimer.h"
#include "mymusic.h"

void setup_pinMode()
{
  pinMode(LED_BUILTIN,OUTPUT);
}

void setup() {
    Serial.begin(115200);
    EEPROM.begin(EEPROM_SIZE);
    setup_pinMode();    
    lcd.begin(16,2);
 
    setup_Wifi();  
    Blynk.begin("9PYDD7BujqynzfqQ4GC4ySMRcioalJBt", ssid, password);

    setup_music();
    myDFPlayer.volume(10);  //Set volume value. From 0 to 30
    //myDFPlayer.play(1);  //Play the first mp3
    
    //rtc.begin();   
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); //Setup Localtimer
    timer.setInterval(1000L, EverySecondDo);// Setup a function to be called every second

}

void loop() 
{
    Blynk.run();
    timer.run();
    printLocalTime();
}
