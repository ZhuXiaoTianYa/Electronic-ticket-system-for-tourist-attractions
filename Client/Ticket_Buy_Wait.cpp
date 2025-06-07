#include "Visual_interface.h"

void Ticket_Buy_Wait()
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(300, 300, _T("Waiting to purchase tickets ..."));
	Sleep(2000);
}