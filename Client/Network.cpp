#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#include "Log.hpp"
#include "Protocol.hpp"

int network_init()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0) //Windows异步套接字的启动命令 
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //创建套接字 
	if (sclient == INVALID_SOCKET)
	{
		printf("创建失败 !");
		return 0;
	}

	// 套接字结构体 
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8086);
	serAddr.sin_addr.S_un.S_addr = inet_addr("123.207.84.219");
	if (connect(sclient, (struct sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)  //连接 
	{
		printf("连接失败!");
		closesocket(sclient);
		return 0;
	}
	//for (int i = 0; i < 1000; i++)
	//{

	//	const char* sendData = "我是客户端\n";
	//	send(sclient, sendData, strlen(sendData), 0);
	//	char recData[255];
	//	int ret = recv(sclient, recData, 255, 0);//接受 
	//	if (ret > 0)
	//	{

	//		recData[ret] = 0x00;
	//		printf("%d%s", i, recData);
	//	}
	//}

	logMessage(NORMAL, "Client connect success");

	return sclient;
}


bool login_request(std::string &id,std::string &passwd,int sock)
{
	Login_Class login_(id,passwd,nullptr);
	login_._account = id;
	login_._password = passwd;
	std::string req="";
	login_.request_serialize(&req);
	std::string request = enLength(req);
	logMessage(NORMAL, "[login] request send: %s", request.c_str());
	send(sock, request.c_str(), request.size(), 0);
	logMessage(NORMAL, "[login] request send success : id = %s passwd = %s", login_._account.c_str(), login_._password.c_str());
	std::string package = "";
	while (true)
	{
		char buf[2048] = {0};
		int n = recv(sock, buf, sizeof(buf) - 1, 0);
		if (n <= 0) {
			logMessage(ERROR, "recv failed or connection closed");
			return false;
		}
		logMessage(NORMAL, "[login] request recv success : %s", buf);
		package += buf;
		//std::string response(buf, n);
		std::string response="";
		if (ParseOnePackage(package,&response))
		{
			std::string res;
			logMessage(NORMAL, "[login] request start deLength");
			deLength(response, &res);
			logMessage(NORMAL, "[login] request end deLength: %s", res.c_str());
			login_.response_deserialize(res);
			logMessage(NORMAL, "[login] response recv success : status = %s", login_._status.c_str());
			if (login_._status.compare(LOGIN_SUCCESS) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}



bool register_request(std::string& name, std::string& passwd, std::string* id, int sock)
{
  class Register_Class register_(name, passwd, nullptr);
  std::string req="";
  register_.request_serialize(&req);
  std::string request = enLength(req);
  send(sock, request.c_str(), request.size(), 0);
  logMessage(NORMAL, "[register] request send success : name = %s passwd = %s", register_._name.c_str(), register_._password.c_str());
  std::string package = "";
  while (true)
  {
	  char buf[2048] = { 0 };
	  int n = recv(sock, buf, sizeof(buf) - 1, 0);
	  if (n <= 0) {
		  logMessage(ERROR, "recv failed or connection closed");
		  return false;
	  }
	  logMessage(NORMAL, "[register] request recv success : %s", buf);
	  package += buf;
	  std::string response = "";
	  if (ParseOnePackage(package, &response))
	  {
		  std::string res;
		  deLength(response, &res);
		  register_.response_deserialize(res);
		  logMessage(NORMAL, "[register] response recv success : status = %s", register_._status.c_str());
		  if (register_._status.compare(REGISTER_SUCCESS) == 0)
		  {
			  return true;
		  }
		  else
		  {
			  return false;
		  }
	  }
  }
	return true;
}



bool areas_request(std::string& aid, int sock)
{
	class Areas_Class areas_(aid, nullptr);
	std::string req = "";
	areas_.request_serialize(&req);
	std::string request = enLength(req);
	send(sock, request.c_str(), request.size(), 0);
	logMessage(NORMAL, "[areas] request send success : aid = %s", areas_._aid.c_str());
	std::string package = "";
	while (true)
	{
		char buf[2048] = { 0 };
		int n = recv(sock, buf, sizeof(buf) - 1, 0);
		if (n <= 0) {
			logMessage(ERROR, "recv failed or connection closed");
			return false;
		}
		logMessage(NORMAL, "[areas] request recv success : %s", buf);
		package += buf;
		std::string response = "";
		if (ParseOnePackage(package, &response))
		{
			std::string res;
			deLength(response, &res);
			areas_.response_deserialize(res);
			logMessage(NORMAL, "[areas] response recv success :\n aid: %s\nname: %s\nintroduction: %s\n_tickets_total: %s\_remaining_tickets: %s status = %s", areas_._aid.c_str(), areas_._name.c_str(), areas_._introduction.c_str(), areas_._tickets_total.c_str(), areas_._remaining_tickets.c_str(), areas_._status.c_str());
			if (areas_._status.compare(AREAS_SUCCESS) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}




bool tickets_request(std::string id, std::string aid, std::string option, std::string num, int sock)
{
	class Tickets_Class tickets_(id,aid,option,num, nullptr);
	std::string req = "";
	tickets_.request_serialize(&req);
	std::string request = enLength(req);
	send(sock, request.c_str(), request.size(), 0);
	logMessage(NORMAL, "[tickets] request send success : option = %s, id = %s, aid = %s, num = %s", tickets_._option.c_str(), tickets_._id.c_str(), tickets_._aid.c_str(), tickets_._num.c_str());
	std::string package = "";
	while (true)
	{
		char buf[2048] = { 0 };
		int n = recv(sock, buf, sizeof(buf) - 1, 0);
		if (n <= 0) {
			logMessage(ERROR, "recv failed or connection closed");
			return false;
		}
		logMessage(NORMAL, "[tickets] request recv success : %s", buf);
		package += buf;
		std::string response = "";
		if (ParseOnePackage(package, &response))
		{
			std::string res;
			deLength(response, &res);
			tickets_.response_deserialize(res);
			logMessage(NORMAL, "[tickets] request send success : option = %s, id = %s, aid = %s, num = %s, status = %s", tickets_._option.c_str(), tickets_._id.c_str(), tickets_._aid.c_str(), tickets_._num.c_str(), tickets_._status.c_str());
			if (tickets_._status.compare(TICKET_SUCCESS) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}


bool record_request(std::string id,std::vector<std::string> *records, int sock)
{
	class Record_Class record_(id, nullptr);
	std::string req = "";
	record_.request_serialize(&req);
	std::string request = enLength(req);
	send(sock, request.c_str(), request.size(), 0);
	logMessage(NORMAL, "[record] request send success : id = %s", record_._id.c_str());
	std::string package = "";
	while (true)
	{
		char buf[2048] = { 0 };
		int n = recv(sock, buf, sizeof(buf) - 1, 0);
		if (n <= 0) {
			logMessage(ERROR, "recv failed or connection closed");
			return false;
		}
		logMessage(NORMAL, "[record] request recv success : %s", buf);
		package += buf;
		std::string response = "";
		if (ParseOnePackage(package, &response))
		{
			std::string res;
			deLength(response, &res);
			record_.response_deserialize(res);
			logMessage(NORMAL, "[record] request send success : id = %s, status = %s", record_._id.c_str(), record_._status.c_str());
			if (record_._status.compare(RECORD_SUCCESS) == 0)
			{
				*records = record_._record;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}
