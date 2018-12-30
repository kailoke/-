#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/*
1.�����ṹ��洢���ʺͷ���
2.���ص��ʿ⣬��ʽ���洢���ѿռ�
3.����ģʽѡ��
4.��ѯ����ĵ��ʣ����ط��루�����ڴ�ռ䣩
5.�ȴ���������(����ر�)

x.���ӷ�Χ����
*/

int(*index)[27];

void loadWord()
{
	//���ص��ʿ�
	FILE *fp = fopen("dictA.txt", "r");
	if (!fp)
	{
		printf("���ص��ʿ�ʧ��!\n");
		dict_exit(1);
	}

	//��ʽ���洢
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
		printf(" ============��ӭʹ��kailoke�ֵ�==========\n\n");
	else 
	{
		printf("load");
		dict_exit();
	}
}


void showmenu()
{
	printf("------------    �ʵ�˵�����   ------------\n\
|\t1.Ӣ�뺺\t\t\t  |\n\
|\t2.����Ӣ\t\t\t  |\n\
|\t\t\t\t\t  |\n\
|\t\t\t\t\t  |\n\
|   ϵͳָ�  \t\t\t  |\n\
|   \t@menu:���ز˵�����\t\t  |\n\
|   \t@exit:�˳�����\t\t\t  |\n\
|- - - - - - - - - - - - - - - - - - - - -|\n\
==<dict>== ����ģʽ--->:"
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
			printf("<%s>�����ڴ����෭��ģʽ�����������룺", input);
		}
		else
		{
			//printf("<system>���벻�Ϸ�������������<system>\n");
			showmenu();
		}
	} while (pat==nonepat);
}


void transTips(Pat pat)
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


int txt_scanf(char *des)
{
	scanf("%s", des);
	if (!strcmp(des, "@exit"))
	{
		dict_exit(0);
		//�˳�����
	}
	if (!strcmp(des, "@menu"))
	{
		return 1;
	}
	
	return 0;
}