//DFRobotDFPlayerMini函式庫下載：https://github.com/DFRobot/DFRobotDFPlayerMini
#include "DFRobotDFPlayerMini.h"
#include <WiFi.h>
const char* ssid = "RyanRoy";
const char* password = "3838383838";
WiFiServer server(80);
HardwareSerial myHardwareSerial(1); //ESP32可宣告需要一個硬體序列，軟體序列會出錯
DFRobotDFPlayerMini myDFPlayer;//啟動DFPlayer撥放器
void printDetail(uint8_t type, int value);//宣告播放控制程式
void setup()
{
  Serial.begin(115200);
  //啟動WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) //等候連線成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");//連線成功
  //啟動WEB Server
  server.begin();
  Serial.println("Server started");
  //顯示IP
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("use 'http://ip/?mp3=x;' to play x'th mp3 file");
  //啟動mp3連線
  myHardwareSerial.begin(9600, SERIAL_8N1, 12, 13); // Serial的TX,RX
  //實際上只用到TX傳送指令，因此RX可不接（接收player狀態）
  Serial.println("Initializing DFPlayer ... (May take 1-2 seconds)");
  myDFPlayer.begin(myHardwareSerial);//將DFPlayer播放器宣告在HardwareSerial控制
  delay(500);
  myDFPlayer.volume(30);  //設定聲音大小（0-30）
  Serial.println("test1");
  myDFPlayer.playMp3Folder(1);  //播放mp3內的0001.mp3 3秒鐘
  delay(3000);
  //  Serial.println("test2");
  //  myDFPlayer.playMp3Folder(2);  //播放mp3內的0002.mp3 3秒鐘
  //  delay(3000);
  //  Serial.println("test3");
  //  myDFPlayer.playMp3Folder(3);  //播放mp3內的0003.mp3 3秒鐘
  //  delay(3000);
  //  Serial.println("test4");
  //  myDFPlayer.playMp3Folder(4);  //播放mp3內的0004.mp3 3秒鐘
  //  delay(3000);
  myDFPlayer.pause();
}
void loop()
{
  String s_mp3no = "x";//x代表初始值，即網路沒有指令
  int i_mp3no = -1;//-1代表初始值，即網路沒有傳指令
  //WIFI指令-------------------
  WiFiClient client = server.available();
  if (!client)    //有人連入才執行
  {
    return;
  }
  Serial.println("new client");
  delay(100);
  //讀取url中的指令
  String request = client.readStringUntil('\r');
  Serial.println(request);
  if (request.indexOf("mp3=") != -1)
  {
    String s_mp3no = request.substring(request.indexOf("mp3=") + 4, request.indexOf(";"));
    Serial.print("s_mp3no=");
    Serial.println(s_mp3no);
    i_mp3no = s_mp3no.toInt();
    Serial.print("i_mp3no=");
    Serial.println(i_mp3no);
    //ledcWrite(0, 255);
    if ((i_mp3no > 0)) {
      Serial.print("play"); Serial.println(i_mp3no);
      myDFPlayer.playMp3Folder(i_mp3no);
    }
    if (i_mp3no == 0) {
      Serial.print("i_mp3no=");
      Serial.println(i_mp3no);
      myDFPlayer.pause();
    }
  }
  //-------------------以下為網站內容：HTML語法
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("<h1>Mp3 now is playing: ");
    client.print(i_mp3no);
    client.print("</h1>");
    client.println("</html>");
    delay(1);
    //-------------------網站內容結束
    client.flush();//清除client
    Serial.println("Client disconnected");
    Serial.println("");
}
