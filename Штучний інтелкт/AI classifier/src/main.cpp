#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "model.h"
#include <map>

#define EXAMPLES 6
#define SIZE_FIREBASE_ARRAY 8
#define FIREBASE_HOST "careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_SECRET "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0"

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 0 // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 0 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Eloquent::ML::Port::SVM classifier;

int n = 0;
const char* ssid = "Vlad";
const char* pass = "0987654321a";


std::array<String, SIZE_FIREBASE_ARRAY> check_array;
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void load_const_networks();

void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");

  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);

  load_const_networks();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void load_const_networks()
{
  for (int i = 0; i < SIZE_FIREBASE_ARRAY; ++i) {
    if (Firebase.RTDB.getString(&fbdo, "const_signal/SSID_" + String(i))) {
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_string) {
        Serial.print("\nsucces " + String(fbdo.to<String>()));
        check_array[i] = fbdo.to<String>();
      }
    }
    delay(50);
  }
  Serial.print("\n");
}

bool check_ssid(String ssid_n)
{
  return std::find(check_array.begin(), check_array.end(), ssid_n) != check_array.end();
}

void scan_networks(std::map<String, float> &map)
{
  int number_of_networks = WiFi.scanNetworks();
  for (int i = 0; i < number_of_networks; ++i) {
    String name_ssid = WiFi.SSID(i);
    float rssi = WiFi.RSSI(i);

    if (check_ssid(name_ssid)) {
      map[name_ssid] = rssi;
    }
  }
}


const char* classify() 
{
  std::map<String, float> networks;
  float x_sample[EXAMPLES];

  scan_networks(networks);

  int it = 0;
  for (const auto el : networks) {
    x_sample[it] = el.second;
    ++it;
  }

  return classifier.predictLabel(x_sample);
}

// ADDAFRUIT::Print(clasify())

void loop() 
{
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(classify());
  display.display();
}
