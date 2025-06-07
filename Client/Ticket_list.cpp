#include "Visual_interface.h"

void Ticket_list()
{
	setlinecolor(RGB(0, 0, 0));
	rectangle(350, 30, 900, 560);
	setfillcolor(WHITE);
	fillroundrect(450, 200, 820, 270, 50, 250);
	fillroundrect(450, 320, 820, 390, 50, 250);
	fillroundrect(450, 440, 820, 510, 50, 250);

	settextcolor(RGB(0, 0, 0));
	settextstyle(50, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(550, 70, _T("Ticket List"));
	settextstyle(35, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(520, 220, _T("Great Wall,Beijing"));
	outtextxy(480, 340, _T("Victoria Peak,Guangdong"));
	outtextxy(520, 460, _T("The Bund,Shanghai"));

	outtextxy(1100, 650, _T("<-Return"));

	while (true)
	{
		flushmessage();
		ExMessage mouse_ = getmessage(EX_MOUSE);
		if (mouse_.lbutton)
		{
			if (mouse_.x >= 450 && mouse_.x <= 820 && mouse_.y >= 200 && mouse_.y <= 270)
			{
				areas_aid = BEIJING;
				areas_request(areas_aid, sock_global);
				pos_global = static_cast<int>(Scene::Ticket_details_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 450 && mouse_.x <= 820 && mouse_.y >= 320 && mouse_.y <= 390)
			{
				areas_aid = GUANGDONG;
				areas_request(areas_aid, sock_global);
				pos_global = static_cast<int>(Scene::Ticket_details_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 450 && mouse_.x <= 820 && mouse_.y >= 440 && mouse_.y <= 510)
			{
				areas_aid = SHANGHAI;
				areas_request(areas_aid, sock_global);
				pos_global = static_cast<int>(Scene::Ticket_details_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 1100 && mouse_.x <= 1250 && mouse_.y >= 600 && mouse_.y <= 700)
			{
				pos_global = static_cast<int>(Scene::Home_Sc);
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