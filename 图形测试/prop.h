/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_PROP_H_
#define	_PROP_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_PROP ( 39 )                     // ツールの数
#define LIFE_PROP (100)
//*************************************
// ツールのの状態
//*************************************
typedef enum
{
	PROPSTATE_START = 0,	// 開始
	PROPSTATE_NORMAL,		// 通常
	PROPSTATE_END,		// 終了
	PROPSTATE_MAX
} PROPSTATE;
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
	int nLife;				// ライフ
	PROPSTATE state;			// 状態
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
	D3DXMATRIX				mtxWorld;					//ワールドマトリックス
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//拡大縮小、向き、位置マトリックス
	LPDIRECT3DTEXTURE9			pTextureProp ;			//テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffProp ;			//頂点バッファへのポインタ
} PROP;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitProp( void );
void UninitProp( void );
void UpdateProp( void );
void DrawProp( void );

PROP *GetProp( void );

#endif