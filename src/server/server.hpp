#ifndef SRC_SERVER
#define SRC_SERVER


#include "database/databaseMySQL.hpp"
#include "sensor/sensor.hpp"
#include <string>

class Server
{
private:
    std::string insert;
    MySQL db;
    Sensor sensor;
    void insertData(int data);

public:
    Server(const char** const details);
    ~Server();
};


#endif