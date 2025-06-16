
#define SCREEN_ADDRESS 0x3C // Crea un oggetto display con l'indirizzo I2C (tipicamente 0x3C)

void setupDisplay(Adafruit_SSD1306 display) {
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