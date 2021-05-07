/********模擬電話鈴聲********/
#define buzzerPin 2         //蜂鳴器接至GPIO2
const int pwmChannel = 0;   //PWM頻道為0~15
const int resolution = 10; //解析度可選1~15位元

void setup() {
  pinMode(buzzerPin,OUTPUT);
  ledcAttachPin(buzzerPin, pwmChannel);   //PWM頻道0由GPIO2輸出PWM波形
}

void loop() {
  for(int i=0;i<10;i++) {
    ledcSetup(pwmChannel, 1000, resolution);     //設定頻道0、頻率為10000Hz、解析度為10位元的PWM波形
    ledcWrite(pwmChannel, 512);     //PWM波形工作週期為50%
    delay(50);      //頻率1000Hz的方波輸出維持50ms
    ledcSetup(pwmChannel, 500, resolution);     //設定頻道0、頻率為500Hz、解析度為10位元的PWM波形
    ledcWrite(pwmChannel, 512);     //PWM波形工作週期為50%
    delay(50);      //頻率500Hz的方波輸出維持50ms
  }
  ledcWrite(pwmChannel, 0);       //關閉聲音
  delay(2000);      //聲音關閉2秒鐘
}
