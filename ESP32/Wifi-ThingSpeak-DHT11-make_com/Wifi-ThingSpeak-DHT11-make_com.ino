
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "../../../secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#define DHTPIN 4          // What digital pin we're connected to
// Uncomment whatever type you're using!
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
int sensorValue=0;

// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = 0;
int number4 = 0;
String myStatus = "";
//==========================
void UploadData(){ 
  HTTPClient http;  
  String url1= url+"field1="+(int)sensorValue;
  http.begin(url1);
  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK){
    String payload = http.getString();
    Serial.print("網頁內容=");
    Serial.println(payload);
  } 
  else{
     Serial.println("網路傳送失敗");
  }
  http.end(); 
}


void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  pinMode(BUILTIN_LED,OUTPUT);
  dht.begin();
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }


  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  Serial.println(h);
  Serial.println(t);
  // set the fields with the values
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setField(3, h);
  ThingSpeak.setField(4, t);

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
