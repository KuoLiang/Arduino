const char* ntpServer = "watch.stdtime.gov.tw";
const long  gmtOffset_sec = 8*60*60; //+8hrs
const int   daylightOffset_sec = 0;

void check_motion()
{
  if(digitalRead(35))
  {
    motion=1;
    motion_delay=20;
  }
  if(motion_delay>=0 && motion==1)
  {
    motion=1;
    lcd.setPWM(REG_RED, motion_delay*10);
    lcd.setPWM(REG_GREEN, motion_delay*10);
    lcd.setPWM(REG_BLUE, motion_delay*10);

    motion_delay--;
    Serial.println(motion_delay);
  }
  else
  {
    motion=0;
    motion_delay=20;
  }
}
void EverySecondDo()
{
  currentTime = ((timeinfo.tm_hour*60)+timeinfo.tm_min)*60 + timeinfo.tm_sec;
  //currentDate = String(day()) + " " + month() + " " + year();
  //Blynk.virtualWrite(V6, currentTime);
  //Serial.print("current:");
  //Serial.println(currentTime);
  //Serial.print("wakeup :");
  //Serial.println(wakeup_time_long);
  //Serial.println(digitalRead(35));
  if(currentTime-PLAY_TIME>=wakeup_time_long && lastplay==1 || digitalRead(35))
  {
    myDFPlayer.stop();
    play=0;
    lastplay=0;
    Serial.println("Stop");
  }
  else if(currentTime==wakeup_time_long && lastplay==0)
  {
    play=1; 
    lastplay=1;
    myDFPlayer.play(1);
    Serial.println("Playing");
  }
  //Serial.println(  EEPROM.read(0));

  check_motion();
  
}

void printLocalTime()
{

    if(!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");
      return;
    }
    //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    lcd.setCursor(0, 0);
    lcd.print(&timeinfo, "%B %d %Y"); //Month, Day, Year
    lcd.setCursor(0, 1);
    lcd.print(&timeinfo, "%H:%M:%S"); //Hour, Minute, Second
    lcd.setCursor(10,1);
    int myhour=wakeup_time_long/(60*60);
    lcd.print(myhour);
    lcd.print(":");
    int myminute=(wakeup_time_long-myhour*60*60)/60;
    if(myminute<10) lcd.print("0");
    lcd.print(myminute);
    delay(1000);
    (lcd_on==1)?lcd.display():lcd.noDisplay();
    
}
