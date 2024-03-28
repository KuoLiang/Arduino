int segments[] = {2, 3, 4, 5, 6, 7, 8}; // 定義連接到七段顯示器各段的 pin
int buttonPin = 9; // 定義按鈕的 pin
int lastButtonState = LOW; // 上次按鈕狀態，用於邊緣檢測
unsigned long lastDebounceTime = 0;  // 上次變化時間
unsigned long debounceDelay = 50;    // 防抖動延遲

void setup() {
  randomSeed(analogRead(0)); // 初始化隨機數發生器
  for(int i = 0; i < 7; i++){
    pinMode(segments[i], OUTPUT); // 設定七段顯示器段落的 pins 為 OUTPUT
  }
  pinMode(buttonPin, INPUT); // 設定按鈕 pin 為 INPUT
}

void loop() {
  int buttonState = digitalRead(buttonPin); // 讀取當前按鈕狀態
  // 檢測按鈕邊緣
  if (buttonState != lastButtonState) {
    lastDebounceTime = millis(); // 重置最後變化時間
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 如果按鈕狀態穩定超過防抖時間，則進行處理
    if (buttonState == LOW && lastButtonState == HIGH) {
      // 隨機選擇一個段落來點亮
      int rndSegment = random(0, 7); // 生成一個在 0 到 6 之間的隨機數
      int totalSteps = 7 * (1 + random(1, 4)); // 總步數 = 7段 * (1到3圈)

      for(int step = 0; step < totalSteps; step++){
        int currentSegment = step % 7; // 當前要點亮的段落

        // 先關閉所有段落
        for(int j = 0; j < 7; j++){
          digitalWrite(segments[j], HIGH);
        }
        
        // 點亮當前段落
        digitalWrite(segments[currentSegment], LOW);

        // 等待一段時間以觀察動畫效果
        delay(100); // 可以根據需要調整這個延遲時間
      }

      // 最後確保隨機選擇的那個段落被點亮
      for(int j = 0; j < 7; j++){
        digitalWrite(segments[j], HIGH);
      }
      digitalWrite(segments[rndSegment], LOW);
      delay(1000); // 讓最後選擇的段落保持
