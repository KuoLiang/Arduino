/*
*   例1-2：開啟序列埠傳輸功能，透過序列埠傳送Hello World出去
*/
void setup() {
  Serial.begin(9600);   //傳輸速率為 9600 bps
}

void loop() {
  Serial.println("Hello World");  //透過序列埠傳送字串"Hello World"
  delay(1000);                    //延時1秒鍾（1000ms）
}
