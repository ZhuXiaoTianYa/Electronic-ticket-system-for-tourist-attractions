#include "Visual_interface.h"
#include <json/json.h>
#include <string>
void Start()
{
	Json::Value root;
	std::string name = "Electronic ticket system for tourist attractions";
	judgment_err_ = false;
	settextcolor(RGB(0, 0, 0));
	settextstyle(30, 0, _T("Î¢ÈíÑÅºÚ"));
	//outtextxy(400, 60, _T("Electronic ticket system for tourist attractions"));
	outtextxy(400, 60, (name.c_str()));
	outtextxy(600, 200, _T("1.Login"));
	outtextxy(600, 300, _T("2.Register"));
	outtextxy(600, 400, _T("3.Quit"));
	setlinecolor(RGB(0, 0, 0));
	rectangle(550, 190, 800, 240);
	rectangle(550, 290, 800, 340);
	rectangle(550, 390, 800, 440);
	while (true)
	{

		ExMessage mouse_ = getmessage(EX_MOUSE);
		if (mouse_.lbutton)
		{
			if (mouse_.x >= 550 && mouse_.x <= 800 && mouse_.y >= 190 && mouse_.y <= 240)
			{
				pos_ = static_cast<int>(Scene::Login_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 550 && mouse_.x <= 800 && mouse_.y >= 290 && mouse_.y <= 340)
			{
				pos_ = static_cast<int>(Scene::Register_Sc);
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 550 && mouse_.x <= 800 && mouse_.y >= 390 && mouse_.y <= 440)
			{
				pos_ = static_cast<int>(Scene::Quit_Sc);
				judgment_err_ = false;
				return;
			}
			else
			{
				judgment_err_ = true;
				continue;
			}
		}

		/*Clear();
		printf("%s", start_);
		printf("%s", LINE_SEP);
		int num=Choose();
		switch (num)
		{
		case static_cast<int>(Scene::Login_Sc):
		case static_cast<int>(Scene::Register_Sc):
		case static_cast<int>(Scene::Quit_Sc):
			pos_ = num;
			judgment_err_ = false;
			return;
		default:
			judgment_err_ = true;
			continue;
		}*/
	}
}
