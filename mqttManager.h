#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "sensorManager.h"

void setupMqttClient();
void loopMqttClient();
void tryReconnect();
void tryPublishUpdates();

#endif