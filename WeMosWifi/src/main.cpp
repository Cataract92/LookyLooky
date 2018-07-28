#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Network.h"


void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial connection.
  }
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  int n = WiFi.scanNetworks(false, true);

  String SSID;
  String encryptionTypeString;
  uint8_t encryptionType;
  int32_t RSSI;
  String BSSIDstr;
  uint8_t* BSSID;
  int32_t channel;
  bool isHidden;

  for (int i = 0; i < n; i++)
  {
    WiFi.getNetworkInfo(i, SSID, encryptionType, RSSI, BSSID, channel, isHidden);
    BSSIDstr= WiFi.BSSIDstr(i);
    switch( encryptionType )
    {
      case 2 : {
        encryptionTypeString = "WPA/PSK";
        break;
      }

      case 4 : {
        encryptionTypeString = "WPA2/PSK";
        break;
      }

      case 5 : {
        encryptionTypeString = "WEP";
        break;
      }

      case 7 : {
        encryptionTypeString = "open";
        break;
      }

      case 8 : {
        encryptionTypeString = "WPA/WPA2/PSK";
        break;
      }

      default :
      {
        encryptionTypeString = "unkown";
      }
    }

    Network::updateNetwork(*BSSID, BSSIDstr, SSID, channel, encryptionTypeString, isHidden, RSSI);

  }
}
