#ifndef HEADER_CLIENT
#define CLIENT

#include "../database/database.hpp"
#include "../args/args.hpp"

class Client
{

private:
    Args args;
    MySQL db;

public:
    Client(int argc, const char** argv);
    ~Client();
    void startClient();
};

#endif