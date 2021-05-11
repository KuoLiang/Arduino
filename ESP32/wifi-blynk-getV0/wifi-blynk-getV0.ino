//#include<WiFi.h>
#include <BlynkSimpleEsp32.h>
const char* ssid = "tcap";
const char* password = "3838383838";

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
}

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
  Blynk.begin("0Hx-V_ZtxFY01BkTK6Vcqco8ASA-1pN3", ssid, password);
  
}

void loop(){
      Blynk.run();
      
}
