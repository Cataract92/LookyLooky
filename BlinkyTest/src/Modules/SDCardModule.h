#pragma once
#include <Arduino.h>
#include "../SdFat/SdFat.h"

class SDCardModule: public SdFatSdioEX
{
  public:
    SDCardModule();
    void writeToFile(const char* fileName, String text);
    void openFile(const char* fileName);
    void close();
    void write(String text);


  private:
    File file;

};
