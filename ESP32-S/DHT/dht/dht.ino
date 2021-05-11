#include <analogWrite.h>
#include "DHT.h"

DHT dht(14, DHT11 ); // Initialize DHT sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  pinMode(14,INPUT);
  pinMode(36,INPUT);
  dht.begin();//啟動DHT
}

void loop() {
  // put your main code here, to run repeatedly:
  int level = analogRead(36);
  analogWrite(4,level);
  Serial.println(level);
  go_DHT();
}

void go_DHT()
{
  float h = dht.readHumidity();//讀取濕度
  float t = dht.readTemperature(false);//讀取攝氏溫度
  float f = dht.readTemperature(true);//讀取華氏溫度
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("無法從DHT傳感器讀取！");
    //return;
  }
  Serial.print("濕度: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("攝氏溫度: ");
  Serial.print(t);
  Serial.print("*C\t");
  Serial.print("華氏溫度: ");
  Serial.print(f);
  Serial.print("*F\n");
  delay(1000);//延時1秒
}
