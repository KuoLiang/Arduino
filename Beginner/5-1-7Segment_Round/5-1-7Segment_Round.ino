// 定義連接到七段顯示器的腳位
const int segmentPins[] = {3, 4, 5, 6, 7, 8}; // 假設這些是外圍LED的連接腳位
const int buttonPin = 2; // 按鈕連接的腳位
int buttonState = 0; // 按鈕的狀態
int lastButtonState = 0; // 最後一次讀取的按鈕狀態
bool startSequence = false; // 是否開始點亮LED的序列
unsigned long lastLEDChangeTime = 0; // 上一次改變LED狀態的時間
const long interval = 500; // LED改變的間隔時間，以毫秒計
int currentLED = -1; // 當前亮起的LED，初始為-1表示沒有LED亮

void setup() {
  // 初始化七段顯示器的腳位為輸出
  for (int i = 0; i < 6; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], HIGH); // 將所有LED先設置為熄滅狀態（共陰極配置）
  }
  
  // 初始化按鈕腳位為輸入
  pinMode(buttonPin, INPUT);
}

void loop() {
  // 讀取按鈕的狀態
  int reading = digitalRead(buttonPin);
  
  // 檢查按鈕是否被按下（從未按到按）
  if (reading != lastButtonState) {
    if (reading == HIGH) {
      startSequence = true;
      lastLEDChangeTime = millis(); // 重置計時器
      currentLED = -1; // 重置當前LED
    }
  }
  lastButtonState = reading; // 更新按鈕狀態
  
  // 如果啟動了LED點亮序列
  if (startSequence) {
    unsigned long currentMillis = millis();
    
    // 檢查是否達到了點亮下一個LED的時間
    if (currentMillis - lastLEDChangeTime >= interval) {
      lastLEDChangeTime = currentMillis; // 保存當前時間
      
      // 移到下一個LED
      currentLED = (currentLED + 1) % 6;
      
      // 先將所有LED熄滅
      for (int i = 0; i < 6; i++) {
        digitalWrite(segmentPins[i], HIGH); // 共陰極配置，設為HIGH熄滅
      }
      
      // 然後點亮當前的LED
      digitalWrite(segmentPins[currentLED], LOW); // 共陰極配置，設為LOW點亮
      
      // 如果所有LED都已經點亮過，結束序列
      if (currentLED == 5) {
        startSequence = false;
      }
    }
  }
}
