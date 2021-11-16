#include <string.h>

#include "args/args.hpp"
#include "database/database.hpp"
#include "urm_37/urm_37.hpp"

int main(int argc, char const** argv)
{
    Args args;
    args.parseArgs(argc, argv);
    MySQL db(args.arguments);

    db.mysql_connection_setup();
    db.mysql_execute_query();
    db.mysql_show_results();

    return 0;
}
