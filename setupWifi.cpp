#include "secrets.h"
#include "WiFiType.h"
#include "setupWifi.h"

void setupWifi() {
  display.clearDisplay();
  delay(10);
  display.println("Connecting to WiFi...");
  display.display();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned short retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    display.print(".");
    display.display();
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    showWifiConnected();
  } else {
    showWifiNotConnected();
  }

  display.display();
  delay(5000);
}

void showWifiConnected() {
  display.println("");
  display.println("Connected to WiFi."); 
  display.print("IP: ");
  display.println(WiFi.localIP());
  Serial.println("WiFi Connected!");
}

void showWifiNotConnected() {
  display.println("");
  display.println("WiFi not connected.");
  Serial.println("WiFi not connected");
}