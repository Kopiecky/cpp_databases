#include "server.hpp"

#include <stdio.h>
#include <string.h>

Server::Server(int argc, const char** argv)
{
    if (args.parseArgs(argc, argv, "server"))
    {
        exit(1);
    }
    else
    {
        meas_type = args.arguments[SENSOR_NUM];
        db.mysql_connection_setup(details);
        sensor.openSensor(args.arguments[PORT_NUM]);
    }
    args.~Args();
}

Server::~Server()
{
    ;
}

void Server::startServer()
{
    unsigned int i = 0;

    sensor.readSensor(meas_type);
    while (1)
    {
        ++i;
        if (i == 50)
        {
            sprintf(value, "%d);", sensor.reading);
            strcat(insert, value);
            db.mysql_execute_query(insert);
            strcpy(insert, INSERT);
            break;
        }
    }
}