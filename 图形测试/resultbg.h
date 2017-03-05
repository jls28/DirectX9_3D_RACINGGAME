/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef _RESULTBG_H_
#define _RESULTBG_H_
//プロトタイプ宣言
HRESULT InitResultBg(void);
void UninitResultBg(void);
void UpdateResultBg(void);
void DrawResultBg(void);
#endif