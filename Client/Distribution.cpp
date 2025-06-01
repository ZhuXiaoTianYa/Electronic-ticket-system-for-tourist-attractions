#include "Visual_interface.h"


void Distribution()
{
	while (true)
	{
		switch (pos_)
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
		}
	}
}

