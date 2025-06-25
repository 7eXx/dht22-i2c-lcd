#include "mqttManager.h"
#include "sensorManager.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "mosquitto.raspi-home";
const int mqtt_port = 1883;

unsigned long prevMqttConnectionMillis = 0;
const unsigned long mqttConnectionMillis = 5000;
unsigned long prevMqttUpdateMillis = 0;
const unsigned long mqttUpdateDelayMs = 3000;

void setupMqttClient() {
  // setup mqtt server
  client.setServer(mqtt_server, mqtt_port);
}

void loopMqttClient() {
  // looping connection
  client.loop();
}

void tryReconnect() {
  // wifi not connected
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }
  // broken already connected
  if (client.connected()) {
    return;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - prevMqttConnectionMillis > mqttConnectionMillis) {
    prevMqttConnectionMillis = currentMillis;
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // client.subscribe("your/topic"); // optional
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying next time...");
    }
  }
}

void tryPublishUpdates() {
  // wifi is not connected
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }
  // broker mqtt not connected
  if (!client.connected()) {
    return;
  }

  unsigned long now = millis();
  if (now - prevMqttUpdateMillis > mqttUpdateDelayMs) {
    prevMqttUpdateMillis = now;
    // Convert the value to a char array
    char tempString[8];
    dtostrf(getTemperature(), 1, 2, tempString);
    client.publish("esp32/temperature", tempString);
    // Convert the value to a char array
    char humString[8];
    dtostrf(getHumidity(), 1, 2, humString);
    client.publish("esp32/humidity", humString);
  }
}
