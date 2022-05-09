/*
 * 
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos
 * d
 * Created by FILIPEFLOP
 * 
 */
#include <SPI.h>
#include <MFRC522.h>
#include "music.h"
 
#define SS_PIN 5 //it is for select SDAorNSS; 18:SCK ; 23:MOSI ; 19:MISO
#define RST_PIN 32
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(13,OUTPUT); // for buzz  有源
  pinMode(12,OUTPUT); // for tone  無源

  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(13,LOW);
  music();
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  digitalWrite(LED_BUILTIN,HIGH);
  digitalWrite(13,HIGH);

  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


  if (content.substring(1) == "99 A9 E4 6E" || content.substring(1) == "89 8D CE 6E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(1000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(1000);
  }
} 
