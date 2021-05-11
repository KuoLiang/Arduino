#include <PN532_HSU.h>
#include <PN532.h>
      
PN532_HSU pn532hsu(Serial2);
PN532 nfc(pn532hsu);

void setup() {
  Serial.begin(9600);

  nfc.begin();

  int versiondata = nfc.getFirmwareVersion();   //取得韌體版本
  if (! versiondata) {                //未發現NFC PN532模組
    Serial.print("Didn't find PN53x board");
    while (1); 
  }
  
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX);    //取得NFC晶片型號
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);      //取得NFC模組韌體版本
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  
  //設定讀取卡片重試最大次數，0xFF為不斷嘗試
  nfc.setPassiveActivationRetries(0xFF);
  
  nfc.SAMConfig();      //配置模組讀取RFID標籤
    
  Serial.println("Waiting for an ISO14443A card");
}

void loop() {
  int success;
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  //用來儲存返回的UID
  byte uidLength;                        // UID長度變數
  //成功取得UID與UID長度後，success=1，否則為0
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");       
    Serial.print(uidLength, DEC);     //以十進制形式顯示UID長度
    Serial.println(" bytes");
    Serial.print("  UID Value: ");
    for(int i=0;i<uidLength;i++)
    {
      Serial.print(" 0x");
      Serial.print(uid[i],HEX);       //以十六進制形式顯示UID
    }
    Serial.println("");
       
    uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    
    //使用KeyA作為驗證，驗證成功返回值為1，反之，則為0
    success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);
   
    if (success)
    {
      Serial.println("Block has been authenticated");
      byte writeData[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                          0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16};   //欲寫入的資料
      byte readData[16];   //用來儲存讀取資料    

      success = nfc.mifareclassic_WriteDataBlock (4, writeData);    //寫入block4
              
      if (success)
      {
        Serial.println("Have written successful.");
        delay(1000);
      }
      else
      {
        Serial.println("unable to write the requested block.  Try another key?");
      }

      success = nfc.mifareclassic_ReadDataBlock(4, readData);
      if(success)                           //讀取成功
      {
        Serial.println("Reading Block 4:");
        for(int i=0;i<16;i++) {
          Serial.print(" 0x");
          Serial.print(readData[i],HEX);
      }
        Serial.println("");
        while(nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength));  //等待卡片移開
      }
      else      //讀取失敗
      {
        Serial.println("unable to read the requested block.  Try another key?"); 
      }
    }
    else        //驗證失敗
    {
      Serial.println("authentication failed: Try another key?");
    }
  }   
}
