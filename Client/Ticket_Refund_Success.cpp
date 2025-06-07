#include "Visual_interface.h"

void Ticket_Refund_Success()
{
	cleardevice();
	pos_global = static_cast<int>(Scene::Home_Sc);
	settextcolor(RGB(0, 0, 0));
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(370, 300, _T("Ticket refund successful !"));
	Sleep(2000);
}