#define _CRT_SECURE_NO_WARNINGS
#include "Visual_interface.h"

int Choose()
{
	int num = -1;
	if (judgment_err_)
		printf("ѡ���������������\n");
	printf("%s", choose_);
	scanf(" %d", &num);
	return num;
}