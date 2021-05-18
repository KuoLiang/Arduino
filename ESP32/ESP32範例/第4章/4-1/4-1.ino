/********0~9上數計數器，每隔一秒加1********/
const byte _7SegCode[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
const byte _7SegPin[8] = {12,14,27,26,25,33,32,13};   //字節對應GPIO腳位，依序為a b c d e f g dp

void setup() {
  Serial.begin(9600);
  for(int i=0;i<8;i++) {
    pinMode(_7SegPin[i], OUTPUT);
  }

}

void loop() {
  for(int cnt=0;cnt<10;cnt++) {
    for(int seg=0;seg<8;seg++)  {
      digitalWrite(_7SegPin[seg], (_7SegCode[cnt] >> seg) & 0x01);
    }
    delay(1000);
  }

}
