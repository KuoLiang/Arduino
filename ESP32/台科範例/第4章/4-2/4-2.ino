/********0~9999上數計數器********/
const byte _7SegCode[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};  //數字0~9字型碼
const byte _7SegPin[8] = {12,14,27,26,25,33,32,13};   //字節對應GPIO腳位，依序為a b c d e f g dp
const byte _7ComPin[4] = {19,18,5,17};                //com1->19,com2->18,com3->5,com4->17   
const byte com[4][4]={{0,0,0,1},      //com4正常工作，其餘off
                      {0,0,1,0},      //com3正常工作，其餘off
                      {0,1,0,0},      //com2正常工作，其餘off
                      {1,0,0,0}};     //com1正常工作，其餘off
int thous, hund, tens, units;

void setup() {
  for(int i=0;i<8;i++) {
    pinMode(_7SegPin[i], OUTPUT);     //設定ESP32 GPIO為輸出
  }
  for(int x=0;x<4;x++)  {
    pinMode(_7ComPin[x], OUTPUT);     //設定ESP32 GPIO為輸出
  }
}

void loop() {
  for(int cnt=0;cnt<10000;cnt++) {
    thous = cnt/1000;     //取出千位數
    hund = cnt%1000/100;  //取出百位數
    tens = cnt%100/10;    //取出十位數
    units = cnt%10;       //取出個位數
    byte Value[4] = {units, tens, hund, thous};   //顯示順序為個位->十位->百位->千位
    for(int scan=0;scan<4;scan++) {       //com1~4掃描碼
      for(int j=0;j<4;j++)  {
        digitalWrite(_7ComPin[j], com[scan][j]);    //分別寫入com1~4
      }
      for(int seg=0;seg<8;seg++)  {       //七段顯示器顯示數字      
        digitalWrite(_7SegPin[seg], (_7SegCode[Value[scan]] >> seg) & 0x01);
    }
    delay(2);
    }
  }
}
