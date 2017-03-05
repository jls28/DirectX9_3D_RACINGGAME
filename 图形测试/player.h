/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_PLAYER_H_
#define	_PLAYER_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MAX_PLAYER ( 1 )                     // プレイヤーの数
#define MAX_MODEL ( 6 )                     // モデルの数
#define MAX_PARTS ( 60 )                     // パーツの数
#define MAX_KEY ( 5 )                     // キーの数
#define MAX_MOTION ( 5 )                     // モーションの数
/*******************************************************************************
* キー構造体宣言
*******************************************************************************/
typedef struct
{
	float fPosX;			//x軸位置
	float fPosY;			//y軸位置
	float fPosZ;			//z軸位置

	float fRotX;			//x軸回転角
	float fRotY;			//y軸回転角
	float fRotZ;			//z軸回転角
} KEY;

/*******************************************************************************
* キー情報構造体宣言
*******************************************************************************/
typedef struct
{
	int nFrame;			//再生フレーム
	KEY aKey [ MAX_MODEL ];			//各モデルのキー要素
} KEY_INFO;

/*******************************************************************************
* モーション情報構造体宣言
*******************************************************************************/
typedef struct
{
	bool bLoop;		//ループするがどうか
	int nNumKey;		//キー数
	KEY_INFO akeyInfo [ MAX_KEY ];		//各キーのキー要素
} MOTION_INFO;
/*******************************************************************************
* モデル構造体宣言
*******************************************************************************/
typedef struct
{
	LPD3DXMESH pMesh;                  // メッシュの情報
	LPD3DXBUFFER pBuffMat;             // 頂点バッファへのポインタ
	DWORD nNumMat;                     // マテリアル数
	LPDIRECT3DTEXTURE9 pTexture;       // テクスチャへのポインタ
	D3DXMATRIX mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 pos;        // 位置
	D3DXVECTOR3 rot;        // 現在の向き
	D3DXVECTOR3 OldRot;     // 目的の向き
	D3DXVECTOR3 OldPos;     // 目的の位置
	D3DXVECTOR3 scl;        // スケール値
	D3DXVECTOR3 Max;        // 頂点座標の最大値
	D3DXVECTOR3 Min;        // 頂点座標の最小値
	D3DXVECTOR3 Size;       // 衝突判定で使うモデルの半径。
	float Collisoin;        // 衝突判定で使う長さ
	float fPosMove;        //移動量
	int nIndexModelDarent; //親モデルのインデックス
	bool bUse;              // 使用しているかどうか
} MODEL;

/*******************************************************************************
* プレイヤー構造体宣言
*******************************************************************************/
typedef struct
{
	D3DXMATRIX mtxWorld;               // ワールドマトリックス
	D3DXVECTOR3 pos;        // 位置
	D3DXVECTOR3 rot;        // 現在の向き
	D3DXVECTOR3 OldRot;     // 目的の向き
	D3DXVECTOR3 OldPos;     // 目的の位置
	D3DXVECTOR3 scl;        // スケール値
	D3DXVECTOR3 Max;        // 頂点座標の最大値
	D3DXVECTOR3 Min;        // 頂点座標の最小値
	D3DXVECTOR3 Size;       // 衝突判定で使うモデルの半径。
	float Collisoin;        // 衝突判定で使う長さ
	float fPosMove;        //移動量
	MODEL aModel[ MAX_MODEL ];
	MOTION_INFO aMotionInfo [ MAX_MOTION ];
	int nNumParts;         //パーツ数
	int aIndexParent [ MAX_PARTS ];//親インデックスデータ
	bool bUse;             // 使用しているかどうか
} PLAYER;


/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitPlayer( void );
void UninitPlayer( void );
void UpdatePlayer( void );
void DrawPlayer( void );
MODEL *GetModel( void );
PLAYER *GetPlayer( void );
#endif