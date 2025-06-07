#include "Visual_interface.h"

void Register_Success(std::string &name, std::string &id, std::string &passwd)
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(80, 0, _T("微软雅黑"));
	outtextxy(350, 260, _T("Register successful !"));
	setlinecolor(RGB(0, 0, 0));
	fillrectangle(450, 400, 850, 570);
	std::string username = "您的用户名是：" + name;
	std::string studentid = "您的学号为：" + id;
	std::string password = "您的密码是：" + passwd;
	settextstyle(30, 0, _T("微软雅黑"));
	outtextxy(530, 420, username.c_str());
	outtextxy(530, 470, studentid.c_str());
	outtextxy(530, 520, password.c_str());
	Sleep(3000);
}