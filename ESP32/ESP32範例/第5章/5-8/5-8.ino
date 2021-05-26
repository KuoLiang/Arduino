/*
*   例5-8：從ESP32的接腳傳送信號，利用ULN2003模組控制單極性步進馬達 28BYJ-48
*   旋轉方向：順時針   
*/

const byte pin1 = 32;      //定義接腳編號
const byte pin2 = 33;
const byte pin3 = 25;
const byte pin4 = 26;
const byte delayTime = 2;  //必要的延遲，讓馬達的轉子足夠反應，走到定位

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
}

void loop() {
  digitalWrite(pin4, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, HIGH);   //高態經過晶片轉換後，會得到低態，電流由COM腳流入線圈
  delay(delayTime);

  digitalWrite(pin4, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, LOW);
  delay(delayTime);
  
  digitalWrite(pin4, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, LOW);
  delay(delayTime);
  
  digitalWrite(pin4, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, HIGH);
  delay(delayTime);
  }
