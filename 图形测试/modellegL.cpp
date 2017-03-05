/*******************************************************************************
* タイトル： モデルbody描画関数
* ファイル名： modellegL.cpp
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
#include "modelLegL.h"
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
#define MODELLEGL_INERTIA_MOVE	( 0.025f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELLEGL g_aModelLegL[ MAX_MODELLEGL ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelLegL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelLegL( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modellegL.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL,		// マテリアル情報
									   NULL,
									   &g_aModelLegL[ nCntModelLegL ].nNumMatModelLegL,			// マテリアル数
									   &g_aModelLegL[ nCntModelLegL ].pMeshModelLegL ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelLegL[ nCntModelLegL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegL[ nCntModelLegL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelLegL[ nCntModelLegL ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelLegL[ nCntModelLegL ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegL[ nCntModelLegL ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegL[ nCntModelLegL ].fPosMove = POSMOVE_MODELLEGL;
		g_aModelLegL[ nCntModelLegL ].fAngle = 0.0f;
		g_aModelLegL[ nCntModelLegL ].propR = 1.0f;		//半径
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelLegL[ nCntModelLegL ].Min.x )		g_aModelLegL[ nCntModelLegL ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelLegL[ nCntModelLegL ].Max.x )		g_aModelLegL[ nCntModelLegL ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelLegL[ nCntModelLegL ].Min.y )		g_aModelLegL[ nCntModelLegL ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelLegL[ nCntModelLegL ].Max.y )		g_aModelLegL[ nCntModelLegL ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelLegL[ nCntModelLegL ].Min.z )		g_aModelLegL[ nCntModelLegL ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelLegL[ nCntModelLegL ].Max.z )		g_aModelLegL[ nCntModelLegL ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelLegL[ nCntModelLegL ].Size.x = ( fabs( g_aModelLegL[ nCntModelLegL ].Min.x ) + fabs( g_aModelLegL[ nCntModelLegL ].Max.x ) ) / 2;
		g_aModelLegL[ nCntModelLegL ].Size.y = ( fabs( g_aModelLegL[ nCntModelLegL ].Min.y ) + fabs( g_aModelLegL[ nCntModelLegL ].Max.y ) ) / 2;
		g_aModelLegL[ nCntModelLegL ].Size.z = ( fabs( g_aModelLegL[ nCntModelLegL ].Min.z ) + fabs( g_aModelLegL[ nCntModelLegL ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelLegL[ nCntModelLegL ].Size.x < g_aModelLegL[ nCntModelLegL ].Size.z )
		{
			g_aModelLegL[ nCntModelLegL ].Collisoin = g_aModelLegL[ nCntModelLegL ].Size.z;
		}
		else
		{
			g_aModelLegL[ nCntModelLegL ].Collisoin = g_aModelLegL[ nCntModelLegL ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelLegL[ nCntModelLegL ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelLegL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelLegL( void )
{
	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++ )
	{
		// メッシュ情報の開放
		if( g_aModelLegL[ nCntModelLegL ].pMeshModelLegL != NULL )
		{
			g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->Release();
			g_aModelLegL[ nCntModelLegL ].pMeshModelLegL = NULL;
		}

		// バッファの開放
		if( g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL != NULL )
		{
			g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL->Release();
			g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelLegL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelLegL( void )
{

	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelLegL_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelLegL_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelLegL_03 = GetPropModel_03 ();

	MODELBODY *pModelBody = GetModelBody();

	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelLegL[ nCntModelLegL ].pos.x = pModelBody->pos.x ;
			g_aModelLegL[ nCntModelLegL ].pos.z = pModelBody->pos.z ;
			g_aModelLegL[ nCntModelLegL ].pos.y = pModelBody->pos.y+ g_aModelLegL[ nCntModelLegL ].propR * sinf( g_aModelLegL[ nCntModelLegL ].fAngle );
			g_aModelLegL[ nCntModelLegL ].fAngle += 20.0f * D3DX_PI / 120.0f;					// 角の弧を増える

		g_aModelLegL[ nCntModelLegL ].pos = D3DXVECTOR3( g_aModelLegL[ nCntModelLegL ].pos.x, g_aModelLegL[ nCntModelLegL ].pos.y, g_aModelLegL[ nCntModelLegL ].pos.z );
		g_aModelLegL[ nCntModelLegL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelLegL[ nCntModelLegL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegL[ nCntModelLegL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelLegL[ nCntModelLegL ].OldPos.x - g_aModelLegL[ nCntModelLegL ].Collisoin ) )
		{	// 左の壁
			g_aModelLegL[ nCntModelLegL ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelLegL[ nCntModelLegL ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelLegL[ nCntModelLegL ].OldPos.x + g_aModelLegL[ nCntModelLegL ].Collisoin ) )
		{	// 右の壁
			g_aModelLegL[ nCntModelLegL ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelLegL[ nCntModelLegL ].Collisoin;
		}
		if(( g_aModelLegL[ nCntModelLegL ].OldPos.z - g_aModelLegL[ nCntModelLegL ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelLegL[ nCntModelLegL ].OldPos.z = 20550.0f + g_aModelLegL[ nCntModelLegL ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}

	}

}

//================================================================================================================================================================================================
// DrawModelLegL関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelLegL( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelLegL[ nCntModelLegL ].scl.x, g_aModelLegL[ nCntModelLegL ].scl.y, g_aModelLegL[ nCntModelLegL ].scl.z );
		D3DXMatrixMultiply( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelLegL[ nCntModelLegL ].rot.y, g_aModelLegL[ nCntModelLegL ].rot.x, g_aModelLegL[ nCntModelLegL ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelLegL[ nCntModelLegL ].pos.x, g_aModelLegL[ nCntModelLegL ].pos.y, g_aModelLegL[ nCntModelLegL ].pos.z );
		D3DXMatrixMultiply( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelLegL[ nCntModelLegL ].nNumMatModelLegL; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelLegL関数
// 引数 void
// 戻り値 
// 説明 ModelLegLを取得する。
//================================================================================================================================================================================================
MODELLEGL *GetModelLegL( void )
{
	return &g_aModelLegL[ 0 ];
}
