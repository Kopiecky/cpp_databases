#ifndef ARGS_HEADER
#define ARGS_HEADER

#define ARGS_DB_NAME "-d"
#define ARGS_USER    "-u"
#define ARGS_HELP    "-h"
#define ARGS_SERVER  "-s"
#define ARGS_DB_TYPE "-t"


#define ARGS_NUM 4

class Args
{
private:
    typedef enum Argument_Types_e
    {
        SERVER,
        USER,
        DB_NAME,
        DB_TYPE
    } Argument_Types_t;

public:
    const char* arguments[ARGS_NUM];

private:
    void showHelp();
    void showError();

public:
    Args();
    ~Args();
    int parseArgs(int argc, const char** argv);
};

#endif