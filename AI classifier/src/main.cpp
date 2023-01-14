#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include "model.h"
#include <map>

#define EXAMPLES 6
#define SIZE_FIREBASE_ARRAY 8
#define FIREBASE_HOST "careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_SECRET "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0"


Eloquent::ML::Port::OneClassSVM classifier;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/16, /* clock=*/5, /* data=*/4);
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

  u8g2.begin();
  u8g2.enableUTF8Print();
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

void loop() 
{
  u8g2.setFont(u8g2_font_b10_t_japanese1);
  u8g2.setFontDirection(0);
  u8g2.firstPage();


  do{
    u8g2.setCursor(0,10);
    u8g2.print(classify());
    u8g2.printf(" %i", n);
    delay(5000);

    ++n;
  } while(u8g2.nextPage());

}
