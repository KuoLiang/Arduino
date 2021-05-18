/******** WS2812B 基礎顯示操作實驗 ********/
#include <Adafruit_NeoPixel.h>
#define PIN 32 // WS2812B Din 接腳

int NUMPIXELS=8; // 設定 LED 數量

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin(); // LED 燈條初始化
}

void loop() {
  pixels.clear(); // LED 關閉
  // 設定各 LED 顏色資料
  for(int i=0; i<NUMPIXELS; i++) {
    // pixels.Color(R,G,B)設定 RGB 值，從 0,0,0 至 255,255,255
    // pixels.setPixelColor()設定第 i 顆 LED 顏色
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
  }
  pixels.show(); // 傳送顏色資料至 LED
  delay(100); // 每個循環延遲 100ms
}
