/*
*   例2-11：使用碰觸輸入，切換 LED 亮滅
*/
const byte LEDPin = 4;
void setup() {
  Serial.begin(9600);      //啟動 UART 傳輸，速率為 9600 bps
  pinMode(LEDPin,OUTPUT);
}

void loop() {
  delay(100);                   //稍作延遲
  if(touchRead(T5)>30)          //如果碰觸輸入值大於30
    digitalWrite(LEDPin,HIGH);  //點亮LED
  else                          //如果沒有大於30
    digitalWrite(LEDPin,LOW);   //熄滅LED
}
