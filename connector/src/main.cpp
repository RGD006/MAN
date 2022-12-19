#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include <array>
#include <String>
#include <algorithm>
#include <cmath>

/*
Connector
 Test macros https://script.google.com/macros/s/AKfycbwvy-xTSn38CozpW-4b318F0Fltj2sCDKsZqAvHDZM3DS1MiCs0DFc94tKf8wlXpKSq/exec?Name="Vlad"&RSSI=-85
 service ID AKfycbwvy-xTSn38CozpW-4b318F0Fltj2sCDKsZqAvHDZM3DS1MiCs0DFc94tKf8wlXpKSq
 fingerprint 2B B5 F0 49 BB 7A DE CB 2F 32 67 2E 10 D5 45 3E BE 2C 18 0B
*/
#define NUMBER_OF_NETWORKS 3
#define HTTP_PORT 8889
#define FIREBASE_HOST "careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_SECRET "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0"

// U8g2 Contructor
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/16, /* clock=*/5, /* data=*/4);

std::array<String, NUMBER_OF_NETWORKS> ssid = {"Test", "Vlad", "Test2"};
std::array<String, NUMBER_OF_NETWORKS> pass = {"123456789", "0987654321a", "What is love"};

FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid[1], pass[1]);
  while(WiFi.status() != WL_CONNECTED){
    delay(300);
    Serial.print(". ");
  }
  u8g2.begin();
  u8g2.enableUTF8Print();
  
  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);
}

void send_data(String name, int value_rssi) {
  if (Firebase.RTDB.setString(&fbdo, "/signal_" + name + "/SSID", name) && Firebase.RTDB.setInt(&fbdo, "/signal_" + name + "/RSSI", value_rssi)) {
    Serial.printf("All ok \nSSID: %s\tRSSI: %i\n", name.c_str(), value_rssi); 
  } else {
    Serial.println("ERROR");
  }
}

void loop() { 
  u8g2.setFont(u8g2_font_b10_t_japanese1);
  u8g2.setFontDirection(0);
  u8g2.firstPage();

  Serial.println();

  int number_of_stations = WiFi.scanNetworks();
  do {
    for (int i = 0; i < number_of_stations; ++i) {
      if (std::find(ssid.begin(), ssid.end(), WiFi.SSID(i)) != ssid.end()) {

        Serial.print(WiFi.SSID(i));
        Serial.printf(" %i", WiFi.RSSI(i));
        Serial.println();
        
        send_data(WiFi.SSID(i), WiFi.RSSI(i));
        delay(100);
      }
    }
    delay(1000);
  } while (u8g2.nextPage());
}
