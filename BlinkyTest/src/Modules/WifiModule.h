#pragma once
#include <Arduino.h>
#include <vector>
#include <SoftwareSerial.h>
#include "Modules/SDCardModule.h"

class WifiModule: public SoftwareSerial
{
  public:
     WifiModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin);
     void process(uint8_t count);
     void begin();

  private:
    static const uint32_t BAUDRATE = 9600;
    SDCardModule* sd;
    std::vector<String> allNetworks;
};
