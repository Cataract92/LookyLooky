#include "BluetoothModule.h"

BluetoothModule::BluetoothModule(uint8_t rxPin, uint8_t txPin,uint8_t enable): SoftwareSerial(rxPin,txPin)
{
  this->enable = enable;
  pinMode(this->enable, OUTPUT);
  digitalWrite(this->enable,HIGH);
}

void BluetoothModule::begin()
{
  SoftwareSerial::begin(BluetoothModule::BAUDRATE);
}

void BluetoothModule::enterATMode()
{

  Serial.println("BluetoothModule: Entering AT Mode. Please press Enter while pressing the Button on the BluetoothModule");
  Serial.println("BluetoothModule: Trying Mode");
  this->begin();

}

void BluetoothModule::sendATCommand(const char* command)
{
  Serial.println(command);
  this->write(command);
  this->write("\r\n ");
  while(this->available() == 0) {}
  Serial.println(this->readString());
}
