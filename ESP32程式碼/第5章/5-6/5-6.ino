/*
*  例5-6：測試直流伺服馬達，將你從上一個範例得到的參數值，套用到第13行中
*  若為定位型馬達，會在0度到180度之間擺動
*  若為連續旋轉型馬達，會在逆轉、停、正轉之間改變
*/

#include <ESP32Servo.h>     //引用函式庫

Servo myServo;              //建立伺服馬達物件，名稱為myServo
byte pos = 0;               //儲存伺服馬達位置

void setup() {
  myServo.attach(33, 500, 2500);  //伺服馬達信號由第33腳輸出
}

void loop() {
  for (pos = 0; pos <= 180; pos++) {          //從0度到180度
    myServo.write(pos);    //下指令給伺服馬達，轉至變數pos所指的位置
    delay(15);             //等待15ms讓伺服馬達轉至該處
  }
  for (pos = 180; pos >= 0; pos--) { //從180度到0度
    myServo.write(pos);    //下指令給伺服馬達，轉至變數pos所指的位置
    delay(15);             //等待15ms讓伺服馬達轉至該處
  }
}
