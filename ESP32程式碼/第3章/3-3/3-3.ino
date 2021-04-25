/*  
*   例3-3：兩個ESP32透過藍牙互相傳遞訊息
*   建立藍牙客戶端，和例3-1的藍牙模組連線，持續傳送文字1、0，讓對方藍牙模組的LED閃爍
*/

#include "BluetoothSerial.h"    //引用藍牙函式庫
BluetoothSerial myBT;           //建立藍牙物件

//變數及常數設定
const String slaveBT = "BT:01";   //對方藍牙的名字，請改為和你配對的同學藍牙名字
const char *PIN = "1234";         //預設的PIN碼，也有可能是0000
bool connected;                   //儲存是否已連線的狀態

void setup() {
  Serial.begin(9600);
  //myBT.setPin(PIN);            //指定其他的PIN碼使用此指令
  myBT.begin("masterBT",true);   //啟動藍牙，並開啟為Master模式
  Serial.println("藍牙已啟動，進入Master模式");
  Serial.println("連線中...");

  connected = myBT.connect(slaveBT);  //連到另一個ESP32的藍牙
  
  if(connected)                       //如果已連線
    Serial.println("連線成功!");
}

void loop() {
  myBT.print('1');  //傳送字元1，對方接收到會點亮LED
  delay(300);
  myBT.print('0');  //傳送字元0，對方接收到會熄滅LED
  delay(300);
}
