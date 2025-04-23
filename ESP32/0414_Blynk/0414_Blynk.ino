/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6iIa5HjkZ"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "22L_P2IlIlcoeHteTBw77S5Sh9hqUpbG"


/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <WiFi.h>
#include <BlynkSimpleWifi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "1111";
char pass[] = "11111111";

BlynkTimer timer;

// LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2); // 設定LCD I2C地址為0x27，16個字符，2行

// 蜂鳴器
#define BUZZER_PIN 8       // 蜂鳴器連接到Arduino Pin 8
#define DHTPIN 9           // DHT11的數據腳位連接到Arduino Pin 9
#define DHTTYPE DHT22      // 使用的DHT型號
DHT dht(DHTPIN, DHTTYPE);

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  digitalWrite(13,value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  dht.begin();
  lcd.init();                      // 初始化LCD
  lcd.backlight();                 // 打開背光
  pinMode(BUZZER_PIN, OUTPUT);     // 設定蜂鳴器腳位為輸出模式

}

void get_DHT22()
{
    // 讀取溫度和濕度
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature(); // 讀取攝氏溫度

  // 檢查是否讀取失敗，如果失敗，就打印錯誤消息
  if (isnan(humidity) || isnan(tempC)) {
    lcd.setCursor(0, 1);
    lcd.print("Failed to read!");
    return;
  }

  // 在LCD上顯示溫度和濕度
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  
  Blynk.virtualWrite(V4, tempC);
  Blynk.virtualWrite(V2, humidity);

  // 判斷是否需要啟動蜂鳴器
  if (humidity > 85 || tempC > 30) {
    digitalWrite(BUZZER_PIN, HIGH);  // 打開蜂鳴器
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // 關閉蜂鳴器
  }

  //delay(2000);  // 等待2秒
}
void loop()
{
  Blynk.run();
  timer.run();
  get_DHT22();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
