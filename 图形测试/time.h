#ifndef _TIME_H_
#define _TIME_H_
//timeの構造体
typedef struct
{
	int time;
	int frame;
} TIME;
//プロトタイプ宣言
void InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
TIME *GetTime( void );
#endif