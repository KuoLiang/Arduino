const char* ntpServer = "watch.stdtime.gov.tw";
const long  gmtOffset_sec = 25200; //+8hrs
const int   daylightOffset_sec = 3600;


void printLocalTime()
{
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");
      return;
    }
    myalarm=100;
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    lcd.setCursor(0, 0);
    lcd.print(&timeinfo, "%B %d %Y"); 
    lcd.setCursor(0, 1);
    lcd.print(&timeinfo, "%H:%M:%S"); 
    delay(1000);
    (lcd_on==1)?lcd.display():lcd.noDisplay();
    //lcd.display();
}
