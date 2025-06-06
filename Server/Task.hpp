#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <functional>
#include "TcpServer.hpp"
#include "Log.hpp"

namespace tcpserver
{
    class Connection;
}

namespace tcpserver
{
    class Connection;
}
class TaskData
{
public:
    std::string _id;
    std::string _aid;
    std::string _num;
    std::string _option;
    std::string _name;
    std::string _account;
    std::string _password;
    bool _status;
};

class Task
{
    using Login_Register = std::function<bool(std::string &, std::string &, tcpserver::Connection *)>;
    using Areas_c = std::function<bool(std::string &, tcpserver::Connection *)>;
    using Ticket_c = std::function<bool(std::string &, std::string &, std::string &, std::string &, tcpserver::Connection *)>;
    using Record_c = std::function<bool(std::string &, tcpserver::Connection *)>;
    // typedef std::function<int(int,int,char)> func_t

public:
    Task()
        : _login_callback(nullptr), _conn(nullptr), _Register_callback(nullptr), _Areas_callback(nullptr), _Ticket_callback(nullptr), _Record_callback(nullptr)
    {
    }

    void Register(std::string &name, std::string &password, tcpserver::Connection *conn, Login_Register func)
    {
        logMessage(DEBUG, "Task Register");
        _Register_callback = func;
        _conn = conn;
        _data._name = name;
        _data._password = password;
    }

    void Areas(std::string &aid, tcpserver::Connection *conn, Areas_c func)
    {
        logMessage(DEBUG, "Task Areas");
        _Areas_callback = func;
        _conn = conn;
        _data._aid = aid;
    }

    void Login(std::string &account, std::string &password, tcpserver::Connection *conn, Login_Register func)
    {
        logMessage(DEBUG, "Task Login");
        _login_callback = func;
        _conn = conn;
        _data._account = account;
        _data._password = password;
    }

    void Record(std::string &id, tcpserver::Connection *conn, Record_c func)
    {
        logMessage(DEBUG, "Task Record");
        _Record_callback = func;
        _conn = conn;
        _data._id = id;
    }

    void Ticket(std::string &id, std::string &aid, std::string &num, std::string &option, tcpserver::Connection *conn, Ticket_c func)
    {
        logMessage(DEBUG, "Task Ticket");
        _Ticket_callback = func;
        _conn = conn;
        _data._id = id;
        _data._aid = aid;
        _data._num = num;
        _data._option = option;
    }

    // Task(std::string &account, std::string &password, tcpserver::Connection *conn, Login_Register func)
    //     : _login_callback(func), _conn(conn), _Register_callback(nullptr)
    // {
    //     logMessage(DEBUG, "Task Login");
    //     _data._account = account;
    //     _data._password = password;
    // }

    bool operator()()
    {
        if (_login_callback != nullptr)
        {
            logMessage(DEBUG, "start Login");
            bool result = _login_callback(_data._account, _data._password, _conn);
            std::cout << "account : " << _data._account << " password : " << _data._password << " status : " << result << std::endl;
            // Reset();
            return result;
        }
        else if (_Register_callback != nullptr)
        {
            logMessage(DEBUG, "start Register");
            bool result = _Register_callback(_data._name, _data._password, _conn);
            std::cout << "name : " << _data._account << " password : " << _data._password << " status : " << result << std::endl;
            // Reset();
            return result;
        }
        else if (_Areas_callback != nullptr)
        {
            logMessage(DEBUG, "start Areas");
            bool result = _Areas_callback(_data._aid, _conn);
            std::cout << "aid : " << _data._aid << " status : " << result << std::endl;
            // Reset();
            return result;
        }
        else if (_Ticket_callback != nullptr)
        {
            logMessage(DEBUG, "start Ticket");
            bool result = _Ticket_callback(_data._id, _data._aid, _data._num, _data._option, _conn);
            std::cout << "id : " << _data._id << " , aid= " << _data._aid << " num= " << _data._num << " option= " << _data._option << " status : " << result << std::endl;
            // Reset();
            return result;
        }
        else if (_Record_callback != nullptr)
        {
            logMessage(DEBUG, "start Record");
            bool result = _Record_callback(_data._id, _conn);
            std::cout << "id : " << _data._id << std::endl;
            // Reset();
            return result;
        }
    }

    std::string toTaskString()
    {
        if (_login_callback != nullptr)
        {
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "account : %s password : %s status : %d", _data._account.c_str(), _data._password.c_str(), _data._status);
            return buffer;
        }
        else if (_Register_callback != nullptr)
        {
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "Register name : %s password : %s status : %d", _data._name.c_str(), _data._password.c_str(), _data._status);
            return buffer;
        }
        else if (_Areas_callback != nullptr)
        {
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "areas aid : %s , status : %d", _data._aid.c_str(), _data._status);
            return buffer;
        }
        else if (_Ticket_callback != nullptr)
        {
            std::cout << "id : " << _data._id << " , aid= " << _data._aid << " num= " << _data._num << " option= " << _data._option << " status : " << _data._status << std::endl;
            char buffer[1024];
            snprintf(buffer, sizeof buffer, "id :  %s , aid= %s,  num= %s, option= %s ,status : %d", _data._id.c_str(), _data._aid.c_str(), _data._num.c_str(), _data._option.c_str(), _data._status);
            return buffer;
        }
        else if (_Record_callback != nullptr)
        {
            // Reset();
            return "id : " + _data._id;
        }
    }

    // void Reset()
    // {
    //     _login_callback = nullptr;
    //     _Register_callback = nullptr;
    // }

    ~Task()
    {
    }

private:
    class TaskData _data;
    Login_Register _login_callback;
    Login_Register _Register_callback;
    Areas_c _Areas_callback;
    Ticket_c _Ticket_callback;
    Record_c _Record_callback;
    tcpserver::Connection *_conn;
};

const std::string oper = "+-*/%";

int mymath(int x, int y, char op)
{
    int result = 0;
    switch (op)
    {
    case '+':
        result = x + y;
        break;
    case '-':
        result = x - y;
        break;
    case '*':
        result = x * y;
        break;
    case '/':
    {
        if (y == 0)
        {
            std::cerr << "div zero error!" << std::endl;
            result = -1;
        }
        else
            result = x / y;
    }
    break;
    case '%':
    {
        if (y == 0)
        {
            std::cerr << "mod zero error!" << std::endl;
            result = -1;
        }
        else
            result = -1;
    }
    break;
    default:
        // do nothing
        break;
    }
    return result;
}