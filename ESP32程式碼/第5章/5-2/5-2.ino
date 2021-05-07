/*
*  例5-2：利用L9110控制直流馬達正轉3秒，停止0.5秒，反轉3秒，重覆執行
*  本程式動作方式和例5-1完全相同，差別在於採用不同的H橋控制晶片
*/

const byte MotorA1 = 32;   //輸出至 L9110 模組 A-IA
const byte MotorA2 = 33;   //輸出至 L9110 模組 A-IB

void setup() {
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
}

void loop() {
  digitalWrite(MotorA1, HIGH);  //假設為正轉，由馬達接線決定
  digitalWrite(MotorA2, LOW);
  delay(3000);                  //延時3秒，馬達正轉3秒

  digitalWrite(MotorA1, LOW);   //模組不給信號，讓馬達失去電壓不運轉
  digitalWrite(MotorA2, LOW);
  delay(1000);                  //延時1秒，給予馬達停止的時間

  digitalWrite(MotorA1, LOW);   //假設為反轉，由馬達接線決定
  digitalWrite(MotorA2, HIGH);
  delay(3000);                  //延時3秒，馬達反轉3秒

  digitalWrite(MotorA1, LOW);   //模組不給信號，讓馬達失去電壓不運轉
  digitalWrite(MotorA2, LOW);
  delay(1000);                  //延時1秒，給予馬達停止的時間
}
