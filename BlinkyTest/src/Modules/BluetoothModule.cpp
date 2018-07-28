#include "BluetoothModule.h"

BluetoothModule::BluetoothModule(uint8_t rxPin, uint8_t txPin, uint8_t state, uint8_t vcc): SoftwareSerial(rxPin,txPin)
{
    this->state = state;
    this->vcc = vcc;
    pinMode(this->state,INPUT);
    pinMode(this->vcc,OUTPUT);
    digitalWrite(this->vcc,HIGH);
}

void BluetoothModule::begin()
{
  SoftwareSerial::begin(BluetoothModule::BAUDRATE);
}

void BluetoothModule::enterATMode()
{
  digitalWrite(this->vcc, LOW);

  char tmp[100];

  Serial.println("BluetoothModule: Entering AT Mode. Please press Enter while pressing the Button on the BluetoothModule");
  Serial.println("BluetoothModule: Trying Mode");
  this->begin();

}

void BluetoothModule::sendATCommand(const char* command)
{
  this->write(command);
  while(this->available() == 0) {}
  Serial.println(this->readString());
}

bool BluetoothModule::isConnected()
{
  return digitalRead(this->state) == HIGH;
}
