
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // Crea un oggetto display con l'indirizzo I2C (tipicamente 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 4
#define DHTTYPE DHT22

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long prevMqttUpdateMillis = 0;
const unsigned long mqtt

unsigned long prevReadMillis = 0;
const unsigned long delayReadMS = 2000;

float hum = 0;  //Variabile in cui verrà inserita la % di umidità  
float temp = 0; //Variabile in cui verrà inserita la temperatura
float minTemp = 1000, maxTemp = -1000;
float minHum = 1000, maxHum = -1000;

DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(9600);
  // initialize dht sensor
  dht.begin();

  setupDisplay();
  setupWifi();
  // setup mqtt server
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  tryReconnect();
  client.loop();

  updateReadValues();

  display.clearDisplay();
  displayTempHum();
  displayMinTempHum();
  displayMaxTempHum();
  display.display();

  tryPublishUpdates();

  delay(500);
}

void setupDisplay() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(1);      // Dimensione testo
  display.setTextColor(SSD1306_WHITE); // Colore testo
}

void setupWifi() {
  display.clearDisplay();
  delay(10);
  display.println("Connecting to WiFi...");
  display.display();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }

  display.println("");
  display.println("Connected to WiFi."); 
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  delay(5000);
}

void tryReconnect() {
  if (client.connected()) {
    return;
  }

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // client.subscribe("your/topic"); // optional
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void updateReadValues() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevReadMillis >= delayReadMS) {
    prevReadMillis = currentMillis;
    // read humidity and temperature
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (temp < minTemp) minTemp = temp;
    if (temp > maxTemp) maxTemp = temp;

    if (hum < minHum) minHum = hum;
    if (hum > maxHum) maxHum = hum;
  }
}

void displayTempHum() {
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(temp);
  display.print(" C");

  display.setCursor(0,10);
  display.print("Humidity: ");
  display.print(hum);
  display.print(" %");

  display.drawLine(0, 20, display.width() - 1, 20, SSD1306_WHITE);
}

void displayMinTempHum() {
  display.setCursor(0, 23);
  display.print("Min Temp: ");
  display.print(minTemp);
  display.print(" C");

  display.setCursor(0, 33);
  display.print("Min Hum: ");
  display.print(minHum);
  display.print(" %");

  display.drawLine(0, 43, display.width() - 1, 43, SSD1306_WHITE);
}

void displayMaxTempHum() {
  display.setCursor(0, 46);
  display.print("Max Temp: ");
  display.print(maxTemp);
  display.print(" C");

  display.setCursor(0, 56);
  display.print("Max Hum: ");
  display.print(maxHum);
  display.print(" %");
}

void tryPublishUpdates() {
  if (!client.connected()) {
    return;
  }

  unsigned long now = millis();
  if (now - prevMqttUpdateMillis > delayReadMS) {
    prevMqttUpdateMillis = now;
    // Convert the value to a char array
    char tempString[8];
    dtostrf(temp, 1, 2, tempString);
    client.publish("esp32/temperature", tempString);
    // Convert the value to a char array
    char humString[8];
    dtostrf(hum, 1, 2, humString);
    client.publish("esp32/humidity", humString);
  }
}
