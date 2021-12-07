#ifndef SRC_CLIENT
#define SRC_CLIENT

#include <string>

#include "database/databaseMySQL.hpp"

class Client
{
    MySQL db;

private:
    const std::string askForQuery();

public:
    Client(const char** const details);
    ~Client();
};
#endif