#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Modules/SDCardModule.h"

class GPSModule: public SoftwareSerial
{
  public:
     GPSModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin);
     bool process(uint32_t count);
     void begin();

  private:
    static const uint32_t BAUDRATE = 9600;
    SDCardModule* sd;

};
