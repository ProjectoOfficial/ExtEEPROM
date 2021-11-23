#ifndef ExtEEPROM_H_
#define ExtEEPROM_H_

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "Wire.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

#define EADDRESS 0x50    //Address of 24LC256 eeprom chip
#define STOPBYTE 255
#define MAXITERATIONS 90

class ExtEEPROM{
    public:
        ExtEEPROM();
        ExtEEPROM(uint8_t EEPROM_Address, uint8_t stop_byte, uint16_t max_iteration);
        void begin();
        char *ERead(unsigned int startaddress);
        void EWrite(unsigned int startaddress, string data) ;

    private:
        void writeEEPROM(unsigned int eeaddress, uint8_t c);
        uint8_t readEEPROM(unsigned int eeaddress);

        uint8_t _EEPROM_Address;
        uint8_t _stop_byte;
        uint16_t _max_iteration;
};

#ifdef __cplusplus
}
#endif

#endif /*ExtEEPROM_H_*/