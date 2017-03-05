/*******************************************************************************
* タイトル： 弾描画関数
* ファイル名： bullet.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/20
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _BULLET_H_
#define _BULLET_H_
//*------------------------------------------------------------------------------
//|	マクロ定義
//------------------------------------------------------------------------------*/
#define MAX_BULLET	(256) //弾の数量
#define BULLET_WIDTH ( 5.0f ) //弾の幅
#define BULLET_HEIGHT ( 7.0f ) //弾の高さ
#define LIFE_BULLET (100)

//*************************************
// 弾の種類
//*************************************
enum
{
	BULLETTYPE_PLAYER = 0,		// プレイヤーの弾
	BULLETTYPE_PLAYER_HOMING,	// プレイヤーのホーミング弾
	BULLETTYPE_ENEMY,			// 敵の弾
	BULLETTYPE_MAX
};

//弾の構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;		//スケール値
	LPDIRECT3DTEXTURE9			pTextureBullet ;			//テクスチャポリゴンへのポインタ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffBullet ;			//頂点バッファへのポインタ
	float collisoin;
	int nLife;
	float fRot;		
	float fWidth;		//幅
	float fHeight;		//高さ
	float flength;
	int nType;				// 種類
	bool bUse;		//使っているかどうか
	D3DXMATRIX mtxWorldBullet;
} BULLET;
//プロトタイプ宣言
HRESULT InitBullet (void);
void UninitBullet (void);
void UpdateBullet (void);
void DrawBullet (void);
void SetBullet( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
BULLET *GetBullet(void);
#endif	