#include "Sock.hpp"
#include "Protocol.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8086);
    connect(sock, (struct sockaddr *)&server, sizeof(server));
    // while (true)
    // {
    //     string acc;
    //     string pas;
    //     cin >> acc;
    //     cin >> pas;
    //     class Login_Class qe(acc, pas, nullptr);
    //     std::string qes;
    //     qe.request_serialize(&qes);
    //     std::string sen = enLength(qes);
    //     std::cout << sen << std::endl;
    //     send(sock, sen.c_str(), sen.size(), 0);
    //     string res;
    //     char buf[1024];
    //     int n = recv(sock, buf, sizeof(buf) - 1, 0);
    //     string s = buf;
    //     string q;
    //     deLength(s, &q);
    //     cout << q << endl;
    //     qe.response_deserialize(q);
    //     cout << qe._status << endl;

    // string name;
    // string pas;
    // cin >> name;
    // cin >> pas;
    // class Register_Class qe(name, pas, nullptr);
    // std::string qes;
    // qe.request_serialize(&qes);
    // std::string sen = enLength(qes);
    // std::cout << sen << std::endl;
    // send(sock, sen.c_str(), sen.size(), 0);
    // string res;
    // char buf[1024];
    // int n = recv(sock, buf, sizeof(buf) - 1, 0);
    // string s = buf;
    // string q;
    // deLength(s, &q);
    // cout << q << endl;
    // qe.response_deserialize(q);
    // cout << qe._name << "  " << qe._status << endl;

    // string aid;
    // cin >> aid;
    // class Areas_Class qe(aid, nullptr);
    // std::string qes;
    // qe.request_serialize(&qes);
    // std::string sen = enLength(qes);
    // std::cout << sen << std::endl;
    // send(sock, sen.c_str(), sen.size(), 0);
    // string res;
    // char buf[2048];
    // int n = recv(sock, buf, sizeof(buf) - 1, 0);
    // string s = buf;
    // string q;
    // deLength(s, &q);
    // cout << q << endl;
    // qe.response_deserialize(q);
    // cout << qe._name << endl;
    // cout << qe._introduction << endl;
    // cout << qe._tickets_total << endl;
    // cout << qe._remaining_tickets << endl;
    // cout << qe._status << endl;

    // string id;
    // string aid;
    // string num;
    // string option;
    // cin >> id;
    // cin >> aid;
    // cin >> num;
    // cin >> option;
    // class Tickets_Class qe(id, aid, option, num, nullptr);
    // std::string qes;
    // qe.request_serialize(&qes);
    // std::string sen = enLength(qes);
    // std::cout << sen << std::endl;
    // send(sock, sen.c_str(), sen.size(), 0);
    // string res;
    // char buf[2048];
    // int n = recv(sock, buf, sizeof(buf) - 1, 0);
    // string s = buf;
    // string q;
    // deLength(s, &q);
    // cout << q << endl;
    // qe.response_deserialize(q);
    // cout << qe._status << endl;

    string id;
    cin >> id;
    class Record_Class qe(id, nullptr);
    std::string qes;
    qe.request_serialize(&qes);
    std::string sen = enLength(qes);
    std::cout << sen << std::endl;
    send(sock, sen.c_str(), sen.size(), 0);
    string res;
    char buf[2048];
    int n = recv(sock, buf, sizeof(buf) - 1, 0);
    string s = buf;
    string q;
    deLength(s, &q);
    cout << q << endl;
    qe.response_deserialize(q);
    int number = std::atoi(qe._number.c_str());
    for (int i = 0; i < number; i++)
    {
        Json::Reader reader;
        Json::Value root;
        reader.parse(qe._record[i], root);
        // for (int j = 0; j < 5; i++)
        // {
        //     cout << root[std::to_string(j)].asString() << " | ";
        // }
        cout << " | " << root["rid"].asString() << " | " << root["name"].asString() << " | " << root["action"].asString() << " | " << root["number"].asString() << " | " << root["date"].asString() << " | " << endl;
    }
    cout << endl;
}
