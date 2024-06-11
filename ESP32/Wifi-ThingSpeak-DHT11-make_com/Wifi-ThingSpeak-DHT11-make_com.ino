// 結合 ThingSpeak 之 Wifi Client 以及呼叫 make.com 之 Wifi HTTPClient
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ThingSpeak.h> 
#include "../../../secrets.h"

#define DHTPIN 4          // for DHT11
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

WiFiClient  client;
DHT dht(DHTPIN, DHTTYPE);

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = 0;
int number4 = 0;
String myStatus = "";

//==========================
//call the webhook of make.com
//==========================

void UploadData(){ 
  HTTPClient myWebClient;  
  String url_str= url+"field1="+(int)number1+"field2="+(int)number2;
  myWebClient.begin(url_str);
  int httpCode = myWebClient.GET();
  if(httpCode == HTTP_CODE_OK){
    String payload = myWebClient.getString();
    Serial.print("Webhook response : ");
    Serial.println(payload);
  } 
  else{
     Serial.println("upload failed");
  }
  myWebClient.end(); 
}

//==========================
//setup
//==========================

void setup() {
  pinMode(BUILTIN_LED,OUTPUT);
  Serial.begin(115200); //Initialize serial
  dht.begin();          //Initialize DHT
  WiFi.mode(WIFI_STA);  //Initialize Wifi
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Connecting to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(1000);     
    } 
    Serial.println("\nConnected.");
  }


  float h = dht.readHumidity();
  float t = dht.readTemperature(); // dht.readTemperature(true) for Fahrenheit
  Serial.println(h);
  Serial.println(t);
  // set the fields with the values
  ThingSpeak.setField(1, number1); // 0 to 99
  ThingSpeak.setField(2, number2); // random
  ThingSpeak.setField(3, h);       // humidity
  ThingSpeak.setField(4, t);       // temperature

  // figure out the status message
  if(number1 > number2){
    myStatus = String("field1 is greater than field2"); 
  }
  else if(number1 < number2){
    myStatus = String("field1 is less than field2");
  }
  else{
    myStatus = String("field1 equals field2");
  }
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  // change the values
  number1++;
  if(number1 > 99){
    number1 = 0;
  }
  number2 = random(0,100);
  digitalWrite(BUILTIN_LED,LOW);
  delay(20000); // Wait 20 seconds to update the channel again
  digitalWrite(BUILTIN_LED,HIGH);
  UploadData();
}
