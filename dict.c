#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/*
1.创建结构体存储单词和翻译
2.加载单词库，格式化存储到堆空间
3.设置模式选择
4.查询输入的单词，返回翻译（独立内存空间）
5.內存数据销毁(程序关闭)

x.增加范围索引
*/

int(*index)[27];

void loadWord()
{
	//加载单词库
	FILE *fp = fopen("dictA.txt", "r");
	if (!fp)
	{
		printf("加载单词库失败!\n");
		dict_exit(1);
	}

	//格式化存储
	list = (dict*)malloc(sizeof(dict) * SIZE);
	int count = 0;
	int totalLen;
	char* temp = (char*)malloc(sizeof(char) * 1024);
	char* temp_word = NULL;

	char flag = 'a';
	index = (int*)malloc(sizeof(int) * 27);
	memset(index, 0, sizeof(int)*27);

	while (!feof(fp))
	{
		memset(temp, 0, 1024);
		fgets(temp, 1024, fp);
		totalLen = strlen(temp);
		temp_word = strtok(temp, "   ");

		list[count].word = (char*)malloc(sizeof(char)*strlen(temp_word) + 1);
		strcpy(list[count].word, temp_word);
		list[count].trans = (char*)malloc(sizeof(char)*(totalLen-strlen(temp_word)) + 1);
		strcpy(list[count].trans, temp+strlen(temp_word)+3);

		//printf("%s,", list[index].word);
		//printf("%s\n", list[index].trans);
		count++;

		if (temp_word[0] == flag)
		{
			(*index)[flag-'a'+1]++;
		}
		else
		{
			flag++;
			(*index)[flag-'a'+1] = (*index)[flag-'a'] + 1;
		}
	}

	//for (size_t i = 0; i < 27; i++)
	//	printf("%c:%d\n", i+'a'-1,(*index)[i]);

	temp_word = NULL;
	free(temp);
	fclose(fp);

	if (count == SIZE)
		printf(" ============欢迎使用kailoke字典==========\n\n");
	else 
	{
		printf("load");
		dict_exit();
	}
}


void showmenu()
{
	printf("------------    词典菜单界面   ------------\n\
|\t1.英译汉\t\t\t  |\n\
|\t2.汉译英\t\t\t  |\n\
|\t\t\t\t\t  |\n\
|\t\t\t\t\t  |\n\
|   系统指令：  \t\t\t  |\n\
|   \t@menu:返回菜单界面\t\t  |\n\
|   \t@exit:退出程序\t\t\t  |\n\
|- - - - - - - - - - - - - - - - - - - - -|\n\
==<dict>== 翻译模式--->:"
);
}


void pattern()
{
	char *input = (char*)malloc(sizeof(char) * 10);
	do
	{
		memset(input, 0, 10);
		pat = nonepat;

		if(txt_scanf(input) == 1)
		{
			showmenu();
			continue;
		}
			
		if (strlen(input)==1)
		{
			for (int i = eng_chn; i <= chn_eng; i++)
			{
				if (input[0]-'0' == i)
				{
					pat = input[0]-'0';
					patternNotice(pat);
					free(input);
					return;
				}
			}
			printf("<%s>敬请期待更多翻译模式，请重新输入：", input);
		}
		else
		{
			//printf("<system>输入不合法，请重新输入<system>\n");
			showmenu();
		}
	} while (pat==nonepat);
}


void transTips(Pat pat)
{
	switch (pat)
	{
	case eng_chn:
		printf("请输入单词：");
		break;
	case chn_eng:
		printf("请输入中文：");
		break;
	default:
		printf("翻译模式错误!\n");
	}
}


void patternNotice(Pat pat)
{
	switch (pat)
	{
	case eng_chn:
		puts("========== <dict>当前模式为将 英文 翻译为 中文 ==========");
		break;
	case chn_eng:
		puts("========== <dict>当前模式为将 中文 翻译为 英文 ==========");
		break;
	default:
		printf("翻译模式错误!\n");
	}
}


int searchword(char * searchTarget, char * result, int(*p_func)(char*, char*))
{
	return (*p_func)(searchTarget, result);
}


void output(int rv)
{
	switch (pat)
	{
	case eng_chn:
		printf(!rv ? "未找到单词\n" : "查找到单词:%s\t\t中文翻译：%s\n", search, result);
		break;
	case chn_eng:
		printf(!rv ? "未找到中文\n" : "查找到中文:%s\t\t英文单词：%s\n", search, result);
		break;
	default:
		break;
	}
}


int txt_scanf(char *des)
{
	scanf("%s", des);
	if (!strcmp(des, "@exit"))
	{
		dict_exit(0);
		//退出程序
	}
	if (!strcmp(des, "@menu"))
	{
		return 1;
	}
	
	return 0;
}