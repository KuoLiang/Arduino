/*
*   例3-4：讓ESP32連上無線基地台（AP）
*/
#include <WiFi.h>          //引用Wi-Fi函式庫

const char *ssid = "基地台的SSID";        //無線網路基地台的SSID
const char *password = "基地台的密碼";    //無線網路基地台的密碼

void setup() {
  WiFi.begin(ssid, password);    //啟動Wi-Fi連線
}

void loop () {
}
