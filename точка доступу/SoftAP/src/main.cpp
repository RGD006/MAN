#include <ESP8266WiFi.h>
#include <FS.h>

// SoftAP

extern "C"
{
#include <user_interface.h>
}

const char *ssid = "Test_2";
const char *pass = "123456789"; 

void setup() {
  Serial.begin(9600);
  delay(1000);
  WiFi.softAP(ssid, pass);

  Serial.println("STARTED");
}

// void scan() {
//   uint8_t num_of_user = wifi_softap_get_station_num();

//   IPAddress address;
//   struct ip4_addr *user;
//   struct station_info *station;

//   station = wifi_softap_get_station_info();

//   Serial.printf("Number of users: %i \n", num_of_user);

//   while (station != nullptr) {
//     user = &station->ip;
//     address = user->addr;

//     Serial.print("IP: ");
//     Serial.print(address);
//     Serial.print("\t");
//     Serial.print("MAC: ");
//     for (int i = 0; i < 6; ++i) {
//       Serial.print(station->bssid[i], HEX);
//       Serial.print(":");
//     }
//     Serial.println();

//     station = STAILQ_NEXT(station, next);
//   }
// }

void loop() {}
