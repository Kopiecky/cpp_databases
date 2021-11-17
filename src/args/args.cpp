#include "args.hpp"

#include <errno.h>
#include <iostream>
#include <string.h>

Args::Args()
{
    ;
}
Args::~Args()
{
    ;
}

int Args::showHelp()
{
    std::cout << "dbcomm 0.0.1" << std::endl;
    std::cout << "MySQL and NoSQL communication comparison from GNU/Linux terminal."
              << std::endl;
    std::cout << "Usage: dbcomm [arguments] command" << std::endl << std::endl;

    std::cout << "Arguments:" << std::endl;
    std::cout << "-t"
              << "\t\t"
              << "Database type selection (mysql or nosql)" << std::endl;
    std::cout << "-s"
              << "\t\t"
              << "Database server" << std::endl;
    std::cout << "-d"
              << "\t\t"
              << "Database name" << std::endl;
    std::cout << "-u"
              << "\t\t"
              << "Database user" << std::endl;
    return -1;
}

int Args::showError(Error_Types_t error)
{
    int ret = 0;

    switch (error)
    {
        case INPUT:
            std::cout << "Not enough input arguments. For help see -h" << std::endl;
            break;
        case VALUE:
            std::cout << "Wrong input value. For help see -h" << std::endl;
            break;
    }
    return -EINVAL;
}

int Args::parseArgs(int argc, const char** argv)
{
    int ret = 0;

    struct
    {
        unsigned int help : 1;
        unsigned int error : 1;
    } flags;

    flags = {0};

    if (argc <= 1)
    {
        ret = showError(INPUT);
        flags.error = 1;
    }
    else if ((argc > 1) && (argc % 2 == 0))
    {
        ret = showError(INPUT);
        flags.error = 1;
    }
    else if (!strcmp(argv[1], ARGS_HELP))
    {
        ret       = showHelp();
        flags.help = 1;
    }
    else
    {
        for (unsigned int i = 1; i < argc; i += 2)
        {
            if (!strcmp(argv[i], ARGS_DB_NAME))
            {
                arguments[DB_NAME] = argv[i + 1];
                arg_counter++;
            }
            else if (!strcmp(argv[i], ARGS_SERVER))
            {
                arguments[SERVER] = argv[i + 1];
                arg_counter++;
            }
            else if (!strcmp(argv[i], ARGS_USER))
            {
                arguments[USER] = argv[i + 1];
                arg_counter++;
            }
            else if (!strcmp(argv[i], ARGS_DB_TYPE))
            {
                arguments[DB_TYPE] = argv[i + 1];
                arg_counter++;
            }
            else
            {
                ret = showError(VALUE);
                flags.help = 1;
                break;
            }
        }
    }

    if ((arg_counter != 4) && (!flags.help) && (!flags.error))
    {
        ret = showError(INPUT);
    }

    return ret;
}