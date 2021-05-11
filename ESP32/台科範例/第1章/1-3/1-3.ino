/*
*   例1-3：透過序列埠控制LED亮滅。
*   當從序列埠收到1時，點亮LED；收到0時，熄滅LED
*/
const byte LEDPin = 4;
char data;                   //宣告變數名稱：data，資料型別：char
void setup() {
  pinMode(LEDPin,OUTPUT);    //將接腳設定為輸出
  Serial.begin(9600);        //啟動序列傳輸，速度 9600 bps
}

void loop() {
  if (Serial.available()) {     //如果序列緩衝區有資料
    data = Serial.read();       //從緩衝區讀取一個字元
    if (data == '1') {
      Serial.println("點亮LED");
      digitalWrite(LEDPin, HIGH);
    } else if (data == '0') {
      Serial.println("熄滅LED");
      digitalWrite(LEDPin, LOW);
    }
  }
}
