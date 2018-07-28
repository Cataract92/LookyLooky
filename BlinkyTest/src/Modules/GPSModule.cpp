#include "GPSModule.h"
GPSModule::GPSModule(uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
}

void GPSModule::begin()
{
  SoftwareSerial::begin(GPSModule::BAUDRATE);
}

bool GPSModule::process(uint8_t count)
{
  bool isReading = true;
  String dataString = "";
  String lineString = "";

  char validity;
  char timestamp[10];
  double latitude;
  double longitude;
  int numberSatellites;
  float height;

  while (isReading)
  {
    if (!this->available())
      continue;

    char c = this->read();

    if (c == '\n')
      continue;

    if (c == '\r')
    {

      if (lineString.startsWith("$GPRMC"))
      {
        sscanf(lineString.c_str(),"$GPRMC,%9s,%c",&timestamp,&validity);
      }
      if (lineString.startsWith("$GPGGA"))
      {
        sscanf(lineString.c_str(),"$GPGGA,%9s,%lf,%*c,%lf,%*c,%*c,%d,%*f,%f",&timestamp,&latitude,&longitude,&numberSatellites,&height);

        if (validity == 'A'){

          double fractpart, intpart;
          fractpart = modf(latitude/100,&intpart);
          latitude = intpart+(fractpart / 60)*100;

          fractpart = modf(longitude/100,&intpart);
          longitude = intpart+(fractpart / 60)*100;


          Serial.printf("%d,%s,%f,%f,%d,%f\n",count,timestamp,latitude,longitude,numberSatellites,height);
        }

        isReading = false;
      }
      dataString += (lineString + "\n");
      lineString = "";
    } else {
      lineString += c;
    }
  }

  if (count == -1)
    return false;

  //Serial.println(dataString.c_str());

  return true;
}
