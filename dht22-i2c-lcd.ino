
#include "displayManager.h"
#include "setupWifi.h"
#include "sensorManager.h"
#include "mqttManager.h"

void setup() {
  Serial.begin(9600);
  // initialize dht sensor
  dhtBegin();

  setupDisplay();
  setupWifi();
  setupMqttClient();
}

void loop() {
  tryReconnect();
  loopMqttClient();

  updateReadValues();
  renderDisplay();

  tryPublishUpdates();

  delay(500);
}
