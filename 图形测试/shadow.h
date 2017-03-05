/*******************************************************************************
* タイトル： 影描画関数
* ファイル名： shadow.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/17
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _SHADOW_H_
#define _SHADOW_H_

//インクルードファイル

//マクロ定義

//シャドー構造体
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9	pVtxBuff;					//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		pTexture;					//テクスチャポリゴンへのポインタ
	D3DXMATRIX				mtxWorld;					//ワールドマトリックス
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//拡大縮小、向き、位置マトリックス
	D3DXVECTOR3				pos;						//位置
	D3DXVECTOR3				rot;						//向き
	D3DXVECTOR3				scl;						//拡大縮小
	bool					bUse;						//弾を使用しているかどうか
}SHADOW;

//プロトタイプの宣言
HRESULT		InitShadow();
void		UninitShadow();
void		DrawShadow();
void		SetShadow( D3DXVECTOR3 pos, float fWIDTH, float fHEIGHT, int nCntShadow, bool bUse );
SHADOW		*GetShadow();

#endif