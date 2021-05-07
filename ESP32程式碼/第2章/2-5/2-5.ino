/* 
*  例2-5：延續例2-4的程式，並解決開關彈跳
   
*/
const byte LEDPin = 4, input = 36;
byte button = 0;    //宣告變數，資料型別為byte，記錄按鈕狀態
void setup() {
  pinMode(input, INPUT);
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  if (digitalRead(input) == false) {   //如果偵測到按鈕低電位
    delay(20);                         //延時20ms，避開開關彈跳時間
    if (digitalRead(input) == false) { //如果按鈕還是低電位，代表真的有按下開關
      button = 1;                      //標記開關按下
    }
  } else {               //如果按鈕回復高電位，不認定為按下開關
    button = 0;          //標記開關沒按
  }

  if (button == 1) {             //如果開關按下
    digitalWrite(LEDPin, HIGH);  //點亮LED
  }
  if (button == 0) {             //如果開關放開
    digitalWrite(LEDPin, LOW);   //關閉LED
  }
}
