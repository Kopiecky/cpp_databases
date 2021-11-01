#include <mysql/mysql.h>
#include <iostream>

#define NUM_OF_ELEMENTS 4

typedef struct Connection_Details_s
{
    const char *server, *user, *password, *database;
} Connection_Details_t;


Connection_Details_t create_details();
MYSQL* mysql_connection_setup(Connection_Details_t mysql_details);
MYSQL_RES* mysql_execute_query(MYSQL* connection, const char* const sql_query);