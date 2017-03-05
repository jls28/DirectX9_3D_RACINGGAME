#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//インクルードファイル

//マクロ定義
#define TRACK_WIDTH_LEFT		( -100.0f )
#define TRACK_WIDTH_RIGHT		( 100.0f )
//壁の向き
typedef enum
{
	WALL_FRONT = 0,				// 奥の壁
	WALL_BACK,					// 前の壁
	WALL_LEFT,					// 左の壁
	WALL_RIGHT,					// 右の壁
	WALL_MAX
}WALLSTATE;

//ウォールの構造体
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
}MESHWALL;

//プロトタイプの宣言
HRESULT		InitMeshWall();
void		UninitMeshWall();
void		UpdateMeshWall();
void		DrawMeshWall();
MESHWALL	*GetMeshWall();

#endif