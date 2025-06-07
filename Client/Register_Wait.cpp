#include "Visual_interface.h"

void Register_Wait()
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(420, 300, _T("Waiting to Register ..."));
	Sleep(3000);
}