#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  dht.begin();

  Wire.begin(21, 22);     // SDA, SCL ESP32
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("DHT11 Ready");
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  

  lcd.clear();
  lcd.setCursor(0, 0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Loi doc DHT11!");
    return;
    lcd.print("Loi doc DHT11!");

  }
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C");

  Serial.print("Do am: ");
  Serial.print(h);
  Serial.print(" % | ");

  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.println(" C");
}
