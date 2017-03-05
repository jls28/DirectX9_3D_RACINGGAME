/*******************************************************************************
* タイトル： モデル描画関数
* ファイル名： PropModel_01.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/05
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
//2015/11/20/14:09:37 // モデルの移動 //
/*******************************************************************************
		インクルードファイル
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "main.h"
#include "propmodel_Group.h"
#include "effect.h"
#include "modelbody.h"
#include "shadow.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "propshow.h"
#include "propmpmax.h"
#include "propmplife.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "propexplosion.h"
#include "propmp.h"
#include "obstacle.h"
#include "money.h"
#include "timebg.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define GR							0.03f				// 重力加速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void RotMove_01 (void);
void RotMove_02 (void);
void RotMove_03 (void);
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
PROPMODELGROUP g_aPropModel_01;		// モデル1の情報
PROPMODELGROUP g_aPropModel_02;		// モデル2の情報
PROPMODELGROUP g_aPropModel_03;		// モデル3の情報
//================================================================================================================================================================================================
// InitPropModel_Group関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitPropModel_Group( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\prop001.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aPropModel_01.pBuffMatPropModel,		// マテリアル情報
									   NULL,
									   &g_aPropModel_01.nNumMatPropModel,			// マテリアル数
									   &g_aPropModel_01.pMeshPropModel ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aPropModel_01.pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		g_aPropModel_01.rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_01.scl = D3DXVECTOR3( 0.5f,  0.5f, 0.5f );
		g_aPropModel_01.Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_01.Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_01.fPosMove = POSMOVE_PROPMODEL_01;
		g_aPropModel_01.fAngle = 0.0f;
		g_aPropModel_01.propR = 20.0f;		//半径
		g_aPropModel_01.bRotUse = true;
		g_aPropModel_01.bUseCheck = false;
		g_aPropModel_01.bActive = true;
		g_aPropModel_01.time = 0;
		g_aPropModel_01.nLife = 100;
		g_aPropModel_01.cnt = -1;
		g_aPropModel_01.Type = PROWT_0;
		g_aPropModel_01.state = PROWT_SPIN;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aPropModel_01.pMeshPropModel->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aPropModel_01.pMeshPropModel->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aPropModel_01.pMeshPropModel->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aPropModel_01.Min.x )		g_aPropModel_01.Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aPropModel_01.Max.x )		g_aPropModel_01.Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aPropModel_01.Min.y )		g_aPropModel_01.Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aPropModel_01.Max.y )		g_aPropModel_01.Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aPropModel_01.Min.z )		g_aPropModel_01.Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aPropModel_01.Max.z )		g_aPropModel_01.Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aPropModel_01.pMeshPropModel->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aPropModel_01.Size.x = ( fabs( g_aPropModel_01.Min.x ) + fabs( g_aPropModel_01.Max.x ) ) / 2;
		g_aPropModel_01.Size.y = ( fabs( g_aPropModel_01.Min.y ) + fabs( g_aPropModel_01.Max.y ) ) / 2;
		g_aPropModel_01.Size.z = ( fabs( g_aPropModel_01.Min.z ) + fabs( g_aPropModel_01.Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aPropModel_01.Size.x < g_aPropModel_01.Size.z )
		{
			g_aPropModel_01.Collisoin = g_aPropModel_01.Size.z;
		}
		else
		{
			g_aPropModel_01.Collisoin = g_aPropModel_01.Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aPropModel_01.bUse = false;
	
/***************************************************************************************************************************************************************/

		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\prop002.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aPropModel_02.pBuffMatPropModel,		// マテリアル情報
									   NULL,
									   &g_aPropModel_02.nNumMatPropModel,			// マテリアル数
									   &g_aPropModel_02.pMeshPropModel ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aPropModel_02.pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		g_aPropModel_02.rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_02.scl = D3DXVECTOR3( 0.5f,  0.5f, 0.5f );
		g_aPropModel_02.Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_02.Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_02.fPosMove = POSMOVE_PROPMODEL_02;
		g_aPropModel_02.fAngle = 0.0f;
		g_aPropModel_02.propR = 20.0f;		//半径
		g_aPropModel_02.bRotUse = true;
		g_aPropModel_02.bUseCheck = false;
		g_aPropModel_02.bActive = true;
		g_aPropModel_02.time = 0;
		g_aPropModel_02.nLife = 100;
		g_aPropModel_02.cnt = -1;
		g_aPropModel_02.Type = PROWT_0;
		g_aPropModel_02.state = PROWT_SPIN;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aPropModel_02.pMeshPropModel->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aPropModel_02.pMeshPropModel->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aPropModel_02.pMeshPropModel->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aPropModel_02.Min.x )		g_aPropModel_02.Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aPropModel_02.Max.x )		g_aPropModel_02.Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aPropModel_02.Min.y )		g_aPropModel_02.Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aPropModel_02.Max.y )		g_aPropModel_02.Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aPropModel_02.Min.z )		g_aPropModel_02.Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aPropModel_02.Max.z )		g_aPropModel_02.Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aPropModel_02.pMeshPropModel->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aPropModel_02.Size.x = ( fabs( g_aPropModel_02.Min.x ) + fabs( g_aPropModel_02.Max.x ) ) / 2;
		g_aPropModel_02.Size.y = ( fabs( g_aPropModel_02.Min.y ) + fabs( g_aPropModel_02.Max.y ) ) / 2;
		g_aPropModel_02.Size.z = ( fabs( g_aPropModel_02.Min.z ) + fabs( g_aPropModel_02.Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aPropModel_02.Size.x < g_aPropModel_02.Size.z )
		{
			g_aPropModel_02.Collisoin = g_aPropModel_02.Size.z;
		}
		else
		{
			g_aPropModel_02.Collisoin = g_aPropModel_02.Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aPropModel_02.bUse = false;
	

/***************************************************************************************************************************************************************/

		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\prop003.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aPropModel_03.pBuffMatPropModel,		// マテリアル情報
									   NULL,
									   &g_aPropModel_03.nNumMatPropModel,			// マテリアル数
									   &g_aPropModel_03.pMeshPropModel ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aPropModel_03.pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		g_aPropModel_03.rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_03.scl = D3DXVECTOR3( 0.5f,  0.5f, 0.5f );
		g_aPropModel_03.Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_03.Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPropModel_03.fPosMove = POSMOVE_PROPMODEL_03;
		g_aPropModel_03.fAngle = 0.0f;
		g_aPropModel_03.propR = 20.0f;		//半径
		g_aPropModel_03.bRotUse = true;
		g_aPropModel_03.time = 0;
		g_aPropModel_03.nLife = 100;
		g_aPropModel_03.cnt = -1;
		g_aPropModel_03.Type = PROWT_0;
		g_aPropModel_03.state = PROWT_SPIN;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aPropModel_03.pMeshPropModel->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aPropModel_03.pMeshPropModel->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aPropModel_03.pMeshPropModel->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aPropModel_03.Min.x )		g_aPropModel_03.Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aPropModel_03.Max.x )		g_aPropModel_03.Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aPropModel_03.Min.y )		g_aPropModel_03.Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aPropModel_03.Max.y )		g_aPropModel_03.Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aPropModel_03.Min.z )		g_aPropModel_03.Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aPropModel_03.Max.z )		g_aPropModel_03.Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aPropModel_03.pMeshPropModel->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aPropModel_03.Size.x = ( fabs( g_aPropModel_03.Min.x ) + fabs( g_aPropModel_03.Max.x ) ) / 2;
		g_aPropModel_03.Size.y = ( fabs( g_aPropModel_03.Min.y ) + fabs( g_aPropModel_03.Max.y ) ) / 2;
		g_aPropModel_03.Size.z = ( fabs( g_aPropModel_03.Min.z ) + fabs( g_aPropModel_03.Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aPropModel_03.Size.x < g_aPropModel_03.Size.z )
		{
			g_aPropModel_03.Collisoin = g_aPropModel_03.Size.z;
		}
		else
		{
			g_aPropModel_03.Collisoin = g_aPropModel_03.Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aPropModel_03.bUse = false;
	
/***************************************************************************************************************************************************************/
	return S_OK;
}

//================================================================================================================================================================================================
// UninitPropModel_Group関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitPropModel_Group( void )
{

		// メッシュ情報の開放
		if( g_aPropModel_01.pMeshPropModel != NULL )
		{
			g_aPropModel_01.pMeshPropModel->Release();
			g_aPropModel_01.pMeshPropModel = NULL;
		}

		// バッファの開放
		if( g_aPropModel_01.pBuffMatPropModel != NULL )
		{
			g_aPropModel_01.pBuffMatPropModel->Release();
			g_aPropModel_01.pBuffMatPropModel = NULL;
		}
	
/***************************************************************************************/

		// メッシュ情報の開放
		if( g_aPropModel_02.pMeshPropModel != NULL )
		{
			g_aPropModel_02.pMeshPropModel->Release();
			g_aPropModel_02.pMeshPropModel = NULL;
		}

		// バッファの開放
		if( g_aPropModel_02.pBuffMatPropModel != NULL )
		{
			g_aPropModel_02.pBuffMatPropModel->Release();
			g_aPropModel_02.pBuffMatPropModel = NULL;
		}
	

		// メッシュ情報の開放
		if( g_aPropModel_03.pMeshPropModel != NULL )
		{
			g_aPropModel_03.pMeshPropModel->Release();
			g_aPropModel_03.pMeshPropModel = NULL;
		}

		// バッファの開放
		if( g_aPropModel_03.pBuffMatPropModel != NULL )
		{
			g_aPropModel_03.pBuffMatPropModel->Release();
			g_aPropModel_03.pBuffMatPropModel = NULL;
		}
	
}

//================================================================================================================================================================================================
// UpdatePropModel_Group関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdatePropModel_Group( void )
{
	PROW *pProw = GetProw();
	PROPMPMAX *pObstacle_BoxMpMax = GetPropMpMax();
	PROPMPLIFE *pObstacle_BoxMpLife = GetPropMpLife();
	PROPMP *pObstacle_BoxMp = GetPropMp();
	TIMEBG *pTimeBg = GetTimeBg();
	//モデルを取得
	MODELBODY		*pModelBody		= GetModelBody();
	int cnt = pProw->nPattern;

	if(cnt!= PROWT_3)
	{
		pModelBody->fPosMove = POSMOVE_MODELBODY ;
	}
	if(pProw->bUse == true && pProw->bProwUse == true )
	{
		if(pObstacle_BoxMpMax->bUse == false)
		{
			cnt = PROWT_0;
		}
		else
		{
			cnt = pProw->nPattern;
		}
		switch( cnt )
		{
		case PROWT_1:
			g_aPropModel_02.bUse = false;
			g_aPropModel_03.bUse = false;
			if(GetKeyboardTrigger ( DIK_SPACE ))
			{
				g_aPropModel_01.state = PROWT_BULLET;
				SetPropModel_01( pModelBody->pos, pModelBody->rot, 80 );

			}
			switch(g_aPropModel_01.state)
			{
			case PROWT_SPIN:
				g_aPropModel_01.bUse = true;
				RotMove_01();
				break;
				
			case PROWT_BULLET:
				pModelBody->fPosMove = POSMOVE_MODELBODY ;
				g_aPropModel_01.bUse = true;
				if( !g_aPropModel_01.bUseCheck )
				{
					g_aPropModel_01.rot.y = pModelBody->rot.y;
					g_aPropModel_01.pos.y += 10.0f;
					g_aPropModel_01.pos.x = pModelBody->pos.x;
					g_aPropModel_01.bUseCheck = true;
				}

				g_aPropModel_01.pos.x  += sinf( D3DX_PI + g_aPropModel_01.rot.y ) * POSMOVE_PROPMODEL_01;		// 角度 * 移動量
				g_aPropModel_01.pos.z  += cosf( D3DX_PI + g_aPropModel_01.rot.y ) * POSMOVE_PROPMODEL_01;		// 角度 * 移動量
				//MoveShellModel01();
				g_aPropModel_01.bActive = true;
				g_aPropModel_01.nLife--;
				HitPropModel_01();
				//effect
				SetEffect(pModelBody->pos,	(255, 0, 0,255),8,70,EFFECTTYPE_NORMAL );
				if(g_aPropModel_01.nLife <= 0 )
				{
					pObstacle_BoxMpMax->bUse = false;
					g_aPropModel_01.bUse = false;
					pModelBody->time = 0;
					pProw->bUse = false;
					pProw->bProwUse = false;
					pObstacle_BoxMpLife->bUse = false;
					pObstacle_BoxMp->bUse = false;
					pObstacle_BoxMpLife->time =0;
					
				}
				break;

			default:
			break;
			}

		
			break;

		case PROWT_2:
			g_aPropModel_01.bUse = false;
			g_aPropModel_03.bUse = false;
			if(GetKeyboardTrigger ( DIK_SPACE ))
			{
				g_aPropModel_02.state = PROWT_BULLET;
				SetPropModel_02( pModelBody->pos, pModelBody->rot, 80 );
				
			}
			switch(g_aPropModel_02.state)
			{
			case PROWT_SPIN:
				g_aPropModel_02.bUse = true;
				RotMove_02();
				break;
				
			case PROWT_BULLET:
				pModelBody->fPosMove = POSMOVE_MODELBODY ;
				g_aPropModel_02.bUse = true;
				if( !g_aPropModel_02.bUseCheck )
				{
					AddTimebg(10);
					g_aPropModel_02.rot.y = pModelBody->rot.y;
					g_aPropModel_02.pos.y += 10.0f;
					g_aPropModel_02.pos.x = pModelBody->pos.x;
					g_aPropModel_02.bUseCheck = true;
				}
				g_aPropModel_02.pos.y  += 5.0f;		// 角度 * 移動量
				//MoveShellModel02();
				g_aPropModel_02.bActive = true;
				g_aPropModel_02.nLife--;
				HitPropModel_02();
				//effect
				SetEffect(pModelBody->pos,D3DXCOLOR(255,165 ,0,255),8,70,EFFECTTYPE_NORMAL );
				if(g_aPropModel_02.nLife <= 0 )
				{
					pObstacle_BoxMpMax->bUse = false;
					g_aPropModel_02.bUse = false;
					pModelBody->time = 0;
					pProw->bUse = false;
					pProw->bProwUse = false;
					pObstacle_BoxMpLife->bUse = false;
					pObstacle_BoxMp->bUse = false;
					pObstacle_BoxMpLife->time =0;
				}
				break;

			default:
			break;
			
		
		}
			break;

		case PROWT_3:
			g_aPropModel_01.bUse = false;
			g_aPropModel_02.bUse = false;
			if(GetKeyboardTrigger ( DIK_SPACE ))
			{
				g_aPropModel_03.state = PROWT_BULLET;
				SetPropModel_03( pModelBody->pos, pModelBody->rot, 80 );
			}
			switch(g_aPropModel_03.state)
			{
			case PROWT_SPIN:
				g_aPropModel_03.bUse = true;
				RotMove_03();
				break;
				
			case PROWT_BULLET:
				pModelBody->fPosMove = (POSMOVE_MODELBODY + POSMOVE_PROPMODEL_SPEED );
				g_aPropModel_03.bUse = true;
				g_aPropModel_03.nLife--;
				RotMove_03();
				//effect
				SetEffect(g_aPropModel_03.pos,D3DXCOLOR(0,0,255,255),8,70,EFFECTTYPE_NORMAL );
				//effect
				SetEffect(pModelBody->pos,D3DXCOLOR(0,0,255,255),8,70,EFFECTTYPE_NORMAL );
				if(g_aPropModel_03.nLife <= 0 )
				{
					pObstacle_BoxMpMax->bUse = false;
					g_aPropModel_03.bUse = false;
					pProw->bUse = false;
					pProw->bProwUse = false;
					pObstacle_BoxMpLife->bUse = false;
					pObstacle_BoxMp->bUse = false;
					pObstacle_BoxMpLife->time =0;
					pModelBody->fPosMove = POSMOVE_MODELBODY ;
				}
				break;

			default:
			break;
			
				
		}
			break;

			default:
			break;
		}
	
	}
}
//================================================================================================================================================================================================
// DrawPropModel_Group関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawPropModel_Group( void )
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );


		if(g_aPropModel_01.bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aPropModel_01.mtxWorldPropModel );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aPropModel_01.scl.x, g_aPropModel_01.scl.y, g_aPropModel_01.scl.z );
		D3DXMatrixMultiply( &g_aPropModel_01.mtxWorldPropModel, &g_aPropModel_01.mtxWorldPropModel, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aPropModel_01.rot.y, g_aPropModel_01.rot.x, g_aPropModel_01.rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aPropModel_01.mtxWorldPropModel, &g_aPropModel_01.mtxWorldPropModel, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aPropModel_01.pos.x, g_aPropModel_01.pos.y, g_aPropModel_01.pos.z );
		D3DXMatrixMultiply( &g_aPropModel_01.mtxWorldPropModel, &g_aPropModel_01.mtxWorldPropModel, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aPropModel_01.mtxWorldPropModel );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aPropModel_01.pBuffMatPropModel->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aPropModel_01.nNumMatPropModel; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aPropModel_01.pMeshPropModel->DrawSubset( nCntMat );
		}
		
	}
/********************************************************************************************************************/

		if(g_aPropModel_02.bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aPropModel_02.mtxWorldPropModel );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aPropModel_02.scl.x, g_aPropModel_02.scl.y, g_aPropModel_02.scl.z );
		D3DXMatrixMultiply( &g_aPropModel_02.mtxWorldPropModel, &g_aPropModel_02.mtxWorldPropModel, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aPropModel_02.rot.y, g_aPropModel_02.rot.x, g_aPropModel_02.rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aPropModel_02.mtxWorldPropModel, &g_aPropModel_02.mtxWorldPropModel, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aPropModel_02.pos.x, g_aPropModel_02.pos.y, g_aPropModel_02.pos.z );
		D3DXMatrixMultiply( &g_aPropModel_02.mtxWorldPropModel, &g_aPropModel_02.mtxWorldPropModel, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aPropModel_02.mtxWorldPropModel );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aPropModel_02.pBuffMatPropModel->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aPropModel_02.nNumMatPropModel; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aPropModel_02.pMeshPropModel->DrawSubset( nCntMat );
		}
		
	}
/********************************************************************************************************************/

		if(g_aPropModel_03.bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aPropModel_03.mtxWorldPropModel );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aPropModel_03.scl.x, g_aPropModel_03.scl.y, g_aPropModel_03.scl.z );
		D3DXMatrixMultiply( &g_aPropModel_03.mtxWorldPropModel, &g_aPropModel_03.mtxWorldPropModel, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aPropModel_03.rot.y, g_aPropModel_03.rot.x, g_aPropModel_03.rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aPropModel_03.mtxWorldPropModel, &g_aPropModel_03.mtxWorldPropModel, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aPropModel_03.pos.x, g_aPropModel_03.pos.y, g_aPropModel_03.pos.z );
		D3DXMatrixMultiply( &g_aPropModel_03.mtxWorldPropModel, &g_aPropModel_03.mtxWorldPropModel, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aPropModel_03.mtxWorldPropModel );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aPropModel_03.pBuffMatPropModel->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aPropModel_03.nNumMatPropModel; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aPropModel_03.pMeshPropModel->DrawSubset( nCntMat );
		}
		
	}
	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetPropModel_01関数
// 引数 void
// 戻り値 
// 説明 PropModel_01を取得する。
//================================================================================================================================================================================================
PROPMODELGROUP *GetPropModel_01( void )
{
	return &g_aPropModel_01;
}
//================================================================================================================================================================================================
// *GetPropModel_02関数
// 引数 void
// 戻り値 
// 説明 PropModel_02を取得する。
//================================================================================================================================================================================================
PROPMODELGROUP *GetPropModel_02( void )
{
	return &g_aPropModel_02;
}
//================================================================================================================================================================================================
// *GetPropModel_03関数
// 引数 void
// 戻り値 
// 説明 PropModel_03を取得する。
//================================================================================================================================================================================================
PROPMODELGROUP *GetPropModel_03( void )
{
	return &g_aPropModel_03;
}
//================================================================================================================================================================================================
// RotMove_01関数
// 引数 void
// 戻り値 
// 説明 ツール1回転用
//================================================================================================================================================================================================
void RotMove_01 (void)
{
	//モデルを取得
	MODELBODY		*pModelBody		= GetModelBody();

		if(g_aPropModel_01.bUse == true)
			{
				g_aPropModel_01.pos.x = pModelBody->pos.x + g_aPropModel_01.propR * cosf( g_aPropModel_01.fAngle );
				g_aPropModel_01.pos.z = pModelBody->pos.z + g_aPropModel_01.propR * sinf( g_aPropModel_01.fAngle );
				g_aPropModel_01.pos.y = pModelBody->pos.y;
				g_aPropModel_01.fAngle += 4.0f * D3DX_PI / 120.0f;					// 角の弧を増える
				if ( g_aPropModel_01.fAngle > ( 2.0f * D3DX_PI ) ) 
					{
						g_aPropModel_01.fAngle -= 2.0f * D3DX_PI;
					}
			}
	
}
//================================================================================================================================================================================================
// RotMove_02関数
// 引数 void
// 戻り値 
// 説明 ツール2回転用
//================================================================================================================================================================================================
void RotMove_02 (void)
{
	//モデルを取得
	MODELBODY		*pModelBody		= GetModelBody();

		if(g_aPropModel_02.bUse == true)
			{
				g_aPropModel_02.pos.x = pModelBody->pos.x + g_aPropModel_02.propR * cosf( g_aPropModel_02.fAngle );
				g_aPropModel_02.pos.z = pModelBody->pos.z + g_aPropModel_02.propR * sinf( g_aPropModel_02.fAngle );
				g_aPropModel_02.pos.y = pModelBody->pos.y;
				g_aPropModel_02.fAngle += 4.0f * D3DX_PI / 120.0f;					// 角の弧を増える
				if ( g_aPropModel_02.fAngle > ( 2.0f * D3DX_PI ) ) 
					{
						g_aPropModel_02.fAngle -= 2.0f * D3DX_PI;
					}
			}
	
}

//================================================================================================================================================================================================
// RotMove_03関数
// 引数 void
// 戻り値 
// 説明 ツール3回転用
//================================================================================================================================================================================================
void RotMove_03 (void)
{
	//モデルを取得
	MODELBODY		*pModelBody		= GetModelBody();

		if(g_aPropModel_03.bUse == true)
			{
				g_aPropModel_03.pos.x = pModelBody->pos.x + g_aPropModel_03.propR * cosf( g_aPropModel_03.fAngle );
				g_aPropModel_03.pos.z = pModelBody->pos.z + g_aPropModel_03.propR * sinf( g_aPropModel_03.fAngle );
				g_aPropModel_03.pos.y = pModelBody->pos.y;
				g_aPropModel_03.fAngle += 4.0f * D3DX_PI / 120.0f;					// 角の弧を増える
				if ( g_aPropModel_03.fAngle > ( 2.0f * D3DX_PI ) ) 
					{
						g_aPropModel_03.fAngle -= 2.0f * D3DX_PI;
					}
			}
	
}
void SetPropModel_01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{

		if(g_aPropModel_01.bUse == false )
		{
			// 位置の設定
			g_aPropModel_01.pos = pos;

			// 移動量の設定
			g_aPropModel_01.rot = rot;

			// 寿命の設定
			g_aPropModel_01.nLife = nLife;

			// ツールを使用状態にする
			g_aPropModel_01.bUse = true;
			
		}
	
}
void SetPropModel_02( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{

		if(g_aPropModel_02.bUse == false )
		{
			// 位置の設定
			g_aPropModel_02.pos = pos;

			// 移動量の設定
			g_aPropModel_02.rot = rot;

			// 寿命の設定
			g_aPropModel_02.nLife = nLife;

			// ツールを使用状態にする
			g_aPropModel_02.bUse = true;
			
		}
	
}
void SetPropModel_03( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{

		if(g_aPropModel_03.bUse == false )
		{
			// 位置の設定
			g_aPropModel_03.pos = pos;

			// 移動量の設定
			g_aPropModel_03.rot = rot;

			// 寿命の設定
			g_aPropModel_03.nLife = nLife;

			// ツールを使用状態にする
			g_aPropModel_03.bUse = true;
			
		}
	
}
//================================================================================================================================================================================================
// HitPropModel_01関数
// 引数 void
// 戻り値 
// 説明 ツール1当たり判定用
//================================================================================================================================================================================================
void HitPropModel_01(void)
{
	ENEMY *pEnemy =GetEnemy();
	OBSTACLE *pObstacle_Box = GetObstacle_Box();
	for( int nCntBox = 0; nCntBox < MAX_OBSTACLE_BOX; nCntBox++ )
		{
			if(
				(pObstacle_Box+nCntBox)->pos.z < g_aPropModel_01.pos.z+ g_aPropModel_01.Collisoin
				&& (pObstacle_Box+nCntBox)->pos.x >  g_aPropModel_01.pos.x- g_aPropModel_01.Collisoin
				&& (pObstacle_Box+nCntBox)->pos.x <  g_aPropModel_01.pos.x+ g_aPropModel_01.Collisoin
				&& (pObstacle_Box+nCntBox)->pos.z > g_aPropModel_01.pos.z- g_aPropModel_01.Collisoin
				&& (pObstacle_Box+nCntBox)->bUse == true 
				)
			{
				g_aPropModel_01.nLife = 0;
				SetExplosion( (pObstacle_Box+nCntBox)->pos );
				(pObstacle_Box+nCntBox)->bUse = false;
				SetMoney(D3DXVECTOR3((pObstacle_Box+nCntBox)->pos.x,30.0f,(pObstacle_Box+nCntBox)->pos.z),(pObstacle_Box+nCntBox)->rot,800 );
			}
		}
}

//================================================================================================================================================================================================
// HitPropModel_02関数
// 引数 void
// 戻り値 
// 説明 ツール1当たり判定用
//================================================================================================================================================================================================
void HitPropModel_02(void)
{
	ENEMY *pEnemy =GetEnemy();
	BULLET *pBullet = GetBullet();
	if(g_aPropModel_02.pos.z < pEnemy->pos.z+ pEnemy->Collisoin
		&& g_aPropModel_02.pos.x >  pEnemy->pos.x- pEnemy->Collisoin
		&& g_aPropModel_02.pos.x <  pEnemy->pos.x+ pEnemy->Collisoin
		&& g_aPropModel_02.pos.z > pEnemy->pos.z- pEnemy->Collisoin
		&& g_aPropModel_02.bUse == true )
	{
		g_aPropModel_02.nLife = 0;
		SetExplosion( pEnemy->pos );
	}
}
// 砲弾の移動
int MoveShellModel01( void )
{

	if ( g_aPropModel_01.bActive == true)
	{
		g_aPropModel_01.pos.x += g_aPropModel_01.v3Vel.x;
		g_aPropModel_01.pos.y += g_aPropModel_01.v3Vel.y;
		g_aPropModel_01.pos.z += g_aPropModel_01.v3Vel.z;
		g_aPropModel_01.v3Vel.y += -GR;
		if (g_aPropModel_01.pos.y < 1.0f )
		{
			g_aPropModel_01.bActive = false;
		//	g_aPropModel_01.nLife = 0;
		}
		
	}


	return 0;
}
// 砲弾の移動
int MoveShellModel02( void )
{

	if ( g_aPropModel_02.bActive == true)
	{
		g_aPropModel_02.pos.x += g_aPropModel_02.v3Vel.x;
		g_aPropModel_02.pos.y += g_aPropModel_02.v3Vel.y;
		g_aPropModel_02.pos.z += g_aPropModel_02.v3Vel.z;
		g_aPropModel_02.v3Vel.y += -GR;
		if (g_aPropModel_02.pos.y <1.0f )
		{
			g_aPropModel_02.bActive = false;
		//	g_aPropModel_02.nLife = 0;
		}
	}

	return 0;
}