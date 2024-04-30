#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 9          // DHT22接在Arduino的9號腳位
#define DHTTYPE DHT22     // 使用DHT22型號
#define BUZZER_PIN 8      // 蜂鳴器接在Arduino的8號腳位

DHT dht(DHTPIN, DHTTYPE);

// 初始化LCD，設定I2C地址為0x27，16列2行
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();             // 初始化LCD
  lcd.backlight();        // 開啟背光
  dht.begin();            // 啟動DHT22感測器
  pinMode(BUZZER_PIN, OUTPUT); // 設定蜂鳴器腳位為輸出模式
}

void loop() {
  // 讀取濕度和溫度值
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // 預設讀取攝氏溫度

  // 檢查讀取是否成功
  if (isnan(humidity) || isnan(temperature)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Failed to read");
    lcd.setCursor(0, 1);
    lcd.print("from DHT sensor!");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");

    // 檢查是否需要發聲警報
    if (temperature > 30.0 || humidity > 85.0) {
      digitalWrite(BUZZER_PIN, HIGH); // 打開蜂鳴器
    } else {
      digitalWrite(BUZZER_PIN, LOW); // 關閉蜂鳴器
    }
  }
  delay(2000);  // 更新間隔2秒
}
