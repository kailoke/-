#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "translate.h"


int t_eng_chn(char* search, char* result)
{
	if (!search || !result)
	{
		printf("输入的信息异常(t_eng_chn)");
		return -1;
	}

	for (int i =(*index)[search[0]-'a']; i < (*index)[search[0]-'a'+1]; i++)
	{
		if (!strcmp(search, list[i].word))
		{
			strcpy(result, list[i].trans);
			return 1;
		}
	}
	return 0;
}



int t_chn_eng(char* search, char* result)
{
	int count = 0;
	if (!search || !result)
	{
		printf("输入的信息异常(t_eng_chn)");
		return -1;
	}

	for (int i = 0; i < SIZE; i++)
	{
		if (strstr(list[i].trans, search))
		{
			strcat(result, list[i].word);
			strcat(result, "|");
			count++;
		}
	}
	return count;
}
