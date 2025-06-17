#include "sensorManager.h"
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float hum = 0, temp = 0;
float minTemp = 1000, maxTemp = -1000;
float minHum = 1000, maxHum = -1000;
unsigned long prevReadMillis = 0;
const unsigned long readDelayMs = 2000;

void dhtBegin() {
  dht.begin();
}

void updateReadValues() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevReadMillis >= readDelayMs) {
    prevReadMillis = currentMillis;
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (temp < minTemp) minTemp = temp;
    if (temp > maxTemp) maxTemp = temp;
    if (hum < minHum) minHum = hum;
    if (hum > maxHum) maxHum = hum;
  }
}

float getTemperature() { return temp; }
float getHumidity() { return hum; }
float getMinTemperature() { return minTemp; }
float getMaxTemperature() { return maxTemp; }
float getMinHumidity() { return minHum; }
float getMaxHumidity() { return maxHum; }
