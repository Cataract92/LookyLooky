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

void blink(u_int32_t count, u_int32_t uptime, u_int32_t downtime){
    if (count > 0) {
      for (size_t i = 0; i < count; i++) {
        digitalWrite(ledPin, HIGH);
        delay(uptime);
        digitalWrite(ledPin, LOW);
        delay(downtime);
      }
    }
}
void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
  Serial.begin(9600);

  delay(10000);

  sd = new SDCardModule();
  // christian
  //bl = new BluetoothModule(sd,7,8,6);
  // nico
  bl = new BluetoothModule(sd,0,1,3,2, false);
  gps = new GPSModule(sd,9,10);
  //wifi = new WifiModule(sd,33,34);

  //wifi->begin();
  gps->begin();
  bl->setup();

  Serial.println("Setup Complete!");
  //blink(2, 250, 250);
}

void loop()
{
  Serial.println("loop");
  //blink(2, 500, 500);
  if (!gps->process(count)){
      //blink(3, 250, 250);
      Serial.println("no GPS");
      return;
  } else {
    Serial.println("GPS");
    digitalWrite(ledPin, HIGH);

  //wifi->process(count);

  // bl process braucht 2,5sek vorlauf bis es gestartet ist (Scan mode)
  bl->process(count);
  // es hat auch 1,5 sek nachlauf (shutdown) -> gesamt 14 sek
    digitalWrite(ledPin, LOW);
  }

  delay(5000);

  count++;
}
