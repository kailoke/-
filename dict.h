#pragma once
#define SIZE 7989
#ifndef NULL
	#define NULL 0
#endif // !NULL

//ȫ�ֱ����Ķ���	�ṹ�����������
typedef	struct DICT
{
	char *word;
	char *trans;
}dict;
extern dict* list;

typedef enum PATTERN
{
	nonepat,eng_chn, chn_eng
}Pat;
extern Pat pat;

//��������
int loadWord(void);
void pattern(void);
void showmenu(int);
void searchInfo(Pat);
void patternNotice(Pat);
int searchword(char * searchTarget, char * result, int(*p_func)(char*, char*));
void output(int);