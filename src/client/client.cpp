#include "client.hpp"
#include <string>
#include <string.h>
#include <iostream>

Client::Client(int argc, const char** argv)
{
    if (args.parseArgs(argc, argv, "client")) 
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

void Client::askForQuery()
{
    std::string query_s;

    std::cout << "Query: ";
    std::getline(std::cin, query_s);

    query = strdup(query_s.data());
}

void Client::startClient()
{
    askForQuery();
    db.mysql_execute_query(query);
    db.mysql_show_results();
}