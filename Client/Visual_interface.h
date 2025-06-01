#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#define LINE_SEP "\n\n\n\n\n\n\n\n\n"


enum class Scene :int
{
    Quit_Sc = -1,
    Start_Sc,
    Login_Sc,
    Register_Sc,
    Home_Sc
};

extern int pos_;
extern bool judgment_err_;
extern const char* start_;
extern const char* login_ ;
extern const char* choose_;

int Choose();


void Clear();

void Start();
	

    // Login() º¯ÊýÊµÏÖ
void Login();


    void Register();


	void Distribution();


