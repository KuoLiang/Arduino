/*  
*  例2-6：讀取類比電壓，輸出相對的數值
*/
const byte anaPin = 25;      //採用 GPIO 25 作類比輸入腳
short val;                   //宣告變數為短整數，名稱為：val
void setup() {
  Serial.begin(9600);
  pinMode(anaPin, INPUT);
}
void loop() {
  val = analogRead(anaPin);   //讀取類比輸入，並轉換為數位值
  Serial.println(val);
  delay(100);
}
