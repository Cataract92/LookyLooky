#pragma once
#include "Arduino.h"
#include <SoftwareSerial.h>

class BluetoothModule: public SoftwareSerial
{
  public:
     BluetoothModule(uint8_t rxPin, uint8_t txPin,uint8_t enable);
     void process(uint8_t count);
     bool isConnected();
     void enterATMode();
     void begin();

     void sendATCommand(const char* command);

  private:
     uint8_t enable;
     static const uint32_t BAUDRATE = 38400;


};
