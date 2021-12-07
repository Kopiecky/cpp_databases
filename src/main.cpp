#include <iostream>

#include "argparser/argparser.hpp"
#include "client/client.hpp"
#include "server/server.hpp"

int main(int argc, const char** argv)
{
    Argparser argparser;

    argparser.add("-t", "Type select", true);
    argparser.add("-db", "Database select (nosql or mysql)", true);
    bool error = argparser.parse(argc, argv);

    if (!error)
    {
        std::vector<std::string> arguments = argparser.getArguments();
        std::vector<const char*> ptrs;
        for (std::string const& str : arguments)
        {
            ptrs.push_back(str.data());
        }

        if (!arguments[0].compare("client"))
        {
            Client client(ptrs.data());
        }
        if (!arguments[0].compare("server"))
        {
            Server server(ptrs.data());
        }
    }

    return 0;
}