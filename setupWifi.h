
#include "config.h"

void setupWifi(Adafruit_SSD1306 display) {
  display.clearDisplay();
  delay(10);
  display.println("Connecting to WiFi...");
  display.display();
  WiFi.begin(ssid, password);

  unsigned short retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    display.print(".");
    display.display();
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    display.println("");
    display.println("Connected to WiFi."); 
    display.print("IP: ");
    display.println(WiFi.localIP());
    Serial.println("WiFi Connected!");
  } else {
    display.println("");
    display.println("WiFi not connected.");
    Serial.println("WiFi not connected");
  }
  
  display.display();
  delay(5000);
}