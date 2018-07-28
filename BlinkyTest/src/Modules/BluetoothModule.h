#include "Arduino.h"
#include <SoftwareSerial.h>

class BluetoothModule: public SoftwareSerial
{
  public:
     BluetoothModule(uint8_t rxPin, uint8_t txPin, uint8_t state, uint8_t vcc);
     void process(uint8_t count);
     bool isConnected();
     void enterATMode();
     void begin();

  private:
     uint8_t vcc;
     uint8_t state;
     static const uint32_t BAUDRATE = 38400;

     void sendATCommand(const char* command);
};
