#include <Arduino.h>
#include <SoftwareSerial.h>

class GPSModule: public SoftwareSerial
{
  public:
     GPSModule(uint8_t rxPin, uint8_t txPin);
     bool process(uint8_t count);
     void begin();

  private:
    static const uint32_t BAUDRATE = 9600;

};
