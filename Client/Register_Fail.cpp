#include "Visual_interface.h"

void Register_Fail()
{
	cleardevice();
	settextcolor(RED);
	settextstyle(60, 0, _T("΢���ź�"));
	outtextxy(480, 300, _T("Register failed"));
	Sleep(3000);
}