const int segmentPins[] = {3, 4, 5, 6, 7, 8}; // 假設這些是外圍LED的連接腳位
const int buttonPin = 2; // 按鈕連接的腳位
int buttonState = 0; // 按鈕的當前狀態
int lastButtonState = 0; // 最後一次讀取的按鈕狀態
bool isSequenceActive = false; // LED點亮序列是否激活
unsigned long lastDebounceTime = 0; // 最後抖動的時間
unsigned long debounceDelay = 50; // 抖動延遲時間，以毫秒計
unsigned long lastLEDChangeTime = 0; // 最後一次改變LED狀態的時間
int currentLED = 0; // 當前亮起的LED
const long ledInterval = 500; // LED變化的間隔時間，以毫秒計

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], HIGH); // 先將所有LED熄滅
  }
  pinMode(buttonPin, INPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == HIGH) {
        // 如果按鈕被按下，切換LED序列的激活狀態
        isSequenceActive = !isSequenceActive;
        if (isSequenceActive) {
          // 重置LED序列
          currentLED = 0;
          lastLEDChangeTime = millis();
          for (int i = 0; i < 6; i++) {
            digitalWrite(segmentPins[i], HIGH); // 先熄滅所有LED
          }
          digitalWrite(segmentPins[currentLED], LOW); // 開始點亮第一個LED
        } else {
          // 停止LED序列時，熄滅所有LED
          for (int i = 0; i < 6; i++) {
            digitalWrite(segmentPins[i], HIGH);
          }
        }
      }
    }
  }
  
  lastButtonState = reading;
  
  // 如果LED序列激活，則自動依序點亮LED
  if (isSequenceActive && (millis() - lastLEDChangeTime >= ledInterval)) {
    // 移動到下一個LED
    digitalWrite(segmentPins[currentLED], HIGH); // 熄滅當前LED
    currentLED = (currentLED + 1) % 6;
    digitalWrite(segmentPins[currentLED], LOW); // 點亮下一個LED
    lastLEDChangeTime = millis(); // 更新時間
    
    // 如果完成一圈，停止序列
    if (currentLED == 0) {
      isSequenceActive = false;
      for (int i = 0; i < 6; i++) {
        digitalWrite(segmentPins[i],HIGH); // 完成一圈後熄滅所有LED
      }
    }
  }
}