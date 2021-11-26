#include "ExtEEPROM.h"

ExtEEPROM::ExtEEPROM(){
    _EEPROM_Address = EADDRESS;
    _terminator = TERMINATOR;
    _max_iterations = MAXITERATIONS;
}

ExtEEPROM::ExtEEPROM(uint8_t EEPROM_Address, uint8_t terminator, uint16_t max_iteration){
    _EEPROM_Address = EEPROM_Address;
    _terminator = terminator;
    _max_iterations = max_iteration;
}

void ExtEEPROM::begin(){

    Wire.begin();
}

void ExtEEPROM::EWrite(String data) {
  /*
   * @brief performs a sequential page write
  */

  int len = data.length();

  char *cdata = (char *)calloc(len, sizeof(char));
  
  strcpy(cdata, data.c_str());
  Wire.beginTransmission(EADDRESS);
  Wire.write((int)(0 >> 8));   // MSB
  Wire.write((int)(0 & 0xFF)); // LSB
  for (unsigned int i = 0; i < len ; i++){
    Wire.write((uint8_t) cdata[i ]);
  }
    
  Wire.write((uint8_t) _terminator);
  Wire.endTransmission();
}

void ExtEEPROM::writeEEPROM(unsigned int eeaddress, uint8_t c)
{
  /*
   * @brief performs a write operation of a single byte at a specific address
  */
  Wire.beginTransmission(EADDRESS);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(c);
  Wire.endTransmission();
}

char *ExtEEPROM::ERead() {
  /*
   * @brief performs a sequential read until it reads the terminator character
  */
  char *cdata = (char *) calloc(1, sizeof(char));
  unsigned int i = 0;
  
  uint8_t rdata = readEEPROM(i);
  while (rdata != _terminator && i < _max_iterations) {
    cdata = (char *)realloc(cdata, i + 2);
    cdata[i] = (char) rdata;
    cdata[i + 1] = '\0';
    i++;
    
    rdata = readEEPROM(i);
  }

  return cdata;
}

uint8_t ExtEEPROM::readEEPROM(unsigned int eeaddress)
{
  /*
   * @brief reads a single byte from eeprom at the specified address
  */
  uint8_t rdata = (uint8_t) 0xFF;

  Wire.beginTransmission(EADDRESS);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(EADDRESS, 1);

  if (Wire.available()) rdata = Wire.read();
  return rdata;
}