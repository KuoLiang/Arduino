/*  
*  例2-3：採用提升電阻作為輸入電路，驅動LED輸出
*/

const byte LEDPin = 4;     //LED 接於 GPIO 4
void setup() {
  pinMode(36, INPUT);      //GPIO 36 作為輸入
  pinMode(LEDPin, OUTPUT); //LED 腳作為輸出
}

void loop() {
  if (digitalRead(36) == false) {   //如果偵測到按鈕低電位，代表按鈕按下
    digitalWrite(LEDPin, HIGH);     //點亮LED
  } else {
    digitalWrite(LEDPin, LOW);      //關閉LED
  }
}
