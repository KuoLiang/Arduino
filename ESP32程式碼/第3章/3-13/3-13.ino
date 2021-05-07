/*
*  例3-13：從NTP取回時間並顯示
*/
#include <WiFi.h>  //引用Wi-Fi函式庫
#include <time.h>  //引用時間格式及操作函式庫

const char *ssid = "基地台的SSID";        //無線網路基地台的SSID
const char *password = "基地台的密碼";    //無線網路基地台的密碼

const char *ntpServer = "pool.ntp.org"; //ntp伺服器網址
const long  gmtOffset_sec = 28800;      //台灣位於GMT+8，為28800秒
const int   daylightOffset_sec = 0;     //台灣不使用日光節約時間，設為0

void setup() {
  Serial.begin(9600);
  Serial.printf("連線到 %s ", ssid);
  WiFi.begin(ssid, password);              //連到基地台
  while (WiFi.status() != WL_CONNECTED){   //當狀態不是已連線
    delay(500);                            //等待0.5秒
    Serial.print(".");                     //印出一個點提示讓你知道
  }                                        //回到迴圈判斷處，再判斷一次
  Serial.println("已連線");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  //設定NTP參數
}
void loop() {
  struct tm timeinfo;                   //建立一個時間結構，名字為timeinfo
  if (!getLocalTime(&timeinfo)) {       //取回NTP時間
    Serial.println("網路時間取回失敗");    //如果失敗，回傳訊息
    return;
  }
  Serial.println(&timeinfo, "%F %T ");  //列印取回的時間
  delay(1000);
}
