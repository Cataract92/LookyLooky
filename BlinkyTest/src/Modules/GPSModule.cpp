#include "GPSModule.h"
GPSModule::GPSModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin): SoftwareSerial(rxPin,txPin)
{
  this->sd = sd;
}

void GPSModule::begin()
{
  SoftwareSerial::begin(GPSModule::BAUDRATE);
}

bool GPSModule::process(uint32_t count)
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
    //Serial.println("GPS loop");
    if (!this->available()){
      //Serial.println("no data");
      //delay(1000);
      continue;
    }
    char c = this->read();

    if (c == '\n'){
      continue;
    }
    if (c == '\r')
    {

      if (lineString.startsWith("$GPRMC"))
      {
        sscanf(lineString.c_str(),"$GPRMC,%9s,%c",&timestamp,&validity);
        Serial.println(lineString.c_str());
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

          char buffer[256];
          sprintf(buffer,"%d,%s,%f,%f,%d,%f\n",count,timestamp,latitude,longitude,numberSatellites,height);
          sd->writeToFile("gps.csv",buffer);
          Serial.printf("%d,%s,%f,%f,%d,%f\n",count,timestamp,latitude,longitude,numberSatellites,height);

          isReading = false;
        } else
        {
          //return false;
          return false;
        }

      }
      dataString += (lineString + "\n");
      lineString = "";
    } else {
      lineString += c;
    }
  }

  return true;
}
