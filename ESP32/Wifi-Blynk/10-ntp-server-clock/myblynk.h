const char* ssid = "RyanRoy";
const char* password = "3838383838";

BlynkTimer timer;
void setup_Wifi()
{
    Serial.println("Trying");
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
    Serial.println("WiFi connected");
    digitalWrite(LED_BUILTIN,HIGH);
}

BLYNK_WRITE(V7)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  int start=pinValue;
}
BLYNK_WRITE(V8)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  lcd.setPWM(REG_RED, pinValue);
  lcd.setPWM(REG_GREEN, pinValue);
  lcd.setPWM(REG_BLUE, pinValue);
}
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  lcd_on=pinValue;
}
