#ifndef DATABASE_HEADER
#define DATABASE_HEADER

#include <iostream>
#include <mysql/mysql.h>

#include "../args/args.hpp"

#define NUM_OF_DETAILS 5
class MySQL
{
private:
    typedef enum Argument_Types_e
    {
        SERVER,
        USER,
        DATABASE,
        PASSWORD,
        QUERY
    } Argument_Types_t;

    const char* details[NUM_OF_DETAILS];

    Args args;
    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;

private:
    void mysql_askForPassword();
    void mysql_askForQuery();

public:
    MySQL(int argc, const char** argv);
    ~MySQL();
    int mysql_connection_setup();
    int mysql_execute_query();
    int mysql_show_results();
};

#endif