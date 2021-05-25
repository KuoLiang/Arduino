/*
*  例5-3：透過L9110加上PWM信號，推動馬達單向運轉
*  輸出5V共2秒、輸出4V共2秒、輸出3V共2秒、停止
*/

const byte MotorA1 = 32;   //輸出至L9110模組A-IA
const byte MotorA2 = 33;   //輸出至L9110模組A-IB

void setup() {
  pinMode(MotorA1, OUTPUT);     //設定接腳為輸出屬性
  pinMode(MotorA2, OUTPUT);

  ledcSetup(0, 5000, 8);        //設定LED PWM功能，通道0，頻率5000Hz，解析度8位元
  ledcAttachPin(MotorA1, 0);    //將PWM通道0連接至 GPIO 接腳 32

  ledcSetup(1, 5000, 8);        //設定LED PWM功能，通道1，頻率5000Hz，解析度8位元
  ledcAttachPin(MotorA2, 1);    //將PWM通道1連接至 GPIO 接腳 33
}

void loop() {
  ledcWrite(0, 255);  //通道0 工作週期 255，L9110輸出平均電壓為5V
  ledcWrite(1, 0);    //通道1 工作週期 0，輸出平均電壓0V，兩支接腳的電位差5V
  delay(2000);

  ledcWrite(0, 204);  //通道0 工作週期 204，L9110輸出平均電壓為4V
  ledcWrite(1, 0);    //通道1 工作週期 0，輸出平均電壓0V，兩支接腳的電位差4V
  delay(2000);

  ledcWrite(0, 153);  //通道0 工作週期 153，L9110輸出平均電壓為3V
  ledcWrite(1, 0);    //通道1 工作週期 0，輸出平均電壓0V，兩支接腳的電位差3V
  delay(2000);
}
