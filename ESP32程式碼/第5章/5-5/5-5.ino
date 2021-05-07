/*
*  例5-5：旋轉可變電阻，測試伺服馬達信號上下限、及反應
*/

#include <ESP32Servo.h>  //引用函式庫

Servo myServo;     //建立伺服馬達物件，名稱為 myServo

const byte servoPin = 33;    //使用 GPIO33 作為信號輸出
const byte VR = 32;          //使用 GPIO32 作為可變電阻之信號輸入
short val;                   //可變電阻之類比讀值儲存處

void setup() {
  pinMode(servoPin, OUTPUT);
  pinMode(VR, INPUT);
  Serial.begin(9600);
  myServo.setPeriodHertz(50); //50hz代表信號週期為20ms
  myServo.attach(servoPin);   //連接伺服馬達物件
}

void loop() {
  val = analogRead(VR);                //讀取可變電阻的數位值(0到4095)
  val = map(val, 0, 4095, 500, 2500);  //轉換到500到2500之間
  Serial.print(val);                   //印出目前數位值
  Serial.println("us");                //印出單位
  myServo.writeMicroseconds(val);      //驅動到伺服馬達
  delay(200);                          //稍作等待讓馬達反應
}
