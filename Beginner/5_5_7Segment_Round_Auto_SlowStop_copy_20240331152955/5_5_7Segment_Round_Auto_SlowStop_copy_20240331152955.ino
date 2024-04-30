// ChatGPT 4.0 @ 2024/3/30
/* 請提供 Arduino 程式，其中pin3,pin4,pin5,pin6,pin7,pin8分別接LED，其電壓為LOW時為點亮，電壓為HIGH時熄滅，
同時， pin 2 接一個按鈕接下拉電阻，並等待使用者按下按鈕後啟動以下動作：
對使用者按下按鈕的動作進行編號，並以序列埠顯示目前的編號值，
若編號值為奇數，則分別以100ms時間間隔不停止地循環點亮pin3至pin8的6顆LED，
並且在點亮每個LED前檢查使用者是否有按下按鈕，直到使用者按下按鈕的編號為偶數時進行slowStop的程序。
在進行 slowStop時，先取得一個12至18之間的亂數並命名為the_final，
並由100ms漸漸增加時間間隔循環點亮共the_final個LED，最後一個被點亮的LED與前一個被點亮的LED時間間隔不超過300ms，
且最後一個被點亮的LED保持每秒3次的時間問隔閃爍，
並保持閃爍的狀態，等待使用者再次按下按鈕時，則繼續執行上述編號為奇數或偶數的程序
*/

const int buttonPin = 5; // for esp32 按鈕連接到pin 5
const int ledPins[] = {17,18,19,21,22,23}; // for ESP32 七段顯示器外圍LED的腳位

// 定義LED與按鈕的引腳

const int numLeds = 6;

// 變數宣告
int buttonState = 0;        
int lastButtonState = 0;    
int current_index=0;
int last_index=0;
unsigned long lastDebounceTime = 1; 
unsigned long debounceDelay = 50;   
int actionCount = 1;        
bool isActionOdd = true;   
void checkButton();
void oddAction();
void slowStop();
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); 
  for(current_index = 0; current_index < numLeds; current_index++) {
    pinMode(ledPins[current_index], OUTPUT);
    digitalWrite(ledPins[current_index], HIGH); // 預設狀態為熄滅
  }
  while(!digitalRead(buttonPin)){;}
  delay(500);
}

void loop() {
  int reading = digitalRead(buttonPin);
    checkButton(); 
    if(isActionOdd) {
      oddAction();
    } else {
      slowStop();
    }

  lastButtonState = reading;
}

void oddAction() {
  while(isActionOdd) {
    for(current_index = current_index % numLeds; current_index < numLeds && isActionOdd; current_index++) {
      checkButton();
      digitalWrite(ledPins[current_index], LOW); // 點亮LED
      delay(50);
      digitalWrite(ledPins[current_index], HIGH); // 熄滅LED
    }
  }
}

void slowStop() {
  int the_final = random(12, 19); // 生成12至18之間的亂數
  int delayTime = 100;
  for(int j = current_index; j < the_final; j++) {
    checkButton();
    digitalWrite(ledPins[j % numLeds], LOW);
    delay(delayTime);
    digitalWrite(ledPins[j % numLeds], HIGH);
    
    if (delayTime < 300) {
      delayTime += 20; // 漸漸增加時間間隔
    }
    last_index = j;
  }
  
  // 最後一個LED保持閃爍
  while(!isActionOdd) {
    checkButton();
    digitalWrite(ledPins[(the_final - 1) % numLeds], LOW);
    delay(167); // 每秒閃爍3次
    digitalWrite(ledPins[(the_final - 1) % numLeds], HIGH);
    delay(167);
  }
}

void checkButton() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        actionCount++;
        isActionOdd = (actionCount % 2) != 0;
      }
    }
  }
  lastButtonState = reading;
  //Serial.println(isActionOdd); // 顯示當前的編號值  
}
