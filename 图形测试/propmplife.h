/*******************************************************************************
* タイトル： ツール描画関数
* ファイル名： propmplife	.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/12/15
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _PROPMPLIFE_H_
#define _PROPMPLIFE_H_

//*------------------------------------------------------------------------------
//|	マクロ定義
//------------------------------------------------------------------------------*/
#define MAX_PROPMPLIFE	( 100 ) //ツールlifeの数量
#define PROPMPLIFE_WIDTH ( 15.0f ) //ツールの幅
#define PROPMPLIFE_HEIGHT ( 1.0f ) //ツールの高さ
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 move;	// 移動量
	D3DXCOLOR col;		// 色
	bool bUse;			// 使用しているかどうか
	int time;
	int frame;
} PROPMPLIFE;
//プロトタイプ宣言
HRESULT InitPropMpLife (void);
void UninitPropMpLife (void);
void UpdatePropMpLife (void);
void DrawPropMpLife (void);
PROPMPLIFE *GetPropMpLife( void );
#endif