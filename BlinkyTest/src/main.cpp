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
//GPSModule* gps;
//WifiModule* wifi;
//Sim800l* gsm;
uint32_t count = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial connection.
  }


  bl = new BluetoothModule(7,8,6);
  //gps = new GPSModule(9,10);
  //wifi = new WifiModule(0,1);

  //gsm = new Sim800l();
  //gsm->begin();
  bl->begin();
  //wifi->begin();
  //gps->begin();
  Serial.println("Setup Complete!");

  //bl->enterATMode();

  bl->sendATCommand("AT+UART=38400,0,0");
  bl->sendATCommand("AT+RMAAD");
  bl->sendATCommand("AT+CLASS=0");
  bl->sendATCommand("AT+ROLE=1");
  //delay(2000);
  bl->sendATCommand("AT+RESET");
  //delay(2000);
  bl->sendATCommand("AT+INIT");
  bl->sendATCommand("AT+CMODE=1");
  bl->sendATCommand("AT+INQM=1,1,48");
  bl->sendATCommand("AT+IPSCAN=800,12,800,12");
  bl->sendATCommand("AT+PSWD=\"9999\"");
}

void loop()
{


    if (Serial.available()){
      bl->write(Serial.read());
    }
    if (bl->available())
      Serial.write(bl->read());


    //Serial.write(gsm->dateNet().c_str());

/*
    if (!gps->process(count)){
        return;
    }
*/

    //wifi->process(count);

/*
    if (wifi->available())
      Serial.write(wifi->read());
*/
    count++;
}
