#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <time.h>

#define SCREEN_WIDTH 128 // 設定OLED螢幕的寬度像素
#define SCREEN_HEIGHT 64 // 設定OLED螢幕的寬度像素
#define OLED_RESET     -1 // Reset pin 如果OLED上沒有RESET腳位，將它設置為-1

//OLED顯示器使用I2C連線並宣告名為display物件
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid       = "AP名稱";
const char* password   = "AP密碼";

const char* ntpServer = "pool.ntp.org";    //NTP Server網址 
const long  gmtOffset_sec = 28800;         //台灣為GMT+8小時，8hrs=28800sec
const int   daylightOffset_sec = 0;       //日光節約時間為0

bool OLEDStatus = true;

static const unsigned char PROGMEM str_1[]={    //現
0x00,0x08,0x01,0xFC,0xFD,0x08,0x11,0x08,0x11,0xF8,0x11,0x08,0x11,0x08,0x7D,0xF8,
0x11,0x08,0x11,0x08,0x11,0xF8,0x1D,0x48,0xF0,0xA0,0x41,0x22,0x02,0x22,0x0C,0x1E  
};
static const unsigned char PROGMEM str_2[]={    //在
0x02,0x00,0x02,0x00,0x02,0x04,0xFF,0xFE,0x04,0x00,0x04,0x40,0x08,0x40,0x08,0x48,
0x13,0xFC,0x30,0x40,0x50,0x40,0x90,0x40,0x10,0x40,0x10,0x44,0x17,0xFE,0x10,0x00
};
static const unsigned char PROGMEM str_3[]={    //時
0x00,0x20,0x04,0x20,0x7E,0xF8,0x44,0x20,0x44,0x20,0x45,0xFC,0x44,0x10,0x7C,0x10,
0x47,0xFE,0x44,0x10,0x44,0x90,0x44,0x50,0x7C,0x50,0x44,0x10,0x00,0x50,0x00,0x20
};
static const unsigned char PROGMEM str_4[]={    //間
0x00,0x08,0x7C,0xFC,0x44,0x88,0x7C,0xF8,0x44,0x88,0x7C,0xF8,0x40,0x08,0x4F,0xC8,
0x48,0x48,0x4F,0xC8,0x48,0x48,0x4F,0xC8,0x48,0x48,0x40,0x08,0x40,0x28,0x40,0x10
};

void setup() {
  Serial.begin(115200);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // 設定位址為0x3c
    Serial.println(F("SSD1306 allocation failed")); //F(字串)：將字串儲存在flash並非在RAM
    OLEDStatus = false;     //開啟OLED失敗
  }
  
  Serial.printf("Connecting to %s ", ssid);     //顯示連線AP SSID
  WiFi.begin(ssid, password);       //建立WiFi連線
  while (WiFi.status() != WL_CONNECTED) {     //等待WiFi連線
      delay(5000);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);   //設定NTP參數
}

void loop() {
  struct tm timeinfo;   //建立一個時間結構，稱為timeinfo
  if(!getLocalTime(&timeinfo)){   //取回NTP時間
    Serial.println("Failed to obtain time");    //若失敗，顯示"失敗訊息"
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");   //顯示"星期，月日年，時:分:秒"
  if(OLEDStatus==true) {
    display.clearDisplay();     //清除螢幕
    display.setTextSize(2);     //設定字型大小為2
    display.setCursor(4,0);     //設定文字起始位置為(4,0)
    display.setTextColor(WHITE, BLACK);   //設定白字黑底
    display.println(&timeinfo, "%F");     //設定文字內容為年月日，格式為"西元年-月-日"
    display.setCursor(24,16);     //設定文字起始位置為(24,16)
    display.println(&timeinfo, "%A");   //設定文字內容為星期，格式為"Mondy Tuesday..."
    
    display.drawBitmap(0,32,str_1,16,16,WHITE);     //現，位置(0,32)，字型大小16*16，顏色白色
    display.drawBitmap(18,32,str_2,16,16,WHITE);    //在，位置(18,32)，字型大小16*16，顏色白色
    display.drawBitmap(36,32,str_3,16,16,WHITE);    //時，位置(36,32)，字型大小16*16，顏色白色
    display.drawBitmap(54,32,str_4,16,16,WHITE);    //間，位置(54,32)，字型大小16*16，顏色白色
    
    display.setCursor(16,48);     //設定文字起始位置為(16,48)
    display.println(&timeinfo, "%T");     //設定文字內容為年月日，格式為"時:分:秒"
    display.display();        //顯示所設定的文字
  }
  delay(1000);    //延遲1秒
}
