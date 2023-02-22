#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <U8g2lib.h>

#include <cmath>
#include <array>
#include <numeric>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/16, /* clock=*/5, /* data=*/4);
std::array<int, 10> rssi_array_for_mid_value{255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
int it = 0;
double mid_rssi;
void setup()
{
    WiFi.begin();
    Serial.begin(9600);

    u8g2.begin();
    u8g2.enableUTF8Print();
}

// pow(10, static_cast<double>((-51 + abs(rssi))) / static_cast<double>((10 * 3)))

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

void loop()
{
    int rssi = 0;

    int number_of_networks = WiFi.scanNetworks();

    for (int i = 0; i < number_of_networks; ++i)
    {
        if (WiFi.SSID(i) == "Test_1")
        {
            rssi = WiFi.RSSI(i);
        }
    }

    u8g2.firstPage();
    do{
        u8g2.setFont(u8g2_font_4x6_tr);
        u8g2.drawStr(0, 10, String(rssi).c_str());
        u8g2.drawStr(0, 20, String(it).c_str());
        if (it != 10)
        {
            rssi_array_for_mid_value[it++] = rssi;
        }
        else
        {
            mid_rssi = std::accumulate(rssi_array_for_mid_value.begin(), rssi_array_for_mid_value.end(), 0) / 10;
            u8g2.drawStr(0, 30, String(mid_rssi).c_str());
            u8g2.drawStr(20, 10, String(pow(10, static_cast<double>((-52 + abs(mid_rssi))) / static_cast<double>((10 * 3)))).c_str());
            rssi_array_for_mid_value = std::array<int, 10>({255, 255, 255, 255, 255, 255, 255, 255, 255, 255});
            mid_rssi = 0;
            it = 0;
        }
    } while(u8g2.nextPage());
    delay(3000);
}