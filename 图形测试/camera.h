/*******************************************************************************
* タイトル： カメラ関数
* ファイル名： camera.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/16
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/

#ifndef _CAMERA_H_
#define _CAMERA_H_
//マクロ定義
#define ANGLE_CAMERA (45.0f)		//ラジアン
#define ASPECT_CAMERA (SCREEN_WIDTH/SCREEN_HEIGHT)		//アスペクト比
#define NEAR_Z (10.0f)		//NearZ値
#define FAR_Z (10000000.0f)		//FarZ値


//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV;		//視点
	D3DXVECTOR3 posR;		//注視点
	D3DXVECTOR3 vecU;		//上方面ベクトル
	D3DXMATRIX mtxProjection;		//プロジェクションストリックス
	D3DXMATRIX mtxView;		//ビューマトリックス

	D3DXVECTOR3 rot;		//向き
	float fDistance;		//距離
	bool bRotate;	//trueなら視点を中心、falseなら注視点を中心
	D3DXVECTOR3 RotCheck;		//check向き
	float correction_x;
	float correction_z;
	int wait;
} CAMERA;
//プロトタイプ宣言
void InitCamera (void);
void UninitCamera (void);
void UpdateCamera (void);
void SetCamera (void);
void Autorotation (void);
CAMERA GetCamera(void);
#endif