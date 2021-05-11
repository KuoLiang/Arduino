/*
*   例5-10：從ESP32的接腳送信號，控制單極性步進馬達28BYJ-48
*   激磁方式：半步進
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
  digitalWrite(pin4, LOW);  //半步激磁的原理，就是1相、2相、1相、2相
  digitalWrite(pin3, LOW);  //以此類推
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, HIGH);
  delay(delayTime);

  digitalWrite(pin4, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, HIGH);
  delay(delayTime);

  digitalWrite(pin4, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, LOW);
  delay(delayTime);

  digitalWrite(pin4, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, LOW);
  delay(delayTime);

  digitalWrite(pin4, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, LOW);
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
  digitalWrite(pin1, LOW);
  delay(delayTime);

  digitalWrite(pin4, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, HIGH);
  delay(delayTime);
  }
