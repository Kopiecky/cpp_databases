#include "args.hpp"

#include <iostream>
#include <string.h>
#include <errno.h>

Args::Args()
{
    ;
}

Args::~Args()
{
    ;
}

void Args::showHelp()
{
    std::cout << "This is help" << std::endl;
}

void Args::showError()
{
    std::cout << "Error" << std::endl;
}

int Args::parseArgs(int argc, const char** argv)
{
    unsigned int counter = 0;
    int ret              = 0;

    if ((argc > 1) && (argc % 2 == 0))
    {
        showError();
    }
    else
    {
        for (unsigned int i = 1; i < argc; i += 2)
        {
            if (!strcmp(argv[i], ARGS_DB_NAME))
            {
                arguments[DB_NAME] = argv[i + 1];
            }
            else if (!strcmp(argv[i], ARGS_SERVER))
            {
                arguments[SERVER] = argv[i + 1];
            }
            else if (!strcmp(argv[i], ARGS_USER))
            {
                arguments[USER] = argv[i + 1];
            }
            else if (!strcmp(argv[i], ARGS_DB_TYPE))
            {
                arguments[DB_TYPE] = argv[i + 1];
            }
            else if (!strcmp(argv[i], ARGS_HELP))
            {
                showHelp();
            }
            else
            {
                showError();
            }
        }
    }
    return 0;
}