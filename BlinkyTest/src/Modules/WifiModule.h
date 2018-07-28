#include <Arduino.h>
#include <SoftwareSerial.h>

class WifiModule: public SoftwareSerial
{
  public:
     WifiModule(uint8_t rxPin, uint8_t txPin);
     void process(uint8_t count);
     void begin();

  private:
    static const uint32_t BAUDRATE = 9600;
};
