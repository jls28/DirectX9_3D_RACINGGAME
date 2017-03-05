/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_PROPEXPLOSION_H_
#define	_PROPEXPLOSION_H_

#include <xnamath.h>
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_PROPEXPLOSION ( 1 )                     // モデルの数


/*******************************************************************************
* 構造体宣言
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexture;       // テクスチャへのポインタ
	LPD3DXBUFFER pBuffMat;             // 頂点バッファへのポインタ
	LPD3DXMESH pMesh;                  // メッシュの情報
	DWORD nNumMat;                     // マテリアル数
	D3DXMATRIX mtxWorld;               // ワールドマトリックス

	bool bUse;              // 使用しているかどうか

	D3DXVECTOR3 pos;        // 位置
	D3DXVECTOR3 rot;        // 現在の向き
	D3DXVECTOR3 OldRot;     // 目的の向き
	D3DXVECTOR3 OldPos;     // 目的の位置
	D3DXVECTOR3 scl;        // スケール値
	D3DXVECTOR3 Max;        // 頂点座標の最大値
	D3DXVECTOR3 Min;        // 頂点座標の最小値
	D3DXVECTOR3 Size;       // MaxとMinの絶対値を足して２で割ったもの。また衝突判定で使うモデルの半径。x:幅 y:高さ z:奥行き。
	float Collisoin;        // 衝突判定で使う長さ。sizeのxとzで、大きかった方を衝突判定に使う。
	float			fPosMove;	//移動量
	bool bAutoRot;
	float time;
} PROPEXPLOSION;
// 頂点構造体
struct CUSTOMVERTEX {
    XMFLOAT4	v4Pos;
	XMFLOAT2	v2UV;
};
// 爆発構造体
struct Explosion {
	int			bActive;						// 有効フラグ
	int			nTime;							// 発生してからの時間
	XMFLOAT3	v3CenterPos;					// 中心位置
	float		fRadius;						// 半径
	float		fAngle;							// 角度
	XMMATRIX	matMatrix;						// 変換行列
	float		fBright;						// 明るさ
};
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitPropExplosion( void );
void UninitPropExplosion( void );
void UpdatePropExplosion( void );
void DrawPropExplosion( void );

PROPEXPLOSION *GetPropExplosion( void );
int MakeSphereIndexed( CUSTOMVERTEX *pVertices, int *pVertexNum,
					   WORD *pIndices, int *pIndexNum );		// 球の作成(インデックス付き)
int MoveExplosion( void );
#endif