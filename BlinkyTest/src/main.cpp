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
const int ledPin = 13;
void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial connection.
  }


  bl = new BluetoothModule(7,8,6,5);
  //gps = new GPSModule(9,10);
  //wifi = new WifiModule(0,1);

  //gsm = new Sim800l();
  //gsm->begin();
  //wifi->begin();
  //gps->begin();
  Serial.println("Setup Complete!");

  bl->enterATMode();
  bl->begin();
  bl->sendATCommand("AT+ORGL");
  Serial.print(bl->getReply());
  bl->sendATCommand("AT+RESET");
  Serial.print(bl->getReply());
  bl->switchOff();
  bl->enterATMode();
  bl->sendATCommand("AT+UART=38400,0,0");
  Serial.print(bl->getReply());
  bl->sendATCommand("AT+RMAAD");
  Serial.print(bl->getReply());
  bl->sendATCommand("AT+CLASS=0");
  Serial.print(bl->getReply());
  bl->sendATCommand("AT+ROLE=1");
  Serial.print(bl->getReply());
  //delay(2000);
  bl->sendATCommand("AT+RESET");
  // Serial.print(bl->getReply());
  bl->switchOff();
  bl->enterATMode();
  // delay(2000);
  bl->sendATCommand("AT+INIT");
  Serial.print(bl->getReply());
  bl->sendATCommand("AT+CMODE=1");
  Serial.print(bl->getReply());
  bl->sendATCommand("AT+INQM=1,1,1");
  Serial.print(bl->getReply());
  // bl->sendATCommand("AT+IPSCAN=800,12,800,12");
  // Serial.print(bl->getReply());
  bl->sendATCommand("AT+PSWD=\"9999\"");
  Serial.print(bl->getReply());
  bl->switchOff();
  // bl->enterScanMode();
  // delay(10000);
  // bl->sendATCommand("AT");
  // Serial.print(bl->getReply());
  // // bl->sendATCommand("AT+INQ");
  //
  // while (bl->available()){
  //   Serial.print(bl->getReply());
  // }
  // bl->switchOff();
  // // bl->enterATMode();

}

void loop()
{

  bl->enterScanMode();
  digitalWrite(ledPin,HIGH);
  unsigned long del = millis();
  while (millis()-del < 10000){
    // if (bl->available()){
    Serial.print(bl->getReply());
  // } else {
  //     delay(1);
  // }
  }
  digitalWrite(ledPin,LOW);
  bl->switchOff();
 // flush
  while (bl->available())
    bl->getReply();
  delay(5000);

    // if (Serial.available()){
    //   bl->write(Serial.read());
    // }
    // if (bl->available())
    //   Serial.write(bl->read());


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
