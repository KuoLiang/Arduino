#include "WiFi.h"
void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);//STA Mode, others are  WIFI_AP、WIFI_AP_STA、WIFI_OFF
    WiFi.disconnect();//初始化
}

void loop(){
    Serial.println("Scanning ...");
    int n = WiFi.scanNetworks();//The # of wifi ap scanned
    Serial.println("AP List :");
    if (n == 0) {
        Serial.println("No Wifi there");
    } else {
        Serial.print(n);
        Serial.println(" Wifi AP Found");
        for (int i = 0; i < n; ++i) {       //SSID, RSSI, 加密
            Serial.print(i + 1); // start by 1 for showing, indexed by 0
            Serial.print(": ");
            Serial.print(WiFi.SSID(i)); // ssid
            Serial.print(" : ");
            Serial.print(WiFi.RSSI(i)); // signal
            Serial.print(" : ");
            Serial.println(WiFi.encryptionType(i));
            delay(10);
            /*
               encryptionType 0:WIFI_AUTH_OPEN
                encryptionType 1:WIFI_AUTH_WEP
                encryptionType 2:WIFI_AUTH_WPA_PSK
                encryptionType 3:WIFI_AUTH_WPA2_PSK
                encryptionType 4:WIFI_AUTH_WPA_WPA2_PSK
                encryptionType 5:WIFI_AUTH_WPA2_ENTERPRISE
                encryptionType 6:WIFI_AUTH_MAX
             */
        }
    }
    Serial.println("");
    delay(5000);
}
