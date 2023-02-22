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

#define SIZE 8
#define HTTP_PORT 8889
#define FIREBASE_HOST "careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_SECRET "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0"

const char* ssid = "Vlad";
const char* pass = "0987654321a";
String a_networks[SIZE];

FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void first_scan();
void send_data();

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);

  first_scan();
  send_data();
}

void send_data()
{
  bool all_succes = true;
  while(1) {
    for (int i = 0; i < SIZE; ++i) {
      if (Firebase.RTDB.setString(&fbdo, "/const_signal/SSID_ " + String(i), a_networks[i])) {
        Serial.println(a_networks[i] + " succes");
      } else {
        Serial.println(a_networks[i] + " failed");
        all_succes = false;
        break;
      }
      delay(50);
    }
    if (all_succes) break;
  }
}

void first_scan()
{
  int number_of_networks = WiFi.scanNetworks();

  for (int i = 0; i < number_of_networks; ++i) {
    String ssid = WiFi.SSID(i);

    a_networks[i] = ssid;
  }
}

void loop()
{

}
