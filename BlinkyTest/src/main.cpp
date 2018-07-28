/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "Modules/GPSModule.h"
#include "Modules/BluetoothModule.h"
#include "Modules/WifiModule.h"

BluetoothModule* bl;
GPSModule* gps;
WifiModule* wifi;
uint32_t count = -1;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial connection.
  }


  //bl = new BluetoothModule(0,1,3,2);
  //gps = new GPSModule(0,1);
  wifi = new WifiModule(0,1);

  //bl->begin();
  wifi->begin();
  //gps->begin();
  Serial.println("Setup Complete!");

  //bl->enterATMode();
  delay(1000);
}

void loop()
{
  /*
    if (Serial.available())
      bl->write(Serial.read());
    if (bl->available())
      Serial.write(bl->read());


    if (!gps->process(count)){
        count++;
        return;
    }
*/

    wifi->process(count);

/*
    if (wifi->available())
      Serial.write(wifi->read());
*/
    count++;
}
