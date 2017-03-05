/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_OBSTACLE_H_
#define	_OBSTACLE_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_OBSTACLE_BOX ( 26 )                     // 障害物1の数
#define MAX_OBSTACLE_CAR ( 3 )                     // 障害物2の数
#define MAX_OBSTACLE_CAT_01 ( 14 )                     // 障害物3の数
#define POSMOVE_OBSTACLE_BOX	( 5.0f )		// 障害物1移動量
#define POSMOVE_OBSTACLE_CAR	( 3.0f )		// 障害物2移動量
#define POSMOVE_OBSTACLE_CAT_01	( 0.5f )		// 障害物2移動量
#define FRONT_WALL		(  100.0f )		// 奥の壁
#define BACK_WALL		( -100.0f )		// 手前の壁
#define LEFT_WALL		( -100.0f )		// 左の壁
#define RIGHT_WALL		(  100.0f )		// 右の壁
#define CEILING			(  500.0f )		// 天井
#define GROUND			(    1.0f )		// 地面

//*************************************
// 障害物の種類
//*************************************
typedef enum
{
	OBSTACLE_NORMAL = 0,		// 障害物なし
	OBSTACLE_BOX,	// 障害物1
	OBSTACLE_CAR,	// 障害物2
	OBSTACLE_CAT_01,	// 障害物3
	OBSTACLE_MAX
} OBSTACLETYPE;
/*******************************************************************************
* 構造体宣言
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTextureObstacle;       // テクスチャへのポインタ
	LPD3DXBUFFER pBuffMatObstacle;             // 頂点バッファへのポインタ
	LPD3DXMESH pMeshObstacle;                  // メッシュの情報
	DWORD nNumMatObstacle;                     // マテリアル数
	D3DXMATRIX mtxWorldObstacle;               // ワールドマトリックス

	bool bUse;              // 使用しているかどうか
	bool bMove;
	bool bRot;
	bool bCatRotCheck;
	D3DXVECTOR3 pos;        // 位置
	D3DXVECTOR3 rot;        // 現在の向き
	D3DXVECTOR3 OldRot;     // 目的の向き
	D3DXVECTOR3 OldPos;     // 目的の位置
	D3DXVECTOR3 scl;        // スケール値
	D3DXVECTOR3 Max;        // 頂点座標の最大値
	D3DXVECTOR3 Min;        // 頂点座標の最小値
	D3DXVECTOR3 Size;       // MaxとMinの絶対値を足して２で割ったもの。また衝突判定で使うモデルの半径。x:幅 y:高さ z:奥行き。
	float Collisoin;        // 衝突判定で使う長さ。sizeのxとzで、大きかった方を衝突判定に使う。
	OBSTACLETYPE Type;
	float			fPosMove;	//移動量
	bool bAutoRot;
	float time;
	int nLife;
} OBSTACLE;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitObstacle( void );
void UninitObstacle( void );
void UpdateObstacle( void );
void DrawObstacle( void );
void HitObstacle_Box(void);
OBSTACLE *GetObstacle_Box( void );
OBSTACLE *GetObstacle_Car( void );
OBSTACLE *GetObstacle_Cat_01( void );
#endif