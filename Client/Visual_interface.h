#pragma once
#include <string>
#include <graphics.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>

#define LINE_SEP "\n\n\n\n\n\n\n\n\n"
#define BEIJING "10001"
#define GUANGDONG "10002"
#define SHANGHAI "10003"

enum class Scene : int
{
    Quit_Sc = -1,
    Start_Sc,
    Login_Sc,
    Register_Sc,
    Home_Sc,
    Ticket_list_Sc,
    Ticket_details_Sc,
    Ticket_Buy_Wait_Sc,
    Ticket_Buy_Success_Sc,
    Ticket_Buy_Fail_Sc,
    Ticket_Refund_Wait_Sc,
    Ticket_Refund_Success_Sc,
    Ticket_Refund_Fail_Sc,
    Ticket_Records_Sc,
    Login_Wait_Sc,
    Login_Success_Sc,
    Login_Fail_Sc,
    Register_Wait_Sc,
    Register_Success_Sc,
    Register_Fail_Sc
};
extern int sock_global;
extern int pos_global;
extern bool judgment_err_;
extern const char *start_;
extern const char *login_;
extern const char *choose_;
extern std::string id_global;
extern std::string name_global;
extern std::string passwd_global;
extern std::string areas_aid;
extern std::string areas_name;
extern std::string areas_introduction;
extern std::string areas_remaining_tickets;
extern std::string areas_tickets_total;
extern std::vector<std::string> records_global;

int Choose();
void Clear();
void Start();
void Login();
void Register();
void Distribution();
void Home();
void Ticket_list();
void Ticket_Details(std::string name, std::string introduction, std::string tickets_total, std::string remaining_tickets);
void Ticket_Buy_Wait();
void Ticket_Buy_Success();
void Ticket_Buy_Fail();
void Ticket_Records(std::vector<std::string> &records);
void Ticket_Refund_Wait();
void Ticket_Refund_Success();
void Ticket_Refund_Fail();
int network_init();
bool login_request(std::string &id, std::string &passwd, int sock);
bool register_request(std::string &name, std::string &passwd, std::string *id, int sock);
bool areas_request(std::string &aid, int sock);
bool tickets_request(std::string id, std::string aid, std::string option, std::string num, int sock);
bool record_request(std::string id, std::vector<std::string> *records, int sock);
void Login_Wait();
void Login_Success();
void Login_Fail();
void Register_Wait();
void Register_Fail();
void Register_Success(std::string &name, std::string &id, std::string &passwd);
