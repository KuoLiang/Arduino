/*  
*  例3-10：啟用ESP32網頁伺服器功能，回應客戶端的請求
*/
#include <WiFi.h>                //引用Wi-Fi函式庫
#include <WebServer.h>           //引用WebServer函式庫

const char *ssid = "基地台的SSID";       //無線網路基地台的SSID
const char *password = "基地台的密碼";   //無線網路基地台的密碼

WebServer server(80);        //建立伺服器物件，監聽80號埠(尚未啟動)

void handleRoot() {          //處理程序：回覆根目錄請求
  server.send(200, "text/html; charset=UTF-8", "Hello World!");  //送出訊息到客戶端
  }

void handleNotFound() {      //處理程序：未找到檔案時
  server.send(404, "text/plain; charset=UTF-8", "找不到檔案");
}

void setup(void) {
  Serial.begin(9600);
  WiFi.begin(ssid, password);              //連線到無線基地台
  while (WiFi.status() != WL_CONNECTED) {  //持續嘗試連線至成功為止
    delay(500);
    Serial.print(".");
  }
  Serial.print("已連線到基地台：");
  Serial.println(ssid);
  Serial.print("基地台配發給我的IP位址：");
  Serial.println(WiFi.localIP());    //列出基地台配發給我的位址

  server.on("/", handleRoot);        //登錄處理程序：根目錄請求
  server.onNotFound(handleNotFound); //登錄處理程序：未找到檔案
  server.begin();                    //啟動伺服器物件
  Serial.println("HTTP 伺服器已啟動");
}

void loop(void) {
  server.handleClient();            //啟動客戶端請求處理程序
}
