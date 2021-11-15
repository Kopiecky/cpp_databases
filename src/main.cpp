#include "database/database.hpp"
#include "urm_37/urm_37.hpp"

int main(int argc, char const **argv)
{
    char server[] = "localhost";
    char user[] = "daniel";
    char database[] = "PBD";
    char password[] = "password"; 
    char query[] = "select * from dane_pomiarowe";

    MySQL db(server, user, database, password);
    Urm_37 sensor("/dev/ttyUSB0");

    db.mysql_connection_setup();
    db.mysql_execute_query(query);
    db.mysql_show_results();

    while (1)
    {
       unsigned int reading = sensor.readSensor("distance");
       std::cout << reading << std::endl;
    }

    return 0;
}