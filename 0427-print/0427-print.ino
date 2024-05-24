#include <WiFiS3.h>
#include "arduino_secrets.h" 
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define RELAY_PIN 8      // 繼電器接在Arduino的8號腳位
#define DHTPIN 2          // 上風處主機板DHT11接在Arduino的9號腳位
#define DHTPIN_CLO 3     // 衣服間DHT11接在Arduino的10號腳位
#define DHTTYPE DHT11     // 使用DHT11型號
DHT dht(DHTPIN, DHT11);
DHT dht_clo(DHTPIN_CLO, DHT11);
bool FanOn = false;
// 初始化LCD，設定I2C地址為0x27，16列2行
LiquidCrystal_I2C lcd(0x27, 16, 2);
void Read_DHT(){

  // 讀取濕度和溫度值
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // 預設讀取攝氏溫度

  float humidity_clo = dht_clo.readHumidity();
  float temperature_clo = dht_clo.readTemperature(); // 預設讀取攝氏溫度

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temperature);
    lcd.print("C -> ");

    lcd.print(temperature_clo);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print(humidity);
    lcd.print("%");
    lcd.print(" -> ");
    lcd.print(humidity_clo);
    lcd.print("%");
 
    // 檢查是否需要打開風扇
    if (temperature_clo > 30.0 || humidity_clo > 80.0) {
      digitalWrite(RELAY_PIN, HIGH); // 打開風扇
      FanOn = true;
    } else {
      digitalWrite(RELAY_PIN, LOW); // 關閉風扇
      FanOn = false;
    }
  

///
  WiFiClient client;
  // 使用 80 Port 連線
  client.connect(server, 80); //連接 ThingSpeak.com
  client.print(String("GET ") + resource + apiKey + "&field1=" + temperature + "&field2=" + humidity + 
                  "&field3=" + FanOn +
                  "&field4=" + temperature_clo + "&field5=" + humidity_clo + 
                  " HTTP/1.1\r\n" +
                  "Host: " + server + "\r\n" + 
                  "Connection: close\r\n\r\n"); //將溫濕度及風扇開關等數值寫入 ThingSpeak.com
                  
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!client.available()) {
     Serial.println("No response, going back to sleep");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop();
}

void connect_to_wifi(){
  Serial.println("Wifi Setup");
  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.println("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(3000);
  }
  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
}
/////////////////////////////////////
void setup() {
  Serial.begin(9600);
  lcd.init();             // 初始化LCD
  //lcd.backlight();        // 開啟背光
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");
  dht.begin();            // 啟動DHT11感測器
  dht_clo.begin();        // 啟動衣服間的DHT11
  pinMode(RELAY_PIN, OUTPUT); // 設定蜂鳴器腳位為輸出模式
  connect_to_wifi();
}

void loop() {
  Read_DHT();
  delay(10000);
}