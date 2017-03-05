/*******************************************************************************
* タイトル： カメラ関数
* ファイル名： camera.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/16
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/

//************************************************************************************************************************************************************************************************
// インクルードファイル
//************************************************************************************************************************************************************************************************
#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "camera.h"

#include "use.h"
#include "time.h"
#include "modelbody.h"
//************************************************************************************************************************************************************************************************
// マクロ定義
//************************************************************************************************************************************************************************************************
#define POSMOVE_CAMERA	(    2.00f )	// カメラ座標の移動量
#define ROTMOVE_CAMERA	(    0.01f )	// カメラ回転の移動量
#define ZOOM			(   10.00f )	// ズーム。視点(posV)と注視点(posR)の距離が一番短い。
#define WIDE			( 1000.00f )	// ワイド。視点(posV)と注視点(posR)の距離が一番遠い。
#define CORRECTION_X		(0.0f)
#define CORRECTION_Z		(100.0f)
#define TIME_CAMERA			(1)
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
CAMERA g_camera;	// カメラ情報

float Camera_Move;		//カメラの移動量
//================================================================================================================================================================================================
// InitCamera関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void InitCamera( void )
{
	// 視点（自分）
	g_camera.posV = D3DXVECTOR3( 0.0f, 80.0f, -200.0f );	// 0, 100~200, -100~-300

	// 注視点（見てる先）
	g_camera.posR = D3DXVECTOR3( 0.0f,   60.0f,    0.0f );

	// 上方向ベクトル（カメラ頭頂部）
	g_camera.vecU = D3DXVECTOR3( 0.0f,   1.0f,    0.0f );	// ほぼ変えない。

	// 向き（角度）
	g_camera.rot  = D3DXVECTOR3( 0.0f,   0.0f,    0.0f );

	Camera_Move = POSMOVE_CAMERA;		//カメラの移動量の初期化

	// posVとposRの対角線の長さ
	g_camera.fDistance = sqrtf( ( ( g_camera.posR.x - g_camera.posV.x ) * ( g_camera.posR.z - g_camera.posV.z ) ) 
							  + ( ( g_camera.posR.z - g_camera.posV.z ) * ( g_camera.posR.z - g_camera.posV.z ) ) );

	g_camera.bRotate = false;

	g_camera.correction_x = CORRECTION_X;

	g_camera.correction_z = CORRECTION_Z;

	g_camera.wait =TIME_CAMERA;
}

//================================================================================================================================================================================================
// UninitCamera関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitCamera( void )
{
}

//================================================================================================================================================================================================
// UpdateCamera関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateCamera( void )
{
	//float rot;
	// モデルのポインタを取得
	MODELBODY *pModelBody = GetModelBody();
	//モデルカメラの追従
	g_camera.posR.x = pModelBody -> pos.x;														//モデルの座標からposR(注視点)を求める。
	g_camera.posR.z = pModelBody -> pos.z;														//モデルの座標からposR(注視点)を求める。
	g_camera.posV.x = g_camera.posR.x - (sinf( g_camera.rot.y )) * g_camera.fDistance;		//posR(注視点)からposV(視点)を求める。
	g_camera.posV.z = g_camera.posR.z - (cosf( g_camera.rot.y )) * g_camera.fDistance;		//posR(注視点)からposV(視点)を求める。

	//if( GetKeyboardPress( DIK_F4) )			//カメラの回り込み使用する
	//{
	//	pModel->bAutoRot = false;
	//}
	//else if( GetKeyboardPress( DIK_F5) )			//カメラの回り込み使用しない
	//{
	//	pModel->bAutoRot = true;
	//}

	//if(pModel->bAutoRot == false)
	//{
	//	if(g_camera.wait>=0)
	//	{
	//		g_camera.wait--;
	//	}
	//}
	//else
	//{
	//	g_camera.wait =TIME_CAMERA;
	//}
	//if(g_camera.wait <= 0)
	//{
	//	g_camera.RotCheck.y = pModel->rot.y + D3DX_PI;
	//	//向き角度のチェック
	//	if( g_camera.RotCheck.y > D3DX_PI )
	//	{
	//		g_camera.RotCheck.y -= D3DX_PI * 2.0f;

	//	}
	//	if( g_camera.RotCheck.y < - D3DX_PI )
	//	{
	//		g_camera.RotCheck.y += D3DX_PI * 2.0f;
	//	}
	//	
	//	rot = g_camera.RotCheck.y -g_camera.rot.y;

	//	if( rot > D3DX_PI )
	//	{
	//		rot -= D3DX_PI * 2.0f;
	//	}
	//	if( rot < - D3DX_PI )
	//	{
	//		rot += D3DX_PI * 2.0f;
	//	}
	//	g_camera.rot.y += rot*0.08f;
	//	g_camera.bRotate = true;
	//}
/****************************************************************************************************************************************************************/
	//視点旋回
	if( GetKeyboardPress( DIK_Z ) )			//左旋回
	{
		g_camera.rot.y += D3DX_PI * 0.01f;
		g_camera.bRotate = true;			//旋回中心を注視点に設定
	}
	else if( GetKeyboardPress( DIK_C ) )	//右旋回
	{
		g_camera.rot.y -= D3DX_PI * 0.01f;
		g_camera.bRotate = true;			//旋回中心を注視点に設定
	}

	//注視点旋回
	if( GetKeyboardPress( DIK_Q ) )			//左旋回
	{
		g_camera.rot.y -= D3DX_PI * 0.01f;
	}
	else if( GetKeyboardPress( DIK_E ) )	//右旋回
	{
		g_camera.rot.y += D3DX_PI * 0.01f;
	}

	//視点操作
	if( GetKeyboardPress( DIK_Y ) )			//上移動
	{
		g_camera.posV.y += 2.5f;
	}
	else if( GetKeyboardPress( DIK_N ) )	//下移動
	{
		g_camera.posV.y -= 2.5f;
	}

	//注視点操作
	if( GetKeyboardPress( DIK_T ) )			//上移動
	{
		g_camera.posR.y += 2.5f;
	}
	else if( GetKeyboardPress( DIK_B ) )	//下移動
	{
		g_camera.posR.y -= 2.5f;
	}

	//視点と注視点の距離操作
	if( GetKeyboardPress( DIK_U ) )
	{
		g_camera.fDistance += 2.0f;
		g_camera.bRotate = true;
	}
	else if( GetKeyboardPress( DIK_M ) )
	{
		g_camera.fDistance -= 2.0f;
		g_camera.bRotate = true;
	}

	//視点と注視点の距離のチェック
	if( g_camera.fDistance > 300.0f )
	{
		g_camera.fDistance = 300.0f;
	}
	else if( g_camera.fDistance < 100.0f )
	{
		g_camera.fDistance = 100.0f;
	}
		//向き角度のチェック
	if( g_camera.rot.y > D3DX_PI )
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	if( g_camera.rot.y < - D3DX_PI )
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//視点中心
	if( g_camera.bRotate == true)
	{
		g_camera.posV.x = g_camera.posR.x - g_camera.fDistance * sinf( g_camera.rot.y );
		g_camera.posV.z = g_camera.posR.z - g_camera.fDistance * cosf( g_camera.rot.y );
		g_camera.bRotate = false;
	}

	//注視点中心
	else
	{
		g_camera.posR.x = g_camera.posV.x + g_camera.fDistance * sinf( g_camera.rot.y );
		g_camera.posR.z = g_camera.posV.z + g_camera.fDistance * cosf( g_camera.rot.y );
	}
		MESHWALL *pWall = GetMeshWall();
		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if( (pWall + WALL_FRONT)->pos.z < ( g_camera.posR.z + pModel->Collisoin ) )
	//	{	// 奥の壁
	//		g_camera.posR.z =( pWall + WALL_FRONT)->pos.z  - pModel->Collisoin;
	//		g_camera.posV.z =g_camera.posR.z-CORRECTION_Z;
	//	}
	//	else if( (pWall + WALL_BACK)->pos.z > ( g_camera.posR.z - pModel->Collisoin ) )
	//	{	// 前の壁
	//		g_camera.posR.z = (pWall + WALL_BACK)->pos.z + pModel->Collisoin;
	//		g_camera.posV.z =g_camera.posR.z-CORRECTION_Z;
	//	}	
	//	if( (pWall + WALL_LEFT)->pos.x > ( g_camera.posR.x - pModel->Collisoin ) )
	//	{	// 左の壁
	//		g_camera.posR.x =  (pWall + WALL_LEFT)->pos.x + pModel->Collisoin;
	//		g_camera.posV.x =g_camera.posR.x-CORRECTION_X;
	//	}
	//	else if(  (pWall + WALL_RIGHT)->pos.x < ( g_camera.posR.x + pModel->Collisoin ) )
	//	{	// 右の壁
	//		g_camera.posR.x =  (pWall + WALL_RIGHT)->pos.x - pModel->Collisoin;
	//		g_camera.posV.x =g_camera.posR.x-CORRECTION_X;
	//	}
	//	if( CEILING < ( g_camera.posR.y + pModel->Size.y ) )
	//	{	// 天井
	//		g_camera.posR.y = CEILING - pModel->Size.y;
	//	}
	//	else if( GROUND > ( g_camera.posR.y - pModel->Size.y ) )
	//	{	// 床
	//		g_camera.posR.y = GROUND + pModel->Size.y;
	//	}
}
//================================================================================================================================================================================================
// DrawCamera関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawCamera( void )
{

}

//================================================================================================================================================================================================
// SetCamera関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void SetCamera( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity( &g_camera.mtxView );

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH( &g_camera.mtxProjection,
							    ( D3DX_PI / 4 ),						// 視野角（カメラのレンズのように、広角or望遠）
							    ( SCREEN_WIDTH / SCREEN_HEIGHT ),		// アスペクト比(16:9)
							    NEAR_Z,									// NearZ値（カメラに映す範囲の、最前の距離）
							    FAR_Z );								// Far値  （カメラに映す範囲の、最奥の距離）

	// プロジェクションマトリックスの設定
	pDevice->SetTransform( D3DTS_PROJECTION, &g_camera.mtxProjection );

	// ビューマトリックスの初期化
	D3DXMatrixIdentity( &g_camera.mtxView );

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH( &g_camera.mtxView,
					    &g_camera.posV,
					    &g_camera.posR,
					    &g_camera.vecU );

	// ビューマトリックスの設定
	pDevice->SetTransform( D3DTS_VIEW, &g_camera.mtxView );
}

//================================================================================================================================================================================================
// GetCameraPosV関数
// 引数 void
// 戻り値 D3DXVECTOR3
// 説明 
//================================================================================================================================================================================================
D3DXVECTOR3 GetCameraPosV( void )
{
	return g_camera.posV;
}

//================================================================================================================================================================================================
// GetCameraPosR関数
// 引数 void
// 戻り値 D3DXVECTOR3
// 説明 
//================================================================================================================================================================================================
D3DXVECTOR3 GetCameraPosR( void )
{
	return g_camera.posR;
}

//================================================================================================================================================================================================
// GetCamera関数
// 引数 void
// 戻り値 D3DXVECTOR3
// 説明 
//================================================================================================================================================================================================
CAMERA GetCamera( void )
{
	return g_camera;
}
