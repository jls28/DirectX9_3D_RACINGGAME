#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//インクルードファイル

//マクロ定義
#define MESHFIELD_TEXTURE_FILE	"data\\TEXTURE\\field001.jpg"	//地面テクスチャファイル位置
#define MESHFIELD_WIDTH			( 200.0f )						//フィールドの幅
#define MESHFIELD_HEIGHT		( 200.0f )						//フィールドの高さ

typedef struct
{
	MESH mesh;
	LPDIRECT3DTEXTURE9			pTexture;		//テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuff;		//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9		pIdxBuff;		//インデックスバッファへのポインター
	MATRIX						mtx;			//マトリックス
	D3DXVECTOR3					pos;			//位置
	D3DXVECTOR3					rot;			//向き
	D3DXVECTOR3					scl;			//拡大縮小
	float						fFixedPos;		//ウォール用三軸固定座標係数
}MESHFIELD;

//プロトタイプの宣言
HRESULT		InitMeshField();
void		UninitMeshField();
void		UpdateMeshField();
void		DrawMeshField();
MESHFIELD	*GetMeshField();

#endif