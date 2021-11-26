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
#define TERMINATOR 0xFE
#define MAXITERATIONS 1000

class ExtEEPROM{
    public:
        ExtEEPROM();
        ExtEEPROM(uint8_t EEPROM_Address, uint8_t terminator, uint16_t max_iteration);
        void begin();
        char *ERead();
        void EWrite(String data) ;
        void writeEEPROM(unsigned int eeaddress, uint8_t c);
        uint8_t readEEPROM(unsigned int eeaddress);

    private:

        uint8_t _EEPROM_Address;
        uint8_t _terminator;
        uint16_t _max_iterations;
};

#ifdef __cplusplus
}
#endif

#endif /*ExtEEPROM_H_*/