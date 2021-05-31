const char* ssid = "R410";
const char* password = "R410R410";

void setup_Wifi()
{
    Serial.print("Connecting");
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
    Serial.print("WiFi connected");
    digitalWrite(LED_BUILTIN,HIGH);
    Blynk.begin("9PYDD7BujqynzfqQ4GC4ySMRcioalJBt", ssid, password);
}
