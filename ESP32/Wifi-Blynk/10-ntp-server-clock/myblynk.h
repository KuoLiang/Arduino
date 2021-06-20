const char* ssid = "RyanRoy";
const char* password = "3838383838";

BlynkTimer timer;

void setup_Wifi()
{
    Serial.print("Connecting");
    digitalWrite(LED_BUILTIN,LOW);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
      lcd.setCursor(0, 0);
      lcd.print("Connecting");
      digitalWrite(LED_BUILTIN,HIGH);
      delay(200);
      Serial.print(".");
      digitalWrite(LED_BUILTIN,LOW);
      delay(200);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connected");
    Serial.println("Connected");
    digitalWrite(LED_BUILTIN,HIGH);

}

BLYNK_WRITE(V7)
{
  int pinValue = param.asInt(); 
  int start=pinValue;
}
BLYNK_WRITE(V6)       //volume
{
  my_volume = param.asInt(); 
  myDFPlayer.volume(my_volume);
}
BLYNK_WRITE(V8)       //1602 backlight
{
  int pinValue = param.asInt(); 
  lcd.setPWM(REG_RED, pinValue);
  lcd.setPWM(REG_GREEN, pinValue);
  lcd.setPWM(REG_BLUE, pinValue);
}
BLYNK_WRITE(V0)       //1602 show text
{
  lcd_on= param.asInt(); 
}

BLYNK_WRITE(V1)       //play music
{
  int pinValue = param.asInt(); 
  if(pinValue==1)
  {
      if(lastplay==0)
      {
        play=1; 
        lastplay=1;
        myDFPlayer.playMp3Folder(1);
      }
      else;
  }
  else
  {
    play=0;
    lastplay=0;
    myDFPlayer.pause();
  }
}

BLYNK_WRITE(V9)     //setup wakeup time as Long
{
  wakeup_time_long = param.asLong(); 
  wakeup_time_str = param.asStr();
  int wakeup_hour= wakeup_time_long/60/60;
  int wakeup_min=(wakeup_time_long-wakeup_hour*60*60)/60;
  EEPROM.write(0, wakeup_hour);
  EEPROM.write(1, wakeup_min);
  Serial.print("Save to");
  Serial.print(wakeup_hour);
  Serial.print(":");
  Serial.print(wakeup_min);
  EEPROM.commit();
  Serial.print("Committed");
}

void printf_bin(float num)//注意这次这里的参数类型改成了float
{
    int i, j, k;
    unsigned char *p = (unsigned char*)&num + 3;

    for (i = 0; i < 4; i++) //处理4个字节(32位）
{
        j = *(p - i); //取每个字节的首地址
        for (int k = 7; k >= 0; k--) //处理每个字节的8个位
        {
            if (j & (1 << k))
                printf("1");
            else
                printf("0");
        }
        printf(" ");
}
    printf("\r\n");
}
