#include "server.hpp"

#include <ctime>

Server::Server(const char** const details)
{
    std::string type = details[1];
    if (!type.compare("mysql"))
    {
        int response = db.connect(details);
        if (response >= 0)
        {
            insertDataMySQL(5);
        }
    }
    else if (!type.compare("nosql"))
    {
        int response = db.connect(details);
        if (response >= 0)
        {
            myMongo = new MongoManager();
            myMongo->accessCollection();
            insertDataNoSQL(3);
        }
    }
}

Server::~Server()
{
    delete myMongo;
}

void Server::insertDataMySQL(int data)
{
    insert                 = "insert into dane_pomiarowe(czas, dane) values(now(), ";
    std::string dataString = std::to_string(data);
    dataString += ");";
    insert.append(dataString);
    db.executeQuery(insert.c_str());
    insert.clear();
}

void Server::insertDataNoSQL(int data)
{
    auto time      = std::chrono::system_clock::now();
    std::time_t t  = std::chrono::system_clock::to_time_t(time);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size() - 1);
    myMongo->insertData(ts, "distance", 3);
}