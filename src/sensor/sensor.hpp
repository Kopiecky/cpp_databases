#ifndef SRC_SENSOR
#define SRC_SENSOR

#include <vector>

#include "serial/serial.hpp"

class Sensor
{
private:
    enum Types
    {
        DISTANCE,
        TEMPERATURE
    };
    static const unsigned int CMD_SIZE       = 4;
    const uint8_t read_temperature[CMD_SIZE] = {0x11, 0x00, 0x00, 0x11};
    const uint8_t read_distance[CMD_SIZE]    = {0x22, 0x00, 0x00, 0x22};
    uint8_t buffer[CMD_SIZE];
    Serial serial;
    std::string m_port;

private:
    Types checkType(std::string& what);

public:
    Sensor(std::string port = "/dev/ttyUSB0");
    ~Sensor();
    unsigned int read(std::string what = "distance");
};

#endif