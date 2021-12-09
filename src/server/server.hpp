#ifndef SRC_SERVER
#define SRC_SERVER


#include "database/databaseMySQL.hpp"
#include "sensor/sensor.hpp"
#include "database/mongoManager.hpp"
#include <string>

class Server
{
private:
    MongoManager* myMongo;
    std::string insert;
    MySQL db;
    Sensor sensor;
    void insertDataMySQL(int data);
    void insertDataNoSQL(int data);

public:
    Server(const char** const details);
    ~Server();
};


#endif