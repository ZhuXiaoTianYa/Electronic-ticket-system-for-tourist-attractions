#include "Visual_interface.h"

void Login_Fail()
{
	cleardevice();
	settextcolor(RED);
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(500, 300, _T("Login failed"));
	Sleep(3000);
}