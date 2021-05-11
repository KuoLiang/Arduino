/* 
* 例6-2：依據溫、溼度切換風扇開關
*/
#include "DHTesp.h"                          //引用函式庫

DHTesp dht;                                  //宣告物件，名字為 dht
const byte dhtPin = 17, LED = 0, SSR = 19;   //GPIO 17 接收溫溼度，GPIO 0推動LED，GPIO 19推動SSR

void setup() {
  dht.setup(dhtPin, DHTesp::DHT11);   //若使用DHT22，則把DHT11改為DHT22
  pinMode(LED, OUTPUT);               //LED接腳設定為輸出
  pinMode(SSR, OUTPUT);               //驅動光耦合器
}
void loop() {
  TempAndHumidity lastValues = dht.getTempAndHumidity();   //取得溫溼度值
  if(lastValues.temperature >= 28){    //如果溫度大於等於28
    digitalWrite(LED, HIGH);           //點亮LED
    digitalWrite(SSR, HIGH);           //驅動電風扇
}
  else if(lastValues.temperature < 27) {  //如果溫度小於27
    digitalWrite(LED, LOW);               //熄滅LED
    digitalWrite(SSR, LOW);               //關閉電風扇
}
  delay(2000);
}
