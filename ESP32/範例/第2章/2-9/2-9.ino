/*
*  例2-9：呼吸燈，LED 會由暗漸亮，再由亮漸暗，有如人類呼吸之韻律
*/
const byte LEDPin = 0;  //由 GPIO 0 輸出 PWM 信號

// 設定 PWM屬性
const int frequency = 5000;     //頻率 5000Hz
const int ledChannel = 0;       //使用 LED PWM 第 0 個通道
const int resolution = 8;       //解析度為 8 位元
const byte LEDIntensity = 80;   //LED 的最高亮度，依需求更改 0 至 255

void setup() {
  ledcSetup(ledChannel, frequency, resolution);   //設定LED PWM功能
  ledcAttachPin(LEDPin, ledChannel);              //將 PWM 功能連接至 GPIO 接腳
}

void loop() {
  for (byte i = 0; i <= LEDIntensity; i++) {     //遞增LED亮度
    ledcWrite(ledChannel, i);       //更改PWM的工作週期，以改變LED亮度
    delay(25);
  }
 
  for (byte j = LEDIntensity; j > 0; j--) {      //遞減LED亮度
    ledcWrite(ledChannel, j);       //更改PWM的工作週期，以改變LED亮度
    delay(25);
  }
   delay(300);       //讓LED熄滅久一點，減少亮暗切換的頓挫感
}
