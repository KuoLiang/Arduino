/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: ESP32 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires installation of EPS32 core. See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details. 
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/
#include <DHT.h>
#include <WiFi.h>
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include "images.h"
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#define DHTPIN 15          // What digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
DHT dht(DHTPIN, DHTTYPE);
SSD1306Wire display(0x3c, SDA, SCL);   // ADDRESS, SDA, SCL  
void check_buttom();

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
float h,t;
// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = 0;
int number4 = 0;
String myStatus = "";
int showout = 0;

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  pinMode(BUILTIN_LED,OUTPUT);
  pinMode(12,OUTPUT);//yellow led
  pinMode(13,OUTPUT);//green led
  pinMode(16,OUTPUT);//red led
  pinMode(36,INPUT);//buttom B
  
  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  dht.begin();
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  digitalWrite(12,HIGH); //yellow
  digitalWrite(13,HIGH); //green
  digitalWrite(16,HIGH);//red
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
  h = dht.readHumidity();
  t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
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
    display.clear();
    digitalWrite(BUILTIN_LED,LOW);
    digitalWrite(12,LOW); //yellow
    digitalWrite(13,LOW); //green
    digitalWrite(16,HIGH);//red
    check_buttom();
    delay(10000); // Wait 10 seconds to update the channel again
    digitalWrite(12,HIGH); //yellow
    digitalWrite(13,LOW); //green
    digitalWrite(16,LOW); //red
    check_buttom();
    delay(10000); // Wait 10 seconds to update the channel again 
    digitalWrite(BUILTIN_LED,HIGH);
    digitalWrite(12,LOW); //yellow
    digitalWrite(13,HIGH); //green
    digitalWrite(16,LOW); //red
    check_buttom();
  
}

void check_buttom()
{
  if(!digitalRead(36))
  { 
    display.displayOn();
    String show;
    show = "Temperature:"+String(t);
    show += "\nHumidity:"+String(h);
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128, show);
    display.display();
    delay(3000); // Wait 3 seconds to showout 
  }
    display.clear();
    display.display();
}
