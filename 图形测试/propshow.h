/*******************************************************************************
* タイトル： ツール描画関数
* ファイル名： propshow	.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/12/15
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _PROPSHOW_H_
#define _PROPSHOW_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	マクロ定義
//------------------------------------------------------------------------------*/
#define MAX_PROW	(1) //ツールの数量
#define PROW_WIDTH ( 30.0f ) //ツールの幅
#define PROW_HEIGHT ( 30.0f ) //ツールの高さ
#define	PROW_SIZE_X		(100.0f)							// ツールの数字の幅
#define	PROW_SIZE_Y		(100.0f)							// ツールの数字の高さ
#define	PROW_INTERVAL_X	(0.0f)							// ツールの数字の表示間隔

#define	NUM_PLACE_PROW			(1)								// ツールの桁数

#define	NUM_PATTERN_PROW			(3)						// アニメーションのパターン数

#define	TEXTURE_SIZE_X_PROW		(1.0f / NUM_PATTERN_PROW)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_PROW		(1.0f)					// テクスチャ内の１パターンの高さ

#define	PROW_POS_X			(SCREEN_WIDTH - (PROW_INTERVAL_X + PROW_SIZE_X) * NUM_PLACE_PROW - 10.0f)	// ツールの表示基準位置Ｘ座標
#define	PROW_POS_Y			(10.0f)																	// ツールの表示基準位置Ｙ座標

#define	INTERVAL_PATTERN_PROW	(5)						// アニメーションの切り替え間隔
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
	bool bProwUse;
} PROW;
//プロトタイプ宣言
HRESULT InitProw (void);
void UninitProw (void);
void UpdateProw (void);
void DrawProw (void);
PROW *GetProw( void );
#endif