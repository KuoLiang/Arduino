/* 
*  例3-2：ESP32讀取可變電阻的類比信號，傳送到手機
*/

#include "BluetoothSerial.h" //引用藍牙函式庫

BluetoothSerial myBT;        //建立藍牙物件，名稱叫作myBT

char incomeData;             //接收資料用的變數

void setup() {
 myBT.begin("BT:01");        //定義此藍牙的名字，01換成你的座號
}

void loop() {
  if (myBT.available()) {       //如果藍牙模組收到資料
    incomeData = myBT.read();   //將資料讀出

    if (incomeData == 49) {     //如果是ASCII碼49，等於字元"1"，代表收到手機的索取信號
      myBT.print("pin 36 analog reading is: ");  //回傳訊息給手機
      myBT.println(analogRead(36));              //回傳類比讀值給手機
    }
  }
}
