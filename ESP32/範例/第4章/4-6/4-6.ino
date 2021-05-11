#define buzzerPin 2 //蜂鳴器接至GPIO2

const int ledChannel = 0;   //PWM頻道為0
const int resolution = 10;  //解析度為10位元
const int Tone[6] =  {262,294,330,349,392,440};     //音階頻率
//小蜜蜂樂譜
const byte melody[] = {5,3,3,4,2,2,1,2,3,4,5,5,5,5,3,3,4,2,2,1,3,5,5,3,2,2,2,2,2,3,4,3,3,3,3,3,4,5,5,3,3,4,2,2,1,3,5,5,1};
//小蜜蜂節拍
const byte beats[]={1,1,2,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1,1,4};
//const byte melody[]={1,1,5,5,6,6,5,4,4,3,3,2,2,1,5,5,4,4,3,3,2,5,5,4,4,3,3,2,1,1,5,5,6,6,5,4,4,3,3,2,2,1};
//const byte beats[]={1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,2};
const int tempo=333;   //每分鐘180拍，1拍時間=333毫秒
void setup() {
  pinMode(buzzerPin,OUTPUT);
  ledcAttachPin(buzzerPin, ledChannel);   //PWM頻道0由GPIO2輸出PWM波形
}

void loop() {
  for(int i=0;i<sizeof(beats);i++)  {
    tone(Tone[melody[i]-1],beats[i]*tempo);   //傳送音階頻率與節拍
  }
  ledcWrite(ledChannel, 0);     //關閉聲音
  delay(1000);    //關閉1秒
}

void tone(int frequency, int duration)
{
   ledcSetup(ledChannel, frequency, resolution);    //設定頻道0、頻率為10000Hz、解析度為10位元的PWM波形
   ledcWrite(ledChannel, 512);   //PWM波形工作週期為50%
   delay(duration);   //節拍時間，每拍333毫秒
}
