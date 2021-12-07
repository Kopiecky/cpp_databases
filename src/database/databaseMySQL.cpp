#include "databaseMySQL.hpp"

#include <cassert>
#include <iostream>

MySQL::MySQL() {}

MySQL::~MySQL() 
{
    mysql_free_result(res);
    mysql_close(con);
}

int MySQL::connect(const char** const details)
{
    int ret = 0;

    setDetails(details);

    con = mysql_init(NULL);

    if (!mysql_real_connect(
            con,
            m_details[SERVER].c_str(),
            m_details[USER].c_str(),
            m_details[PASSWORD].c_str(),
            m_details[DATABASE].c_str(),
            0,
            NULL,
            0))
    {
        std::cout << "Connection error: " << mysql_error(con) << std::endl;
        ret = -1;
    }
    return ret;
}

void MySQL::setDetails(const char** const details)
{
    if (!details[2])
        for (size_t i = 0; i < NUM_OF_DETAILS; ++i)
        {
            m_details[i] = d_details[i].c_str();
        }
    else
    {
        for (size_t i = 0; i < NUM_OF_DETAILS - 1; ++i)
        {
            m_details[i] = details[i];
        }
        askForPassword();
    }
}

void MySQL::askForPassword()
{
    std::cout << "Password: ";
    std::getline(std::cin, m_details[PASSWORD]);
}

int MySQL::executeQuery(const char* const query)
{
    int ret = 0;
    m_query = query;

    if (mysql_query(con, m_query.c_str()))
    {
        std::cout << "MySQL Query Error: " << mysql_error(con) << std::endl;
        res = NULL;
        ret = -1;
    }
    else
    {
        res = mysql_use_result(con);
        ret = 0;
    }
    return ret;
}

void MySQL::showResults()
{
    std::cout << std::endl << "DATABASE: " << m_details[DATABASE] << std::endl;
    std::cout << "QUERY: " << m_query << std::endl;
    std::cout << "RESULT:" << std::endl << std::endl;

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        std::cout << row[0] << " | " << row[1] << " | " << row[2] << " | " << std::endl;
    }

    std::cout << std::endl;
}

inline const std::string& MySQL::get(Details what) const
{
    switch (what)
    {
        case SERVER:
            return m_details[SERVER];
            break;
        case DATABASE:
            return m_details[DATABASE];
            break;
        case USER:
            return m_details[USER];
            break;
    }
}