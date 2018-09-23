#pragma once
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SDCardModule.h"

class GPSModule: public SoftwareSerial
{
  public:
     GPSModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin);
     bool process();
     void begin();
     void newTime() {time_set = false;};
     uint64_t get_timestamp() {return time;};
  private:
    static const uint32_t BAUDRATE = 9600;
    SDCardModule* sd;

    uint64_t time =0;
    bool time_set = false;
    void set_time(uint64_t t){
      if (!time_set){
        time_set = true;
        time = t;
      }
    }

};
