#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <array>
#include <String>
#include <algorithm>
#include <cmath>

// Connector

#define NUMBER_OF_NETWORKS 3


// U8g2 Contructor
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/16, /* clock=*/5, /* data=*/4);

std::array<String, NUMBER_OF_NETWORKS> ssid = {"Test", "Vlad", "Test2"};
std::array<String, NUMBER_OF_NETWORKS> pass = {"123456789", "0987654321a", "What is love"};

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid[1], pass[1]);
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
    Serial.print(". ");
  }
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop() { 
  u8g2.setFont(u8g2_font_b10_t_japanese1);
  u8g2.setFontDirection(0);
  u8g2.firstPage();

  Serial.println();

  int number_of_stations = WiFi.scanNetworks();
  do {
    u8g2.setCursor(0, 0);
    int x = 0, y = 15;

    for (int i = 0; i < number_of_stations; ++i) {
      if (std::find(ssid.begin(), ssid.end(), WiFi.SSID(i)) != ssid.end()) {
        u8g2.setCursor(x, y);
        u8g2.print(WiFi.SSID(i));

        x += 30;

        Serial.print(WiFi.SSID(i));
        Serial.printf(" %i", WiFi.RSSI(i));
        Serial.println();

        u8g2.setCursor(x, y);
        u8g2.print(WiFi.RSSI(i));
        
        y += 15;
        x = 0;
        delay(100);
      }
    }
    delay(1000);
  } while (u8g2.nextPage());
  WiFi.begin();
}
