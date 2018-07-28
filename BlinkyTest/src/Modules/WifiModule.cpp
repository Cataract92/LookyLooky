
#include "WifiModule.h"
WifiModule::WifiModule(uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
}

void WifiModule::begin()
{
  SoftwareSerial::begin(WifiModule::BAUDRATE);
}
