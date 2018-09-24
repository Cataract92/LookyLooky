#include "GPSModule.h"
GPSModule::GPSModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
  this->sd = sd;
}

void GPSModule::begin()
{
  SoftwareSerial::begin(GPSModule::BAUDRATE);
}

bool GPSModule::process()
{
  bool isReading = true;
  // String dataString = "";
  String lineString = "";

  char validity;
  char timestamp[10];
  double latitude;
  double longitude;
  int numberSatellites;
  float height;
  u_int8_t kill_count = 50;
  while (isReading && kill_count > 0)
  {

    if (!this->available()){
      kill_count--;
      delay(200);
      continue;
    }
    char c = this->read();

    if (c == '\n'){
      continue;
    }
    if (c == '\r')
    {
      Serial.println(lineString.c_str());
      if (lineString.startsWith("$GPRMC"))
      {
        sscanf(lineString.c_str(),"$GPRMC,%9s,%c",timestamp,&validity);
        Serial.println(timestamp);
        set_time(std::strtoul(timestamp,NULL,10));
        Serial.printf("%llu\n",time);
      }
      if (lineString.startsWith("$GPGGA"))
      {
        sscanf(lineString.c_str(),"$GPGGA,%9s,%lf,%*c,%lf,%*c,%*c,%d,%*f,%f",timestamp,&latitude,&longitude,&numberSatellites,&height);
        Serial.println(timestamp);
        set_time(std::strtoul(timestamp,NULL,10));
        Serial.printf("%u\n",time);
        if (validity == 'A'){

          double fractpart, intpart;
          fractpart = modf(latitude/100,&intpart);
          latitude = intpart+(fractpart / 60)*100;

          fractpart = modf(longitude/100,&intpart);
          longitude = intpart+(fractpart / 60)*100;

          char buffer[256];
          sprintf(buffer,"%llu,%f,%f,%d,%f\n",time,latitude,longitude,numberSatellites,height);
          sd->writeToFile("gps.csv",buffer);
          Serial.printf("%llu,%f,%f,%d,%f\n",time,latitude,longitude,numberSatellites,height);

          isReading = false;
        } else
        {
          return false;
        }

      }
      // dataString += (lineString + "\n");
      lineString = "";
    } else {
      lineString += c;
    }
  }
  return kill_count != 0;
}
