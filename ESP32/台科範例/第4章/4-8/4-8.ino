/******** 利用可變電阻改變 LED 亮燈數 ********/
#include <Adafruit_NeoPixel.h>
#define PIN 32 // WS2812B Din 接腳
#define SliderPIN 33 // 可變電阻類比電位輸入腳

int NUMPIXELS=8; // 設定 LED 數量
int preColorVal = 0, nowColorVal = 0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pixels.begin(); // LED 燈條初始化
  preColorVal = analogRead(SliderPIN)/511;
  NUMPIXELS = preColorVal;
  WS2812SHOW();
  delay(100);
}

void loop() {
  nowColorVal = analogRead(SliderPIN)/511;
  if(nowColorVal != preColorVal) // 當可變電阻有變化時，才更新 LED 資料
  {
    preColorVal = nowColorVal;
    if(nowColorVal!=8)
      NUMPIXELS=8-nowColorVal;
    else
      NUMPIXELS=0;
  WS2812SHOW();
  }
  // 傳送顏色資料至 LED
  delay(1); // 每個循環延遲 1ms
}

void WS2812SHOW() {
  pixels.clear(); // LED 關閉
  // 設定各 LED 顏色資料
  for(int i=0; i<NUMPIXELS; i++) {
    // pixels.Color(R,G,B)設定 RGB 值，從 0,0,0 至 255,255,255
    // pixels.setPixelColor()設定第 i 顆 LED 顏色
    pixels.setPixelColor(i, pixels.Color(255, 255, 0));
  }
  pixels.show(); // 傳送顏色資料至 LED
}
