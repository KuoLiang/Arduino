/* 
*    例3-6：連上無線基地台，並顯示目前的IP等資訊
*/
#include <WiFi.h>          //引用Wi-Fi函式庫

const char *ssid = "基地台的SSID";         //無線網路基地台的SSID
const char *password = "基地台的密碼";     //無線網路基地台的密碼

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);              //連接網路

  while (WiFi.status() != WL_CONNECTED) {  //當狀態不是已連線
    delay(500);                            //等待0.5秒
    Serial.print(".");                     //印出一個點提示讓你知道
  }                                        //回到迴圈判斷處，再判斷一次

  Serial.println("已連上 WiFi");
  Serial.print("我的 IP 位址: ");
  Serial.println(WiFi.localIP());       //印出ESP32取得的IP

  Serial.print("子網路遮罩: ");
  Serial.println(WiFi.subnetMask());    //印出子網路遮罩

  Serial.print("閘道器位址: ");
  Serial.println(WiFi.gatewayIP());     //印出閘道器位址

  Serial.print("DNS位址: ");
  Serial.println(WiFi.dnsIP());         //印出DNS位址
}

void loop() {
}
