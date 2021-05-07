/*  Woody 輔助板測試，可測試下列功能：
*    1、程式上傳後，全部 LED 會熄滅。依序按上、下、左、右按鈕，會有對應的 LED 亮。
*    2、開啟序列埠監控視窗，設定速率：9600 bps，碰觸 Touch 5 或 Touch 4，會顯示碰觸前後的讀取值
*    3、從第19腳以1秒為間隔高/低變化，可利用杜邦線接至光耦合輸入，測試光耦合功能
*    
*    開發板生產廠商眾多，接腳順位不徑相同，本程式以 NodeMCU 32S 以及 Goouuu-esp32 為使用版本
*/
unsigned long lastTime; //時間戳記
bool stat;              //第19腳電位狀態

void setup() {
  Serial.begin(9600);
  pinMode(36, INPUT);     //按鈕「右」
  pinMode(39, INPUT);     //按鈕「上」
  pinMode(34, INPUT);     //按鈕「左」
  pinMode(35, INPUT);     //按鈕「下」
  pinMode(4, OUTPUT);     //LED D1
  pinMode(0, OUTPUT);     //LED D2
  pinMode(2, OUTPUT);     //LED D3
  pinMode(15, OUTPUT);    //LED D4
  pinMode(19, OUTPUT);    //輸出閃爍
}

void loop() {
  if (digitalRead(39) == LOW) //由於本輔助板之按鈕接成上拉電阻（提升電阻），因此按鈕按下時是低態
    digitalWrite(4, HIGH);    //如果偵測到低態，代表按鈕按下，輔助板的D1亮
  else
    digitalWrite(4, LOW);

  if (digitalRead(35) == LOW) //按輔助板的「下」按鈕
    digitalWrite(0, HIGH);    //輔助板的D2亮
  else
    digitalWrite(0, LOW);

  if (digitalRead(34) == LOW) //按輔助板的「左」按鈕
    digitalWrite(2, HIGH);    //輔助板的D3亮
  else
    digitalWrite(2, LOW);

  if (digitalRead(36) == LOW) //按輔助板的「右」按鈕
    digitalWrite(15, HIGH);   //輔助板的D4亮
  else
    digitalWrite(15, LOW);

  Serial.print("Touch 5 讀值為：");
  Serial.print(touchRead(T5));
  Serial.print(", Touch 4 讀值為：");
  Serial.println(touchRead(T4));

  if (millis() - lastTime >= 1000) {   //第19腳狀態切換
    digitalWrite(19, stat);
    stat = !stat;
    lastTime = millis();
  }
}
