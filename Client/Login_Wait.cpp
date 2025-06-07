#include "Visual_interface.h"

void Login_Wait()
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(450, 300, _T("Waiting to Login ..."));
	Sleep(3000);
}