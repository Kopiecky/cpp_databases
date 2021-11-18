#ifndef HEADER_SERVER
#define HEADER_SERVER

#include "../args/args.hpp"
#include "../database/database.hpp"
#include "../urm_37/urm_37.hpp"

#define PORT_NUM   0
#define SENSOR_NUM 2
#define INSERT     "insert into dane_pomiarowe(czas, pomiar) values(now(), "

class Server
{

public:
    typedef enum Measurement_Type_e
    {
        DISTANCE,
        TEMPERATURE
    } Measurement_Type_t;

private:

    char insert[80] = "insert into dane_pomiarowe(czas, pomiar) values(now(), ";
    char value[10];

    const char* details[NUM_OF_DETAILS] = {"localhost", "daniel", "PBD"};
    
    const char* meas_type;
    
    Args args;
    MySQL db;
    Urm_37 sensor;

public:
    Server(int argc, const char** argv);
    ~Server();
    void startServer();
};


#endif