#include "Visual_interface.h"

void Start()
{
	judgment_err_ = false;
	setlinecolor(RGB(0, 0, 0));
	fillroundrect(550, 190, 800, 240, 50, 250);
	fillroundrect(550, 290, 800, 340, 50, 250);
	fillroundrect(550, 390, 800, 440, 50, 250);
	settextcolor(RGB(0, 0, 0));
	settextstyle(50, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(300, 60, _T("Electronic ticket system for tourist attractions"));
	settextstyle(30, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(600, 200, _T("1.Login"));
	outtextxy(600, 300, _T("2.Register"));
	outtextxy(600, 400, _T("3.Quit"));

	while (true)
	{

		ExMessage mouse_ = getmessage(EX_MOUSE);
		if (mouse_.lbutton)
		{
			if (mouse_.x >= 550 && mouse_.x <= 800 && mouse_.y >= 190 && mouse_.y <= 240)
			{
				pos_global = static_cast<int>(Scene::Login_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 550 && mouse_.x <= 800 && mouse_.y >= 290 && mouse_.y <= 340)
			{
				pos_global = static_cast<int>(Scene::Register_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 550 && mouse_.x <= 800 && mouse_.y >= 390 && mouse_.y <= 440)
			{
				pos_global = static_cast<int>(Scene::Quit_Sc);
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
