/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_RUNLEG_H_
#define	_RUNLEG_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_RUNLEG ( 2 )                     // ツールの数

/*******************************************************************************
* 構造体宣言
*******************************************************************************/
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
	D3DXMATRIX				mtxWorld;					//ワールドマトリックス
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//拡大縮小、向き、位置マトリックス
	LPDIRECT3DTEXTURE9			pTextureRunLeg ;			//テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffRunLeg ;			//頂点バッファへのポインタ
	int nCount;			// カウンタ
	int nPattern;		// パターンNo.
} RUNLEG;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitRunLeg( void );
void UninitRunLeg( void );
void UpdateRunLeg( void );
void DrawRunLeg( void );
void ResetRunLeg(void);
RUNLEG *GetRunLeg( void );
void SetTextureRunLeg(int nRunLegID);
#endif