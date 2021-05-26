/*
* 例2-1：LED 跑馬燈（LED Marquee）
*/

const byte LED[] = {4, 0, 2, 15};  //宣告陣列，內容為各接腳編號

void setup() {
  for (byte i = 0; i <= 3; i++) { //從0掃瞄到3
    pinMode(LED[i], OUTPUT);      //這些接腳設定為輸出
  }
}

void loop() {
  for (byte i = 0; i <= 3; i++) { //從0掃瞄到3
    digitalWrite(LED[i], HIGH);   //點亮
    delay(300);                   //維持0.3秒
    digitalWrite(LED[i], LOW);    //熄滅
  }
}
