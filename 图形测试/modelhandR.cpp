/*******************************************************************************
* タイトル： モデルbody描画関数
* ファイル名： modelbody.cpp
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
#include "modelhandR.h"
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
#include "modelarmR.h"
#include "fade.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MODELHANDR_INERTIA_MOVE	( 0.025f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELHANDR g_aModelHandR[ MAX_MODELHANDR ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelHandR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelHandR( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelhandR.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR,		// マテリアル情報
									   NULL,
									   &g_aModelHandR[ nCntModelHandR ].nNumMatModelHandR,			// マテリアル数
									   &g_aModelHandR[ nCntModelHandR ].pMeshModelHandR ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelHandR[ nCntModelHandR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelHandR[ nCntModelHandR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelHandR[ nCntModelHandR ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelHandR[ nCntModelHandR ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandR[ nCntModelHandR ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandR[ nCntModelHandR ].fPosMove = POSMOVE_MODELHANDR;

		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelHandR[ nCntModelHandR ].Min.x )		g_aModelHandR[ nCntModelHandR ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelHandR[ nCntModelHandR ].Max.x )		g_aModelHandR[ nCntModelHandR ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelHandR[ nCntModelHandR ].Min.y )		g_aModelHandR[ nCntModelHandR ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelHandR[ nCntModelHandR ].Max.y )		g_aModelHandR[ nCntModelHandR ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelHandR[ nCntModelHandR ].Min.z )		g_aModelHandR[ nCntModelHandR ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelHandR[ nCntModelHandR ].Max.z )		g_aModelHandR[ nCntModelHandR ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelHandR[ nCntModelHandR ].Size.x = ( fabs( g_aModelHandR[ nCntModelHandR ].Min.x ) + fabs( g_aModelHandR[ nCntModelHandR ].Max.x ) ) / 2;
		g_aModelHandR[ nCntModelHandR ].Size.y = ( fabs( g_aModelHandR[ nCntModelHandR ].Min.y ) + fabs( g_aModelHandR[ nCntModelHandR ].Max.y ) ) / 2;
		g_aModelHandR[ nCntModelHandR ].Size.z = ( fabs( g_aModelHandR[ nCntModelHandR ].Min.z ) + fabs( g_aModelHandR[ nCntModelHandR ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelHandR[ nCntModelHandR ].Size.x < g_aModelHandR[ nCntModelHandR ].Size.z )
		{
			g_aModelHandR[ nCntModelHandR ].Collisoin = g_aModelHandR[ nCntModelHandR ].Size.z;
		}
		else
		{
			g_aModelHandR[ nCntModelHandR ].Collisoin = g_aModelHandR[ nCntModelHandR ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelHandR[ nCntModelHandR ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelHandR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelHandR( void )
{
	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++ )
	{
		// メッシュ情報の開放
		if( g_aModelHandR[ nCntModelHandR ].pMeshModelHandR != NULL )
		{
			g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->Release();
			g_aModelHandR[ nCntModelHandR ].pMeshModelHandR = NULL;
		}

		// バッファの開放
		if( g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR != NULL )
		{
			g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR->Release();
			g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelHandR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelHandR( void )
{
	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelHandR_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelHandR_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelHandR_03 = GetPropModel_03 ();

	MODELARMR *pModelArmR = GetModelarmR();

	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++)
	{
		if(pModelBody->bKeyUse == true)
		{
		g_aModelHandR[ nCntModelHandR ].pos = D3DXVECTOR3(  pModelBody->pos.x, pModelArmR ->pos.y,  pModelBody->pos.z );
		g_aModelHandR[ nCntModelHandR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelHandR[ nCntModelHandR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody ->pos.y, pModelBody ->pos.z );
		g_aModelHandR[ nCntModelHandR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelHandR[ nCntModelHandR ].OldPos.x - g_aModelHandR[ nCntModelHandR ].Collisoin ) )
		{	// 左の壁
			g_aModelHandR[ nCntModelHandR ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelHandR[ nCntModelHandR ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelHandR[ nCntModelHandR ].OldPos.x + g_aModelHandR[ nCntModelHandR ].Collisoin ) )
		{	// 右の壁
			g_aModelHandR[ nCntModelHandR ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelHandR[ nCntModelHandR ].Collisoin;
		}
		if(( g_aModelHandR[ nCntModelHandR ].OldPos.z - g_aModelHandR[ nCntModelHandR ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelHandR[ nCntModelHandR ].OldPos.z = 20550.0f + g_aModelHandR[ nCntModelHandR ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}
	}

}

//================================================================================================================================================================================================
// DrawModelHandR関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelHandR( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelHandR[ nCntModelHandR ].scl.x, g_aModelHandR[ nCntModelHandR ].scl.y, g_aModelHandR[ nCntModelHandR ].scl.z );
		D3DXMatrixMultiply( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelHandR[ nCntModelHandR ].rot.y, g_aModelHandR[ nCntModelHandR ].rot.x, g_aModelHandR[ nCntModelHandR ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelHandR[ nCntModelHandR ].pos.x, g_aModelHandR[ nCntModelHandR ].pos.y, g_aModelHandR[ nCntModelHandR ].pos.z );
		D3DXMatrixMultiply( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelHandR[ nCntModelHandR ].nNumMatModelHandR; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelHandR関数
// 引数 void
// 戻り値 
// 説明 ModelHandRを取得する。
//================================================================================================================================================================================================
MODELHANDR *GetModelHandR( void )
{
	return &g_aModelHandR[ 0 ];
}
