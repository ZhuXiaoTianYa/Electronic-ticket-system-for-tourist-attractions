#include "Visual_interface.h"

void Ticket_Refund_Wait()
{
	cleardevice();
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(320, 300, _T("Waiting to refund tickets ..."));
	Sleep(2000);
}