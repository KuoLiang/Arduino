/* 
*  例3-7：將ESP32啟動為軟體無線網路基地台（Soft AP）模式
*/
#include <WiFi.h>              //引用Wi-Fi函式庫

void setup() {
  WiFi.softAP("ESP32基地台");  //啟動Soft AP，SSID為”ESP32基地台”
}

void loop() {
}
