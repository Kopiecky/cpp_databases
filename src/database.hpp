#include <mysql/mysql.h>
#include <iostream>

#define NUM_OF_DETAILS 4
class MySQL
{
    private:
        typedef enum Detail_Types_e
        {
            SERVER,
            USER,
            PASSWORD,
            DATABASE
        } Detail_Types_t;

        const char* details[NUM_OF_DETAILS];
        const char* query;

        MYSQL* con;
        MYSQL_RES* res;
        MYSQL_ROW row;

    public:
        MySQL(const char* server, const char* user, const char* database, const char* password);
        ~MySQL();
        int mysql_connection_setup();
        int mysql_execute_query(const char* const sql_query);
        int mysql_show_results();
};