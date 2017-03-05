/*******************************************************************************
		インクルードの重複読み込み防止

*******************************************************************************/
#ifndef	_PROPMODEL_GROUP_H_
#define	_PROPMODEL_GROUP_H_

/*******************************************************************************
* マクロ定義
*******************************************************************************/

#define POSMOVE_PROPMODEL_01	(    10.0f )		// 移動量

#define POSMOVE_PROPMODEL_02	(    10.0f )		// 移動量

#define POSMOVE_PROPMODEL_03	(    10.0f )		// 移動量


#define POSMOVE_PROPMODEL_SPEED	(    40.0f)		//+のspeed


//*************************************
// ツールの種類
//*************************************
typedef enum
{
	PROWT_0 = -1,		// ツールなし
	PROWT_1,	// ツール1
	PROWT_2,	// ツール2
	PROWT_3,	// ツール3
	PROWT_MAX
} PROWTYPE;

//*************************************
// ツールの状態(回転/弾)
//*************************************
typedef enum
{
	PROWT_TYPE = -1,		// ツールなし
	PROWT_SPIN,	// ツール回転
	PROWT_BULLET,	// ツール弾
	PROWT_STATEMAX
} PROWSTATE;

/*******************************************************************************
* 構造体宣言
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexturePropModel;       // テクスチャへのポインタ
	LPD3DXBUFFER pBuffMatPropModel;             // 頂点バッファへのポインタ
	LPD3DXMESH pMeshPropModel;                  // メッシュの情報
	DWORD nNumMatPropModel;                     // マテリアル数
	D3DXMATRIX mtxWorldPropModel;               // ワールドマトリックス

	bool bUse;              // 使用しているかどうか
	bool bRotUse;			//	回転使用しているかどうか
	bool bUseCheck;
	int nLife;
	D3DXVECTOR3 pos;        // 位置
	D3DXVECTOR3 v3Vel;	// 速度
	D3DXVECTOR3 rot;        // 現在の向き
	D3DXVECTOR3 OldRot;     // 目的の向き
	D3DXVECTOR3 OldPos;     // 目的の位置
	D3DXVECTOR3 scl;        // スケール値
	D3DXVECTOR3 Max;        // 頂点座標の最大値
	D3DXVECTOR3 Min;        // 頂点座標の最小値
	D3DXVECTOR3 Size;       // MaxとMinの絶対値を足して２で割ったもの。また衝突判定で使うモデルの半径。x:幅 y:高さ z:奥行き。
	float Collisoin;        // 衝突判定で使う長さ。sizeのxとzで、大きかった方を衝突判定に使う。
	float			fPosMove;	//移動量
	float			fAngle;							// 角度
	float			propR;//半径
	float			time;
	int cnt;
	PROWTYPE Type;
	PROWSTATE state;

	bool				bActive;							// 有効フラグ


} PROPMODELGROUP;
/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
HRESULT InitPropModel_Group( void );
void UninitPropModel_Group( void );
void UpdatePropModel_Group( void );
void DrawPropModel_Group( void );

PROPMODELGROUP *GetPropModel_01( void );
PROPMODELGROUP *GetPropModel_02( void );
PROPMODELGROUP *GetPropModel_03( void );
void SetPropModel_01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
void SetPropModel_02( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
void SetPropModel_03( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
void HitPropModel_01(void);
void HitPropModel_02(void);
int MoveShellModel01( void );
int MoveShellModel02( void );
#endif