/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

#define ledPin  2

#define RECV_PIN  25    //紅外線接收腳位綁定ESP32 GPIO25
unsigned int recvData;

IRrecv irrecv(RECV_PIN);    //宣告一個名為irrecv的物件，並綁定接收腳位

decode_results results;     //宣告一個名為results的物件

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();    //開始接收
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {      //接收數據並解碼
    recvData = results.value;         //解碼後數據
    Serial.println(recvData, HEX);    //將數據顯示於序列埠
    if(recvData == 0xFF30CF)
      digitalWrite(ledPin, HIGH);
    else if(recvData == 0xFF18E7)
      digitalWrite(ledPin, LOW);
    irrecv.resume();        //繼續接收下一筆資料
  }
  delay(100);
}
