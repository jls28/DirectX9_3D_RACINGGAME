/*******************************************************************************
* タイトル： モデルbody描画関数
* ファイル名： modelarmR.cpp
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
#include "modelarmR.h"
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
#define MODELARMR_INERTIA_MOVE	( 0.025f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELARMR g_aModelarmR[ MAX_MODELARMR ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelarmR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelarmR( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelarmR.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR,		// マテリアル情報
									   NULL,
									   &g_aModelarmR[ nCntModelarmR ].nNumMatModelarmR,			// マテリアル数
									   &g_aModelarmR[ nCntModelarmR ].pMeshModelarmR ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelarmR[ nCntModelarmR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelarmR[ nCntModelarmR ].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmR[ nCntModelarmR ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelarmR[ nCntModelarmR ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmR[ nCntModelarmR ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmR[ nCntModelarmR ].fPosMove = POSMOVE_MODELARMR;
		g_aModelarmR[ nCntModelarmR ].fAngle = 0.0f;
		g_aModelarmR[ nCntModelarmR ].propR = 1.0f;		//半径
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelarmR[ nCntModelarmR ].Min.x )		g_aModelarmR[ nCntModelarmR ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelarmR[ nCntModelarmR ].Max.x )		g_aModelarmR[ nCntModelarmR ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelarmR[ nCntModelarmR ].Min.y )		g_aModelarmR[ nCntModelarmR ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelarmR[ nCntModelarmR ].Max.y )		g_aModelarmR[ nCntModelarmR ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelarmR[ nCntModelarmR ].Min.z )		g_aModelarmR[ nCntModelarmR ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelarmR[ nCntModelarmR ].Max.z )		g_aModelarmR[ nCntModelarmR ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelarmR[ nCntModelarmR ].Size.x = ( fabs( g_aModelarmR[ nCntModelarmR ].Min.x ) + fabs( g_aModelarmR[ nCntModelarmR ].Max.x ) ) / 2;
		g_aModelarmR[ nCntModelarmR ].Size.y = ( fabs( g_aModelarmR[ nCntModelarmR ].Min.y ) + fabs( g_aModelarmR[ nCntModelarmR ].Max.y ) ) / 2;
		g_aModelarmR[ nCntModelarmR ].Size.z = ( fabs( g_aModelarmR[ nCntModelarmR ].Min.z ) + fabs( g_aModelarmR[ nCntModelarmR ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelarmR[ nCntModelarmR ].Size.x < g_aModelarmR[ nCntModelarmR ].Size.z )
		{
			g_aModelarmR[ nCntModelarmR ].Collisoin = g_aModelarmR[ nCntModelarmR ].Size.z;
		}
		else
		{
			g_aModelarmR[ nCntModelarmR ].Collisoin = g_aModelarmR[ nCntModelarmR ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelarmR[ nCntModelarmR ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelarmR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelarmR( void )
{
	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++ )
	{
		// メッシュ情報の開放
		if( g_aModelarmR[ nCntModelarmR ].pMeshModelarmR != NULL )
		{
			g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->Release();
			g_aModelarmR[ nCntModelarmR ].pMeshModelarmR = NULL;
		}

		// バッファの開放
		if( g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR != NULL )
		{
			g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR->Release();
			g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelarmR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelarmR( void )
{
	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelarmR_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelarmR_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelarmR_03 = GetPropModel_03 ();


	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelarmR[ nCntModelarmR ].pos.x = pModelBody->pos.x ;
			g_aModelarmR[ nCntModelarmR ].pos.z = pModelBody->pos.z ;
			g_aModelarmR[ nCntModelarmR ].pos.y = pModelBody->pos.y+ g_aModelarmR[ nCntModelarmR ].propR * sinf( g_aModelarmR[ nCntModelarmR ].fAngle );
			g_aModelarmR[ nCntModelarmR ].fAngle += 20.0f * D3DX_PI / 120.0f;					// 角の弧を増える

		g_aModelarmR[ nCntModelarmR ].pos = D3DXVECTOR3( g_aModelarmR[ nCntModelarmR ].pos.x, g_aModelarmR[ nCntModelarmR ].pos.y, g_aModelarmR[ nCntModelarmR ].pos.z );
		g_aModelarmR[ nCntModelarmR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelarmR[ nCntModelarmR ].pos = D3DXVECTOR3( pModelBody->pos.x,pModelBody->pos.y,pModelBody->pos.z );
		g_aModelarmR[ nCntModelarmR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelarmR[ nCntModelarmR ].OldPos.x - g_aModelarmR[ nCntModelarmR ].Collisoin ) )
		{	// 左の壁
			g_aModelarmR[ nCntModelarmR ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelarmR[ nCntModelarmR ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelarmR[ nCntModelarmR ].OldPos.x + g_aModelarmR[ nCntModelarmR ].Collisoin ) )
		{	// 右の壁
			g_aModelarmR[ nCntModelarmR ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelarmR[ nCntModelarmR ].Collisoin;
		}
		if(( g_aModelarmR[ nCntModelarmR ].OldPos.z - g_aModelarmR[ nCntModelarmR ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelarmR[ nCntModelarmR ].OldPos.z = 20550.0f + g_aModelarmR[ nCntModelarmR ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}

	}

}

//================================================================================================================================================================================================
// DrawModelarmR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelarmR( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelarmR[ nCntModelarmR ].scl.x, g_aModelarmR[ nCntModelarmR ].scl.y, g_aModelarmR[ nCntModelarmR ].scl.z );
		D3DXMatrixMultiply( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelarmR[ nCntModelarmR ].rot.y, g_aModelarmR[ nCntModelarmR ].rot.x, g_aModelarmR[ nCntModelarmR ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelarmR[ nCntModelarmR ].pos.x, g_aModelarmR[ nCntModelarmR ].pos.y, g_aModelarmR[ nCntModelarmR ].pos.z );
		D3DXMatrixMultiply( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelarmR[ nCntModelarmR ].nNumMatModelarmR; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelarmR関数
// 引数 void
// 戻り値 
// 説明 ModelarmRを取得する。
//================================================================================================================================================================================================
MODELARMR *GetModelarmR( void )
{
	return &g_aModelarmR[ 0 ];
}
