#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

#include <map>
#include <array>
#include <algorithm>

#define SIZE_FIREBASE_ARRAY 8
#define FIREBASE_HOST "careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_SECRET "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0"

const char* ssid = "Vlad";
const char* pass = "0987654321a";
int min_rssi = -90;

std::map<String, int> networks_ssid_rssi;
std::array<String, SIZE_FIREBASE_ARRAY> check_array;

FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

void load_const_networks();

void setup() 
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");

  config.database_url = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_SECRET;

  Firebase.reconnectWiFi(true);

  Firebase.begin(&config, &auth);

  load_const_networks();
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


void scan_networks()
{
  int number_of_networks = WiFi.scanNetworks();
  for (int i = 0; i < number_of_networks; ++i) {
    String name_ssid = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);

    if (check_ssid(name_ssid)) {
      networks_ssid_rssi[name_ssid] = rssi;
    }
  }
}

void send_data()
{
  int number_of_pair;


  if (Firebase.RTDB.getInt(&fbdo, "Number/n"))
    number_of_pair = fbdo.to<int>();
  else return;


  while(1) {
    bool all_succes = true;
    for (const auto network : networks_ssid_rssi) {
      if (Firebase.RTDB.setInt(&fbdo, "Value/Pair_" + String(number_of_pair) + "/" + network.first, network.second)) {
        Serial.println("succes");
      } else {
        Serial.println("error");
        Serial.print(fbdo.errorReason());
        all_succes = false;
        break;
      }
      delay(50);
    }

    if (all_succes) break;
  }

  Firebase.RTDB.setInt(&fbdo, "Number/n", ++number_of_pair);
}

void print_map() 
{
  for (const auto network : networks_ssid_rssi) {
    Serial.print(String(network.first) + " : " + String(network.second));
  }
  Serial.println("All networks: " + String(networks_ssid_rssi.size()) + "\n");
}

void reset_map()
{
  for (auto network : networks_ssid_rssi) 
    network.second = 0;
}

void loop() 
{
  scan_networks();
  print_map();
  send_data();
  reset_map();
  delay(5000);
}