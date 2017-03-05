/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef _SKIPBG_H_
#define _SKIPBG_H_
#define MAX_SKIPBG	(1) //ツールの数量
#define	SKIPBG_SIZE_X		(700.0f)							// ツールの数字の幅
#define	SKIPBG_SIZE_Y		(300.0f)							// ツールの数字の高さ
#define	SKIPBG_INTERVAL_X	(0.0f)							// ツールの数字の表示間隔

#define	NUM_PLACE_SKIPBG			(1)								// ツールの桁数

#define	NUM_PATTERN_SKIPBG			(7)						// アニメーションのパターン数

#define	TEXTURE_SIZE_X_SKIPBG		(1.0f / NUM_PATTERN_SKIPBG)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_SKIPBG		(1.0f)					// テクスチャ内の１パターンの高さ

#define	SKIPBG_POS_X			(200.0f)	// ツールの表示基準位置Ｘ座標
#define	SKIPBG_POS_Y			(200.0f)																	// ツールの表示基準位置Ｙ座標

#define	INTERVAL_PATTERN_SKIPBG	(65)						// アニメーションの切り替え間隔
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 move;	// 移動量
	D3DXCOLOR col;		// 色
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.
	bool bUse;			// 使用しているかどうか
} SKIPBG;
//プロトタイプ宣言
HRESULT InitSkipBg(void);
void UninitSkipBg(void);
void UpdateSkipBg(void);
void DrawSkipBg(void);
#endif