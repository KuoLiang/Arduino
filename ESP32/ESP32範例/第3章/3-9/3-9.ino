/*
*  例3-9：建立客戶端物件，並嘗試連上網站
*/
#include <WiFi.h>        //引用Wi-Fi函式庫
#include <HTTPClient.h>  //引用函式庫
HTTPClient http;         //建立物件

const char *ssid = "基地台的SSID";         //無線網路基地台的SSID
const char *password = "基地台的密碼";     //無線網路基地台的密碼

void setup() {
  Serial.begin(9600);
  Serial.println();              //分行符號，和ESP32開機訊息分隔
  WiFi.begin(ssid, password);              //連到無線基地台
  while (WiFi.status() != WL_CONNECTED) {  //當狀態不是已連線
    delay(500);                            //等待0.5秒
    Serial.print(".");                     //印出一個點提示讓你知道
  }                                        //回到迴圈判斷處，再判斷一次
  Serial.println("已連上Wi-Fi");
}
void loop() {
  http.begin("http://www.tcivs.tc.edu.tw/home?cid=1084");  //學校的網址
  int httpCode = http.GET();        //執行GET請求
  
  String reply = http.getString();  //取出網站回傳的資料
  Serial.println(reply);
  
  delay(5000);    //間隔5秒再傳送一次，以免重覆頻率太高
}
