#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Địa chỉ I2C thường là 0x27 hoặc 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin(21, 22);  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("B22DCDT156");

  lcd.setCursor(0, 1);
  lcd.print("Hoang Trung Kien");
}

void loop() {
}
