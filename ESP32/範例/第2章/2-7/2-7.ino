/*  
 *   例2-7：將讀取出來的數位值，推算回類比電壓量
*/
const byte anaPin = 25;   //採用 GPIO 25 作類比輸入腳
short val;                //宣告變數為短整數，名稱為：val
float voltage;            //原始輸入的電壓，因為會用到小數，所以用float宣告

void setup() {
  Serial.begin(9600);
  pinMode(anaPin, INPUT);
}
void loop() {
  val = analogRead(anaPin);    //讀取類比接腳，並轉換為數位值
  voltage = 3.3 * val / 4096;  //計算電壓值
  Serial.print(voltage, 3);    //顯示計算出來的電壓值，顯示到小數第3位
  Serial.println("V");         //顯示V字樣，為電壓單位
  delay(100);
}
