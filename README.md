README: IoT Weather Monitoring with DHT11, OLED Display, and ThingSpeak

Overview

This project is a weather monitoring system using a DHT11 sensor for temperature and humidity measurements, an SSD1306 OLED display for local visualization, and ThingSpeak for cloud-based data logging. The system connects to Wi-Fi for real-time data uploading.

Features

1.Temperature and Humidity Sensing:
  * Uses the DHT11 sensor to measure ambient temperature and humidity.
  * Computes the heat index based on sensor readings.
2.Data Visualization:
  * Displays sensor data (temperature, humidity, and heat index) on a 128x64 OLED display.
3.Cloud Integration:
  * Sends data to ThingSpeak for remote monitoring and analysis.
4.Wi-Fi Connectivity:
  *Connects to a specified Wi-Fi network for internet-based data logging.

Hardware Requirements

1.ESP32 or ESP8266 microcontroller.
2.DHT11 sensor.
3.SSD1306 OLED display (128x64).
4.Pull Up Resistor (10kΩ) for the DHT11 sensor.
5.Breadboard and jumper wires.
Software Requirements

1.Arduino IDE with the following libraries installed:
  * DHT Sensor Library
  * Adafruit Unified Sensor
  * Adafruit GFX Library
  * Adafruit SSD1306
  * ThingSpeak Library

Circuit Connections

1.DHT11 Sensor:
  * VCC → 3.3V or 5V.
  * GND → GND.
  * Data Pin → GPIO 4 (ESP32/ESP8266).

2.OLED Display:
  * SDA → Default SDA pin (e.g., GPIO 21 for ESP32).
  * SCL → Default SCL pin (e.g., GPIO 22 for ESP32).

Setup Instructions

1.Install the required libraries in Arduino IDE.
2.Replace the following variables in the code with your own:
  * ssid: Your Wi-Fi SSID.
  * password: Your Wi-Fi password.
  * ChannelID: Your ThingSpeak channel ID.
  * myWriteAPIKey: Your ThingSpeak write API key.
3.Upload the code to your ESP32/ESP8266 microcontroller.
4.Power the microcontroller and observe the data on the OLED display and ThingSpeak channel.

Code Functionality

1.Initialization:
  * Connects to the OLED display.
  * Initializes the DHT sensor and sets up Wi-Fi and ThingSpeak.
2.Data Reading and Display:
  * Reads temperature and humidity from the DHT11 sensor.
  * Computes the heat index.
  * Displays the readings on the OLED screen.
3.Cloud Upload:
  * Sends the sensor data to ThingSpeak fields:
    * Field 1: Temperature.
    * Field 2: Humidity.
    * Field 3: Heat Index.
  * Logs success or failure messages to the serial monitor and OLED.
4.Loop Execution:
  * Repeats the data collection, display, and cloud upload every 30 seconds.

Possible Enhancements

1.Add more sensors (e.g., barometer, CO2) for extended environmental monitoring.
2.Use interrupt-based DHT readings for better efficiency.
3.Secure communication with ThingSpeak using HTTPS (ESP32 required).

Troubleshooting

1.Wi-Fi Connection Issues:
  * Ensure correct ssid and password.
  * Check for network availability.
2.DHT Sensor Errors:
  * Verify wiring and pull-up resistor.
  * Ensure proper power supply (3.3V or 5V depending on the board).
3.OLED Display Not Working:
  * Check I2C connections (SDA/SCL).
  * Verify the I2C address (default is 0x3C).