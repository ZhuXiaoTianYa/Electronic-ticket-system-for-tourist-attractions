#include "MySQL.hpp"

// 饿汉式单例初始化
MySQL &MySQL::getInstance()
{
    static MySQL instance;
    return instance;
}

MySQL::MySQL()
{
    _mys.resize(5, nullptr); // 初始化5个连接
    init_MySQL();
}

void MySQL::init_MySQL()
{
    for (auto &conn : _mys)
    {
        conn = mysql_init(nullptr);
        if (!conn)
        {
            logMessage(ERROR, "MySQL init error");
            exit(1);
        }

        if (!mysql_real_connect(conn, host.c_str(), user.c_str(),
                                passwd.c_str(), db.c_str(), port, nullptr, 0))
        {
            logMessage(ERROR, "MySQL connection error: %s", mysql_error(conn));
            exit(2);
        }

        // 设置自动重连
        my_bool reconnect = 1;
        mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect);

        logMessage(NORMAL, "MySQL connection established");
    }
}

MySQL::~MySQL()
{
    for (auto &conn : _mys)
    {
        if (conn)
        {
            mysql_close(conn);
            conn = nullptr;
        }
    }
}

MYSQL *MySQL::getConnection()
{
    // 简单轮询分配连接
    static size_t index = 0;
    MYSQL *conn = _mys[index];
    index = (index + 1) % _mys.size();
    return conn;
}