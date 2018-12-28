#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "translate.h"

dict *list = NULL;
Pat pat = nonepat;
char* search;
char* result;
void output(int);
void clean();

int main(void)
{
	// 加载单词库
	int num = loadWord();
	if (num == SIZE)
		printf("<system>词典初始化成功！\n");
	else
	{puts("程序即将退出");system("pause");return -2;}

	pattern();

	search = (char*)malloc(sizeof(char) * 1024);
	result = (char*)malloc(sizeof(char) * 1024);
	while (1)
	{
		memset(search, 0, 1024);
		memset(result, 0, 1024);

		searchInfo(pat);
		scanf("%s", search);
		if (!strcmp(search, "@exit"))
		{
			printf("程序退出");
			break;
		}
		if (!strcmp(search, "@pattern"))
		{
			pattern();
			continue;
		}

		switch (pat)
		{
		case eng_chn:
			output(searchword(search, result, t_eng_chn));
			break;
		case chn_eng:
			output(searchword(search, result, t_chn_eng));
			break;
		default:
			break;
		}
	}

	free(search);
	free(result);
	clean();
	system("pause");
	return 0;
}


void clean()
{
	if (!list)
		return;
	for (size_t i = 0; i < SIZE; i++)
	{
		free(list[i].word);
		free(list[i].trans);
	}
	free(list);
}

