
#include "WifiModule.h"
#include "../Regexp/Regexp.h"


WifiModule::WifiModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
  this->sd = sd;
  this->setTimeout(1000);
}

void WifiModule::begin()
{
  SoftwareSerial::begin(WifiModule::BAUDRATE);
}

void WifiModule::process(uint64_t count)
{

  bool isReading = true;
  String lineString = "";

  u_int8_t kill_count = 50;
  while (isReading && kill_count > 0)
  {
    if (!this->available()){
      // Serial.println("no WLAN data");
      delay(100);
      kill_count--;
      continue;
    }
    char c = this->read();

    if (c == '\n')
    {

      if (lineString.startsWith("end"))
      {
        isReading = false;
      }
      if (lineString.startsWith("42,"))
      {
        char buffer[256] = {'\0'};
        MatchState ms;
        // Serial.println(lineString);
        ms.Target(const_cast<char*>(lineString.c_str()));
        if (!ms.Match ("42,%x%x?:%x%x?:%x%x?:%x%x?:%x%x?:%x%x?,[^,]+,[^,]+,%d+,[01],[%-]?%d+$")) {
            lineString = "";
            // Serial.println("no MATCH!");
            continue;
        }
        // Serial.println("match!");


        const char delim[2] = ",";
        strtok(const_cast<char*>(lineString.c_str()), delim);
        char * BSSIDstr = strtok(NULL, delim);
        char *  SSID = strtok(NULL, delim);
        char *  encryptionTypeString = strtok(NULL, delim);
        int channel = atoi(strtok(NULL, delim));
        int isHidden = atoi(strtok(NULL, delim));
        int RSSI = atoi(strtok(NULL, delim));

        bool isNewNetwork = true;
        for (std::vector<String>::iterator it=allNetworks.begin(); it != allNetworks.end(); ++it)
        {
          if (!strcmp(it->c_str(),BSSIDstr))
          {
            isNewNetwork = false;
          }
        }

        if (isNewNetwork)
        {

          allNetworks.push_back(BSSIDstr);
          char buffer2[256] = {'\0'};
          sprintf(buffer2,"%s,%s,%s,%d,%d\n",BSSIDstr,SSID,encryptionTypeString,channel,isHidden);
          sd->writeToFile("networks.csv",buffer2);
          Serial.printf("%s,%s,%s,%d,%d\n", BSSIDstr,SSID,encryptionTypeString,channel,isHidden);
          // Serial.printf("%s\n", buffer2);
        }

        sprintf(buffer,"%llu,%s,%d\n",count, BSSIDstr,RSSI);
        sd->writeToFile("wifi.csv",buffer);
        Serial.printf("%llu,%s,%d\n",count, BSSIDstr,RSSI);
      }
      lineString = "";
    } else {
      lineString += c;
    }
  }

}
