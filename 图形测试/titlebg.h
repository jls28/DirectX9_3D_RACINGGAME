/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef _TITLEBG_H_
#define _TITLEBG_H_
//プロトタイプ宣言
HRESULT InitTitleBg(void);
void UninitTitleBg(void);
void UpdateTitleBg(void);
void DrawTitleBg(void);
#endif