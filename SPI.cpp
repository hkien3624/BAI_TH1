#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#include <TFT_eSPI.h>
#include <SPI.h>

/* ===== DHT11 ===== */
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* ===== LCD I2C ===== */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ===== TFT SPI ===== */
TFT_eSPI tft = TFT_eSPI();

unsigned long lastRead = 0;

void setup() {
  Serial.begin(115200);

  /* DHT */
  dht.begin();

  /* I2C LCD */
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.print("DHT11 Ready");

  /* TFT */
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop() {
  if (millis() - lastRead >= 2000) {
    lastRead = millis();

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Loi doc DHT11!");
      return;
    }

    /* ===== LCD I2C ===== */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("H:");
    lcd.print(h);
    lcd.print("%");

    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(t);
    lcd.print("C");

    /* ===== TFT SPI ===== */
    tft.fillScreen(TFT_BLACK);

    tft.drawCentreString("DHT11 SENSOR", 80, 5, 2);

    tft.drawCentreString("Humidity", 80, 30, 2);
    tft.drawFloat(h, 1, 50, 45, 6);
    tft.drawString("%", 110, 45, 4);

    tft.drawCentreString("Temperature", 80, 80, 2);
    tft.drawFloat(t, 1, 50, 95, 6);
    tft.drawString("C", 110, 95, 4);

    /* ===== Serial ===== */
    Serial.print("Do am: ");
    Serial.print(h);
    Serial.print(" % | ");

    Serial.print("Nhiet do: ");
    Serial.print(t);
    Serial.println(" C");
  }
}
