// Example testing sketch for various DHT humidity/temperature sensors written by Alevivash
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <WiFi.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ThingSpeak.h>

const char* ssid = "MARTE3";
const char* password = "carabobo1972";

WiFiClient client;

unsigned long ChannelID = 2805648;
const char* myWriteAPIKey = "W85UCBNM4G7YHUXL";

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

#define DHTPIN 4
#define DHTTYPE DHT11

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  dht.begin();
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Initializing...");
  display.display();
  delay(2000);
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("\nWiFi connected.");
    }

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Sensor Error!");
      display.display();
      return;
    }

    float hic = dht.computeHeatIndex(t, h, false);


    // Display data on OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Humidity: ");
    display.print(h);
    display.println(" %");
    display.setCursor(0, 10);
    display.print("Temp: ");
    display.print(t);
    display.println(" C");
    display.setCursor(0, 20);
    display.print("Heat Index: ");
    display.print(hic);
    display.println(" C");
    display.display();

    // Write to ThingSpeak

    ThingSpeak.setField(1, t);
    ThingSpeak.setField(2, h);
    ThingSpeak.setField(3, hic);

    if (ThingSpeak.writeFields(ChannelID, myWriteAPIKey)) {
      Serial.println("Data sent to ThingSpeak");
      display.setCursor(0, 30);
      display.println("Sent to ThingSpeak");
      display.display();
    } else {
      Serial.println("Failed to send data");
      display.setCursor(0, 30);
      display.println("Failed to send data");   
      display.display();   
    }

    lastTime = millis();
  }
}

