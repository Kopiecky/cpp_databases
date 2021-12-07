#ifndef SRC_DATABASE_MYSQL
#define SRC_DATABASE_MYSQL

#include <mysql/mysql.h>
#include <string>
#include <vector>

class MySQL
{
private:
    static const size_t NUM_OF_DETAILS = 4;
    const std::string d_details[NUM_OF_DETAILS] = {"localhost", "daniel", "PBD", "password"};

    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;

    std::string m_details[NUM_OF_DETAILS];
    std::string m_query;
    std::string m_password;

public:
    enum Details
    {
        SERVER,
        USER,
        DATABASE,
        PASSWORD
    };

private:
    void setDetails(const char** const details);
    void askForPassword();

public:
    MySQL();
    int connect(const char** const details);
    int executeQuery(const char* query = "select * from dane_pomiarowe");
    void showResults();
    const std::string& get(Details what) const;
    ~MySQL();
};

#endif