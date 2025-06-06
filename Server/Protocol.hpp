#pragma once

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <jsoncpp/json/json.h>
#include <vector>
#include <functional>
// #include "TcpServer.hpp"
#include "StatusCode.hpp"

#define SEP " "
#define SEP_LEN strlen(SEP)
#define LINE_SEP "\r\n"
#define LINE_SEP_LEN strlen(LINE_SEP)

enum
{
    OK = 0,
    DIV_ZERO,
    MOD_ZERO,
    OP_ERROR
};

std::string enLength(const std::string &text)
{
    std::string send_string = std::to_string(text.size());
    send_string += LINE_SEP;
    send_string += text;
    send_string += LINE_SEP;
    return send_string;
}

bool deLength(std::string &package, std::string *text)
{
    size_t pos = package.find(LINE_SEP);
    if (pos == std::string::npos)
        return false;
    std::string text_len_string = package.substr(0, pos);
    int text_len = std::stoi(text_len_string);
    *text = package.substr(pos + LINE_SEP_LEN, text_len);
    return true;
}

class Request_Class
{
public:
    static const char *request_deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        std::string type = root["Request"].asString();
        if (type.compare("Login") == 0)
        {
            return "Login";
        }
        else if (type.compare("Register") == 0)
        {
            return "Register";
        }
        else if (type.compare("Areas") == 0)
        {
            return "Areas";
        }
        else if (type.compare("Ticket") == 0)
        {
            return "Ticket";
        }
        else if (type.compare("Record") == 0)
        {
            return "Record";
        }
        return nullptr;
    }
};

class Login_Class
{
    using func_t = std::function<bool(std::string &, std::string &)>;

public:
    Login_Class(std::string account, std::string password, func_t func)
        : _account(account), _password(password), _status(""), _callback(func)
    {
    }

    Login_Class()
    {
    }

    // bool operator()()
    // {
    //     bool result = _callback(_account, _password);
    //     chstatus(result);
    //     std::cout << "account : " << _account << " password : " << _password << " status : " << result << std::endl;
    //     return result;
    // }
    std::string toTaskString()
    {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "[Login] account : %s password : %s status : ", _account.c_str(), _password.c_str());
        return buffer;
    }
    bool request_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Login";
        root["account"] = _account;
        root["password"] = _password;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool request_deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _account = root["account"].asString();
        _password = root["password"].asString();
        logMessage(DEBUG, "[login] request deserialize success: id = %s, password = %s", _account.c_str(), _password.c_str());
        return true;
    }

    void chstatus(bool code)
    {
        _status = "";
        if (code)
        {
            _status = LOGIN_SUCCESS;
        }
        else
        {
            _status = LOGIN_FAIL;
        }
    }

    bool response_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Login";
        root["status"] = _status;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool response_deserialize(std::string &in)
    {
        std::cout << "1" << std::endl;
        _status = "";
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _status = root["status"].asString();
        std::cout << "2" << std::endl;
        return true;
    }

public:
    std::string _account;
    std::string _password;
    std::string _status;
    func_t _callback;
};

class Register_Class
{
    using func_t = std::function<bool(std::string &, std::string &)>;

public:
    Register_Class(std::string name, std::string password, func_t func)
        : _name(name), _password(password), _status(""), _callback(func)
    {
    }

    Register_Class()
    {
    }

    // bool operator()()
    // {
    //     bool result = _callback(_account, _password);
    //     chstatus(result);
    //     std::cout << "account : " << _account << " password : " << _password << " status : " << result << std::endl;
    //     return result;
    // }
    std::string toTaskString()
    {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "[Register] name : %s password : %s status : ", _name.c_str(), _password.c_str());
        return buffer;
    }
    bool request_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Register";
        root["name"] = _name;
        root["password"] = _password;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool request_deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _name = root["name"].asString();
        _password = root["password"].asString();
        return true;
    }

    void chstatus(bool code)
    {
        _status = "";
        if (code)
        {
            _status = LOGIN_SUCCESS;
        }
        else
        {
            _status = LOGIN_FAIL;
        }
    }

    bool response_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Register";
        root["id"] = _id;
        root["status"] = _status;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool response_deserialize(std::string &in)
    {
        std::cout << "1" << std::endl;
        _status = "";
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _status = root["status"].asString();
        _id = root["id"].asString();
        std::cout << "2" << std::endl;
        return true;
    }

public:
    std::string _name;
    std::string _id;
    std::string _account;
    std::string _password;
    std::string _status;
    func_t _callback;
};

class Areas_Class
{
    using func_t = std::function<bool(std::string &, std::string &)>;

public:
    Areas_Class(std::string aid, func_t func)
        : _aid(aid), _callback(func)
    {
    }

    Areas_Class()
    {
    }

    std::string toTaskString()
    {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "[Areas] aid : %s name : %s status : ", _aid.c_str(), _name.c_str());
        return buffer;
    }
    bool request_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Areas";
        root["aid"] = _aid;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool request_deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _aid = root["aid"].asString();
        return true;
    }

    bool response_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Areas";
        root["aid"] = _aid;
        root["name"] = _name;
        root["introduction"] = _introduction;
        root["remaining_tickets"] = _remaining_tickets;
        root["tickets_total"] = _tickets_total;
        root["status"] = _status;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool response_deserialize(std::string &in)
    {
        std::cout << "1" << std::endl;
        _status = "";
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);

        _name = root["name"].asString();
        _introduction = root["introduction"].asString();
        _remaining_tickets = root["remaining_tickets"].asString();
        _tickets_total = root["tickets_total"].asString();
        _status = root["status"].asString();
        _aid = root["aid"].asString();
        std::cout << "2" << std::endl;
        return true;
    }

public:
    std::string _name;
    std::string _aid;
    std::string _introduction;
    std::string _tickets_total;
    std::string _remaining_tickets;
    std::string _status;
    func_t _callback;
};

class Tickets_Class
{
    using func_t = std::function<bool(std::string &, std::string &, std::string &)>;

public:
    Tickets_Class(std::string id, std::string aid, std::string option, std::string num, func_t func)
        : _id(id), _aid(aid), _status(""), _option(option), _num(num), _callback(func)
    {
    }

    Tickets_Class()
    {
    }

    std::string toTaskString()
    {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "[%s] id : %s, aid : %s ,num: %s ,status : ", _option.c_str(), _aid.c_str(), _num.c_str(), _status.c_str());
        return buffer;
    }
    bool request_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Ticket";
        root["option"] = _option;
        root["id"] = _id;
        root["aid"] = _aid;
        root["num"] = _num;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool request_deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _option = root["option"].asString();
        _id = root["id"].asString();
        _aid = root["aid"].asString();
        _num = root["num"].asString();
        // _status = TICKET_FAIL;
        return true;
    }

    bool response_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Ticket";
        root["status"] = _status;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool response_deserialize(std::string &in)
    {
        std::cout << "1" << std::endl;
        _status = "";
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _status = root["status"].asString();
        std::cout << "2" << std::endl;
        return true;
    }

public:
    std::string _aid;
    std::string _id;
    std::string _num;
    std::string _option;
    std::string _status;
    func_t _callback;
};

class Record_Class
{
    using func_t = std::function<bool(std::string &, std::string &)>;

public:
    Record_Class(std::string id, func_t func)
        : _id(id), _callback(func)
    {
    }

    Record_Class()
    {
    }

    std::string toTaskString()
    {
        char buffer[1024];
        snprintf(buffer, sizeof buffer, "[Records] id : %s, id : %s ,num: %s ,status : ", _id.c_str(), _number.c_str(), _status.c_str());
        return buffer;
    }
    bool request_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Record";
        root["id"] = _id;
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool request_deserialize(std::string &in)
    {
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _id = root["id"].asString();
        // _status = TICKET_FAIL;
        return true;
    }

    bool response_serialize(std::string *out)
    {
        Json::Value root;
        root["Request"] = "Record";
        root["number"] = _number;
        root["id"] = _id;
        root["status"] = _status;
        for (int i = 0; i < _record.size(); i++)
        {
            root[std::to_string(i)] = _record[i];
        }
        Json::StyledWriter writer;
        *out = writer.write(root);
        return true;
    }

    bool response_deserialize(std::string &in)
    {
        std::cout << "1" << std::endl;
        _status = "";
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _status = root["status"].asString();
        _number = root["number"].asString();
        _id = root["id"].asString();
        int number = std::atoi(_number.c_str());
        for (int i = 0; i < number; i++)
        {
            _record.push_back(root[std::to_string(i)].asString());
        }
        std::cout << "2" << std::endl;
        return true;
    }

public:
    std::string _id;
    std::string _number;
    std::string _status;
    // Json::Value _record;
    std::vector<std::string> _record;
    func_t _callback;
};

bool ParseOnePackage(std::string &inbuffer, std::string *text)
{
    logMessage(DEBUG, "ParseOnePackage in");
    *text = "";
    size_t pos = inbuffer.find(LINE_SEP);
    if (pos == std::string::npos)
        return false;
    logMessage(DEBUG, "find LINE_SEP");
    std::string text_len_string = inbuffer.substr(0, pos);
    int text_len = std::stoi(text_len_string);
    int total_len = text_len_string.size() + 2 * LINE_SEP_LEN + text_len;
    logMessage(DEBUG, "text_len = %d, total_len = %d.inbuffer.size() = %d", text_len, total_len, inbuffer.size());

    if (inbuffer.size() < total_len)
        return false;

    *text = inbuffer.substr(0, total_len);
    inbuffer.erase(0, total_len);
    logMessage(DEBUG, "ParseOnePackage success");
    return true;
}