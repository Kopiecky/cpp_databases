#include "server/server.hpp"

Server::Server(const char** const details) 
{
    std::string type = details[1];
    if (!type.compare("mysql"))
    {
        int response = db.connect(details);
        if (response >= 0)
        {
            insertData(5);
        }
    }
}

Server::~Server() {}

void Server::insertData(int data)
{
    insert = "insert into dane_pomiarowe(czas, dane) values(now(), ";
    std::string dataString = std::to_string(data);
    dataString += ");";
    insert.append(dataString);
    db.executeQuery(insert.c_str());
    insert.clear();
}