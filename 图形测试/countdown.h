//=============================================================================
//
// 倒時計処理 [countdown.h]
// 2016/02/24 LIHAOSHENG
//
//=============================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	マクロ定義
//------------------------------------------------------------------------------*/
#define MAX_COUNTDOWN	(1) //倒時計の数量
#define	COUNTDOWN_SIZE_X		(450.0f)							// 倒時計の数字の幅
#define	COUNTDOWN_SIZE_Y		(350.0f)							// 倒時計の数字の高さ
#define	COUNTDOWN_INTERVAL_X	(0.0f)							// 倒時計の数字の表示間隔

#define	NUM_PLACE_COUNTDOWN			(1)								// 倒時計の桁数

#define	NUM_PATTERN_COUNTDOWN			(3)						// アニメーションのパターン数

#define	TEXTURE_SIZE_X_COUNTDOWN		(1.0f / NUM_PATTERN_COUNTDOWN)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_COUNTDOWN		(1.0f)					// テクスチャ内の１パターンの高さ

#define	COUNTDOWN_POS_X			(430.0f)	// 倒時計の表示基準位置Ｘ座標
#define	COUNTDOWN_POS_Y			(200.0f)																	// 倒時計の表示基準位置Ｙ座標

#define	INTERVAL_PATTERN_COUNTDOWN	(60)						// アニメーションの切り替え間隔
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
} COUNTDOWN;
//プロトタイプ宣言
HRESULT InitCountdown (void);
void UninitCountdown (void);
void UpdateCountdown (void);
void DrawCountdown (void);
COUNTDOWN *GetCountdown( void );
#endif