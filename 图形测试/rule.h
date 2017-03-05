/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef _RULE_H_
#define _RULE_H_
//プロトタイプ宣言
HRESULT InitRule(void);
void UninitRule(void);
void UpdateRule(void);
void DrawRule(void);
#endif