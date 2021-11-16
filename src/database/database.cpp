#include "database.hpp"
#include <string.h>

MySQL::MySQL(const char** const arguments)
{
    details[SERVER]   = arguments[SERVER];
    details[USER]     = arguments[USER];
    details[DATABASE] = arguments[DATABASE];
}

MySQL::~MySQL()
{
    mysql_free_result(res);
    mysql_close(con);
}

void MySQL::mysql_askForPassword()
{
    std::string pass;

    std::getline(std::cin, pass);

    details[PASSWORD] = strdup(pass.data());
}

void MySQL::mysql_askForQuery()
{
    std::string query;

    std::getline(std::cin, query);

    details[QUERY] = strdup(query.data());
}

int MySQL::mysql_connection_setup()
{
    mysql_askForPassword();
    mysql_askForQuery();

    con = mysql_init(NULL);

    if (!mysql_real_connect(
            con,
            details[SERVER],
            details[USER],
            details[PASSWORD],
            details[DATABASE],
            0,
            NULL,
            0))
    {
        std::cout << "Connection error: " << mysql_error(con) << std::endl;
        exit(1);
    }
    return 0;
}

int MySQL::mysql_execute_query()
{
    if (mysql_query(con, details[QUERY]))
    {
        std::cout << "MySQL Query Error: " << mysql_error(con) << std::endl;
        exit(1);
    }
    res = mysql_use_result(con);
    return 0;
}

int MySQL::mysql_show_results()
{
    std::cout << std::endl << "DATABASE: " << details[DATABASE] << std::endl;
    std::cout << "QUERY: " << details[QUERY] << std::endl;
    std::cout << "RESULT:" << std::endl << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        std::cout << row[0] << " | " << row[1] << " | " << row[2]
                  << " | " << std::endl;
    }

    std::cout << std::endl;

    return 0;
}