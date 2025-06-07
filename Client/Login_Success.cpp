#include "Visual_interface.h"

void Login_Success()
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(80, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(400, 300, _T("Login successful !"));
	Sleep(3000);
}