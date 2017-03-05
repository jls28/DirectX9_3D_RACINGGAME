/*******************************************************************************
* タイトル： モデルbody描画関数
* ファイル名： modellegR.cpp
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
#include "modelLegR.h"
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
#define MODELLEGR_INERTIA_MOVE	( 0.025f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELLEGR g_aModelLegR[ MAX_MODELLEGR ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelLegR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelLegR( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modellegR.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR,		// マテリアル情報
									   NULL,
									   &g_aModelLegR[ nCntModelLegR ].nNumMatModelLegR,			// マテリアル数
									   &g_aModelLegR[ nCntModelLegR ].pMeshModelLegR ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelLegR[ nCntModelLegR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegR[ nCntModelLegR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelLegR[ nCntModelLegR ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelLegR[ nCntModelLegR ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegR[ nCntModelLegR ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegR[ nCntModelLegR ].fPosMove = POSMOVE_MODELLEGR;
		g_aModelLegR[ nCntModelLegR ].fAngle = 0.0f;
		g_aModelLegR[ nCntModelLegR ].propR = 1.0f;		//半径
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelLegR[ nCntModelLegR ].Min.x )		g_aModelLegR[ nCntModelLegR ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelLegR[ nCntModelLegR ].Max.x )		g_aModelLegR[ nCntModelLegR ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelLegR[ nCntModelLegR ].Min.y )		g_aModelLegR[ nCntModelLegR ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelLegR[ nCntModelLegR ].Max.y )		g_aModelLegR[ nCntModelLegR ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelLegR[ nCntModelLegR ].Min.z )		g_aModelLegR[ nCntModelLegR ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelLegR[ nCntModelLegR ].Max.z )		g_aModelLegR[ nCntModelLegR ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelLegR[ nCntModelLegR ].Size.x = ( fabs( g_aModelLegR[ nCntModelLegR ].Min.x ) + fabs( g_aModelLegR[ nCntModelLegR ].Max.x ) ) / 2;
		g_aModelLegR[ nCntModelLegR ].Size.y = ( fabs( g_aModelLegR[ nCntModelLegR ].Min.y ) + fabs( g_aModelLegR[ nCntModelLegR ].Max.y ) ) / 2;
		g_aModelLegR[ nCntModelLegR ].Size.z = ( fabs( g_aModelLegR[ nCntModelLegR ].Min.z ) + fabs( g_aModelLegR[ nCntModelLegR ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelLegR[ nCntModelLegR ].Size.x < g_aModelLegR[ nCntModelLegR ].Size.z )
		{
			g_aModelLegR[ nCntModelLegR ].Collisoin = g_aModelLegR[ nCntModelLegR ].Size.z;
		}
		else
		{
			g_aModelLegR[ nCntModelLegR ].Collisoin = g_aModelLegR[ nCntModelLegR ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelLegR[ nCntModelLegR ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelLegR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelLegR( void )
{
	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++ )
	{
		// メッシュ情報の開放
		if( g_aModelLegR[ nCntModelLegR ].pMeshModelLegR != NULL )
		{
			g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->Release();
			g_aModelLegR[ nCntModelLegR ].pMeshModelLegR = NULL;
		}

		// バッファの開放
		if( g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR != NULL )
		{
			g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR->Release();
			g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelLegR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelLegR( void )
{


	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelLegR_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelLegR_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelLegR_03 = GetPropModel_03 ();

	MODELBODY *pModelBody = GetModelBody();

	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelLegR[ nCntModelLegR ].pos.x = pModelBody->pos.x ;
			g_aModelLegR[ nCntModelLegR ].pos.z = pModelBody->pos.z ;
			g_aModelLegR[ nCntModelLegR ].pos.y = pModelBody->pos.y+ g_aModelLegR[ nCntModelLegR ].propR * sinf( g_aModelLegR[ nCntModelLegR ].fAngle );
			g_aModelLegR[ nCntModelLegR ].fAngle += 20.0f * D3DX_PI / 120.0f;					// 角の弧を増える

		g_aModelLegR[ nCntModelLegR ].pos = D3DXVECTOR3( g_aModelLegR[ nCntModelLegR ].pos.x, g_aModelLegR[ nCntModelLegR ].pos.y, g_aModelLegR[ nCntModelLegR ].pos.z );
		g_aModelLegR[ nCntModelLegR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelLegR[ nCntModelLegR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegR[ nCntModelLegR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelLegR[ nCntModelLegR ].OldPos.x - g_aModelLegR[ nCntModelLegR ].Collisoin ) )
		{	// 左の壁
			g_aModelLegR[ nCntModelLegR ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelLegR[ nCntModelLegR ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelLegR[ nCntModelLegR ].pos.x + g_aModelLegR[ nCntModelLegR ].Collisoin ) )
		{	// 右の壁
			g_aModelLegR[ nCntModelLegR ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelLegR[ nCntModelLegR ].Collisoin;
		}
		if(( g_aModelLegR[ nCntModelLegR ].OldPos.z - g_aModelLegR[ nCntModelLegR ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelLegR[ nCntModelLegR ].OldPos.z = 20550.0f + g_aModelLegR[ nCntModelLegR ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}
	}

}

//================================================================================================================================================================================================
// DrawModelLegR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelLegR( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelLegR[ nCntModelLegR ].scl.x, g_aModelLegR[ nCntModelLegR ].scl.y, g_aModelLegR[ nCntModelLegR ].scl.z );
		D3DXMatrixMultiply( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelLegR[ nCntModelLegR ].rot.y, g_aModelLegR[ nCntModelLegR ].rot.x, g_aModelLegR[ nCntModelLegR ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelLegR[ nCntModelLegR ].pos.x, g_aModelLegR[ nCntModelLegR ].pos.y, g_aModelLegR[ nCntModelLegR ].pos.z );
		D3DXMatrixMultiply( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelLegR[ nCntModelLegR ].nNumMatModelLegR; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelLegR関数
// 引数 void
// 戻り値 
// 説明 ModelLegRを取得する。
//================================================================================================================================================================================================
MODELLEGR *GetModelLegR( void )
{
	return &g_aModelLegR[ 0 ];
}
