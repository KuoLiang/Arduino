#include<WiFi.h>
#include <HTTPClient.h>
const char ssid[]="RyanRoy"; //修改為你家的WiFi網路名稱
const char pwd[]="klou802827"; //修改為你家的WiFi密碼

int sensorValue;

//String url = "https://api.thingspeak.com/update?api_key=改成你的API Key";
String url = "https://hook.us1.make.com/rewpgcxzu2skqes1kldqhrdd75gyyygp?";

//讀取土壤濕度感測器
void ReadSensor(){
  sensorValue=analogRead(13); //讀取感測器回傳值
  Serial.print("value:");
  Serial.println(sensorValue);
}


//將資料上傳ThinkSpeak
void UploadData(){ 
  
  //建立一個網頁
  HTTPClient http;  

  //把土壤濕度數值寫入網址
  String url1= url+"field1="+(int)sensorValue;

  //提交網址
  http.begin(url1);

  //讀取網頁內容
  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK){
    String payload = http.getString();
    Serial.print("網頁內容=");
    Serial.println(payload);
  } 
  else{
     Serial.println("網路傳送失敗");
  }

  //關閉網頁
  http.end(); 
  
}


void setup() {
  
  pinMode(13,INPUT);
  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA); //設置WiFi模式
  WiFi.begin(ssid,pwd); 

  Serial.print("WiFi connecting");

  //當WiFi連線時會回傳WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);   
  }

  Serial.println("");
  Serial.print("IP位址:");
  Serial.println(WiFi.localIP()); //讀取IP位址
  Serial.print("WiFi RSSI:");
  Serial.println(WiFi.RSSI()); //讀取WiFi強度

}

void loop() {
  ReadSensor();
  UploadData();
  delay(30000);
}