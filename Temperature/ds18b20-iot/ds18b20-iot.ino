#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
//===DHT
#include "DHT.h"

#include <WiFi.h>
#include <HTTPClient.h>

char ssid[] = "RyanRoy";
char password[] = "3838383838";
//請修改為你自己的API Key，並將https改為http
String url = "http://api.thingspeak.com/update?api_key=4LEMK7ADTGWLC6CX";


/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float tempc=0;
float tempf=0;

//int BIN_LED=2;
#define BIN_LED 2
#define DHTPIN 32 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);




void setup() {
  pinMode(BIN_LED, OUTPUT);
  
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println("Temperature Sensor");
  // 初始化
  sensors.begin();

  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
  dht.begin();
}

void loop() {

  digitalWrite(BIN_LED,HIGH);
  sensors.requestTemperatures();
  tempc = sensors.getTempCByIndex(0);
  tempf = sensors.getTempFByIndex(0);
  Serial.println(tempc);
  delay(1000);
  //DHT
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Print  on the first line of the LCD:
  
  lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
  lcd.print("R:"); 
  lcd.print(t);
  lcd.print(" C "); 
  lcd.print(h);
  lcd.print("%"); 
  
  // Print  on the second line of the LCD:
  lcd.setCursor(0, 1); // Set the cursor on the third column and first row.
  lcd.print("W:"); 
  lcd.print(tempc);
  lcd.print(" C "); 
  lcd.print(tempf);
  lcd.print("F"); 


  //開始傳送到thingspeak
  Serial.println("啟動網頁連線");
  HTTPClient http;
  //將溫度及濕度以http get參數方式補入網址後方
  String url1 = url + "&field1=" + (int)tempc + "&field2=" + (int)tempf;
  //http client取得網頁內容
  http.begin(url1);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)      {
    //讀取網頁內容到payload
    String payload = http.getString();
    //將內容顯示出來
    Serial.print("網頁內容=");
    Serial.println(payload);
  } else {
    //讀取失敗
    Serial.println("網路傳送失敗");
  }
  http.end();
  
  digitalWrite(BIN_LED,LOW);
  delay(20000);//休息20秒
}
