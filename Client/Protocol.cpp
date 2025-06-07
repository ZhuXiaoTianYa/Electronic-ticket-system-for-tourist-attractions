#pragma once

#include "Protocol.hpp"

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

const char *Request_Class::request_deserialize(std::string &in)
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

Login_Class::Login_Class(std::string account, std::string password, func_t func)
    : _account(account), _password(password), _status(""), _callback(func)
{
}

Login_Class::Login_Class()
{
}

std::string Login_Class::toTaskString()
{
    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[Login] account : %s password : %s status : ", _account.c_str(), _password.c_str());
    return buffer;
}
bool Login_Class::request_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Login";
    root["account"] = _account;
    root["password"] = _password;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Login_Class::request_deserialize(std::string &in)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(in, root);
    _account = root["account"].asString();
    _password = root["password"].asString();
    return true;
}

void Login_Class::chstatus(bool code)
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

bool Login_Class::response_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Login";
    root["status"] = _status;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Login_Class::response_deserialize(std::string in)
{
    logMessage(DEBUG, "response_deserialize input = [%s], length = %d", in.c_str(), (int)in.length());
    _status = "";
    // ÄÚ´æ¼ì²éµã
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

    int heapCheck = _CrtCheckMemory();
    if (!heapCheck)
    {
        logMessage(ERROR, "Heap corruption detected before JSON parse");
        return false;
    }

    Json::Value root;
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();

    const char *begin = in.c_str();
    const char *end = begin + in.size();
    std::string errors;

    bool parsingSuccessful = reader->parse(begin, end, &root, &errors);
    delete reader;

    if (!parsingSuccessful)
    {
        logMessage(ERROR, "JSON parse failed: %s", errors.c_str());
        return false;
    }

    if (!root.isMember("status"))
    {
        logMessage(ERROR, "Missing 'status' field in JSON");
        return false;
    }

    _status = root["status"].asString();

    heapCheck = _CrtCheckMemory();
    if (!heapCheck)
    {
        logMessage(ERROR, "Heap corruption detected after JSON parse");
        return false;
    }

    return true;
}

Register_Class::Register_Class(std::string name, std::string password, func_t func)
    : _name(name), _password(password), _status(""), _callback(func)
{
}

Register_Class::Register_Class()
{
}

std::string Register_Class::toTaskString()
{
    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[Register] name : %s password : %s status : ", _name.c_str(), _password.c_str());
    return buffer;
}
bool Register_Class::request_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Register";
    root["name"] = _name;
    root["password"] = _password;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Register_Class::request_deserialize(std::string &in)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(in, root);
    _name = root["name"].asString();
    _password = root["password"].asString();
    return true;
}

void Register_Class::chstatus(bool code)
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

bool Register_Class::response_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Register";
    root["id"] = _id;
    root["status"] = _status;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Register_Class::response_deserialize(std::string &in)
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

Areas_Class::Areas_Class(std::string aid, func_t func)
    : _aid(aid), _callback(func)
{
}

Areas_Class::Areas_Class()
{
}

std::string Areas_Class::toTaskString()
{
    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[Areas] aid : %s name : %s status : ", _aid.c_str(), _name.c_str());
    return buffer;
}
bool Areas_Class::request_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Areas";
    root["aid"] = _aid;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Areas_Class::request_deserialize(std::string &in)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(in, root);
    _aid = root["aid"].asString();
    return true;
}

bool Areas_Class::response_serialize(std::string *out)
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

bool Areas_Class::response_deserialize(std::string &in)
{
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
    return true;
}

Tickets_Class::Tickets_Class(std::string id, std::string aid, std::string option, std::string num, func_t func)
    : _id(id), _aid(aid), _status(""), _option(option), _num(num), _callback(func)
{
}

Tickets_Class::Tickets_Class()
{
}

std::string Tickets_Class::toTaskString()
{
    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[%s] id : %s, aid : %s ,num: %s ,status : ", _option.c_str(), _aid.c_str(), _num.c_str(), _status.c_str());
    return buffer;
}
bool Tickets_Class::request_serialize(std::string *out)
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

bool Tickets_Class::request_deserialize(std::string &in)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(in, root);
    _option = root["option"].asString();
    _id = root["id"].asString();
    _aid = root["aid"].asString();
    _num = root["num"].asString();
    return true;
}

bool Tickets_Class::response_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Ticket";
    root["status"] = _status;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Tickets_Class::response_deserialize(std::string &in)
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

Record_Class::Record_Class(std::string id, func_t func)
    : _id(id), _callback(func)
{
}

Record_Class::Record_Class()
{
}

std::string Record_Class::toTaskString()
{
    char buffer[1024];
    snprintf(buffer, sizeof buffer, "[Records] id : %s, id : %s ,num: %s ,status : ", _id.c_str(), _number.c_str(), _status.c_str());
    return buffer;
}
bool Record_Class::request_serialize(std::string *out)
{
    Json::Value root;
    root["Request"] = "Record";
    root["id"] = _id;
    Json::StyledWriter writer;
    *out = writer.write(root);
    return true;
}

bool Record_Class::request_deserialize(std::string &in)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(in, root);
    _id = root["id"].asString();
    // _status = TICKET_FAIL;
    return true;
}

bool Record_Class::response_serialize(std::string *out)
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

bool Record_Class::response_deserialize(std::string &in)
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
        Json::Value Row;
        Json::Reader Row_reader;
        Row_reader.parse(root[std::to_string(i)].asString(), Row);
        char buf[2048] = {0};
        snprintf(buf, sizeof buf - 1, "|   %s   |  %s   |   %s    |    %s    |  %s |", Row["rid"].asString().c_str(), Row["name"].asString().c_str(), Row["action"].asString().c_str(), Row["number"].asString().c_str(), Row["date"].asString().c_str());
        _record.push_back(buf);
        logMessage(DEBUG, "rid: %s, name: %s ,action: %s, num: %s, data: %s", Row["rid"].asString().c_str(), Row["name"].asString().c_str(), Row["action"].asString().c_str(), Row["number"].asString().c_str(), Row["date"].asString().c_str());
        std::cout << buf << std::endl;
    }
    std::cout << "2" << std::endl;
    return true;
}

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