const char* ntpServer = "watch.stdtime.gov.tw";
const long  gmtOffset_sec = 8*60*60; //+8hrs
const int   daylightOffset_sec = 0;

void EverySecondDo()
{
  currentTime = ((hour()*60)+minute())*60 + second();
  //currentDate = String(day()) + " " + month() + " " + year();
  Blynk.virtualWrite(V6, currentTime);
  //Serial.print("current:");
  //Serial.println(currentTime);
  //Serial.print("wakeup :");
  //Serial.println(wakeup_time);

  if(currentTime-60>=wakeup_time_long)
  {
    myDFPlayer.stop();
  }
  else if(currentTime>=wakeup_time_long)
  {
    myDFPlayer.play(1);
  }
  
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
    lcd.print(myminute);
    delay(1000);
    (lcd_on==1)?lcd.display():lcd.noDisplay();
    
}
