#define _CRT_SECURE_NO_WARNINGS
#include "Visual_interface.h"

void ticket_details(std::string name, std::string introduction, std::string tickets_total, std::string remaining_tickets, int *num)
{
	cleardevice();
	settextcolor(BLACK);
	settextstyle(50, 0, _T("΢���ź�"));
	outtextxy(430, 50, name.c_str()); // == outtextxy(520, 460, ��guangdon��);

	setlinecolor(RGB(0, 0, 0));
	rectangle(300, 110, 980, 520);

	settextstyle(30, 0, _T("΢���ź�"));

	RECT r = {300, 120, 980, 520};
	drawtext(introduction.c_str(), &r, DT_CENTER);

	std::string ticket_total_str = "��Ʊ����" + tickets_total;
	outtextxy(280, 550, ticket_total_str.c_str());
	std::string remaining_tickets_str = "ʣ��Ʊ����" + remaining_tickets;
	outtextxy(280, 590, remaining_tickets_str.c_str());

	settextstyle(55, 0, _T("΢���ź�"));
	outtextxy(870, 550, "-");
	circle(880, 580, 20);
	settextstyle(40, 0, _T("΢���ź�"));
	// ��ʾƱ������ʱд��Ϊ��1��
	outtextxy(930, 560, std::to_string(*num).c_str());
	outtextxy(990, 560, "+");
	circle(1000, 580, 20);

	fillroundrect(860, 610, 1020, 650, 50, 250);
	fillroundrect(860, 660, 1020, 700, 50, 250);
	settextstyle(25, 0, _T("΢���ź�"));
	outtextxy(895, 618, "Buy Ticket");
	outtextxy(895, 668, "<-Return");
}

void Ticket_Details(std::string name, std::string introduction, std::string tickets_total, std::string remaining_tickets)
{
	int num = 1;
	ticket_details(name, introduction, tickets_total, remaining_tickets, &num);
	int remaining_tickets_num = std::atoi(remaining_tickets.c_str());
	while (true)
	{
		ExMessage mouse_ = getmessage(EX_MOUSE);
		if (mouse_.lbutton)
		{
			flushmessage();
			if (mouse_.x >= 860 && mouse_.x <= 900 && mouse_.y >= 560 && mouse_.y <= 600)
			{
				if (num > 1)
				{
					num--;
				}
				ticket_details(name, introduction, tickets_total, remaining_tickets, &num);
				// ��һ��Ʊ
				printf("--");
				// flushmessage();
				// return;
			}
			else if (mouse_.x >= 980 && mouse_.x <= 1020 && mouse_.y >= 560 && mouse_.y <= 600)
			{
				// ��һ��Ʊ
				if (num < remaining_tickets_num)
				{
					num++;
				}
				ticket_details(name, introduction, tickets_total, remaining_tickets, &num);
				printf("++");
				// return;
			}
			else if (mouse_.x >= 860 && mouse_.x <= 1020 && mouse_.y >= 610 && mouse_.y <= 650)
			{

				pos_global = static_cast<int>(Scene::Ticket_Buy_Wait_Sc);
				Ticket_Buy_Wait();
				int result = tickets_request(id_global, areas_aid, "Buy", std::to_string(num), sock_global);
				if (result)
				{
					pos_global = static_cast<int>(Scene::Ticket_Buy_Success_Sc);
				}
				else
				{
					pos_global = static_cast<int>(Scene::Ticket_Buy_Fail_Sc);
				}
				judgment_err_ = false;
				return;
			}
			else if (mouse_.x >= 860 && mouse_.x <= 1020 && mouse_.y >= 660 && mouse_.y <= 700)
			{

				pos_global = static_cast<int>(Scene::Ticket_list_Sc);
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