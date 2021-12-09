#ifndef SRC_CLIENT
#define SRC_CLIENT

#include <string>

#include "database/databaseMySQL.hpp"
#include "database/mongoManager.hpp"

class Client
{
    MySQL db;

private:
    const std::string askForQuery();
    MongoManager* myMongo;

public:
    Client(const char** const details);
    ~Client();
};
#endif