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
#include "Modules/GSMModule.h"

uint32_t count = 0;
const int ledPin = 13;

SDCardModule* sd;
BluetoothModule* bl;
GPSModule* gps;
WifiModule* wifi;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
  Serial.begin(9600);

  delay(10000);

  sd = new SDCardModule();
  bl = new BluetoothModule(sd,7,8,6);
  gps = new GPSModule(sd,9,10);
  wifi = new WifiModule(sd,0,1);

  wifi->begin();
  gps->begin();
  bl->setup();

  Serial.println("Setup Complete!");
}

void loop()
{

  if (!gps->process(count)){
      return;
  }

  wifi->process(count);

  // bl process braucht 2,5sek vorlauf bis es gestartet ist (Scan mode)
  digitalWrite(ledPin, HIGH);
  bl->process(count);
  digitalWrite(ledPin, LOW);
  // es hat auch 1,5 sek nachlauf (shutdown) -> gesamt 14 sek
  delay(5000);

  count++;
}
