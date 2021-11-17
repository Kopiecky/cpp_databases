#ifndef URM_37_HEADER
#define URM_37_HEADER

#include <stdint.h>
#include "../serial/serial.hpp"

class Urm_37
{
private:
    const uint8_t read_temperature_cmd[4] = {0x11, 0x00, 0x00, 0x11};
    const uint8_t read_distance_cmd[4]    = {0x22, 0x00, 0x00, 0x22};
    const char* port;
    uint8_t buffer[4];
    
    Serial serial;

public:
    Urm_37(const char* const port);
    ~Urm_37();
    unsigned int readSensor(const char* const type);
};

#endif