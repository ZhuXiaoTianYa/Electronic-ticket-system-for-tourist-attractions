#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <graphics.h>
#include <conio.h>
//#include "Protocol.hpp"

#define LINE_SEP "\n\n\n\n\n\n\n\n\n"


enum class Scene :int
{
    Quit_Sc = -1,
    Start_Sc,
    Login_Sc,
    Register_Sc,
    Home_Sc
};

extern int sock_global;
extern int pos_;
extern bool judgment_err_;
extern const char* start_;
extern const char* login_ ;
extern const char* choose_;


int Choose();
void Clear();
void Start();
void Login();
void Register();
void Distribution();

int network_init();
bool login_request(std::string& id, std::string& passwd, int sock);
bool register_request(std::string& name ,std::string& passwd, std::string* id,int sock);
bool areas_request(std::string& aid, int sock);
bool tickets_request(std::string id, std::string aid, std::string option, std::string num, int sock);
bool record_request(std::string id, std::vector<std::string>* records, int sock);
