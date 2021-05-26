/*
*  例5-1：利用L298N控制直流馬達正轉3秒，停止0.5秒，反轉3秒，重覆執行
*/
const byte MotorA1 = 32;   //輸出至 L298N 模組 IN1
const byte MotorA2 = 33;   //輸出至 L298N 模組 IN2

void setup() {
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
}

void loop() {
  digitalWrite(MotorA1, HIGH);  //假設為正轉
  digitalWrite(MotorA2, LOW);
  delay(3000);                  //延時3秒，馬達正轉3秒

  digitalWrite(MotorA1, LOW);   //模組不給信號，讓馬達失去電壓不運轉
  digitalWrite(MotorA2, LOW);
  delay(1000);                  //延時1秒，給予馬達停止的時間

  digitalWrite(MotorA1, LOW);   //假設為反轉
  digitalWrite(MotorA2, HIGH);
  delay(3000);                  //延時3秒，馬達反轉3秒

  digitalWrite(MotorA1, LOW);   //模組不給信號，讓馬達失去電壓不運轉
  digitalWrite(MotorA2, LOW);
  delay(1000);                  //延時1秒，給予馬達停止的時間
}
