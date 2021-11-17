#ifndef ARGS_HEADER
#define ARGS_HEADER

#define ARGS_DB_NAME "-d"
#define ARGS_USER    "-u"
#define ARGS_HELP    "-h"
#define ARGS_SERVER  "-s"
#define ARGS_DB_TYPE "-t"

#define NUM_OF_ARGS 4

class Args
{
private:

    typedef enum Error_Types_e
    {
        INPUT,
        VALUE
    } Error_Types_t;
    typedef enum Argument_Types_e
    {
        SERVER,
        USER,
        DB_NAME,
        DB_TYPE
    } Argument_Types_t;

public:
    const char* arguments[NUM_OF_ARGS] = {0};
    unsigned int arg_counter = 0;

private:
    int showHelp();
    int showError(Error_Types_t error);

public:
    Args();
    ~Args();
    int parseArgs(int argc, const char** argv);
};

#endif