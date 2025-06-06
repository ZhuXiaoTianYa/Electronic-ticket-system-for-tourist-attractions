#pragma once
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include "Log.hpp"

class MySQL
{
private:
    // 私有构造函数（禁止外部创建实例）
    MySQL();

    // 删除拷贝构造和赋值运算符
    MySQL(const MySQL &) = delete;
    MySQL &operator=(const MySQL &) = delete;

    // 数据库配置
    const std::string host = "127.0.0.1";
    const std::string user = "study";
    const std::string passwd = "123456";
    const std::string db = "Electronic_ticket_system_for_tourist_attractions";
    const unsigned int port = 3306;

    // 初始化数据库连接
    void init_MySQL();

public:
    ~MySQL();

    // 获取单例实例
    static MySQL &getInstance();

    // 从连接池获取一个数据库连接
    MYSQL *getConnection();

    // 归还连接（实际是空操作，连接池模式）
    void releaseConnection(MYSQL *) {}

private:
    std::vector<MYSQL *> _mys; // 数据库连接池
};