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
      for (u_int32_t i = 0; i < count; i++) {
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
  blink(3, 500, 500);
  // delay(10000);

  sd = new SDCardModule();
  // christian
  bl = new BluetoothModule(sd,7,8,6,5);
  // nico
  // bl = new BluetoothModule(sd,7,8,6, 5, false);
  gps = new GPSModule(sd,0,1);
  wifi = new WifiModule(sd,9,10);

  wifi->begin();
  gps->begin();
  bl->setup();

  Serial.println("Setup Complete!");
  blink(2, 250, 250);
}

void loop()
{
  Serial.println("measure");
  blink(2, 500, 500);
  // if (!gps->process(count)){
  //     blink(3, 250, 250);
  //     Serial.println("no GPS");
  //
  // } else {
    Serial.println("GPS");
    digitalWrite(ledPin, HIGH);
<<<<<<< HEAD
=======

>>>>>>> 8cd642afad1e6bc1cc644e605ea3d66e50b58d7f
    wifi->process(count);

    // bl process braucht 2,5sek vorlauf bis es gestartet ist (Scan mode)
    bl->process(count);
    // es hat auch 1,5 sek nachlauf (shutdown) -> gesamt 14 sek
    digitalWrite(ledPin, LOW);
  // }

  // delay(20000);

  count++;
}
