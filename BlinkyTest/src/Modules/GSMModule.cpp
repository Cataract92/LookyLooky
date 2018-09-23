#include "GSMModule.h"
GSMModule::GSMModule(uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
}

void GSMModule::begin()
{
  SoftwareSerial::begin(GSMModule::BAUDRATE);
}

bool GSMModule::process(uint32_t count)
{
  return true;
}
