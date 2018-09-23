#pragma once
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SDCardModule.h"
#include <regex>

class BluetoothModule: public SoftwareSerial
{
  public:
    BluetoothModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin,uint8_t enable, uint8_t vcc, bool inverted);
     BluetoothModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin,uint8_t enable, uint8_t vcc);
     BluetoothModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin,uint8_t enable);
     void process(uint32_t count);
     void setup();
     bool isConnected();
     void switchOff();
     void enterATMode();
     void enterScanMode();
     void begin();
     String getReply();

     void sendATCommand(const char* command);

  private:
    SDCardModule* sd;
     uint8_t enable;
     uint8_t vcc=0;
     bool inverted = true;
     static const uint32_t BAUDRATE = 38400;
     const char delim[2] = ",";

};
