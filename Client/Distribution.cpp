#include "Visual_interface.h"

void Distribution()
{
	while (true)
	{
		cleardevice();
		switch (pos_global)
		{
		case static_cast<int>(Scene::Start_Sc):
			Start();
			break;
		case static_cast<int>(Scene::Login_Sc):
			Login();
			break;
		case static_cast<int>(Scene::Register_Sc):
			Register();
			break;
		case static_cast<int>(Scene::Quit_Sc):
			return;
		case static_cast<int>(Scene::Home_Sc):
			Home();
			break;
		case static_cast<int>(Scene::Ticket_list_Sc):
			Ticket_list();
			break;
		case static_cast<int>(Scene::Ticket_details_Sc):
			Ticket_Details(areas_name, areas_introduction, areas_tickets_total, areas_remaining_tickets);
			break;
			//¬Ú∆±Ã· æ¥∞
		case static_cast<int>(Scene::Ticket_Buy_Wait_Sc):
			Ticket_Buy_Wait();
			break;
		case static_cast<int>(Scene::Ticket_Buy_Success_Sc):
			Ticket_Buy_Success();
			break;
		case static_cast<int>(Scene::Ticket_Buy_Fail_Sc):
			Ticket_Buy_Fail();
			break;
			//π∫∆±º«¬º
		case static_cast<int>(Scene::Ticket_Records_Sc):
			Ticket_Records(records_global);
			break;
			//ÕÀ∆±Ã· æ¥∞
		case static_cast<int>(Scene::Ticket_Refund_Wait_Sc):
			Ticket_Refund_Wait();
			break;
		case static_cast<int>(Scene::Ticket_Refund_Success_Sc):
			Ticket_Refund_Success();
			break;
		case static_cast<int>(Scene::Ticket_Refund_Fail_Sc):
			Ticket_Refund_Fail();
			break;
		case static_cast<int>(Scene::Login_Wait_Sc):
			Login_Wait();
			break;
		case static_cast<int>(Scene::Login_Success_Sc):
			Login_Success();
			break;
		case static_cast<int>(Scene::Login_Fail_Sc):
			Login_Fail();
			break;
			//◊¢≤·Ã· æ¥∞
		case static_cast<int>(Scene::Register_Wait_Sc):
			Register_Wait();
			break;
		case static_cast<int>(Scene::Register_Fail_Sc):
			Register_Fail();
			break;
		case static_cast<int>(Scene::Register_Success_Sc):
			Register_Success(name_global,id_global, passwd_global);
			break;
		}
	}
}

