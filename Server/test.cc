#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include "Log.hpp"

int main()
{
    const std::string host = "127.0.0.1";
    const std::string user = "study";
    const std::string passwd = "123456";
    const std::string db = "Electronic_ticket_system_for_tourist_attractions";
    const unsigned int port = 3306;

    MYSQL *my = mysql_init(nullptr);
    if (my == nullptr)
    {
        logMessage(ERROR, "mysql_init failed: %s", mysql_error(my));
        exit(1);
    }

    if (mysql_real_connect(my,
                           host.c_str(),
                           user.c_str(),
                           passwd.c_str(),
                           db.c_str(),
                           port,
                           nullptr,
                           0) == nullptr)
    {
        logMessage(ERROR, "mysql_real_connect failed: %s", mysql_error(my));
        mysql_close(my);
        exit(2);
    }

    logMessage(NORMAL, "MySQL connected successfully");
    mysql_close(my);
    return 0;
}