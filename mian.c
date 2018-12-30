#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "dict.h"
#include "translate.h"


dict *list;
Pat pat;
char *search;
char *result;


int main(void)
{
	// 加载单词库
	loadWord();	
	showmenu();
	pattern();

	search = (char*)malloc(sizeof(char) * 1024);
	result = (char*)malloc(sizeof(char) * 1024);
	while (1)
	{
		memset(search, 0, 1024);
		memset(result, 0, 1024);

		transTips(pat);
		if (txt_scanf(search) == 1) 
		{
			showmenu();
			pattern();
			continue;
		}

		//根据模式，选择调用翻译函数并输出结果
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

}


void clean()
{
	if (index)
	{
		free(index);
	}

	if (search) 
	{
		free(search);
		free(result);
	}

	if (!list)
		return;
	for (size_t i = 0; i < SIZE; i++)
	{
		free(list[i].word);
		free(list[i].trans);
	}
	free(list);
}

void dict_exit(int i)
{
	clean();
	puts("程序即将退出...");
	system("pause");
	exit(i);
}

