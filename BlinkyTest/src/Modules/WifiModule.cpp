
#include "WifiModule.h"

WifiModule::WifiModule(uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
}

void WifiModule::begin()
{
  SoftwareSerial::begin(WifiModule::BAUDRATE);
}

void WifiModule::process(uint8_t count)
{
  bool isReading = true;
  String dataString = "";
  String lineString = "";

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

        char BSSIDstr[18];
        char SSID[lineString.length()-34];
        char encryptionTypeString[13];
        int channel;
        char isHidden[6];
        int RSSI;

        sscanf(lineString.c_str(),"42,%17s,%[^,]s,%[^,]s,%[^,]d,%[^,]s,%[^,]d",&BSSIDstr,&SSID,&encryptionTypeString,&channel,&isHidden,&RSSI);

        Serial.printf("%s , %s , %s , %d , %s , %d\n", BSSIDstr,SSID,encryptionTypeString,channel,isHidden,RSSI);
      }
      dataString += (lineString + "\n");
      lineString = "";
    } else {
      lineString += c;
    }
  }

  //Serial.println(dataString.c_str());
}
