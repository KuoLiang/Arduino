/*
*   例5-11：使用 stepper 函式庫，控制單極性步進馬達28BYJ-48
*/

#include <Stepper.h>     //引用函式庫

const byte pin1 = 32;    //定義接腳編號
const byte pin2 = 33;
const byte pin3 = 25;
const byte pin4 = 26;

//為了修正此馬達接線和函式庫相異處，須將 pin2 及 pin3 互換位置
Stepper myStepper(2048, pin1, pin3, pin2, pin4);  //初始化馬達

void setup() {
  myStepper.setSpeed(10);  //指定轉速為10rpm
}

void loop() {
  myStepper.step(2048);    //順時針旋轉2048步，馬達轉一圈
  delay(500);

  myStepper.step(-500);    //逆時針旋轉500步
  delay(500);
}
