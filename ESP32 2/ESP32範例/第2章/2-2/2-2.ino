/*
* 例2-2：LED 跑馬燈，具來回掃瞄功能
*/
const byte LED[] = {4, 0, 2, 15};   //宣告陣列，內容為各接腳編號

void setup() {
  for (byte i = 0; i <= 3; i++) {   //從0掃瞄到3
    pinMode(LED[i], OUTPUT);        //接腳設定為輸出
  }
}

void loop() {
  for (byte i = 0; i <= 3; i++) {   //從0掃瞄到3
    digitalWrite(LED[i], HIGH);     //點亮
    delay(300);                     //維持0.3秒
    digitalWrite(LED[i], LOW);      //熄滅
  }
  for (byte i = 3; i >= 0; i--) {        //從3掃瞄到0
    digitalWrite(LED[i], HIGH);     //點亮
    delay(300);                     //維持0.3秒
    digitalWrite(LED[i], LOW);      //熄滅
  }
}
