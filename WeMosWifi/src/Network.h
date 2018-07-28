#include <Arduino.h>
#include <list>

class Network
{
  public:
    static void updateNetwork(uint8_t BSSID ,String BSSIDstr, String SSID,int channel, String encType, bool isHidden,int RSSI);
};
