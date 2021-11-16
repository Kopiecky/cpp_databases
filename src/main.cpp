#include "database/database.hpp"
#include "urm_37/urm_37.hpp"
#include <string.h>

#define INSERT "insert into dane_pomiarowe(czas, pomiar) values(now(), "

int main(int argc, char const** argv)
{

    char server[]   = "localhost";
    char user[]     = "daniel";
    char database[] = "PBD";
    char password[] = "password";
    const char select[]    = "select * from dane_pomiarowe";
    const char insert1[] = "insert into dane_pomiarowe(czas, pomiar) values(now(), ";
    char insert[]   = "insert into dane_pomiarowe(czas, pomiar) values(now(), ";
    char value[4];
    char insert_query[40];
    unsigned int i = 0;
    unsigned int reading = 0;

    MySQL db(server, user, database, password);
    Urm_37 sensor("/dev/ttyUSB1");

    db.mysql_connection_setup();

    while (1)
    {
        reading = sensor.readSensor("distance");
        ++i;
        if (i == 50)
        {
            sprintf(value, "%d);", reading);
            strcat(insert, value);
            db.mysql_execute_query(insert);
            db.mysql_execute_query(select);
            db.mysql_show_results();
            strcpy(insert, INSERT);
            i = 0;
    }

    }

    return 0;
}
