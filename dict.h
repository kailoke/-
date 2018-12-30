#pragma once
#define SIZE 7989


//单词
typedef	struct DICT
{
	char *word;
	char *trans;
}dict;
extern dict *list;

//模式
typedef enum PATTERN
{
	nonepat,eng_chn, chn_eng
}Pat;
extern Pat pat;

extern char *search;	//查找目标
extern char *result;	//翻译结果


void loadWord(void);
void pattern(void);
void showmenu();
void transTips(Pat);
void patternNotice(Pat);
int searchword(char *searchTarget, char *result, int(*p_func)(char *, char *));
void output(int);
int txt_scanf(char *);