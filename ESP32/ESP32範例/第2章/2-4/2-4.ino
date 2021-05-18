/*  例2-4：採用提升電阻電路作輸入。
    計數按鈕次數，當按下2次，才點亮LED
*/
int count = 0;        //宣告變數，用來計算按鈕次數
const byte LEDPin = 4, input = 36;   //LED 接於 GPIO 4；按鈕接於 GPIO 36

void setup() {
  pinMode(input, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  if (digitalRead(input) == false) {  //如果偵測到按鈕低電位，代表按鈕按下
    count = count + 1;                //計數值加1
    if (count == 2) {                 //如果按鈕按了2下
      digitalWrite(LEDPin, HIGH);     //點亮LED
      count = 0;                      //清除計數值，以便重新計算
    } else {
      digitalWrite(LEDPin, LOW);      //關閉LED
    }
  }
}
