#pragma once
#define SIZE 7989


//����
typedef	struct DICT
{
	char *word;
	char *trans;
}dict;
extern dict *list;

//ģʽ
typedef enum PATTERN
{
	nonepat,eng_chn, chn_eng
}Pat;
extern Pat pat;

extern char *search;	//����Ŀ��
extern char *result;	//������


void loadWord(void);
void pattern(void);
void showmenu();
void transTips(Pat);
void patternNotice(Pat);
int searchword(char *searchTarget, char *result, int(*p_func)(char *, char *));
void output(int);
int txt_scanf(char *);