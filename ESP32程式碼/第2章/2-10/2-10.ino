/*
*   例2-10：碰觸輸入測試
*/
void setup() {
  Serial.begin(9600);    //啟動UART傳輸，速率為 9600 bps
}

void loop() {
  Serial.println(touchRead(T5));  //透過序列埠，取得T8接腳的觸摸值
  delay(100);
}
