#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include <string.h>

extern char* search;
extern char* result;
/*
1.创建结构体存储单词和翻译
2.加载单词库，格式化存储到堆空间
3.设置模式选择
4.查询输入的单词，返回翻译（独立内存空间）
5.內存数据销毁(程序关闭)

x.增加范围索引
*/


int loadWord()
{
	//加载单词库
	FILE *fp = fopen("dictA.txt", "r");
	if (!fp)
	{
		printf("加载单词库失败\n");
		return -1; 
	}

	//格式化存储
	list = (dict*)malloc(sizeof(dict) * SIZE);
	int index = 0;
	char* temp = (char*)malloc(sizeof(char) * 1024);
	int* totalLen = (int*)malloc(sizeof(int));
	char* temp_word = NULL;
	//char* temp_trans = NULL;

	while (!feof(fp))
	{
		memset(temp, 0, 1024);
		fgets(temp, 1024, fp);
		*totalLen = strlen(temp);
		temp_word = strtok(temp, "   ");
		//temp_trans = strtok(0, "   ");

		list[index].word = (char*)malloc(sizeof(char)*strlen(temp_word) + 1);
		strcpy(list[index].word, temp_word);
		list[index].trans = (char*)malloc(sizeof(char)*(*totalLen-strlen(temp_word)) + 1);
		strcpy(list[index].trans, temp+strlen(temp_word)+3);

		printf("%s,", list[index].word);
		printf("%s\n", list[index].trans);
		index++;
	}
		
	free(temp);
	fclose(fp);

	return index;
}

void pattern()
{
	showmenu(0);

	char* input = (char*)malloc(sizeof(char) * 10);
	do
	{
		memset(input, 0, 10);
		pat = nonepat;
		scanf("%s", input);

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
			printf("敬请期待<%s>更多翻译模式，请重新输入：", input);
		}
		else
		{
			showmenu(1);
		}
	} while (pat==nonepat);
}


void showmenu(int flag)
{
	puts(!flag
		?"<system>支持的翻译模式：\n\t1.英译汉\n\t2.汉译英\n==<dict>== 请输入翻译模式--->:"
		:"<!!!system!!!>不要乱输亲，请按提示输入哈~~~\n<system>支持的翻译模式：\n\t1.英译汉\n\t2.汉译英\n==<dict>== 请输入翻译模式--->:");
}


void searchInfo(Pat pat)
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