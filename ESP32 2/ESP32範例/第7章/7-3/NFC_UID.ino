#include <PN532_HSU.h>
#include <PN532.h>
      
PN532_HSU pn532hsu(Serial2);
PN532 nfc(pn532hsu);

void setup() {
  Serial.begin(9600);
  nfc.begin();
  int versiondata = nfc.getFirmwareVersion();    //取得韌體版本
  if (! versiondata) {            //未發現NFC PN532模組
    Serial.print("Didn't find PN53x board");    
    while (1);
  }
  
  Serial.print("Found chip PN5");
  Serial.println((versiondata>>24) & 0xFF, HEX);  //取得NFC模組型號
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);   //取得NFC模組韌體版本
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  
  //設定讀取卡片重試最大次數，0xFF為不斷嘗試
  nfc.setPassiveActivationRetries(0xFF);
  
  nfc.SAMConfig();  //配置模組讀取RFID標籤
    
  Serial.println("Waiting for an ISO14443A card");
}

void loop(void) {
  int success;
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // 用來儲存返回的UID
  byte uidLength;               // UID長度變數  

  //成功取得UID與UID長度後，success=1，否則為0
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
  
  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: ");
    Serial.print(uidLength, DEC);    //以十進制形式顯示UID長度
    Serial.println(" bytes");
    Serial.print("UID Value: ");    
    for (uint8_t i=0; i < uidLength; i++) 
    {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);  //以十六進制形式顯示UID
    }
    delay(1000);  //等待1秒之後繼續
  }
  else
  {
    Serial.println("Timed out waiting for a card");  //超時等待，未讀取到卡片
  }
}
