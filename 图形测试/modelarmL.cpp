/*******************************************************************************
* タイトル： モデルbody描画関数
* ファイル名： modelarmL.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/08
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
//2016-2-8 09:40:06
/*******************************************************************************
		インクルードファイル
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "modelarmL.h"
#include "camera.h"
#include "meshWall.h"
#include "meshField.h"
#include "bullet.h"
#include "shadow.h"
#include "use.h"
#include "effect.h"
#include "prop.h"
#include "propshow.h"
#include "propmodel_Group.h"
#include "propmp.h"
#include "propmplife.h"
#include "propmpmax.h"
#include "modelbody.h"
#include "fade.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MODELARML_INERTIA_MOVE	( 0.025f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELARML g_aModelarmL[ MAX_MODELARML ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelarmL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelarmL( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelarmL.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL,		// マテリアル情報
									   NULL,
									   &g_aModelarmL[ nCntModelarmL ].nNumMatModelarmL,			// マテリアル数
									   &g_aModelarmL[ nCntModelarmL ].pMeshModelarmL ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelarmL[ nCntModelarmL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelarmL[ nCntModelarmL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelarmL[ nCntModelarmL ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelarmL[ nCntModelarmL ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmL[ nCntModelarmL ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmL[ nCntModelarmL ].fPosMove = POSMOVE_MODELARML;
		g_aModelarmL[ nCntModelarmL ].fAngle = 0.0f;
		g_aModelarmL[ nCntModelarmL ].propR = 1.0f;		//半径
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelarmL[ nCntModelarmL ].Min.x )		g_aModelarmL[ nCntModelarmL ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelarmL[ nCntModelarmL ].Max.x )		g_aModelarmL[ nCntModelarmL ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelarmL[ nCntModelarmL ].Min.y )		g_aModelarmL[ nCntModelarmL ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelarmL[ nCntModelarmL ].Max.y )		g_aModelarmL[ nCntModelarmL ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelarmL[ nCntModelarmL ].Min.z )		g_aModelarmL[ nCntModelarmL ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelarmL[ nCntModelarmL ].Max.z )		g_aModelarmL[ nCntModelarmL ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelarmL[ nCntModelarmL ].Size.x = ( fabs( g_aModelarmL[ nCntModelarmL ].Min.x ) + fabs( g_aModelarmL[ nCntModelarmL ].Max.x ) ) / 2;
		g_aModelarmL[ nCntModelarmL ].Size.y = ( fabs( g_aModelarmL[ nCntModelarmL ].Min.y ) + fabs( g_aModelarmL[ nCntModelarmL ].Max.y ) ) / 2;
		g_aModelarmL[ nCntModelarmL ].Size.z = ( fabs( g_aModelarmL[ nCntModelarmL ].Min.z ) + fabs( g_aModelarmL[ nCntModelarmL ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelarmL[ nCntModelarmL ].Size.x < g_aModelarmL[ nCntModelarmL ].Size.z )
		{
			g_aModelarmL[ nCntModelarmL ].Collisoin = g_aModelarmL[ nCntModelarmL ].Size.z;
		}
		else
		{
			g_aModelarmL[ nCntModelarmL ].Collisoin = g_aModelarmL[ nCntModelarmL ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelarmL[ nCntModelarmL ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelarmL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelarmL( void )
{
	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++ )
	{
		// メッシュ情報の開放
		if( g_aModelarmL[ nCntModelarmL ].pMeshModelarmL != NULL )
		{
			g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->Release();
			g_aModelarmL[ nCntModelarmL ].pMeshModelarmL = NULL;
		}

		// バッファの開放
		if( g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL != NULL )
		{
			g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL->Release();
			g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelarmL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelarmL( void )
{

	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelarmL_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelarmL_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelarmL_03 = GetPropModel_03 ();


	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelarmL[ nCntModelarmL ].pos.x = pModelBody->pos.x ;
			g_aModelarmL[ nCntModelarmL ].pos.z = pModelBody->pos.z ;
			g_aModelarmL[ nCntModelarmL ].pos.y = pModelBody->pos.y+ g_aModelarmL[ nCntModelarmL ].propR * sinf( g_aModelarmL[ nCntModelarmL ].fAngle );
			g_aModelarmL[ nCntModelarmL ].fAngle += 20.0f * D3DX_PI / 120.0f;					// 角の弧を増える

		g_aModelarmL[ nCntModelarmL ].pos = D3DXVECTOR3( g_aModelarmL[ nCntModelarmL ].pos.x, g_aModelarmL[ nCntModelarmL ].pos.y, g_aModelarmL[ nCntModelarmL ].pos.z );
		g_aModelarmL[ nCntModelarmL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelarmL[ nCntModelarmL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y,  pModelBody->pos.z );
		g_aModelarmL[ nCntModelarmL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelarmL[ nCntModelarmL ].OldPos.x - g_aModelarmL[ nCntModelarmL ].Collisoin ) )
		{	// 左の壁
			g_aModelarmL[ nCntModelarmL ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelarmL[ nCntModelarmL ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelarmL[ nCntModelarmL ].OldPos.x + g_aModelarmL[ nCntModelarmL ].Collisoin ) )
		{	// 右の壁
			g_aModelarmL[ nCntModelarmL ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelarmL[ nCntModelarmL ].Collisoin;
		}
		if(( g_aModelarmL[ nCntModelarmL ].OldPos.z - g_aModelarmL[ nCntModelarmL ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelarmL[ nCntModelarmL ].OldPos.z = 20550.0f + g_aModelarmL[ nCntModelarmL ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}
	}

}

//================================================================================================================================================================================================
// DrawModelarmL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelarmL( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelarmL[ nCntModelarmL ].scl.x, g_aModelarmL[ nCntModelarmL ].scl.y, g_aModelarmL[ nCntModelarmL ].scl.z );
		D3DXMatrixMultiply( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelarmL[ nCntModelarmL ].rot.y, g_aModelarmL[ nCntModelarmL ].rot.x, g_aModelarmL[ nCntModelarmL ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelarmL[ nCntModelarmL ].pos.x, g_aModelarmL[ nCntModelarmL ].pos.y, g_aModelarmL[ nCntModelarmL ].pos.z );
		D3DXMatrixMultiply( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelarmL[ nCntModelarmL ].nNumMatModelarmL; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelarmL関数
// 引数 void
// 戻り値 
// 説明 ModelarmLを取得する。
//================================================================================================================================================================================================
MODELARML *GetModelarmL( void )
{
	return &g_aModelarmL[ 0 ];
}
/*******************************************************************************
* 関数名: 八方向移動関数
* 
* 引数  : D3DXVECTOR3	*pos		//位置
		  D3DXVECTOR3	*rot		//向き
		  float			fPosmove	//移動量
		  int			UP			//上ボタン
		  int			DOWN		//下ボタン
		  int			LEFT		//左ボタン
		  int			RIGHT		//右ボタン
* 戻り値: ナシ
* 説明: ナシ
*******************************************************************************/
void ModelarmLMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELARML *pModelarmL = GetModelarmL();
	pModelarmL -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
		}
		else											//前移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
		}
		else											//後移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + 0.0f;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//左上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//左下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else											//左移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//右上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//右下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
		}
		else											//右移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}

	//座標を更新（慣性）
	pModelarmL -> pos.x += ( pModelarmL->OldPos.x - pModelarmL -> pos.x ) * MODELARML_INERTIA_MOVE;
	pModelarmL -> pos.z += ( pModelarmL->OldPos.z - pModelarmL -> pos.z ) * MODELARML_INERTIA_MOVE;
}

/*******************************************************************************
* 関数名: ジョイスティック八方向移動関数
* 
* 引数  : D3DXVECTOR3	*pos		//位置
		  D3DXVECTOR3	*rot		//向き
		  float			fPosmove	//移動量
		  int			UP			//上ボタン
		  int			DOWN		//下ボタン
		  int			LEFT		//左ボタン
		  int			RIGHT		//右ボタン
* 戻り値: ナシ
* 説明: ナシ
*******************************************************************************/
void ModelarmLMovejoystick( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELARML *pModelarmL = GetModelarmL();
	pModelarmL -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetJoysticksTrigger( UP_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//左上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//右上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else											//前移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
			pModelarmL->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( DOWN_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//左下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//右下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else											//後移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + 0.0f;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
		pModelarmL->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( LEFT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//左上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//左下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else											//左移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
		pModelarmL->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( RIGHT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//右上移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//右下移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else											//右移動
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
			pModelarmL->bAutoRot = true;
	}
	else 
	{
			pModelarmL->bAutoRot = false;
	}

	//座標を更新（慣性）
	pModelarmL -> pos.x += ( pModelarmL->OldPos.x - pModelarmL -> pos.x ) * MODELARML_INERTIA_MOVE;
	pModelarmL -> pos.z += ( pModelarmL->OldPos.z - pModelarmL -> pos.z ) * MODELARML_INERTIA_MOVE;
}
