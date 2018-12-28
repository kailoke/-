#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include <string.h>

extern char* search;
extern char* result;
/*
1.�����ṹ��洢���ʺͷ���
2.���ص��ʿ⣬��ʽ���洢���ѿռ�
3.����ģʽѡ��
4.��ѯ����ĵ��ʣ����ط��루�����ڴ�ռ䣩
5.�ȴ���������(����ر�)

x.���ӷ�Χ����
*/


int loadWord()
{
	//���ص��ʿ�
	FILE *fp = fopen("dictA.txt", "r");
	if (!fp)
	{
		printf("���ص��ʿ�ʧ��\n");
		return -1; 
	}

	//��ʽ���洢
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
			printf("�����ڴ�<%s>���෭��ģʽ�����������룺", input);
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
		?"<system>֧�ֵķ���ģʽ��\n\t1.Ӣ�뺺\n\t2.����Ӣ\n==<dict>== �����뷭��ģʽ--->:"
		:"<!!!system!!!>��Ҫ�����ף��밴��ʾ�����~~~\n<system>֧�ֵķ���ģʽ��\n\t1.Ӣ�뺺\n\t2.����Ӣ\n==<dict>== �����뷭��ģʽ--->:");
}


void searchInfo(Pat pat)
{
	switch (pat)
	{
	case eng_chn:
		printf("�����뵥�ʣ�");
		break;
	case chn_eng:
		printf("���������ģ�");
		break;
	default:
		printf("����ģʽ����!\n");
	}
}


void patternNotice(Pat pat)
{
	switch (pat)
	{
	case eng_chn:
		puts("========== <dict>��ǰģʽΪ�� Ӣ�� ����Ϊ ���� ==========");
		break;
	case chn_eng:
		puts("========== <dict>��ǰģʽΪ�� ���� ����Ϊ Ӣ�� ==========");
		break;
	default:
		printf("����ģʽ����!\n");
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
		printf(!rv ? "δ�ҵ�����\n" : "���ҵ�����:%s\t\t���ķ��룺%s\n", search, result);
		break;
	case chn_eng:
		printf(!rv ? "δ�ҵ�����\n" : "���ҵ�����:%s\t\tӢ�ĵ��ʣ�%s\n", search, result);
		break;
	default:
		break;
	}
}