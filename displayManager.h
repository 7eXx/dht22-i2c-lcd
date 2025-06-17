#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void setupDisplay(Adafruit_SSD1306 &display);
void renderDisplay();

#endif
