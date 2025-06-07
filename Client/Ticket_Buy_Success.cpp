#include "Visual_interface.h"

// 购票成功界面
void Ticket_Buy_Success()
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("微软雅黑"));
	outtextxy(350, 300, _T("Ticket purchase successful !"));
	Sleep(3000);
	pos_global = static_cast<int>(Scene::Home_Sc);
}