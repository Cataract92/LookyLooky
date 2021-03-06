#pragma once
#include <Arduino.h>
#include <list>
#include <SoftwareSerial.h>
#include "Modules/SDCardModule.h"

class WifiModule: public SoftwareSerial
{
  public:
     WifiModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin);
     void process(uint32_t count);
     void begin();

  private:
    static const uint32_t BAUDRATE = 9600;
    SDCardModule* sd;
    std::list<char*>* allNetworks = new std::list<char*>();
};
