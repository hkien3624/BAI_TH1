#include <DHT.h>

#define DHTPIN 5      // Chân DATA nối với GPIO 4
#define DHTTYPE DHT11 // Chọn loại cảm biến

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("Doc cam bien DHT11...");
  dht.begin();
}

void loop() {
  delay(2000); // DHT11 đọc mỗi ~2s

  float h = dht.readHumidity();
  float t = dht.readTemperature();      // °C
  float tf = dht.readTemperature(true); // °F

  if (isnan(h) || isnan(t)) {
    Serial.println("Loi doc DHT11!");
    return;
  }

  Serial.print("Do am: ");
  Serial.print(h);
  Serial.print(" %\t");

  Serial.print("Nhiet do: ");
  Serial.print(t);
  Serial.print(" °C\t");

  Serial.print(tf);
  Serial.println(" °F");
}
