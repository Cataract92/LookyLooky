
#include "WifiModule.h"



WifiModule::WifiModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
  this->sd = sd;
}

void WifiModule::begin()
{
  SoftwareSerial::begin(WifiModule::BAUDRATE);
}

void WifiModule::process(uint32_t count)
{
  bool isReading = true;
  String lineString = "";
  char buffer[256];

  while (isReading)
  {
    if (!this->available())
      continue;

    char c = this->read();

    if (c == '\n')
    {
      if (lineString.startsWith("end"))
      {
        isReading = false;
      }
      if (lineString.startsWith("42,"))
      {

        char* BSSIDstr;
        char* SSID;
        char* encryptionTypeString;
        int channel;
        char* isHidden;
        int RSSI;

        const char delim[2] = ",";

        strtok(const_cast<char*>(lineString.c_str()), delim);
        BSSIDstr = strtok(NULL, delim);
        SSID = strtok(NULL, delim);
        encryptionTypeString = strtok(NULL, delim);
        channel = atoi(strtok(NULL, delim));
        isHidden = strtok(NULL, delim);
        RSSI = atoi(strtok(NULL, delim));

        bool isNewNetwork = true;
        for (std::list<char*>::iterator it=allNetworks->begin(); it != allNetworks->end(); ++it)
        {
          if (!strcmp(*it,BSSIDstr))
          {
            isNewNetwork = false;
          }
        }

        if (isNewNetwork)
        {
          char* tmp = (char*) malloc(sizeof(char) * strlen(BSSIDstr));
          strcpy(tmp, BSSIDstr);
          allNetworks->push_back(tmp);

          sprintf(buffer,"%s,%s,%s,%d,%s\n",BSSIDstr,SSID,encryptionTypeString,channel,isHidden);
          sd->writeToFile("networks.csv",buffer);
          //Serial.printf("%s,%s,%s,%d,%s\n", BSSIDstr,SSID,encryptionTypeString,channel,isHidden);
        }

        sprintf(buffer,"%d,%s,%d\n",count, BSSIDstr,RSSI);
        sd->writeToFile("wifi.csv",buffer);
        //Serial.printf("%d,%s,%d\n",count, BSSIDstr,RSSI);
      }
      lineString = "";
    } else {
      lineString += c;
    }
  }

  //Serial.println(dataString.c_str());
}
