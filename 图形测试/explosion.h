//=============================================================================
//
// 爆発処理 [explosion.h]
// 2015/11/24 LIHAOSHENG
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 scl;	//拡大縮小
	D3DXCOLOR col;		// 色z
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.
	bool bUse;			// 使用しているかどうか
	D3DXMATRIX mtxWorldExplosion;					// ワールドマトリックス。ビューマトリックスの逆行列を入れる。

} EXPLOSION;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void ResetExplosion(void);
EXPLOSION *GetExplosion(void);
#endif
