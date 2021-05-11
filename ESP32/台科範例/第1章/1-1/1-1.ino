/*
*  例1-1：透過 GPIO 4 點亮 LED，每隔一秒閃爍一次
*/
const byte LEDPin = 4;     //定義LED使用第4腳

void setup(){
  pinMode(LEDPin, OUTPUT); //設定為輸出模式
}

void loop() {
  digitalWrite(LEDPin, HIGH); //輸出高電位
  delay(1000);                //延時一秒
  digitalWrite(LEDPin, LOW);  //輸出低電位
  delay(1000);                //延時一秒
}
