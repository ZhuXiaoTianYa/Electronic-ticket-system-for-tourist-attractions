#include "Visual_interface.h"

void Ticket_Buy_Fail()
{
	cleardevice();
	settextcolor(RED);
	settextstyle(60, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(400, 300, _T("Ticket purchase failed"));
	Sleep(3000);
	pos_global = static_cast<int>(Scene::Home_Sc);
}