#include "database.hpp"

Connection_Details_t create_details()
{
    Connection_Details_t details =
    {
        .server = "localhost",
        .user = "daniel",
        .password = "password",
        .database = "PBD",
    };
    return details;
}

MYSQL* mysql_connection_setup(Connection_Details_t mysql_details)
{
    MYSQL* connection = mysql_init(NULL);

    if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0))
    {
        std::cout << "Connection error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    return connection;
}

MYSQL_RES* mysql_execute_query(MYSQL* connection, const char* const sql_query)
{
    if (mysql_query(connection, sql_query))
    {
        std::cout << "MySQL Query Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
    return mysql_use_result(connection);
}
