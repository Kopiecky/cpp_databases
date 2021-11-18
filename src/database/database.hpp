#ifndef DATABASE_HEADER
#define DATABASE_HEADER

#include <mysql/mysql.h>

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

    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;

    const char* details[NUM_OF_DETAILS];

private:
    void mysql_parseParameters(const char** const parameters);
    void mysql_askForPassword();
    void mysql_askForQuery();

public:
    MySQL();
    ~MySQL();
    int mysql_connection_setup(const char** const parameters);
    int mysql_execute_query();
    int mysql_show_results();
};

#endif