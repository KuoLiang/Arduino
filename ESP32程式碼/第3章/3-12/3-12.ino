/*  
*  例3-12：ESP32建立為SoftAP，並架設Web Server，供客戶端連入，
*          使用瀏覽器控制LED亮滅
*/

#include <WiFi.h>                //引用Wi-Fi函式庫
#include <WebServer.h>           //引用WebServer函式庫

const char *ssid = "ESP32基地台";      //基地台SSID
const char *password = "12345678";     //基地台密碼

const byte LED = 2;           //LED接腳為GPIO2
WebServer server(80);         //建立伺服器物件，設定監聽80號埠

void handleRoot() {           //處理程序：回覆根目錄請求
  String HTML = "<a href=\"/on\">開啟LED</a>";           //開始組合HTML
  HTML+= "<BR>";
  HTML+= "<a href=\"/off\">關閉LED</a>";
  server.send(200, "text/html; charset=UTF-8", HTML );  //送出訊息到客戶端
  }

void handleNotFound() {      //處理程序：未找到檔案時
  server.send(404, "text/html; charset=UTF-8", "找不到檔案");
}

void handleLedOn(){
  digitalWrite(LED,HIGH);
  server.send(200, "text/html; charset=UTF-8", "LED已開啟<BR>\
              <a href=/off>關閉LED</a>");
  }
  
void handleLedOff(){
  digitalWrite(LED,LOW);
  server.send(200, "text/html; charset=UTF-8", "LED已關閉<BR>\
              <a href=/on>開啟LED</a>");
  }

void setup(void) {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
    
  WiFi.softAP(ssid, password);     //建立無線基地台，SSID為：ESP32基地台，密碼為：123456

  Serial.print("\n已建立基地台：");
  Serial.println(ssid);
  Serial.print("我的IP位址：");
  Serial.println(WiFi.softAPIP());   //列出基地台的位址

  server.on("/", handleRoot);        //登錄處理程序：根目錄
  server.onNotFound(handleNotFound); //登錄處理程序：未找到檔案
  server.on("/on",handleLedOn);      //登錄處理程序：點亮LED
  server.on("/off",handleLedOff);    //登錄處理程序：熄滅LED
  server.begin();                    //啟動伺服器物件
  Serial.println("HTTP 伺服器已啟動");
}

void loop(void) {
  server.handleClient();            //啟動客戶端請求處理程序
}
