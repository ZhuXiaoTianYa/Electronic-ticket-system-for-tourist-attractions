#pragma once

#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <json/json.h>
#include <vector>
#include <functional>
#include <json/json.h>
#include "StatusCode.hpp"
#include "Log.hpp"

#define SEP " "
#define SEP_LEN strlen(SEP)
#define LINE_SEP "\r\n"
#define LINE_SEP_LEN strlen(LINE_SEP)



std::string enLength(const std::string& text);


bool deLength(std::string& package, std::string* text);


class Request_Class
{
public:
    static const char* request_deserialize(std::string& in);
};

class Login_Class
{
    using func_t = std::function<bool(std::string &, std::string &)>;

public:
    Login_Class(std::string account, std::string password, func_t func);
    

    Login_Class();


    std::string toTaskString();

    bool request_serialize(std::string* out);

    bool request_deserialize(std::string& in);


    void chstatus(bool code);


    bool response_serialize(std::string* out);


    bool response_deserialize(std::string in);


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
    Register_Class(std::string name, std::string password, func_t func);

    Register_Class();



    std::string toTaskString();

    bool request_serialize(std::string* out);


    bool request_deserialize(std::string& in);


    void chstatus(bool code);


    bool response_serialize(std::string* out);

    bool response_deserialize(std::string& in);


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
    Areas_Class(std::string aid, func_t func);


    Areas_Class();


    std::string toTaskString();

    bool request_serialize(std::string* out);


    bool request_deserialize(std::string& in);


    bool response_serialize(std::string* out);


    bool response_deserialize(std::string& in);


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
    Tickets_Class(std::string id, std::string aid, std::string option, std::string num, func_t func);

    Tickets_Class();


    std::string toTaskString();

    bool request_serialize(std::string* out);


    bool request_deserialize(std::string& in);


    bool response_serialize(std::string* out);


    bool response_deserialize(std::string& in);


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
    Record_Class(std::string id, func_t func);


    Record_Class();


    std::string toTaskString();

    bool request_serialize(std::string* out);


    bool request_deserialize(std::string& in);


    bool response_serialize(std::string* out);

    bool response_deserialize(std::string& in);


public:
    std::string _id;
    std::string _number;
    std::string _status;
    // Json::Value _record;
    std::vector<std::string> _record;
    func_t _callback;
};

bool ParseOnePackage(std::string& inbuffer, std::string* text);
