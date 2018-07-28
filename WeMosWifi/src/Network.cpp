#include "Network.h"

std::list<String>* allNetworks = new std::list<String>();


void Network::updateNetwork(uint8_t BSSID ,String BSSIDstr, String SSID,int channel, String encType, bool isHidden, int RSSI){

  //Serial.printf("%d\n", allNetworks->count(BSSID));

  bool foundnew= false;

  for (std::list<String>::iterator it = allNetworks.begin(); it != allNetworks.end(); ++it){
      if (*it == BSSIDstr)
      {
        foundnew = true;
      }
  }

  if (!foundnew)
  {
    Serial.printf("New Network: %s %s\n",BSSIDstr.c_str(),SSID.c_str());
  }

  Serial.printf("%d : %d\n", BSSID,RSSI);

}
