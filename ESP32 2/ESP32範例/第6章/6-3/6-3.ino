/* 
 *  例6-3 SHARP灰塵感測器測試
 */
const byte ledPower = 25;   //接至感測器的第3腳 
const byte dustPin = 33;    //接至感測器的第5腳
float dustVal, result;      //灰塵量讀取值，轉換後的結果
       
void setup() {
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);   //點亮感測器LED接腳
}

void loop() {
  //灰塵感測器模組取樣週期開始
  digitalWrite(ledPower, LOW);
  delayMicroseconds(280);
  dustVal = analogRead(dustPin);
  delayMicroseconds(40);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(9680);
  //取樣週期結束

  Serial.print("\n類比讀值(0-4095)：");
  Serial.println(dustVal);              //ESP32得到的類比值

  Serial.print("參照規格書，灰塵密度為：");
  int result = map(dustVal, 670, 2531, 70, 430);   //轉換數值範圍為灰塵密度
  Serial.print(result);
  Serial.println(" ug/m^3");

  delay(2000);
}
