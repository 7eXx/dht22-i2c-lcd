#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>

void setupMqttClient();
void loopMqttClient();
void tryReconnect();
void tryPublishUpdates();

#endif