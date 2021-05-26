/* 
*   例3-1：手機透過藍牙控制ESP32
*   使用手機的藍牙終端機軟體（Bluetooth Terminal），連到ESP32的藍牙，控制LED亮滅
*/

#include "BluetoothSerial.h" //引用藍牙函式庫

BluetoothSerial myBT;        //建立藍牙物件，名稱叫作myBT
char incomeData;             //接收資料用的變數
const byte LED = 2;          //外接LED

void setup() {
  Serial.begin(9600);
  myBT.begin("BT:01");       //定義此藍牙的名字，01換成你的座號
  pinMode (LED, OUTPUT);
}

void loop() {
  if (myBT.available()) {         //如果藍牙模組收到資料
    incomeData = myBT.read();     //將資料讀出
    Serial.print("從藍牙收接到：");
    Serial.println(incomeData);   //從序列埠印出手機傳來的字元

    if (incomeData == '1') {      //如果接收到字元'1'
      digitalWrite(LED, HIGH);    //點亮LED
      myBT.println("LED turned ON");   //回傳訊息給手機
    }

    if (incomeData == '0') {           //如果接收到字元'0'
      digitalWrite(LED, LOW);          //熄滅LED
      myBT.println("LED turned OFF");  //回傳訊息給手機
    }
  }
  delay(20);
}
