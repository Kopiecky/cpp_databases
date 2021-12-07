#include "client.hpp"

#include <iostream>

Client::Client(const char** const details)
{
    std::string type = details[1];
    if (!type.compare("mysql"))
    {
        int response = db.connect(details);
        if (response >= 0)
        {
            std::string query = askForQuery();
            if (query.empty())
            {
                db.executeQuery();
            }
            else
            {
                db.executeQuery(query.c_str());
            }
        }
        db.showResults();
    }
    if(!type.compare("nosql"))
    {
        std::cout << "NoSQL client\n";
    }
}

const std::string Client::askForQuery()
{
    std::string query;
    std::cout << "Query: ";
    std::getline(std::cin, query);
    return query;
}

Client::~Client() {}