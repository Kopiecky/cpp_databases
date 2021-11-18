#include "client.hpp"

Client::Client(int argc, const char** argv)
{
    if (args.parseArgs(argc, argv)) 
    {
        exit(1);
    }
    else
    {
        db.mysql_connection_setup(args.arguments);
    }
    args.~Args();
}

Client::~Client()
{
    ;
}

void Client::startClient()
{
    db.mysql_execute_query();
    db.mysql_show_results();
}