#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Visual_interface.h"
#include <easyx.h>
#include <Windows.h>

int main()
{
	//char s[] = "Hello World";
	initgraph(1280, 720, EX_SHOWCONSOLE);
	releasecapture();
	setbkcolor(RGB(255,255,255));
	cleardevice();

	Distribution();
	system("pause");
	return 0;
}