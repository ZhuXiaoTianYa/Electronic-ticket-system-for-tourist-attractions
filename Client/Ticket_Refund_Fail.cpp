#include "Visual_interface.h"

void Ticket_Refund_Fail()
{
	cleardevice();
	settextcolor(RED);
	pos_global = static_cast<int>(Scene::Home_Sc);
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(420, 300, _T("Ticket refund failed"));
	Sleep(2000);
}