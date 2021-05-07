/* 
*  例3-8：將ESP32啟動為無線網路基地台（Soft AP）模式，並自訂各種屬性
*/
#include <WiFi.h>                       //引用Wi-Fi函式庫

IPAddress local_IP(192, 168, 4, 100);   //設定ESP32身為AP時的IP位址
IPAddress gateway(192, 168, 4, 100);    //設定此網路的閘道器IP位址（一般同於IP位址）
IPAddress subnet(255, 255, 255, 0);     //設定此網路的子網路遮罩

const char *ssid = "ESP32基地台";     //啟動Soft AP，SSID為ESP32基地台
const char *password = "12345678";    //密碼為12345678

void setup() {
  Serial.begin(9600);

  WiFi.softAPConfig(local_IP, gateway, subnet);   //設定AP位址
  while (!WiFi.softAP(ssid, password)) {};        //如果啓動AP失敗，會一直在這，重覆測試直到成功
  Serial.println("\nAP啓動成功");                 //「\n」是換新一行，目的是和ESP32開機訊息分開

  Serial.print("我的IP位址: ");
  Serial.println(WiFi.softAPIP());       //印出IP位址
 }
void loop() {
}
