#include "sensor.hpp"

#include <unistd.h>

Sensor::Sensor(std::string port) : m_port(port), serial(port) {}

Sensor::~Sensor() {}

unsigned int Sensor::read(std::string what)
{
    Types what_type = checkType(what);

    int res = serial.connect();
    if (res >= 0)
    {
        res = serial.writeToPort(what_type ? read_temperature : read_distance, CMD_SIZE);

        if (res >= 0)
        {
            for (size_t i = 0; i < CMD_SIZE; ++i)
            {
                serial.readFromPort(&buffer[i], 1);
            }
            res = buffer[1] << 8;
            res += buffer[2];
        }
        else
        {
            res = 0;
        }
    }
    else
    {
        res = 0;
    }

    return res;
}

Sensor::Types Sensor::checkType(std::string& what)
{
    Types what_type;

    if (!what.compare("distance"))
    {
        what_type = DISTANCE;
    }
    if (!what.compare("temperature"))
    {
        what_type = TEMPERATURE;
    }
    return what_type;
}
