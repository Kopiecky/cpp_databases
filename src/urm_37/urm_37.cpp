#include <string.h>
#include "urm_37.hpp"

Urm_37::Urm_37(const char* const port) : serial(port, "OFF", 9600, 1, 8)
{
    ;
}

Urm_37::~Urm_37()
{
    ;
}

unsigned int Urm_37::readSensor(const char* const type)
{
    serial.serial_write((!strcmp(type, "distance")) ? (uint8_t*)read_distance_cmd : (uint8_t*)read_temperature_cmd, 4);
    
    for (unsigned int i = 0; i < 4; ++i)
    {
        serial.serial_read((uint8_t*)&buffer[i], 1);
    }
    unsigned int reading = buffer[1] << 8;
    reading = reading + buffer[2];
    return reading;
}