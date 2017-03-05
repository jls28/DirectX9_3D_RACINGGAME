/*******************************************************************************
* タイトル： モデルbody描画関数
* ファイル名： modelhandL.cpp
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
#include "modelhandL.h"
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
#include "modelarmL.h"
#include "fade.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MODELHANDL_INERTIA_MOVE	( 0.025f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELHANDL g_aModelHandL[ MAX_MODELHANDL ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelHandL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelHandL( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelhandL.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL,		// マテリアル情報
									   NULL,
									   &g_aModelHandL[ nCntModelHandL ].nNumMatModelHandL,			// マテリアル数
									   &g_aModelHandL[ nCntModelHandL ].pMeshModelHandL ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelHandL[ nCntModelHandL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelHandL[ nCntModelHandL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelHandL[ nCntModelHandL ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelHandL[ nCntModelHandL ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandL[ nCntModelHandL ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandL[ nCntModelHandL ].fPosMove = POSMOVE_MODELHANDL;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelHandL[ nCntModelHandL ].Min.x )		g_aModelHandL[ nCntModelHandL ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelHandL[ nCntModelHandL ].Max.x )		g_aModelHandL[ nCntModelHandL ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelHandL[ nCntModelHandL ].Min.y )		g_aModelHandL[ nCntModelHandL ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelHandL[ nCntModelHandL ].Max.y )		g_aModelHandL[ nCntModelHandL ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelHandL[ nCntModelHandL ].Min.z )		g_aModelHandL[ nCntModelHandL ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelHandL[ nCntModelHandL ].Max.z )		g_aModelHandL[ nCntModelHandL ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelHandL[ nCntModelHandL ].Size.x = ( fabs( g_aModelHandL[ nCntModelHandL ].Min.x ) + fabs( g_aModelHandL[ nCntModelHandL ].Max.x ) ) / 2;
		g_aModelHandL[ nCntModelHandL ].Size.y = ( fabs( g_aModelHandL[ nCntModelHandL ].Min.y ) + fabs( g_aModelHandL[ nCntModelHandL ].Max.y ) ) / 2;
		g_aModelHandL[ nCntModelHandL ].Size.z = ( fabs( g_aModelHandL[ nCntModelHandL ].Min.z ) + fabs( g_aModelHandL[ nCntModelHandL ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelHandL[ nCntModelHandL ].Size.x < g_aModelHandL[ nCntModelHandL ].Size.z )
		{
			g_aModelHandL[ nCntModelHandL ].Collisoin = g_aModelHandL[ nCntModelHandL ].Size.z;
		}
		else
		{
			g_aModelHandL[ nCntModelHandL ].Collisoin = g_aModelHandL[ nCntModelHandL ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelHandL[ nCntModelHandL ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelHandL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelHandL( void )
{
	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++ )
	{
		// メッシュ情報の開放
		if( g_aModelHandL[ nCntModelHandL ].pMeshModelHandL != NULL )
		{
			g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->Release();
			g_aModelHandL[ nCntModelHandL ].pMeshModelHandL = NULL;
		}

		// バッファの開放
		if( g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL != NULL )
		{
			g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL->Release();
			g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelHandL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelHandL( void )
{
//	srand((unsigned)time(NULL));

	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelHandL_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelHandL_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelHandL_03 = GetPropModel_03 ();

	MODELARML *pModelArmL = GetModelarmL();

	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++)
	{
		if(pModelBody->bKeyUse == true)
		{
		g_aModelHandL[ nCntModelHandL ].pos = D3DXVECTOR3(  pModelBody->pos.x, pModelArmL->pos.y,  pModelBody->pos.z );
		g_aModelHandL[ nCntModelHandL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelHandL[ nCntModelHandL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelHandL[ nCntModelHandL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelHandL[ nCntModelHandL ].OldPos.x - g_aModelHandL[ nCntModelHandL ].Collisoin ) )
		{	// 左の壁
			g_aModelHandL[ nCntModelHandL ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelHandL[ nCntModelHandL ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelHandL[ nCntModelHandL ].OldPos.x + g_aModelHandL[ nCntModelHandL ].Collisoin ) )
		{	// 右の壁
			g_aModelHandL[ nCntModelHandL ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelHandL[ nCntModelHandL ].Collisoin;
		}
		if(( g_aModelHandL[ nCntModelHandL ].OldPos.z - g_aModelHandL[ nCntModelHandL ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelHandL[ nCntModelHandL ].OldPos.z = 20550.0f + g_aModelHandL[ nCntModelHandL ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}

	}

}

//================================================================================================================================================================================================
// DrawModelHandL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelHandL( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelHandL[ nCntModelHandL ].scl.x, g_aModelHandL[ nCntModelHandL ].scl.y, g_aModelHandL[ nCntModelHandL ].scl.z );
		D3DXMatrixMultiply( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelHandL[ nCntModelHandL ].rot.y, g_aModelHandL[ nCntModelHandL ].rot.x, g_aModelHandL[ nCntModelHandL ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelHandL[ nCntModelHandL ].pos.x, g_aModelHandL[ nCntModelHandL ].pos.y, g_aModelHandL[ nCntModelHandL ].pos.z );
		D3DXMatrixMultiply( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelHandL[ nCntModelHandL ].nNumMatModelHandL; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelHandL関数
// 引数 void
// 戻り値 
// 説明 ModelHandLを取得する。
//================================================================================================================================================================================================
MODELHANDL *GetModelHandL( void )
{
	return &g_aModelHandL[ 0 ];
}
