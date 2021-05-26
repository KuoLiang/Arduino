//#include<WiFi.h>
#include <BlynkSimpleEsp32.h>
const char* ssid = "R410";
const char* password = "R410R410";

void setup(){
  Serial.begin(115200);
  Serial.println("Trying");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  pinMode(BUILTIN_LED, OUTPUT);
  Blynk.begin("yourkey", ssid, password);
  
}

void loop(){
      Blynk.run();
}
