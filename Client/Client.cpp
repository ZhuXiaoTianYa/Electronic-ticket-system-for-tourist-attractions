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
	//char s[] = "Hello World";
	sock_global =network_init();


	//std::string ac;
	//std::string pa;
	//std::cin >> ac;
	//std::cin >> pa;
	//bool res = login_request(ac,pa, sock_global);
	//std::cout << res << std::endl;



	//std::string name;
	//std::string pa;
	//std::string id;
	//std::cin >> name;
	//std::cin >> pa;
	//bool res = register_request(name, pa, &id,sock_global);
	//std::cout << res << std::endl;



	//std::string aid;
	//std::cin >> aid;
	//bool res = areas_request(aid, sock_global);
	//std::cout << res << std::endl;

	//std::string aid;
	//std::string option;
	//std::string num;
	//std::string id;
	//std::cin >> id;
	//std::cin >> aid;
	//std::cin >> num;
	//std::cin >> option;
	//bool res = tickets_request(id,aid,option,num,sock_global);
	//std::cout << res << std::endl;



	//std::vector<std::string> records;
	//std::string id;
	//std::cin >> id;

	//bool res = record_request(id, &records, sock_global);
	//std::cout << res << std::endl;
	//for (int i = 0; i < records.size(); i++)
	//{
	//	std::cout << records[i] << std::endl;
	//}


	closesocket(sock_global);   //关闭套接口 
	WSACleanup();   //功能是终止Winsock 2 DLL (Ws2_32.dll) 的使用  

	//initgraph(1280, 720, EX_SHOWCONSOLE);
	//releasecapture();
	//setbkcolor(RGB(255,255,255));
	//cleardevice();
	//network_init();
	//Distribution();
	//system("pause");
	return 0;
}