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


  char validity;
  char timestamp[10];
  double latitude;
  double longitude;
  int numberSatellites;
  float height;
  u_int8_t kill_count = 50;
  while (isReading && kill_count > 0)
  {
<<<<<<< HEAD
    // Serial.println("GPS loop");
=======

>>>>>>> 8cd642afad1e6bc1cc644e605ea3d66e50b58d7f
    if (!this->available()){
      Serial.println("no data");
      kill_count--;
      delay(100);
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
<<<<<<< HEAD

  //Serial.println(dataString.c_str());

=======
>>>>>>> 8cd642afad1e6bc1cc644e605ea3d66e50b58d7f
  return kill_count != 0;
}
