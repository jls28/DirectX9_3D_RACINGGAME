/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_BUILDING_RIGHT_H_
#define	_BUILDING_RIGHT_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_BUILDING_RIGHT ( 20 )                     // 建物の数
#define POSMOVE_BUILDING_RIGHT	( 0.0f )		// 建物移動量
#define FRONT_WALL		(  100.0f )		// 奥の壁
#define BACK_WALL		( -100.0f )		// 手前の壁
#define LEFT_WALL		( -100.0f )		// 左の壁
#define RIGHT_WALL		(  100.0f )		// 右の壁
#define CEILING			(  500.0f )		// 天井
#define GROUND			(    1.0f )		// 地面


/*******************************************************************************
* 構造体宣言
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTextureBuilding_Right;       // テクスチャへのポインタ
	LPD3DXBUFFER pBuffMatBuilding_Right;             // 頂点バッファへのポインタ
	LPD3DXMESH pMeshBuilding_Right;                  // メッシュの情報
	DWORD nNumMatBuilding_Right;                     // マテリアル数
	D3DXMATRIX mtxWorldBuilding_Right;               // ワールドマトリックス

	bool bUse;              // 使用しているかどうか

	D3DXVECTOR3 pos;        // 位置
	D3DXVECTOR3 rot;        // 現在の向き
	D3DXVECTOR3 scl;        // スケール値
	D3DXVECTOR3 Max;        // 頂点座標の最大値
	D3DXVECTOR3 Min;        // 頂点座標の最小値
	D3DXVECTOR3 Size;       // MaxとMinの絶対値を足して２で割ったもの。また衝突判定で使うモデルの半径。x:幅 y:高さ z:奥行き。
	float Collisoin;        // 衝突判定で使う長さ。sizeのxとzで、大きかった方を衝突判定に使う。
	float			fPosMove;	//移動量
} BUILDING_RIGHT;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitBuilding_Right( void );
void UninitBuilding_Right( void );
void UpdateBuilding_Right( void );
void DrawBuilding_Right( void );

BUILDING_RIGHT *GetBuilding_Right( void );
#endif