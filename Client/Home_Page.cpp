#include "Visual_interface.h"

void Home()
{
	judgment_err_ = false;
	setlinecolor(RGB(0, 0, 0));
	rectangle(350, 30, 900, 560);
	setfillcolor(WHITE);
	fillroundrect(500, 200, 750, 270, 50, 250);
	fillroundrect(500, 320, 750, 390, 50, 250);
	fillroundrect(500, 440, 750, 510, 50, 250);

	settextcolor(RGB(0, 0, 0));
	settextstyle(50, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(570, 70, _T("HOME"));
	settextstyle(35, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(550, 220, _T("Buy   Ticket"));
	outtextxy(550, 340, _T("Refund Ticket"));
	outtextxy(550, 460, _T("View Records"));

	outtextxy(1100, 650, _T("<-Return"));
	// Sleep(10000);

	while (true)
	{
		flushmessage();
		ExMessage mouse_ = getmessage(EX_MOUSE);
		if (mouse_.lbutton)
		{
			if (mouse_.x >= 500 && mouse_.x <= 750 && mouse_.y >= 200 && mouse_.y <= 270)
			{
				pos_global = static_cast<int>(Scene::Ticket_list_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 500 && mouse_.x <= 750 && mouse_.y >= 320 && mouse_.y <= 390)
			{
				pos_global = static_cast<int>(Scene::Ticket_Records_Sc);
				int result = record_request(id_global, &records_global, sock_global);
				if (result)
				{
					pos_global = static_cast<int>(Scene::Ticket_Records_Sc);
				}
				else
				{
					pos_global = static_cast<int>(Scene::Home_Sc);
				}
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 500 && mouse_.x <= 750 && mouse_.y >= 440 && mouse_.y <= 510)
			{
				pos_global = static_cast<int>(Scene::Ticket_Records_Sc);
				int result = record_request(id_global, &records_global, sock_global);
				if (result)
				{
					pos_global = static_cast<int>(Scene::Ticket_Records_Sc);
				}
				else
				{
					pos_global = static_cast<int>(Scene::Home_Sc);
				}
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 1100 && mouse_.x <= 1250 && mouse_.y >= 600 && mouse_.y <= 700)
			{
				pos_global = static_cast<int>(Scene::Start_Sc);
				judgment_err_ = false;
				return;
			}
			else
			{
				judgment_err_ = true;
				continue;
			}
		}
	}
}