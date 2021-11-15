#include "database.hpp"

MySQL::MySQL(const char* server, const char* user, const char* database, const char* password)
{
    MySQL::details[SERVER] = server;
    MySQL::details[USER] = user;
    MySQL::details[DATABASE] = database;
    MySQL::details[PASSWORD] = password;
}

MySQL::~MySQL()
{
    mysql_free_result(MySQL::res);
    mysql_close(MySQL::con);
}

int MySQL::mysql_connection_setup()
{
    MySQL::con = mysql_init(NULL);

    if (!mysql_real_connect(con, MySQL::details[SERVER], MySQL::details[USER], MySQL::details[PASSWORD], MySQL::details[DATABASE], 0, NULL, 0))
    {
        std::cout << "Connection error: " << mysql_error(con) << std::endl;
        exit(1);
    }
    return 0;
}

int MySQL::mysql_execute_query(const char* const sql_query)
{
    MySQL::query = sql_query;
    if (mysql_query(MySQL::con, sql_query))
    {
        std::cout << "MySQL Query Error: " << mysql_error(MySQL::con) << std::endl;
        exit(1);
    }
    MySQL::res = mysql_use_result(MySQL::con);
    return 0;
}

int MySQL::mysql_show_results()
{
    std::cout << std::endl<< "DATABASE: " << MySQL::details[DATABASE] << std::endl;
    std::cout << "QUERY: " << MySQL::query << std::endl;
    std::cout << "RESULT:" << std::endl << std::endl;

    while ((MySQL::row = mysql_fetch_row(MySQL::res)) != NULL)
    {
        std::cout << MySQL::row[0] << " | " << MySQL::row[1] << " | " << MySQL::row[2] << " | " << std::endl;
    }

    std::cout << std::endl;

    return 0;
}