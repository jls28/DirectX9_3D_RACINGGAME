/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_MONEY_H_
#define	_MONEY_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_MONEY ( 8 )                     // ツールの数
#define LIFE_MONEY (100)
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
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
	int nLife;
	D3DXMATRIX				mtxWorld;					//ワールドマトリックス
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//拡大縮小、向き、位置マトリックス
	LPDIRECT3DTEXTURE9			pTextureMoney ;			//テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffMoney ;			//頂点バッファへのポインタ
} MONEY;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitMoney( void );
void UninitMoney( void );
void UpdateMoney( void );
void DrawMoney( void );

MONEY *GetMoney( void );
void SetMoney( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
#endif