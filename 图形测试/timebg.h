#ifndef _TIMEBG_H_
#define _TIMEBG_H_
//timeの構造体
typedef struct
{
	int time;
	int frame;
	bool bUse;
} TIMEBG;
//プロトタイプ宣言
HRESULT InitTimebg(void);
void UninitTimebg(void);
void UpdateTimebg(void);
void DrawTimebg(void);
void AddTimebg(int valueTimebg);
TIMEBG *GetTimeBg( void );

#endif