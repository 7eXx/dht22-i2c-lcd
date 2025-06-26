#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "sensorManager.h"

extern Adafruit_SSD1306 display;

void setupDisplay();
void renderDisplay();

#endif
