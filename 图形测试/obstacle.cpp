/*******************************************************************************
* タイトル： 障害物描画関数
* ファイル名： Obstacle.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/05
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
//2015/11/20/14:09:37 // 障害物の移動 //
/*******************************************************************************
		インクルードファイル
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include "main.h"
#include "obstacle.h"
#include "modelbody.h"
#include "modellegL.h"
#include "modellegR.h"
#include "modelarmL.h"
#include "modelarmR.h"
#include "modelhandL.h"
#include "modelhandR.h"
#include "meshwall.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define GR							0.03f				// 重力加速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
OBSTACLE g_aObstacle_Box[MAX_OBSTACLE_BOX];		// 障害物1の情報
OBSTACLE g_aObstacle_Car[MAX_OBSTACLE_CAR];		// 障害物2の情報
OBSTACLE g_aObstacle_Cat_01[MAX_OBSTACLE_CAT_01];		// 障害物3の情報
//================================================================================================================================================================================================
// InitObstacle関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitObstacle( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESHWALL *pWall = GetMeshWall();
	g_aObstacle_Box[0].pos = D3DXVECTOR3( -60.0f, 0.0f, 700.0f );

	g_aObstacle_Box[1].pos = D3DXVECTOR3( 0.0f, 0.0f, 1100.0f );

	g_aObstacle_Box[2].pos = D3DXVECTOR3( 50.0f, 0.0f, 1800.0f );

	g_aObstacle_Box[3].pos = D3DXVECTOR3( 50.0f, 0.0f, 2500.0f );

	g_aObstacle_Box[4].pos = D3DXVECTOR3( 0.0f, 0.0f, 2900.0f );

	g_aObstacle_Box[5].pos = D3DXVECTOR3( 0.0f, 0.0f, 3500.0f );

	g_aObstacle_Box[6].pos = D3DXVECTOR3( -60.0f, 0.0f, 4000.0f );

	g_aObstacle_Box[7].pos = D3DXVECTOR3( 60.0f, 0.0f, 4800.0f );

	g_aObstacle_Box[8].pos = D3DXVECTOR3( 60.0f, 0.0f, 5300.0f );

	g_aObstacle_Box[9].pos = D3DXVECTOR3( 0.0f, 0.0f, 6000.0f );

	g_aObstacle_Box[10].pos = D3DXVECTOR3( 30.0f, 0.0f, 7200.0f );

	g_aObstacle_Box[11].pos = D3DXVECTOR3( -70.0f, 0.0f, 8600.0f );

	g_aObstacle_Box[12].pos = D3DXVECTOR3( 60.0f, 0.0f, 8600.0f );

	g_aObstacle_Box[13].pos = D3DXVECTOR3( 0.0f, 0.0f, 9300.0f );

	g_aObstacle_Box[14].pos = D3DXVECTOR3( -30.0f, 0.0f, 10000.0f );

	g_aObstacle_Box[15].pos = D3DXVECTOR3( 40.0f, 0.0f, 11900.0f );

	g_aObstacle_Box[16].pos = D3DXVECTOR3( 20.0f, 0.0f, 12800.0f );

	g_aObstacle_Box[17].pos = D3DXVECTOR3( 0.0f, 0.0f, 13900.0f );

	g_aObstacle_Box[18].pos = D3DXVECTOR3( 70.0f, 0.0f, 14800.0f );

	g_aObstacle_Box[19].pos = D3DXVECTOR3( -50.0f, 0.0f, 15700.0f );

	g_aObstacle_Box[20].pos = D3DXVECTOR3( 10.0f, 0.0f, 16900.0f );

	g_aObstacle_Box[21].pos = D3DXVECTOR3( 60.0f, 0.0f, 17800.0f );

	g_aObstacle_Box[22].pos = D3DXVECTOR3( 30.0f, 0.0f, 18900.0f );

	g_aObstacle_Box[23].pos = D3DXVECTOR3( 0.0f, 0.0f, 19200.0f );

	g_aObstacle_Box[24].pos = D3DXVECTOR3( -10.0f, 0.0f, 19900.0f );

	g_aObstacle_Box[25].pos = D3DXVECTOR3( -50.0f, 0.0f, 20300.0f );
		for( int nCntObstacleBox = 0; nCntObstacleBox < MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\box.jpg",&g_aObstacle_Box[nCntObstacleBox].pTextureObstacle);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\obstacle_box.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle,		// マテリアル情報
									   NULL,
									   &g_aObstacle_Box[nCntObstacleBox].nNumMatObstacle,			// マテリアル数
									   &g_aObstacle_Box[nCntObstacleBox].pMeshObstacle ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// 障害物の初期設定

		g_aObstacle_Box[nCntObstacleBox].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Box[nCntObstacleBox].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aObstacle_Box[nCntObstacleBox].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Box[nCntObstacleBox].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Box[nCntObstacleBox].fPosMove = POSMOVE_OBSTACLE_BOX;
		g_aObstacle_Box[nCntObstacleBox].time = 0;
		g_aObstacle_Box[nCntObstacleBox].nLife = 100;
		g_aObstacle_Box[nCntObstacleBox].Type = OBSTACLE_BOX;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aObstacle_Box[nCntObstacleBox].Min.x )		g_aObstacle_Box[nCntObstacleBox].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aObstacle_Box[nCntObstacleBox].Max.x )		g_aObstacle_Box[nCntObstacleBox].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aObstacle_Box[nCntObstacleBox].Min.y )		g_aObstacle_Box[nCntObstacleBox].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aObstacle_Box[nCntObstacleBox].Max.y )		g_aObstacle_Box[nCntObstacleBox].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aObstacle_Box[nCntObstacleBox].Min.z )		g_aObstacle_Box[nCntObstacleBox].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aObstacle_Box[nCntObstacleBox].Max.z )		g_aObstacle_Box[nCntObstacleBox].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->UnlockVertexBuffer();

		// 障害物の半径の設定。絶対値をabs関数で求める。
		g_aObstacle_Box[nCntObstacleBox].Size.x = ( fabs( g_aObstacle_Box[nCntObstacleBox].Min.x ) + fabs( g_aObstacle_Box[nCntObstacleBox].Max.x ) ) / 2;
		g_aObstacle_Box[nCntObstacleBox].Size.y = ( fabs( g_aObstacle_Box[nCntObstacleBox].Min.y ) + fabs( g_aObstacle_Box[nCntObstacleBox].Max.y ) ) / 2;
		g_aObstacle_Box[nCntObstacleBox].Size.z = ( fabs( g_aObstacle_Box[nCntObstacleBox].Min.z ) + fabs( g_aObstacle_Box[nCntObstacleBox].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aObstacle_Box[nCntObstacleBox].Size.x < g_aObstacle_Box[nCntObstacleBox].Size.z )
		{
			g_aObstacle_Box[nCntObstacleBox].Collisoin = g_aObstacle_Box[nCntObstacleBox].Size.z;
		}
		else
		{
			g_aObstacle_Box[nCntObstacleBox].Collisoin = g_aObstacle_Box[nCntObstacleBox].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aObstacle_Box[nCntObstacleBox].bUse = true;
		}
/***************************************************************************************************************************************************************/
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\obstacle_car.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle,		// マテリアル情報
									   NULL,
									   &g_aObstacle_Car[nCntObstacleCar].nNumMatObstacle,			// マテリアル数
									   &g_aObstacle_Car[nCntObstacleCar].pMeshObstacle ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// 障害物の初期設定
		g_aObstacle_Car[nCntObstacleCar].rot = D3DXVECTOR3( 0.0f,  3.14f, 0.0f );
		g_aObstacle_Car[nCntObstacleCar].scl = D3DXVECTOR3( 3.0f,  3.0f, 3.0f );
		g_aObstacle_Car[nCntObstacleCar].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Car[nCntObstacleCar].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Car[nCntObstacleCar].fPosMove = POSMOVE_OBSTACLE_CAR;
		g_aObstacle_Car[nCntObstacleCar].time = 0;
		g_aObstacle_Car[nCntObstacleCar].nLife = 100;
		g_aObstacle_Car[nCntObstacleCar].Type = OBSTACLE_CAR;
		g_aObstacle_Car[nCntObstacleCar].bMove = true;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aObstacle_Car[nCntObstacleCar].Min.x )		g_aObstacle_Car[nCntObstacleCar].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aObstacle_Car[nCntObstacleCar].Max.x )		g_aObstacle_Car[nCntObstacleCar].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aObstacle_Car[nCntObstacleCar].Min.y )		g_aObstacle_Car[nCntObstacleCar].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aObstacle_Car[nCntObstacleCar].Max.y )		g_aObstacle_Car[nCntObstacleCar].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aObstacle_Car[nCntObstacleCar].Min.z )		g_aObstacle_Car[nCntObstacleCar].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aObstacle_Car[nCntObstacleCar].Max.z )		g_aObstacle_Car[nCntObstacleCar].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->UnlockVertexBuffer();

		// 障害物の半径の設定。絶対値をabs関数で求める。
		g_aObstacle_Car[nCntObstacleCar].Size.x = ( fabs( g_aObstacle_Car[nCntObstacleCar].Min.x ) + fabs( g_aObstacle_Car[nCntObstacleCar].Max.x ) ) / 2;
		g_aObstacle_Car[nCntObstacleCar].Size.y = ( fabs( g_aObstacle_Car[nCntObstacleCar].Min.y ) + fabs( g_aObstacle_Car[nCntObstacleCar].Max.y ) ) / 2;
		g_aObstacle_Car[nCntObstacleCar].Size.z = ( fabs( g_aObstacle_Car[nCntObstacleCar].Min.z ) + fabs( g_aObstacle_Car[nCntObstacleCar].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aObstacle_Car[nCntObstacleCar].Size.x < g_aObstacle_Car[nCntObstacleCar].Size.z )
		{
			g_aObstacle_Car[nCntObstacleCar].Collisoin = g_aObstacle_Car[nCntObstacleCar].Size.z;
		}
		else
		{
			g_aObstacle_Car[nCntObstacleCar].Collisoin = g_aObstacle_Car[nCntObstacleCar].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aObstacle_Car[nCntObstacleCar].bUse = true;
		}
		g_aObstacle_Car[0].pos = D3DXVECTOR3( -30.0f, 0.0f, 20000.0f );
		g_aObstacle_Car[1].pos = D3DXVECTOR3( 60.0f, 0.0f, 12300.0f );
		g_aObstacle_Car[2].pos = D3DXVECTOR3( -70.0f, 0.0f, 5300.0f );
/***************************************************************************************************************************************************************/
		for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 < MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\cat_01.png",&g_aObstacle_Cat_01[nCntObstacleCat_01].pTextureObstacle);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\cat_01.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle,		// マテリアル情報
									   NULL,
									   &g_aObstacle_Cat_01[nCntObstacleCat_01].nNumMatObstacle,			// マテリアル数
									   &g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// 障害物の初期設定

		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aObstacle_Cat_01[nCntObstacleCat_01].Min.x )		g_aObstacle_Cat_01[nCntObstacleCat_01].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aObstacle_Cat_01[nCntObstacleCat_01].Max.x )		g_aObstacle_Cat_01[nCntObstacleCat_01].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aObstacle_Cat_01[nCntObstacleCat_01].Min.y )		g_aObstacle_Cat_01[nCntObstacleCat_01].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aObstacle_Cat_01[nCntObstacleCat_01].Max.y )		g_aObstacle_Cat_01[nCntObstacleCat_01].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aObstacle_Cat_01[nCntObstacleCat_01].Min.z )		g_aObstacle_Cat_01[nCntObstacleCat_01].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aObstacle_Cat_01[nCntObstacleCat_01].Max.z )		g_aObstacle_Cat_01[nCntObstacleCat_01].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->UnlockVertexBuffer();

		// 障害物の半径の設定。絶対値をabs関数で求める。
		g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x = ( fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Min.x ) + fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Max.x ) ) / 2;
		g_aObstacle_Cat_01[nCntObstacleCat_01].Size.y = ( fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Min.y ) + fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Max.y ) ) / 2;
		g_aObstacle_Cat_01[nCntObstacleCat_01].Size.z = ( fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Min.z ) + fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x < g_aObstacle_Cat_01[nCntObstacleCat_01].Size.z )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].Collisoin = g_aObstacle_Cat_01[nCntObstacleCat_01].Size.z;
		}
		else
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].Collisoin = g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_aObstacle_Cat_01[nCntObstacleCat_01].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].time = 0;
		g_aObstacle_Cat_01[nCntObstacleCat_01].nLife = 1000;
		g_aObstacle_Cat_01[nCntObstacleCat_01].Type = OBSTACLE_CAT_01;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bUse = true;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bMove = true;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bRot = false;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bCatRotCheck = false;
		}
		g_aObstacle_Cat_01[0].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[0].Size.x,0.0f,1100.0f);
		g_aObstacle_Cat_01[0].fPosMove = 0.5f;

		g_aObstacle_Cat_01[1].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[1].Size.x,0.0f,2300.0f);
		g_aObstacle_Cat_01[1].fPosMove = 0.8f;

		g_aObstacle_Cat_01[2].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[2].Size.x,0.0f,2800.0f);
		g_aObstacle_Cat_01[2].fPosMove = 0.2f;

		g_aObstacle_Cat_01[3].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[3].Size.x,0.0f,3900.0f);
		g_aObstacle_Cat_01[3].fPosMove = 0.7f;

		g_aObstacle_Cat_01[4].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[4].Size.x,0.0f,4700.0f);
		g_aObstacle_Cat_01[4].fPosMove = 0.1f;

		g_aObstacle_Cat_01[5].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[5].Size.x,0.0f,6000.0f);
		g_aObstacle_Cat_01[5].fPosMove = 0.9f;

		g_aObstacle_Cat_01[6].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[6].Size.x,0.0f,8000.0f);
		g_aObstacle_Cat_01[6].fPosMove = 0.1f;

		g_aObstacle_Cat_01[6].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[6].Size.x,0.0f,11200.0f);
		g_aObstacle_Cat_01[6].fPosMove = 0.2f;


		g_aObstacle_Cat_01[7].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[7].Size.x,0.0f,12000.0f);
		g_aObstacle_Cat_01[7].fPosMove = 0.5f;


		g_aObstacle_Cat_01[8].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[8].Size.x,0.0f,13000.0f);
		g_aObstacle_Cat_01[8].fPosMove = 0.5f;


		g_aObstacle_Cat_01[9].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[9].Size.x,0.0f,14200.0f);
		g_aObstacle_Cat_01[9].fPosMove = 0.5f;


		g_aObstacle_Cat_01[10].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[10].Size.x,0.0f,15700.0f);
		g_aObstacle_Cat_01[10].fPosMove = 1.0f;


		g_aObstacle_Cat_01[11].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[11].Size.x,0.0f,16900.0f);
		g_aObstacle_Cat_01[11].fPosMove = 0.7f;

		g_aObstacle_Cat_01[12].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[12].Size.x,0.0f,18000.0f);
		g_aObstacle_Cat_01[12].fPosMove = 0.6f;

		g_aObstacle_Cat_01[13].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[13].Size.x,0.0f,20000.0f);
		g_aObstacle_Cat_01[13].fPosMove = 1.0f;

	return S_OK;
}

//================================================================================================================================================================================================
// UninitObstacle関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitObstacle( void )
{
	for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		// メッシュ情報の開放
		if( g_aObstacle_Box[nCntObstacleBox].pMeshObstacle != NULL )
		{
			g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->Release();
			g_aObstacle_Box[nCntObstacleBox].pMeshObstacle = NULL;
		}

		// バッファの開放
		if( g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle != NULL )
		{
			g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle->Release();
			g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle = NULL;
		}
	}
/***************************************************************************************/
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		// メッシュ情報の開放
		if( g_aObstacle_Car[nCntObstacleCar].pMeshObstacle != NULL )
		{
			g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->Release();
			g_aObstacle_Car[nCntObstacleCar].pMeshObstacle = NULL;
		}

		// バッファの開放
		if( g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle != NULL )
		{
			g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle->Release();
			g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle = NULL;
		}
	}

/***************************************************************************************/
		for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 < MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		// メッシュ情報の開放
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle != NULL )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->Release();
			g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle = NULL;
		}

		// バッファの開放
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle != NULL )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle->Release();
			g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle = NULL;
		}
	}
	
}

//================================================================================================================================================================================================
// UpdateObstacle関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateObstacle( void )
{
	MESHWALL *pWall = GetMeshWall();
	for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 < MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		if(g_aObstacle_Cat_01[nCntObstacleCat_01].bRot == true)
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].fPosMove = 0.0f;
			g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x+=0.05f;
			if(g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x>=1.57f)
			{
				g_aObstacle_Cat_01[nCntObstacleCat_01].bCatRotCheck = true;
				g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x = 1.57f;
				g_aObstacle_Cat_01[nCntObstacleCat_01].nLife --;

				if(g_aObstacle_Cat_01[nCntObstacleCat_01].nLife<=0)
				{
					g_aObstacle_Cat_01[nCntObstacleCat_01].bUse = false;
				}
			}
		}
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x <= (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].bMove =true;
		}
	else if(g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x >= (pWall + WALL_RIGHT)->pos.x + g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].bMove =false;
		}
		if(g_aObstacle_Cat_01[nCntObstacleCat_01].bMove == true)
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x += g_aObstacle_Cat_01[nCntObstacleCat_01].fPosMove;
		}
		else if(g_aObstacle_Cat_01[nCntObstacleCat_01].bMove ==	false)
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x -= g_aObstacle_Cat_01[nCntObstacleCat_01].fPosMove;

		}
	}
/*******************************************************************************************************************************/
	for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		if(g_aObstacle_Car[nCntObstacleCar].bUse == true)
		{
			if( g_aObstacle_Car[nCntObstacleCar].pos.z <= 0.0f )
			{
				g_aObstacle_Car[nCntObstacleCar].rot = D3DXVECTOR3( 0.0f,  3.14f, 0.0f );
				g_aObstacle_Car[nCntObstacleCar].bMove =true;
			}
		else if(g_aObstacle_Car[nCntObstacleCar].pos.z >= 21000.0f )
			{
				g_aObstacle_Car[nCntObstacleCar].rot = D3DXVECTOR3( 0.0f,  0.00f, 0.0f );
				g_aObstacle_Car[nCntObstacleCar].bMove =false;
			}
			if(g_aObstacle_Car[nCntObstacleCar].bMove == true)
			{
				g_aObstacle_Car[nCntObstacleCar].pos.z += g_aObstacle_Car[nCntObstacleCar].fPosMove;
			}
			else if(g_aObstacle_Car[nCntObstacleCar].bMove ==	false)
			{
				g_aObstacle_Car[nCntObstacleCar].pos.z -= g_aObstacle_Car[nCntObstacleCar].fPosMove;
			}
		}
	}
}
//================================================================================================================================================================================================
// DrawObstacle関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawObstacle( void )
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );
	//モデルに白くになるの魔法コード
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	// レンダーステートの設定（zテスト）
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z値の更新
	// レンダーステートの設定（アルファテスト）
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// アルファ値を判定して、該当のピクセルを描画するようにする。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// 下の値よりアルファ値が大きければ描画する。
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// アルファ値。0で透明な部分。
		for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		if(g_aObstacle_Box[nCntObstacleBox].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aObstacle_Box[nCntObstacleBox].scl.x, g_aObstacle_Box[nCntObstacleBox].scl.y, g_aObstacle_Box[nCntObstacleBox].scl.z );
		D3DXMatrixMultiply( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aObstacle_Box[nCntObstacleBox].rot.y, g_aObstacle_Box[nCntObstacleBox].rot.x, g_aObstacle_Box[nCntObstacleBox].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aObstacle_Box[nCntObstacleBox].pos.x, g_aObstacle_Box[nCntObstacleBox].pos.y, g_aObstacle_Box[nCntObstacleBox].pos.z );
		D3DXMatrixMultiply( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &mtxTrans );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aObstacle_Box[nCntObstacleBox].nNumMatObstacle; nCntMat++ )
		{

			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aObstacle_Box[nCntObstacleBox].pTextureObstacle );

			// メッシュの描画
			g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->DrawSubset( nCntMat );

		}

		}
	}
/********************************************************************************************************************/


	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );
	//モデルに白くになるの魔法コード
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		if(g_aObstacle_Car[nCntObstacleCar].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aObstacle_Car[nCntObstacleCar].scl.x, g_aObstacle_Car[nCntObstacleCar].scl.y, g_aObstacle_Car[nCntObstacleCar].scl.z );
		D3DXMatrixMultiply( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aObstacle_Car[nCntObstacleCar].rot.y, g_aObstacle_Car[nCntObstacleCar].rot.x, g_aObstacle_Car[nCntObstacleCar].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aObstacle_Car[nCntObstacleCar].pos.x, g_aObstacle_Car[nCntObstacleCar].pos.y, g_aObstacle_Car[nCntObstacleCar].pos.z );
		D3DXMatrixMultiply( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aObstacle_Car[nCntObstacleCar].nNumMatObstacle; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, 0 );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、障害物が暗くなったりする。

			// メッシュの描画
			g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->DrawSubset( nCntMat );
		}
			// マテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}

	}
/********************************************************************************************************************/
		for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 <MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		if(g_aObstacle_Cat_01[nCntObstacleCat_01].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aObstacle_Cat_01[nCntObstacleCat_01].scl.x, g_aObstacle_Cat_01[nCntObstacleCat_01].scl.y, g_aObstacle_Cat_01[nCntObstacleCat_01].scl.z );
		D3DXMatrixMultiply( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aObstacle_Cat_01[nCntObstacleCat_01].rot.y, g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x, g_aObstacle_Cat_01[nCntObstacleCat_01].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x, g_aObstacle_Cat_01[nCntObstacleCat_01].pos.y, g_aObstacle_Cat_01[nCntObstacleCat_01].pos.z );
		D3DXMatrixMultiply( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &mtxTrans );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aObstacle_Cat_01[nCntObstacleCat_01].nNumMatObstacle; nCntMat++ )
		{

			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aObstacle_Cat_01[nCntObstacleCat_01].pTextureObstacle );

			// メッシュの描画
			g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->DrawSubset( nCntMat );

		}

		}

	}


}

//================================================================================================================================================================================================
// OBSTACLE *GetObstacle_Box関数
// 引数 void
// 戻り値 
// 説明 Obstacle_Boxを取得する。
//================================================================================================================================================================================================
OBSTACLE *GetObstacle_Box( void )
{
	return &g_aObstacle_Box[0];
}
//================================================================================================================================================================================================
//OBSTACLE *GetObstacle_Car関数
// 引数 void
// 戻り値 
// 説明 g_aObstacle_Car[nCntObstacleCar]を取得する。
//================================================================================================================================================================================================
OBSTACLE *GetObstacle_Car( void )
{
	return &g_aObstacle_Car[0];
}
//================================================================================================================================================================================================
//OBSTACLE *GetObstacle_Cat_01関数
// 引数 void
// 戻り値 
// 説明 g_aObstacle_Car[nCntObstacleCar]を取得する。
//================================================================================================================================================================================================
OBSTACLE *GetObstacle_Cat_01( void )
{
	return &g_aObstacle_Cat_01[0];
}

void SetObstacle_Box( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		if(g_aObstacle_Box[nCntObstacleBox].bUse == false )
		{
			// 位置の設定
			g_aObstacle_Box[nCntObstacleBox].pos = pos;

			// 移動量の設定
			g_aObstacle_Box[nCntObstacleBox].rot = rot;

			// 寿命の設定
			g_aObstacle_Box[nCntObstacleBox].nLife = nLife;

			// ツールを使用状態にする
			g_aObstacle_Box[nCntObstacleBox].bUse = true;
			
		}
	}
	
}
void SetObstacle_Car( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		if(g_aObstacle_Car[nCntObstacleCar].bUse == false )
		{
			// 位置の設定
			g_aObstacle_Car[nCntObstacleCar].pos = pos;

			// 移動量の設定
			g_aObstacle_Car[nCntObstacleCar].rot = rot;

			// 寿命の設定
			g_aObstacle_Car[nCntObstacleCar].nLife = nLife;

			// ツールを使用状態にする
			g_aObstacle_Car[nCntObstacleCar].bUse = true;
			
		}
		}
	
}

//================================================================================================================================================================================================
// void HitObstacle_Box(void)関数
// 引数 void
// 戻り値 
// 説明 障害物1当たり判定用
//================================================================================================================================================================================================
void HitObstacle_Box(void)
{
	MODELBODY *pModelBody = GetModelBody();
	MODELLEGL *pModelLegL = GetModelLegL();
	MODELLEGR *pModelLegR = GetModelLegR();
	MODELHANDL *pModelHandL = GetModelHandL();
	MODELHANDR *pModelHandR = GetModelHandR();
	MODELARML *pModelArmL = GetModelarmL();
	MODELARMR *pModelArmR = GetModelarmR();
	for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{		//当たり判定二倍計算`(左から右)(bdoy)
		if ( pModelBody -> OldPos.x + pModelBody->Collisoin >= (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin  )
			&& (pModelBody -> OldPos.z+  pModelBody -> Collisoin) >= (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin )
			&& (pModelBody -> OldPos.z-  pModelBody -> Collisoin) <= (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin  )
			//&&  pModelBody -> OldPos.x - pModelBody->Collisoin < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin *4 )
			)
		{
			pModelBody -> OldPos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin ) - pModelBody->Collisoin ;
		}
//			//当たり判定二倍計算`(左から右)(handL)
//		if ( pModelHandL -> pos.x + pModelHandL->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandL -> pos.z+  pModelHandL -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandL -> pos.z-  pModelHandL -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelHandL -> pos.x - pModelHandL->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelHandL -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelHandL->Collisoin*2 ;
//		}
//
//			//当たり判定二倍計算`(左から右)(handR)
//		if ( pModelHandR -> pos.x + pModelHandR->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandR -> pos.z+  pModelHandR -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandR -> pos.z-  pModelHandR -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& pModelHandR -> pos.x - pModelHandR->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelHandR -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelHandR->Collisoin*2 ;
//		}
//
//
//			//当たり判定二倍計算`(左から右)(LegL)
//		if ( pModelLegL -> pos.x + pModelLegL->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegL -> pos.z+  pModelLegL -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegL -> pos.z-  pModelLegL -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelLegL -> pos.x - pModelLegL->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelLegL -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelLegL->Collisoin*2 ;
//		}
//
//			//当たり判定二倍計算`(左から右)(LegR)
//		if ( pModelLegR -> pos.x + pModelLegR->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegR -> pos.z+  pModelLegR -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegR -> pos.z-  pModelLegR -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelLegR -> pos.x + pModelLegR->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelLegR -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelLegR->Collisoin*2 ;
//		}
//
//
//			//当たり判定二倍計算`(左から右)(ArmL)
//		if ( pModelArmL -> pos.x + pModelArmL->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmL -> pos.z+  pModelArmL -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmL -> pos.z-  pModelArmL -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& pModelArmL -> pos.x + pModelArmL->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelArmL -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelArmL->Collisoin*2 ;
//		}
//
//
//			//当たり判定二倍計算`(左から右)(ArmR)
//		if ( pModelArmR -> pos.x + pModelArmR->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmR -> pos.z+  pModelArmR -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmR -> pos.z-  pModelArmR -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelArmR -> pos.x + pModelArmR->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelArmR -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelArmR->Collisoin*2 ;
//		}
///************************************************************************************************************************************************************/
//
//		//当たり判定二倍計算`(右から左)(bdoy)
//		if ( pModelBody -> pos.x - pModelBody->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelBody -> pos.z + pModelBody -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelBody -> pos.z - pModelBody -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& pModelBody -> pos.x + pModelBody->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelBody -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin) + pModelBody->Collisoin*2 ;
//		}
	}
}