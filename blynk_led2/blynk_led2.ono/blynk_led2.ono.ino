/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */

#define BLYNK_TEMPLATE_ID "t_id"
#define BLYNK_TEMPLATE_NAME "t_name"
#define BLYNK_AUTH_TOKEN "your_token"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "your_ssid";
char pass[] = "your_wifi_password";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes

BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  Blynk.virtualWrite(V1, value);

  // Update state
  //Blynk.virtualWrite(V1, value);
  if(value == 1)
    digitalWrite(2,HIGH);
  else
    digitalWrite(2,LOW);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  //Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  //Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  //Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  int light = analogRead(36);   //讀取光敏電阻值
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V3, light); //寫入V3
  Serial.println(light);          //顯示數值
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(36,INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

