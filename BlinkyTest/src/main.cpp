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


SDCardModule* sd;
BluetoothModule* bl;
GPSModule* gps;
WifiModule* wifi;


void setup()
{
  Serial.begin(9600);

  delay(10000);

  sd = new SDCardModule();
  //bl = new BluetoothModule(sd,7,8,6);
  gps = new GPSModule(sd,9,10);
  wifi = new WifiModule(sd,0,1);

  //bl->begin();
  wifi->begin();
  gps->begin();
  Serial.println("Setup Complete!");

/*
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
  */
  delay(10000);
}

void loop()
{


    if (!gps->process(count)){
        return;
    }

    wifi->process(count);

    count++;
}
