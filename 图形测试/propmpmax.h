/*******************************************************************************
* タイトル： ツール描画関数
* ファイル名： propmpmax.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/01
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _PROPMPMAX_H_
#define _PROPMPMAX_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	マクロ定義
//------------------------------------------------------------------------------*/
#define MAX_PROPMPMAX	(1) //ツールの数量
#define PROPMPMAX_WIDTH ( 15.0f ) //ツールの幅
#define PROPMPMAX_HEIGHT ( 100.0f ) //ツールの高さ
#define	PROPMPMAX_INTERVAL_X	(0.0f)							// ツールの数字の表示間隔

#define	NUM_PLACE_PROPMPMAX			(1)								// ツールの桁数

#define	NUM_PATTERN_PROPMPMAX			(2)						// アニメーションのパターン数

#define	TEXTURE_SIZE_X_PROPMPMAX		(1.0f / NUM_PATTERN_PROPMPMAX)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_PROPMPMAX		(1.0f)					// テクスチャ内の１パターンの高さ


#define	INTERVAL_PATTERN_PROPMPMAX	(10)						// アニメーションの切り替え間隔
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
} PROPMPMAX;
//プロトタイプ宣言
HRESULT InitPropMpMax (void);
void UninitPropMpMax (void);
void UpdatePropMpMax (void);
void DrawPropMpMax (void);
PROPMPMAX *GetPropMpMax( void );
#endif