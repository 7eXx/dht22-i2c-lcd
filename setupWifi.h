#ifndef SETUP_WIFI_H
#define SETUP_WIFI_H

#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <secrets.h>
#include <displayManager.h>

void setupWifi();
void showWifiConnected();
void showWifiNotConnected();

#endif
