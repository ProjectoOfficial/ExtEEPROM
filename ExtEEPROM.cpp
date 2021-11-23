#include "ExtEEPROM.h"

ExtEEPROM::ExtEEPROM(){
    _EEPROM_Address = EADDRESS;
    _stop_byte = STOPBYTE;
    _max_iteration = MAXITERATIONS;
}

ExtEEPROM::ExtEEPROM(uint8_t EEPROM_Address, uint8_t stop_byte, uint16_t max_iteration){
    _EEPROM_Address = EEPROM_Address;
    _stop_byte = stop_byte;
    _max_iteration = max_iteration;
}

void ExtEEPROM::begin(){

    Wire.begin();
}

void ExtEEPROM::EWrite(unsigned int startaddress, string data) {

  int len = data.length();

  char *cdata = (char *)calloc(len, sizeof(char));
  
  strcpy(cdata, data.c_str());

  for (unsigned int i = startaddress; i < len + startaddress ; i++){
    writeEEPROM(i, (uint8_t) cdata[i - startaddress]);
  }
    
    writeEEPROM(len + startaddress, (uint8_t) STOPBYTE);
}

char *ExtEEPROM::ERead(unsigned int startaddress) {
  char *cdata = (char *) calloc(1, sizeof(char));
  unsigned int i = startaddress;
  
  uint8_t rdata = readEEPROM(i);
  while (rdata != STOPBYTE && i < MAXITERATIONS) {
    cdata = (char *)realloc(cdata, i - startaddress + 2);
    cdata[i - startaddress] = (char) rdata;
    cdata[i - startaddress + 1] = '\0';
    i++;
    
    rdata = readEEPROM(i);
  }

  return cdata;
}

void ExtEEPROM::writeEEPROM(unsigned int eeaddress, uint8_t c)
{
  Wire.beginTransmission(EADDRESS);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(c);
  Wire.endTransmission();

}

uint8_t ExtEEPROM::readEEPROM(unsigned int eeaddress)
{
  uint8_t rdata = (uint8_t) 0xFF;

  Wire.beginTransmission(EADDRESS);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(EADDRESS, 1);

  if (Wire.available()) rdata = Wire.read();
  return rdata;
}