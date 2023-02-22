#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <cmath>
#include <array>
#include <numeric>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 0 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
std::array<int, 10> rssi_array_for_mid_value {255, 255, 255, 255, 255, 255, 255, 255, 255, 255}; 
int it = 0;
double mid_rssi;
void setup() 
{
  WiFi.begin();
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for (;;); // Don't proceed, loop forever
  }
}

double calculateDistance(double rssi, double txPower, double nFactor)
{
  if (rssi == 0) {
      return -1.0; // Помилка: немає даних про RSSI
  }

  double ratio = rssi * 1.0 / txPower;
  if (ratio < 1.0) {
      return pow(ratio, 10.0 / nFactor);
  }
  else {
      double distance = 0.89976 * pow(ratio, 7.7095) + 0.111;
      return distance;
  }
}

// pow(10, static_cast<double>((-51 + abs(rssi))) / static_cast<double>((10 * 3)))

void loop() 
{
  int rssi = 0;

  int number_of_networks = WiFi.scanNetworks();

  for (int i = 0; i < number_of_networks; ++i) {
    if (WiFi.SSID(i) == "Test_1") {
      rssi = WiFi.RSSI(i);
    }
  }

  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  // display.println(pow(10, static_cast<double>((-51 + abs(rssi))) / static_cast<double>((10 * 3))));
  display.print("RSSI: ");
  display.println(rssi);
  display.println(it);
  if (it != 10) {
    rssi_array_for_mid_value[it++] = rssi; 
  } else { 
    mid_rssi = std::accumulate(rssi_array_for_mid_value.begin(), rssi_array_for_mid_value.end(), 0) / 10;
    display.println(mid_rssi);
    display.println(calculateDistance(mid_rssi, -52, 2));
    rssi_array_for_mid_value = std::array<int, 10>({255, 255, 255, 255, 255, 255, 255, 255, 255, 255});
    mid_rssi = 0;
    it = 0;
  }
  display.display();
  delay(3000);

}