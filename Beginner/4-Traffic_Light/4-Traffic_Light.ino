// ChatGPT 4.0 @ 2024/3/2
// 請以Arduino 設計一個由三個LED模擬交通號誌紅黃綠是否點亮的程式碼，紅燈及綠燈分別點亮10秒，中間的黃燈點亮三秒
// 需定義LED連接的Arduino板上的腳位
const int redLED = 10;    // 紅色LED連接到數位腳位10
const int yellowLED = 9;  // 黃色LED連接到數位腳位9
const int greenLED = 8;   // 綠色LED連接到數位腳位8

void setup() {
  // 初始化每個腳位為輸出模式
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  // 綠燈亮起10秒
  digitalWrite(greenLED, HIGH);
  delay(10000); // 10000毫秒 = 10秒

  // 綠燈熄滅
  digitalWrite(greenLED, LOW);

  // 黃燈亮起3秒
  digitalWrite(yellowLED, HIGH);
  delay(3000); // 3000毫秒 = 3秒

  // 黃燈熄滅
  digitalWrite(yellowLED, LOW);

  // 紅燈亮起10秒
  digitalWrite(redLED, HIGH);
  delay(10000); // 10000毫秒 = 10秒

  // 紅燈熄滅，然後循環重新開始
  digitalWrite(redLED, LOW);
}
