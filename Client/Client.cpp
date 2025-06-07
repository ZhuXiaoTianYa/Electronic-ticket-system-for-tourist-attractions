#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Visual_interface.h"
#include <easyx.h>
#include <Windows.h>

int main()
{
	sock_global =network_init();
	initgraph(1280, 720, EX_SHOWCONSOLE);
	releasecapture();
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	Distribution();
	closesocket(sock_global);   //关闭套接口 
	WSACleanup();   //功能是终止Winsock 2 DLL (Ws2_32.dll) 的使用  
	return 0;
}