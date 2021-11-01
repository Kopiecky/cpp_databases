#include "database.hpp"

int main(int argc, char const **argv)
{
    char server[] = "localhost";
    char user[] = "daniel";
    char database[] = "PBD";
    char password[] = "password"; 
    char query[] = "select * from dane_pomiarowe";

    MySQL db(server, user, database, password);

    db.mysql_connection_setup();
    db.mysql_execute_query(query);
    db.mysql_show_results();

    return 0;
}