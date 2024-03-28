const int buttonPin = 8; // 按鈕連接到pin 8
const int leds[] = {2, 3, 4, 5, 6, 7}; // 七段顯示器外圍LED的腳位
const int debounceDelay = 50; // 按鈕去抖動的延遲時間（毫秒）
int buttonState; // 目前按鈕狀態
int lastButtonState = LOW; // 上一次按鈕狀態
unsigned long lastDebounceTime = 0; // 上次觸發去抖動的時間
int pressCount = 0; // 按鈕按壓次數
bool isOdd = false; // 是否為奇數按壓
int currentLed = 0; // 目前點亮的LED索引
unsigned long lastLedChangeTime = 0; // 上次LED變化的時間
const long ledInterval = 100; // LED切換間隔時間（毫秒）

void setup() {
  pinMode(buttonPin, INPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH); // 共陽型，初始化為關閉狀態
  }
}

void loop() {
  int reading = digitalRead(buttonPin);

  // 按鈕去抖動機制
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        pressCount++;
        isOdd = pressCount % 2 != 0;
        if (!isOdd) {
          // 如果按壓次數為偶數，停止在當前LED
          for (int i = 0; i < 6; i++) {
            digitalWrite(leds[i], i == currentLed ? LOW : HIGH); // 關閉所有LED，除了當前的
          }
        }
      }
    }
  }
  lastButtonState = reading;

  // LED控制邏輯，無阻塞
  if (isOdd && (millis() - lastLedChangeTime >= ledInterval)) {
    // 關閉目前的LED
    digitalWrite(leds[currentLed], HIGH); 
    // 計算下一個LED的索引
    currentLed = (currentLed + 1) % 6;
    // 點亮下一個LED
    digitalWrite(leds[currentLed], LOW); 
    lastLedChangeTime = millis();
  }
}
