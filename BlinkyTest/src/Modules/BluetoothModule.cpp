#include "BluetoothModule.h"

BluetoothModule::BluetoothModule(uint8_t rxPin, uint8_t txPin,uint8_t enable, uint8_t vcc): SoftwareSerial(rxPin,txPin)
{
  this->enable = enable;
  this->vcc = vcc;
  pinMode(this->enable, OUTPUT);
  digitalWrite(this->enable,HIGH);
  pinMode(this->vcc, OUTPUT);
  digitalWrite(this->vcc,HIGH);
}

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
void BluetoothModule::switchOff() {
  if (this->vcc != 0){
    delay(500);
    digitalWrite(this->vcc,HIGH);
    digitalWrite(this->enable,LOW);
    delay(1000);
    Serial.println("Bluetooth Module shutdown");
  }
}
void BluetoothModule::enterATMode()
{
  if (this->vcc != 0){
    delay(500);
    digitalWrite(this->enable,HIGH);
    delay(1000);
    digitalWrite(this->vcc,LOW);
    delay(1000);
  Serial.println("BluetoothModule: AT Mode");
  }
}
void BluetoothModule::enterScanMode(){
  if (this->vcc != 0){
    delay(500);
    digitalWrite(this->vcc,LOW);
    delay(1000);
    digitalWrite(this->enable,HIGH);
    delay(1000);
    Serial.println("BluetoothModule: Scan Mode");
} else {
  Serial.println("Reconnect Bluetooth Module for Scan Mode");
}
}
void BluetoothModule::sendATCommand(const char* command)
{
  Serial.println(command);
  this->write(command);
  this->write("\r\n ");
  // while(this->available() == 0) {}
  // Serial.println(this->readString());
}
String BluetoothModule::getReply(){
  uint8_t count =0;
  while(!this->available() && count < 250) {
    count++;
    delay(4);
  }
  if (count >= 250){
    return "Timeout\r\n";
  }
  return this->readString();
}
void BluetoothModule::process(uint32_t count){
    this->enterScanMode();
    // digitalWrite(ledPin,HIGH);
    unsigned long del = millis();
    String res = "";
    while (millis()-del < 10000){
      res+=this->getReply();
    }
    Serial.println(res);
    // digitalWrite(ledPin,LOW);
    this->switchOff();
   // flush
    while (this->available())
      this->getReply();
}
