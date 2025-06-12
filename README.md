# DHT22 with I2C Display on ESP32
This project demonstrates how to read temperature and humidity data from a DHT22 sensor and display it on an I2C OLED display using an ESP32 microcontroller.

## Components Required
- ESP32 development board
- DHT22 temperature and humidity sensor
- I2C OLED display (e.g., SSD1306)
- Jumper wires
- Breadboard (optional)
- Power supply (USB or battery)

## Circuit Diagram
![Circuit Diagram](./dht22-i2c-lcd_bb.png)

## Libraries Required
- `Adafruit_Sensor` for sensor data handling
- `DHT` for DHT22 sensor
- `Wire` for I2C communication
- `Adafruit_GFX` for graphics support
- `Adafruit_SSD1306` for OLED display