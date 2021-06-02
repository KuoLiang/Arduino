#include <EEPROM.h>
#include <Wire.h>
#include <rgb_lcd.h>
#include <BlynkSimpleEsp32.h>
#include <DFRobotDFPlayerMini.h>
#include <TimeLib.h>

#define EEPROM_SIZE 2
int PLAY_TIME=180;
rgb_lcd lcd;
int myalarm=0;
int lcd_on=1;
int play=0;
int lastplay=0;
int motion=1;
int motion_delay=20;

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
  pinMode(35,INPUT); //motion pin
}

void myread_eeprom()
{
  EEPROM.begin(EEPROM_SIZE);
  int wakeup_hour = EEPROM.read(0);
  int wakeup_min = EEPROM.read(1);
  //change to wake up time
  wakeup_time_long = wakeup_hour*60*60 + wakeup_min*60;
  Serial.print("EEPROM=");
  Serial.println(wakeup_time_long);
}
void setup() {
    Serial.begin(115200);
    setup_pinMode();    
    lcd.begin(16,2);
    myread_eeprom();
 
    setup_Wifi();  
    Blynk.begin("ChqgZuNksx9RaZtOnKu75V08IM9s2S_s", ssid, password);

    setup_music();
    myDFPlayer.volume(20);  //Set volume value. From 0 to 30
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
