/*
*  例5-4：透過L9110加上PWM信號，推動馬達正逆轉、及轉速測試
*  以3V正轉2秒、停止1.5秒、3V逆轉2秒，停止1.5秒
*/

const byte MotorA1 = 32;   //輸出至L9110模組A-IA
const byte MotorA2 = 33;   //輸出至L9110模組A-IB

void setup() {
  pinMode(MotorA1, OUTPUT);    //設定接腳為輸出屬性
  pinMode(MotorA2, OUTPUT);

  ledcSetup(0, 5000, 8);        //設定LED PWM功能，通道0，頻率5000Hz，解析度8位元
  ledcAttachPin(MotorA1, 0);    //將PWM通道0連接至 GPIO 接腳 32

  ledcSetup(1, 5000, 8);        //設定LED PWM功能，通道1，頻率5000Hz，解析度8位元
  ledcAttachPin(MotorA2, 1);    //將PWM通道1連接至 GPIO 接腳 33
}

void loop() {
  
  ledcWrite(0, 153);  //通道0 工作週期 153，L9110輸出平均電壓為3V
  ledcWrite(1, 0);    //通道1 工作週期 0，輸出平均電壓0V，馬達以3V慢速正轉
  delay(2000);

  ledcWrite(0, 0);    //通道0 工作週期 0，L9110輸出平均電壓為0V
  ledcWrite(1, 0);    //通道1 工作週期 0，輸出平均電壓0V，兩支接腳的電位差為0V，馬達停止
  delay(1500);

  ledcWrite(0, 0);    //通道0 工作週期 0，L9110輸出平均電壓為0V
  ledcWrite(1, 153);  //通道1 工作週期 153，輸出平均電壓3V，馬達以3V慢速逆轉
  delay(2000);

  ledcWrite(0, 0);    //通道0 工作週期 0，L9110輸出平均電壓為0V
  ledcWrite(1, 0);    //通道1 工作週期 0，輸出平均電壓0V，兩支接腳的電位差為0V，馬達停止
  delay(1500);  
}
