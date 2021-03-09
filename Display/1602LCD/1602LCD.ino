#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4


/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float tempc=0;
float tempf=0;
void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  Serial.println("Temperature Sensor");
  // 初始化
  sensors.begin();
}

void loop() {


  sensors.requestTemperatures();
  tempc = sensors.getTempCByIndex(0);
  tempf = sensors.getTempFByIndex(0);
  Serial.println(tempc);
  delay(1000);
  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
  lcd.print("Water Temperature"); 
  lcd.setCursor(0, 1); // Set the cursor on the third column and first row.
  lcd.print(tempc);
  lcd.print(" C  "); 
  lcd.print(tempf);
  lcd.print(" F"); 
}
