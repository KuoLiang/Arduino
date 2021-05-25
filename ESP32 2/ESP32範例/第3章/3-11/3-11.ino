/*  
*  例3-11：使用瀏覽器控制ESP32上的LED亮滅
*/

#include <WiFi.h>                //引用Wi-Fi函式庫
#include <WebServer.h>           //引用WebServer函式庫

const char *ssid = "基地台的SSID";       //無線網路基地台的SSID
const char *password = "基地台的密碼";   //無線網路基地台的密碼

const byte LED = 2;           //LED接腳為 GPIO 2
WebServer server(80);         //建立伺服器物件，設定監聽 80 號埠

void handleRoot() {           //處理程序：回覆根目錄請求
  String HTML = "<a href=\"/on\">開啟LED</a>";           //開始組合HTML
  HTML += "<BR>";
  HTML += "<a href=\"/off\">關閉LED</a>";
  server.send(200, "text/html; charset=UTF-8", HTML );  //送出訊息到客戶端
}

void handleNotFound() {      //處理程序：未找到檔案時
  server.send(404, "text/html; charset=UTF-8", "找不到檔案");
}
 
void handleLedOn() {         //處理程序：點亮LED
  digitalWrite(LED, HIGH);
  server.send(200, "text/html; charset=UTF-8", "LED已開啟<BR>\
              <a href=/off>關閉LED</a>");
}
void handleLedOff() {        //處理程序：熄滅LED
  digitalWrite(LED, LOW);
  server.send(200, "text/html; charset=UTF-8", "LED已關閉<BR>\
              <a href=/on>開啟LED</a>");
}

void setup(void) {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, password);              //連線到無線基地台
  while (WiFi.status() != WL_CONNECTED) {  //持續嘗試連線至成功為止
    delay(500);
    Serial.print(".");
  }
  Serial.print("已連線到基地台：");
  Serial.println(ssid);
  Serial.print("基地台配發給我的IP位址：");
  Serial.println(WiFi.localIP());    //列出基地台配發給我的位址

  server.on("/", handleRoot);        //登錄處理程序：根目錄
  server.onNotFound(handleNotFound); //登錄處理程序：未找到檔案
  server.on("/on", handleLedOn);     //登錄處理程序：點亮LED
  server.on("/off", handleLedOff);   //登錄處理程序：熄滅LED
  server.begin();                    //啟動伺服器物件
  Serial.println("HTTP 伺服器已啟動");
}

void loop(void) {
  server.handleClient();            //啟動客戶端請求處理程序
}
