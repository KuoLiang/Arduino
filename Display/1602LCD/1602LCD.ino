
/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <LiquidCrystal_I2C.h> // Library for LCD

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println("LCD1602 test");
  // 初始化
}

void loop() {

  delay(1000);
  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
  lcd.print("I am 1602 LCD"); 
  lcd.setCursor(0, 1); // Set the cursor on the third column and first row.
  lcd.print("Good"); 
  lcd.print(" Morning"); 
}
