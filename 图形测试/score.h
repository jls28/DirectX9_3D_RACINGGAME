//=============================================================================
//
// score処理 [score.h]
// 2016/02/20 LIHAOSHENG
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 rot;	// 向き
	D3DXVECTOR3 scl;	//拡大縮小
	D3DXCOLOR col;		// 色z
	bool bUse;			// 使用しているかどうか
	bool bCheck;
	D3DXMATRIX mtxWorld;					// ワールドマトリックス。ビューマトリックスの逆行列を入れる。
	int g_nScore;		//スコアの数
} SCORE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int value);
SCORE *GetScore(void);
int *GetScoreNum(void);
#endif
