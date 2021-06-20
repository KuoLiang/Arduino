
HardwareSerial myHardwareSerial(1); //ESP32可宣告需要一個硬體序列，軟體序列會出錯

void setup_music()
{
    lcd.setCursor(0, 1);
    lcd.print("Reading MP3"); 
    myHardwareSerial.begin(9600, SERIAL_8N1, 10, 9); // Serial的TX,RX
    myDFPlayer.begin(myHardwareSerial);//將DFPlayer播放器宣告在HardwareSerial控制
    delay(500);
    myDFPlayer.volume(15);  //設定聲音大小（0-30）
    lcd.clear();
    myDFPlayer.stop();
}
