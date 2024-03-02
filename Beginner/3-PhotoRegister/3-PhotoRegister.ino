//ChatGPT 4.0 @ 2024/3/2
//請設計一個由光敏電阻數值控制LED是否點亮的程式碼，光亮度大於500時點亮LED，小於等於500時熄滅LED
// 定義光敏電阻和LED的連接腳位
const int photoResistorPin = A0; // 將光敏電阻連接到模擬輸入A0
const int ledPin = 13;           // 將LED連接到數位輸出13

void setup() {
  pinMode(ledPin, OUTPUT);       // 設定LED腳位為輸出模式
  Serial.begin(9600);            // 啟動序列通訊，用於監控光敏電阻的數值
}

void loop() {
  int lightLevel = analogRead(photoResistorPin); // 讀取光敏電阻的數值
  Serial.println(lightLevel);                    // 將光敏電阻的數值輸出到序列監控器

  // 判斷光照亮度，並根據亮度控制LED燈的狀態
  if (lightLevel < 500) {
    digitalWrite(ledPin, HIGH);   // 如果光照亮度大於500，點亮LED
  } else {
    digitalWrite(ledPin, LOW);    // 如果光照亮度小於或等於500，熄滅LED
  }

  delay(200); // 稍作延遲，以便於觀察變化
}
