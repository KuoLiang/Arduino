/*
*   例5-7：利用2個可變電阻，同時操作2個伺服馬達
*   可用於伺服馬達輸出接腳：2,4,5,12-19,21-23,25-27,32-33
*/
#include <ESP32Servo.h>     //引用函式庫
const byte servo1 = 33;     //伺服馬達1接腳
const byte servo2 = 32;     //伺服馬達2接腳
const byte VR1 = 17;        //可變電阻1
const byte VR2 = 16;        //可變電阻2
int pos = 0;                //儲存伺服馬達位置

Servo myServo1;     //建立伺服馬達物件，名稱為 myServo1
Servo myServo2;     //建立伺服馬達物件，名稱為 myServo2

void setup() {
  myServo1.attach(servo1);  //伺服馬達1信號由第33腳輸出
  myServo2.attach(servo2);  //伺服馬達2信號由第32腳輸出
  pinMode(VR1, INPUT);
  pinMode(VR2, INPUT);
}

void loop() {
  int data1 = analogRead(VR1);          //讀取第一個可變電阻值
  data1 = map(data1, 0, 4095, 0, 180);  //轉換為0到180度
  myServo1.write(data1);                //輸出至伺服馬達1
  delay(15);                            //等待15ms讓伺服馬達轉至該處

  int data2 = analogRead(VR2);          //讀取第二個可變電阻值
  data2 = map(data2, 0, 4095, 0, 180);  //轉換為0到180度
  myServo2.write(data2);                //輸出至伺服馬達2
  delay(15);                            //等待15ms讓伺服馬達轉至該處
}
