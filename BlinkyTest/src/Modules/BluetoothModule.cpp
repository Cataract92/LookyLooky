#include "BluetoothModule.h"

BluetoothModule::BluetoothModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin,uint8_t enable, uint8_t vcc): SoftwareSerial(rxPin,txPin) {
  this->sd = sd;
  this->enable = enable;
  this->vcc = vcc;
  this->sd = sd;
  pinMode(this->enable, OUTPUT);
  digitalWrite(this->enable,HIGH);
  pinMode(this->vcc, OUTPUT);
  digitalWrite(this->vcc,inverted ? HIGH : LOW);
  this->setTimeout(1000);
}
BluetoothModule::BluetoothModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin,uint8_t enable, uint8_t vcc, bool inverted): SoftwareSerial(rxPin,txPin)
{
  this->sd = sd;
  this->enable = enable;
  this->vcc = vcc;
  this->sd = sd;
  pinMode(this->enable, OUTPUT);
  digitalWrite(this->enable,HIGH);
  pinMode(this->vcc, OUTPUT);
  digitalWrite(this->vcc,inverted ? HIGH : LOW);
  this->inverted = inverted;
}

BluetoothModule::BluetoothModule(SDCardModule* sd, uint8_t rxPin, uint8_t txPin,uint8_t enable): SoftwareSerial(rxPin,txPin)
{
  this->sd = sd;
  this->enable = enable;
  pinMode(this->enable, OUTPUT);
  digitalWrite(this->enable,HIGH);
}

void BluetoothModule::begin()
{
  SoftwareSerial::begin(BluetoothModule::BAUDRATE);
}

void BluetoothModule::setup()
{
  begin();
  switchOff();
  enterATMode();
  sendATCommand("AT+ORGL");
  Serial.print(getReply());
  sendATCommand("AT+RESET");
  Serial.print(getReply());
  switchOff();
  enterATMode();
  sendATCommand("AT+UART=38400,0,0");
  Serial.print(getReply());
  sendATCommand("AT+RMAAD");
  Serial.print(getReply());
  sendATCommand("AT+CLASS=0");
  Serial.print(getReply());
  sendATCommand("AT+ROLE=1");
  Serial.print(getReply());
  sendATCommand("AT+RESET");
  // this reset never gives an ok
  switchOff();
  enterATMode();
  sendATCommand("AT+INIT");
  Serial.print(getReply());
  sendATCommand("AT+CMODE=1");
  Serial.print(getReply());
  sendATCommand("AT+INQM=1,1,1");
  Serial.print(getReply());
  sendATCommand("AT+PSWD=\"9999\"");
  Serial.print(getReply());
  switchOff();
}

void BluetoothModule::switchOff() {
  if (this->vcc != 0){
    delay(500);
    digitalWrite(this->vcc,inverted ?HIGH : LOW);
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
    digitalWrite(this->vcc,inverted ?LOW : HIGH);
    delay(1000);
    Serial.println("BluetoothModule: AT Mode");
  }
}
void BluetoothModule::enterScanMode(){
  if (this->vcc != 0){
    delay(500);
    digitalWrite(this->vcc,inverted ? LOW : HIGH);
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
void BluetoothModule::process(uint64_t count){
    this->enterScanMode();
    // digitalWrite(ledPin,HIGH);
    unsigned long del = millis();
    String res = "";
    while (millis()-del < 10000){
      res+=this->getReply();
    }
    Serial.println(res);
    this->switchOff();

    // flush
     while (this->available()){
       this->getReply();
    }
    char* line = strtok(const_cast<char*>(res.c_str()), delim);
    char address[15] = {'\0'};
    char classtype[7] = {'\0'};
    char rssi[7] = {'\0'};

    MatchState ms;

    while (line != NULL)
    {

        ms.Target (line);
        if (ms.Match ("%+INQ:%x%x%x%x:%x%x:%x%x%x%x%x%x,%x%x%x%x%x%x,%x%x%x%x") > 0)
        {
            sscanf(line,"+INQ:%14s,%6s,%4s",address,classtype,rssi);
        }
        if (ms.Match ("%+INQ:%x%x%x%x:%x%x:%x%x%x%x%x%x,%x%x%x%x%x,%x%x%x%x") > 0)
        {
            sscanf(line,"+INQ:%14s,%5s,%4s",address,classtype,rssi);
        }
        if (ms.Match ("%+INQ:%x%x%x%x:%x%x:%x%x%x%x%x,%x%x%x%x%x,%x%x%x%x") > 0)
        {
            sscanf(line,"+INQ:%13s,%5s,%4s",address,classtype,rssi);
        }
        if (ms.Match ("%+INQ:%x%x%x%x:%x%x:%x%x%x%x%x,%x%x%x%x%x%x,%x%x%x%x") > 0)
        {
            sscanf(line,"+INQ:%13s,%6s,%4s",address,classtype,rssi);
        }
        if (rssi[0]!='\0') {
          char buffer[256];
          sprintf(buffer,"%llu,%s,%s,%s\n",count,address,classtype,rssi);
          sd->writeToFile("bl.csv",buffer);
          Serial.printf("%llu,%s,%s,%s\n",count,address,classtype,rssi);
        }

        line = strtok(NULL,delim);
    }
    // digitalWrite(ledPin,LOW);


}
