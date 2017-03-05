/*******************************************************************************
* タイトル： boxscore描画関数
* ファイル名： boxscore.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/01
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _BOXSCORE01_H_
#define _BOXSCORE01_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	マクロ定義
//------------------------------------------------------------------------------*/
#define MAX_BOXSCORE01	(256) //BOXSCORE01の数量

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posBase;	// 基準位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	D3DXVECTOR3 scl;		//拡大縮小
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;				// 使用しているかどうか
	int nLife;
	D3DXMATRIX				mtxWorld;					//ワールドマトリックス
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//拡大縮小、向き、位置マトリックス
	LPDIRECT3DTEXTURE9			pTextureBoxScore01 ;			//テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffBoxScore01 ;			//頂点バッファへのポインタ
} BOXSCORE01;
//プロトタイプ宣言
HRESULT InitBoxScore01 (void);
void UninitBoxScore01 (void);
void UpdateBoxScore01 (void);
void DrawBoxScore01 (void);
BOXSCORE01 *GetBoxScore01( void );
void SetBoxScore01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
#endif