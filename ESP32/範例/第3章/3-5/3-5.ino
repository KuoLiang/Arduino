/* 
*  例3-5：利用狀態值判斷是否連線，並重覆嘗試
*/
#include <WiFi.h>          //引用Wi-Fi函式庫

const char *ssid = "基地台的SSID";        //無線網路基地台的SSID
const char *password = "基地台的密碼";    //無線網路基地台的密碼

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);              //連到無線基地台
  while (WiFi.status() != WL_CONNECTED) {  //當狀態不是已連線
    delay(500);               //等待0.5秒
    Serial.print(".");        //印出一個點提示讓你知道
  }                           //回到迴圈判斷處，再判斷一次
  Serial.println("已連線到 Wi-Fi 基地台");
}
void loop() {
}
