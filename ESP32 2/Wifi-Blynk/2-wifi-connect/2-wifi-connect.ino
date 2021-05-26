#include<WiFi.h>
const char* ssid = "R410";
const char* password = "R410R410";

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Trying");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
}

void loop(){
      digitalWrite(BUILTIN_LED,HIGH);
      delay(1000);
      digitalWrite(BUILTIN_LED,LOW);
      delay(1000);
}
