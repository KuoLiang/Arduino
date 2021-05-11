/* 
 * 例8-1：收集溫度、溼度、灰塵密度，連上 ThingSpeak 並傳送資料
*/
//WiFi 相關
#include <WiFi.h>                      //引用Wi-Fi函式庫
#include <HTTPClient.h>                //引用HTTPClient函式庫
const char *APIKey = "通道的 APIKey";   //通道的 APIKey
const char *ssid = "基地台的SSID";      //無線網路基地台的SSID
const char *password = "基地台的密碼";   //無線網路基地台的密碼
HTTPClient http;                       //以HTTPClient類別建立客戶端物件，名字為：http

//溫溼度感測器相關
#include "DHTesp.h"             //引用函式庫（函式庫安裝方式請參考第6章）
DHTesp dht;                     //宣告物件，名字為 dht
const byte dhtPin = 17;         //資料送至 GPIO 17

//灰塵感測器相關
const byte ledPower = 25;       //點亮感測器 IRED 接腳
const byte dustPin = 33;        //從感測器接收類比訊號
float dustVal, dustResult;      //推算出來的灰塵密度 (ug/m^3)

//光敏電阻相關
int light;                      //光敏電阻類比讀值
const byte cdsPin = 32;         //光敏電阻接腳

void setup() {
  Serial.begin(9600);
  dht.setup(dhtPin, DHTesp::DHT22);   //依使用的感測器修改為DHT11或DHT22
  pinMode(ledPower, OUTPUT);          //灰塵感測器
  WiFi.begin(ssid, password);              //連到無線基地台
  
  while (WiFi.status() != WL_CONNECTED) {  //當狀態不是已連線
    delay(500);                            //等待0.5秒
    Serial.print(".");                     //印出一個點提示讓你知道
  }                                        //回到迴圈判斷處，再判斷一次
}

void loop() {
  //取得溫溼度
  TempAndHumidity lastValues = dht.getTempAndHumidity();               //取得溫溼度值
  Serial.println("溫度: " + String(lastValues.temperature, 1) + "度C"); //列印溫度
  Serial.println("溼度: " + String(lastValues.humidity, 1) + " %RH");   //列印溼度

  //灰塵感測器模組取樣
  digitalWrite(ledPower, LOW);
  delayMicroseconds(280);
  dustVal = analogRead(dustPin);
  delayMicroseconds(40);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(9680);
  dustResult = map(dustVal, 670, 2531, 70, 430);     //推算灰塵密度（ug/m^3）
  
  if(dustResult<0)           //如果灰塵感測器輸出太低的類比電壓
     dustResult = 0;         //認定為0，表示未檢出
  Serial.println("灰塵密度：" + String(dustResult) + "ug/m^3");    //列印灰塵密度

  light = analogRead(cdsPin);         //讀取光敏電阻的類比值 
  Serial.println("光敏電阻類比讀值：" + String(light));

  //傳輸資料到ThingSpeak
  if (!http.connected()) {                                  //如果沒有連到ThingSpeak，則執行下面的連線指令
    String Data = "http://api.thingspeak.com/update?key=";  //網址的前頭
    Data =  Data + APIKey + "&field1=" + lastValues.temperature + "&field2=" + lastValues.humidity + "&field3=" + dustResult + "&field4=" + light;   //原本的字串，加上APIKey，再交叉加上字串及變數
    http.begin(Data);                //啟動http連線，並將合成的字串放入
  }
  int httpCode = http.GET();         //執行GET請求
  
  if (httpCode == HTTP_CODE_OK)      //如果HTTP Code為 HTTP_CODE_OK，代表傳送OK
    Serial.println("已將資料傳送至ThingSpeak\n");
  delay(5000);                       //隔5秒後再重新傳送
}
