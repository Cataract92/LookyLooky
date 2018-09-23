#include "SDCardModule.h"

SDCardModule::SDCardModule()
{
  begin();
  chvol();
}

void SDCardModule::writeToFile(const char* fileName, String text)
{
  openFile(fileName);
  write(text);
  close();
}

void SDCardModule::openFile(const char* fileName)
{
  if (!file.open(fileName, O_RDWR | O_APPEND  | O_CREAT))
  {
    Serial.println("Open failed");
  }
}

void SDCardModule::close()
{
  file.close();
}

void SDCardModule::write(String text)
{
  file.write(text.c_str());
}
