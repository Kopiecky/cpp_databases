#include <string.h>

#include "args/args.hpp"
#include "database/database.hpp"
#include "urm_37/urm_37.hpp"

int main(int argc, const char** argv)
{
    MySQL db(argc, argv);

    while (1)
    {
        db.mysql_connection_setup();
        db.mysql_execute_query();
        db.mysql_show_results();
    }
    return 0;
}
