//#include<WiFi.h>
#include <BlynkSimpleEsp32.h>
const char* ssid = "R410";
const char* password = "R410R410";
int pinValueV0 = 0; //initial the V0 value to zero
BLYNK_WRITE(V0)
{
  pinValueV0 = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V0 Slider value is: ");
  Serial.println(pinValueV0);
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
  Blynk.begin("yourkey", ssid, password);
  
}

void loop(){
      Blynk.run();
      digitalWrite(BUILTIN_LED,HIGH);
      delay(pinValueV0);
      digitalWrite(BUILTIN_LED,LOW);
      delay(pinValueV0);
}
