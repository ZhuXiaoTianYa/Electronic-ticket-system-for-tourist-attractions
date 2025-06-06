#include <iostream>
#include <memory>
#include "TcpServer.hpp"
#include "Protocol.hpp"
#include <mysql/mysql.h>
#include "MySQL.hpp"
#include <unordered_map>
#include <vector>

static void usage(std::string proc)
{
    std::cerr << "Usage:\n\t" << proc << " port"
              << "\n\n";
}

bool Login(std::string &account, std::string &password, tcpserver::Connection *conn)
{
    MYSQL *mysql = MySQL::getInstance().getConnection();
    // select((select MD5('123456'))=(select password from users where id=20240001));
    std::string sql = "select((select MD5('" + password + "'))=(select password from users where id=" + account + "));";
    logMessage(NORMAL, "mysql_query: %s", sql.c_str());
    Login_Class login;
    // 执行查询
    if (mysql_query(mysql, sql.c_str()))
    {
        logMessage(ERROR, "Query failed: %s", mysql_error(mysql));
        login._status = LOGIN_FAIL;
        return false;
    }

    // 获取结果集
    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result)
    {
        // 没有结果集（可能是查询没有返回数据）
        logMessage(ERROR, "No result set: %s", mysql_error(mysql));
        login._status = LOGIN_FAIL;
        return false;
    }

    // 检查是否有结果
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0)
    {
        // 用户不存在
        logMessage(WARNING, "User not found: %s", account.c_str());
        mysql_free_result(result);
        login._status = LOGIN_FAIL;
        return false;
    }

    // 处理结果（只取第一行）
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0])
    {
        // 检查匹配结果 (0 = 不匹配, 1 = 匹配)
        int match = atoi(row[0]);
        login._status = ((match == 1) ? LOGIN_SUCCESS : LOGIN_FAIL);
        logMessage(DEBUG, "Match result: %d", match);
    }
    else
    {
        // 无法获取结果
        logMessage(ERROR, "Failed to fetch row");
        login._status = LOGIN_FAIL;
    }

    mysql_free_result(result);
    // MYSQL_RES *result = mysql_store_result(mysql);

    // int rows = mysql_num_rows(result);
    // int fields = mysql_num_fields(result);

    // for (int i = 0; i < rows; i++)
    // {
    //     MYSQL_ROW row = mysql_fetch_row(result);
    //     for (int j = 0; j < fields; j++)
    //     {
    //         std::cout << row[j] << "\t";
    //     }
    //     std::cout << std::endl;
    // }

    // mysql_free_result(result);
    std::string respStr;
    login.response_serialize(&respStr);
    logMessage(DEBUG, "serialize success");
    conn->_outbuffer += enLength(respStr);
    std::cout << "-----------result: " << conn->_outbuffer << std::endl;
    if (conn->_sender)
        conn->_sender(conn);
    return true;
}

bool Register(std::string &name, std::string &password, tcpserver::Connection *conn)
{
    MYSQL *mysql = MySQL::getInstance().getConnection();
    // insert into users (name ,password) values('Andy',MD5('123456'));
    std::string sql = "insert into users (name ,password) values('" + name + "',MD5('" + password + "'));";
    logMessage(NORMAL, "mysql_query: %s", sql.c_str());
    Register_Class register_;
    if (mysql_query(mysql, sql.c_str()))
    {
        logMessage(ERROR, "Query failed: %s", mysql_error(mysql));
        register_._status = REGISTER_FAIL;
        return false;
    }
    // select id from users where name = 'Andy';

    std::string personal_information = "select id from users where name = '" + name + "';";
    logMessage(NORMAL, "mysql_query: %s", personal_information.c_str());
    if (mysql_query(mysql, personal_information.c_str()))
    {
        logMessage(ERROR, "Query failed: %s", mysql_error(mysql));
        register_._status = REGISTER_FAIL;
        return false;
    }

    // 获取结果集
    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result)
    {
        // 没有结果集（可能是查询没有返回数据）
        logMessage(ERROR, "No result set: %s", mysql_error(mysql));
        register_._status = REGISTER_FAIL;
        return false;
    }

    // 检查是否有结果
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0)
    {
        // 用户不存在
        logMessage(WARNING, "User create error: %s", name.c_str());
        mysql_free_result(result);
        register_._status = REGISTER_FAIL;
        return false;
    }

    // 处理结果（只取第一行）
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0])
    {
        logMessage(NORMAL, "user create success, id= %s", row[0]);
        register_._id = row[0];
        register_._status = REGISTER_SUCCESS;
    }
    mysql_free_result(result);
    std::string respStr;
    register_.response_serialize(&respStr);
    logMessage(DEBUG, "serialize success");
    conn->_outbuffer += enLength(respStr);
    std::cout << "-----------result: " << conn->_outbuffer << std::endl;
    if (conn->_sender)
        conn->_sender(conn);
    return true;
}

bool Areas(std::string &aid, tcpserver::Connection *conn)
{
    MYSQL *mysql = MySQL::getInstance().getConnection();
    // select name , introduction ,tickets_total ,remaining_tickets from areas where aid = 10001;
    std::string sql = "select name , introduction ,tickets_total ,remaining_tickets from areas where aid = " + aid + ";";
    logMessage(NORMAL, "mysql_query: %s", sql.c_str());
    Areas_Class areas;
    // 执行查询
    if (mysql_query(mysql, sql.c_str()))
    {
        logMessage(ERROR, "Query failed: %s", mysql_error(mysql));
        areas._status = AREAS_FAIL;
        std::string respStr;
        areas.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 获取结果集
    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result)
    {
        // 没有结果集（可能是查询没有返回数据）
        logMessage(ERROR, "No result set: %s", mysql_error(mysql));
        areas._status = AREAS_FAIL;
        std::string respStr;
        areas.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);

        return false;
    }

    // 检查是否有结果
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0)
    {
        // 景点不存在
        logMessage(WARNING, "Area not found", aid.c_str());
        mysql_free_result(result);
        areas._status = AREAS_FAIL;
        std::string respStr;
        areas.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 处理结果（只取第一行）
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0])
    {
        areas._status = AREAS_SUCCESS;
        areas._name = row[0];
        areas._introduction = row[1];
        areas._tickets_total = row[2];
        areas._remaining_tickets = row[3];
    }
    else
    {
        // 无法获取结果
        logMessage(ERROR, "Failed to fetch row");
        areas._status = AREAS_FAIL;
    }

    mysql_free_result(result);
    // MYSQL_RES *result = mysql_store_result(mysql);

    // int rows = mysql_num_rows(result);
    // int fields = mysql_num_fields(result);

    // for (int i = 0; i < rows; i++)
    // {
    //     MYSQL_ROW row = mysql_fetch_row(result);
    //     for (int j = 0; j < fields; j++)
    //     {
    //         std::cout << row[j] << "\t";
    //     }
    //     std::cout << std::endl;
    // }

    // mysql_free_result(result);
    std::string respStr;
    areas.response_serialize(&respStr);
    logMessage(DEBUG, "serialize success");
    conn->_outbuffer += enLength(respStr);
    std::cout << "-----------result: " << conn->_outbuffer << std::endl;
    if (conn->_sender)
        conn->_sender(conn);
    return true;
}

bool Ticket(std::string &uid, std::string &aid, std::string &num, std::string &option, tcpserver::Connection *conn)
{
    MYSQL *mysql = MySQL::getInstance().getConnection();
    Tickets_Class ticket_resp;

    // 转换参数
    int buy_num = std::stoi(num);
    int area_id = std::stoi(aid);
    int user_id = std::stoi(uid);

    // 开始事务
    if (mysql_query(mysql, "START TRANSACTION"))
    {
        logMessage(ERROR, "Start transaction failed: %s", mysql_error(mysql));
        ticket_resp._status = TICKET_FAIL;
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    char query[512];
    // 1. 锁定行并检查剩余票数
    snprintf(query, sizeof(query),
             "SELECT remaining_tickets, name ,tickets_total FROM areas WHERE aid = %d FOR UPDATE",
             area_id);
    logMessage(NORMAL, "mysql_query: %s", query);

    if (mysql_query(mysql, query))
    {
        logMessage(ERROR, "SELECT failed: %s", mysql_error(mysql));
        mysql_rollback(mysql);
        ticket_resp._status = TICKET_FAIL;
        // sendResponse(ticket_resp, conn);
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    MYSQL_RES *res = mysql_store_result(mysql);
    if (!res || mysql_num_rows(res) == 0)
    {
        logMessage(WARNING, "Area not found: aid=%d", area_id);
        if (res)
            mysql_free_result(res);
        mysql_rollback(mysql);
        ticket_resp._status = TICKET_FAIL;
        // sendResponse(ticket_resp, conn);
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int remaining = std::stoi(row[0]);
    std::string area_name = row[1];
    int _tickets_total = std::stoi(row[2]);
    mysql_free_result(res);
    logMessage(DEBUG, "area_name: %s,_tickets_total: %s ,remaining: %s ", row[1], row[2], row[0]);
    if (option.compare("Buy") == 0)
    {
        // 2. 检查票数是否足够
        if (remaining < buy_num)
        {
            logMessage(WARNING, "Not enough tickets: requested=%d, available=%d", buy_num, remaining);
            mysql_rollback(mysql);
            ticket_resp._status = TICKET_FAIL;
            // sendResponse(ticket_resp, conn);
            std::string respStr;
            ticket_resp.response_serialize(&respStr);
            logMessage(DEBUG, "serialize success");
            conn->_outbuffer += enLength(respStr);
            std::cout << "-----------result: " << conn->_outbuffer << std::endl;
            if (conn->_sender)
                conn->_sender(conn);
            return false;
        }
        // 3. 原子更新票数（确保不会超卖）
        snprintf(query, sizeof(query),
                 "UPDATE areas SET remaining_tickets = remaining_tickets - %d "
                 "WHERE aid = %d AND remaining_tickets >= %d",
                 buy_num, area_id, buy_num);
    }
    else
    {
        // 3. 原子更新票数（确保不会超卖）
        snprintf(query, sizeof(query),
                 "UPDATE areas SET remaining_tickets = remaining_tickets + %d "
                 "WHERE aid = %d AND remaining_tickets >= %d",
                 buy_num, area_id, buy_num);
    }
    logMessage(NORMAL, "mysql_query: %s", query);

    if (mysql_query(mysql, query))
    {
        logMessage(ERROR, "UPDATE failed: %s", mysql_error(mysql));
        mysql_rollback(mysql);
        ticket_resp._status = TICKET_FAIL;
        // sendResponse(ticket_resp, conn);
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 检查是否更新成功
    if (mysql_affected_rows(mysql) != 1)
    {
        logMessage(ERROR, "Update condition failed (tickets insufficient)");
        mysql_rollback(mysql);
        ticket_resp._status = TICKET_SUCCESS;
        // sendResponse(ticket_resp, conn);
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    if (option.compare("Buy") == 0)
    {
        // 4. 创建购票记录
        snprintf(query, sizeof(query),
                 "INSERT INTO records (id, aid, tickets_total , remaining_tickets ,action,num ) VALUES (%d, %d, %d,%d, '%s',%d);",
                 user_id, area_id, _tickets_total, remaining - buy_num, option.c_str(), buy_num);
    }
    else
    {
        // 4. 创建购票记录
        snprintf(query, sizeof(query),
                 "INSERT INTO records (id, aid, tickets_total , remaining_tickets ,action,num ) "
                 "VALUES (%d, %d, %d,%d, '%s',%d)",
                 user_id, area_id, _tickets_total, remaining + buy_num, option.c_str(), buy_num);
    }
    logMessage(NORMAL, "mysql_query: %s", query);

    if (mysql_query(mysql, query))
    {
        logMessage(ERROR, "INSERT failed: %s", mysql_error(mysql));
        mysql_rollback(mysql);
        ticket_resp._status = TICKET_FAIL;
        // sendResponse(ticket_resp, conn);
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 5. 提交事务
    if (mysql_query(mysql, "COMMIT"))
    {
        logMessage(ERROR, "Commit failed: %s", mysql_error(mysql));
        mysql_rollback(mysql);
        ticket_resp._status = TICKET_FAIL;
        // sendResponse(ticket_resp, conn);
        std::string respStr;
        ticket_resp.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 6. 准备成功响应
    ticket_resp._status = TICKET_SUCCESS;
    ticket_resp._aid = aid;

    // sendResponse(ticket_resp, conn);
    logMessage(NORMAL, "Ticket action success: uid=%d, aid=%d, num=%d",
               user_id, area_id, buy_num);
    std::string respStr;
    ticket_resp.response_serialize(&respStr);
    logMessage(DEBUG, "serialize success");
    conn->_outbuffer += enLength(respStr);
    std::cout << "-----------result: " << conn->_outbuffer << std::endl;
    if (conn->_sender)
        conn->_sender(conn);
    return true;
}

bool Record(std::string &id, tcpserver::Connection *conn)
{
    MYSQL *mysql = MySQL::getInstance().getConnection();
    // select * from records where id = 20240001;

    std::string sql = "SELECT r.rid, r.id AS user_id, r.aid, a.name AS area_name, r.tickets_total, r.remaining_tickets, r.action, r.num, r.ticket_time FROM records r JOIN areas a ON r.aid = a.aid WHERE r.id =  " + id + ";";
    logMessage(NORMAL, "mysql_query: %s", sql.c_str());
    Record_Class record;
    // 执行查询
    if (mysql_query(mysql, sql.c_str()))
    {
        logMessage(ERROR, "Query failed: %s", mysql_error(mysql));
        record._status = RECORD_FAIL;
        record._number = "0";
        record._id = id;
        std::string respStr;
        record.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 获取结果集
    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result)
    {
        // 没有结果集（可能是查询没有返回数据）
        logMessage(ERROR, "No result set: %s", mysql_error(mysql));
        record._status = RECORD_FAIL;
        record._number = "0";
        record._id = id;
        std::string respStr;
        record.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // 检查是否有结果
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0)
    {
        // 用户不存在
        logMessage(WARNING, "Record not found: %s", id.c_str());
        mysql_free_result(result);
        record._status = RECORD_FAIL;
        record._number = "0";
        record._id = id;
        std::string respStr;
        record.response_serialize(&respStr);
        logMessage(DEBUG, "serialize success");
        conn->_outbuffer += enLength(respStr);
        std::cout << "-----------result: " << conn->_outbuffer << std::endl;
        if (conn->_sender)
            conn->_sender(conn);
        return false;
    }

    // // 处理结果（只取第一行）
    // MYSQL_ROW row = mysql_fetch_row(result);
    // if (row && row[0])
    // {
    //     // 检查匹配结果 (0 = 不匹配, 1 = 匹配)
    //     int match = atoi(row[0]);
    //     login._status = ((match == 1) ? LOGIN_SUCCESS : LOGIN_FAIL);
    //     logMessage(DEBUG, "Match result: %d", match);
    // }
    // else
    // {
    //     // 无法获取结果
    //     logMessage(ERROR, "Failed to fetch row");
    //     login._status = LOGIN_FAIL;
    // }

    // mysql_free_result(result);
    int rows = mysql_num_rows(result);
    int fields = mysql_num_fields(result);
    Json::Value record_sum;
    record._number = std::to_string(rows);
    std::vector<std::string> re_str;
    for (int i = 0; i < rows; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        logMessage(DEBUG, "start for i= %d", i);
        // select name  from areas  where aid = 10001;
        // std::string aid = row[2];
        // std::string sql_name = "select name  from areas  where aid = " + aid + ";";
        // logMessage(NORMAL, "mysql_query: %s", sql_name.c_str());
        // mysql_query(mysql, sql_name.c_str());
        // MYSQL_RES *name_result = mysql_store_result(mysql);
        // MYSQL_ROW name_row = mysql_fetch_row(name_result);
        // std::string name = name_row[0];
        // logMessage(NORMAL, "area name: %s", name.c_str());
        Json::Value re;
        logMessage(DEBUG, "write start for i= %d", i);
        re["name"] = row[3];
        re["rid"] = row[0];
        re["action"] = row[6];
        re["number"] = row[7];
        re["date"] = row[8];
        logMessage(DEBUG, "value end for i= %d", i);
        Json::StyledWriter writer;
        re_str.push_back(writer.write(re));
        logMessage(DEBUG, "write end for i= %d", i);
        for (int j = 0; j < fields; j++)
        {
            std::cout << row[j] << "\t";
        }
        std::cout << std::endl;
        logMessage(DEBUG, "end for i= %d", i);
    }
    record._id = id;
    record._record = re_str;
    record._status = RECORD_SUCCESS;
    mysql_free_result(result);
    std::string respStr;
    record.response_serialize(&respStr);
    logMessage(DEBUG, "serialize success");
    conn->_outbuffer += enLength(respStr);
    std::cout << "-----------result: " << conn->_outbuffer << std::endl;
    if (conn->_sender)
        conn->_sender(conn);
    return true;
}

void service(tcpserver::Connection *conn)
{
    std::string onePackage;
    while (ParseOnePackage(conn->_inbuffer, &onePackage))
    {
        std::string reqStr;
        if (!deLength(onePackage, &reqStr))
            return;
        std::cout << "去掉报头的正文: \n"
                  << reqStr << std::endl;
        std::string type = Request_Class::request_deserialize(reqStr);
        logMessage(NORMAL, "recv a request, type: %s", type.c_str());
        if (type.compare("Login") == 0)
        {
            Login_Class login;
            if (!login.request_deserialize(reqStr))
                return;
            logMessage(DEBUG, "deserialize success");
            Task T;
            T.Login(login._account, login._password, conn, Login);
            conn->_tsp->push(T);
        }
        else if (type.compare("Register") == 0)
        {
            Register_Class register_;
            if (!register_.request_deserialize(reqStr))
                return;
            logMessage(DEBUG, "deserialize success");
            Task T;
            T.Register(register_._name, register_._password, conn, Register);
            conn->_tsp->push(T);
        }
        else if (type.compare("Areas") == 0)
        {
            Areas_Class areas_;
            if (!areas_.request_deserialize(reqStr))
                return;
            logMessage(DEBUG, "deserialize success");
            Task T;
            T.Areas(areas_._aid, conn, Areas);
            conn->_tsp->push(T);
        }
        else if (type.compare("Ticket") == 0)
        {
            Tickets_Class ticket_;
            if (!ticket_.request_deserialize(reqStr))
                return;
            logMessage(DEBUG, "deserialize success");
            Task T;
            T.Ticket(ticket_._id, ticket_._aid, ticket_._num, ticket_._option, conn, Ticket);
            conn->_tsp->push(T);
        }
        else if (type.compare("Record") == 0)
        {
            Record_Class record_;
            if (!record_.request_deserialize(reqStr))
                return;
            logMessage(DEBUG, "deserialize success");
            Task T;
            T.Record(record_._id, conn, Record);
            conn->_tsp->push(T);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(USAGE_ERR);
    }
    uint16_t port = atoi(argv[1]);
    printf("mysql client Version: %s\n", mysql_get_client_info());

    // 2. 初始化数据库连接池
    try
    {
        MySQL &db = MySQL::getInstance(); // 触发连接建立

        // 可选：测试连接是否有效
        MYSQL *testConn = db.getConnection();
        if (mysql_ping(testConn))
        {
            logMessage(ERROR, "Database ping failed: %s", mysql_error(testConn));
            return EXIT_FAILURE;
        }
        logMessage(NORMAL, "Database connection verified");
    }
    catch (const std::exception &e)
    {
        logMessage(FATAL, "Database initialization failed: %s", e.what());
        return EXIT_FAILURE;
    }

    std::unique_ptr<tcpserver::TcpServer> tp(new tcpserver::TcpServer(service, port));
    tp->InitServer();
    tp->Dispatcher();
    return 0;
}