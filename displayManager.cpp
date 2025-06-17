#include "displayManager.h"
#include "sensorManager.h"
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay(Adafruit_SSD1306 &display) {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
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

void renderDisplay() {
  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(getTemperature());
  display.print(" C");

  display.setCursor(0, 10);
  display.print("Humidity: ");
  display.print(getHumidity());
  display.print(" %");

  display.drawLine(0, 20, display.width() - 1, 20, SSD1306_WHITE);

  display.setCursor(0, 23);
  display.print("Min Temp: ");
  display.print(getMinTemperature());
  display.print(" C");

  display.setCursor(0, 33);
  display.print("Min Hum: ");
  display.print(getMinHumidity());
  display.print(" %");

  display.drawLine(0, 43, display.width() - 1, 43, SSD1306_WHITE);

  display.setCursor(0, 46);
  display.print("Max Temp: ");
  display.print(getMaxTemperature());
  display.print(" C");

  display.setCursor(0, 56);
  display.print("Max Hum: ");
  display.print(getMaxTemperature());
  display.print(" %");

  display.display();
}
