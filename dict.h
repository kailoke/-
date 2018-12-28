#pragma once
#define SIZE 7989
#ifndef NULL
	#define NULL 0
#endif // !NULL

//全局变量的定义	结构体或函数的声明
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

//函数声明
int loadWord(void);
void pattern(void);
void showmenu(int);
void searchInfo(Pat);
void patternNotice(Pat);
int searchword(char * searchTarget, char * result, int(*p_func)(char*, char*));
void output(int);