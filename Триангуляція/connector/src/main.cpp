// #include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <array>
#include <String>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <map> 

#define NUMBER_OF_NETWORKS 3
#define FIREBASE_HOST "careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_SECRET "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0"

// U8g2 Contructor
// U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/16, /* clock=*/5, /* data=*/4);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 0 // Reset pin # (or -1 if sharing Arduino reset pin)

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 0 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

std::array<String, NUMBER_OF_NETWORKS> ssid = {"Test_1", "Test_2", "Test_3"};
std::array<String, NUMBER_OF_NETWORKS> pass = {"123456789", "0987654321a", "What is love"};

std::map<String, std::array<int, 10>> rssi_signal_map; int it = 0;
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void clear_map(std::map<String, std::array<int, 10>> &map) 
{
  for (auto array : map) {
    array.second = std::array<int, 10>({0, 0, 0, 0, 0, 0, 0, 0});
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin("Anchor_of_WiFi", "What is love");
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
    Serial.print(". ");
  }
//   u8g2.begin();
//   u8g2.enableUTF8Print();
  
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  for (String name : ssid) {
    rssi_signal_map[name] = std::array<int, 10>({0, 0, 0, 0, 0, 0, 0, 0, 0});
  }

  clear_map(rssi_signal_map);

//   for (const auto el : rssi_signal_map) {
//     Serial.print(el.first);
//     Serial.print(" ");
//     for (int n : el.second) {
//       Serial.print(n);
//       Serial.print(" ");
//     }
//     Serial.println();
//   }
}

void loop() { 
//   u8g2.setFont(u8g2_font_b10_t_japanese1);
//   u8g2.setFontDirection(0);
//   u8g2.firstPage();
  int number_of_stations = WiFi.scanNetworks();
  Serial.println();

  // do {
    // u8g2.setCursor(0,20);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
    
  for (int i = 0; i < number_of_stations; ++i) {
    if (std::find(ssid.begin(), ssid.end(), WiFi.SSID(i)) != ssid.end()) {


      Serial.print(WiFi.SSID(i));
      Serial.printf(" %i", WiFi.RSSI(i));
      Serial.println();

      rssi_signal_map[WiFi.SSID(i)][it] = WiFi.RSSI(i);
    //   for (const auto el : rssi_signal_map)
    //   {
    //     Serial.print(el.first);
    //     Serial.print(" ");
    //     for (int n : el.second)
    //     {
    //       Serial.print(n);
    //       Serial.print(" ");
    //     }
    //     Serial.println();
    //   }
    }
  }  
  // } while (u8g2.nextPage());
  it++;

  if (it == 10) {
    for (auto array : rssi_signal_map) {
      double mid = std::accumulate(array.second.begin(), array.second.end(), 0) / 10.0;
      if (Firebase.RTDB.setString(&fbdo, "/signal_" + array.first + "/SSID", array.first) 
          && Firebase.RTDB.setDouble(&fbdo, "/signal_" + array.first + "/RSSI", mid))
      {
        Serial.printf("All ok \nSSID: %s\tRSSI: %f\n", array.first.c_str(), mid);
        // u8g2.print("SUCCESED SSID: ");
        // u8g2.print(WiFi.SSID(i));

        display.print("Succesed SSID: ");
        display.println(array.first);
      }
      else {
        Serial.println("ERROR");
        // u8g2.print("FAILED SSID: ");
        // u8g2.print(WiFi.SSID(i));

        display.print("Error SSID: ");
        display.println(array.first);
      }
      delay(1000);
    }
    clear_map(rssi_signal_map);
    it = 0;
  }

  if (it == 11)
  {
    it = 0;
    clear_map(rssi_signal_map);
  }
  display.setCursor(0, 40);
  display.print("iterator: ");
  display.println(it);
  display.display();

  Serial.print(it);
  delay(3000);
}
