#include "database.hpp"

int main(int argc, char const **argv)
{
    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;
    char query[] = "select * from dane_pomiarowe";
    unsigned int i = 0;

    Connection_Details_t connection_details = create_details();

    con = mysql_connection_setup(connection_details);
    res = mysql_execute_query(con, query);

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << std::endl;
    }

    mysql_free_result(res);
    mysql_close(con);

    return 0;
}