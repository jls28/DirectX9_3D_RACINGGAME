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
#include "modelbody.h"
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
#include "modellegL.h"
#include "modellegR.h"
#include "runleg.h"
#include "money.h"
#include "score.h"
#include "obstacle.h"
#include "boxscore.h"
#include "fade.h"
#include "boxscore.h"
#include "score.h"
#include "explosion.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MODELBODY_INERTIA_MOVE	( 0.025f )					//慣性調整係数
#define GR							0.002f				// 重力加速度
#define SHELL_FIRST_VEL				0.15f				// 砲弾初速
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void ModelBodyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY );
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MODELBODY g_aModelBody[ MAX_MODELBODY ];		// モデルの情報

//================================================================================================================================================================================================
// InitModelBody関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitModelBody( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\model.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aModelBody[ nCntModelBody ].pBuffMatModelBody,		// マテリアル情報
									   NULL,
									   &g_aModelBody[ nCntModelBody ].nNumMatModelBody,			// マテリアル数
									   &g_aModelBody[ nCntModelBody ].pMeshModelBody ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aModelBody[ nCntModelBody ].pos = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].OldPos = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].rot = D3DXVECTOR3( 0.0f,  3.14f, 0.0f );
		g_aModelBody[ nCntModelBody ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelBody[ nCntModelBody ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].fPosMove = POSMOVE_MODELBODY;
		g_aModelBody[ nCntModelBody ].time = 0;
		g_aModelBody[ nCntModelBody ].Rand = 0;
		g_aModelBody[ nCntModelBody ].bKeyUse = false;
		g_aModelBody[ nCntModelBody ].bJump = false;
		g_aModelBody[ nCntModelBody ].bMove = false;
		g_aModelBody[ nCntModelBody ].bUseCheck = false;
		g_aModelBody[ nCntModelBody ].bUseCheckCat = false;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aModelBody[ nCntModelBody ].pMeshModelBody->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aModelBody[ nCntModelBody ].pMeshModelBody->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aModelBody[ nCntModelBody ].pMeshModelBody->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelBody[ nCntModelBody ].Min.x )		g_aModelBody[ nCntModelBody ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aModelBody[ nCntModelBody ].Max.x )		g_aModelBody[ nCntModelBody ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aModelBody[ nCntModelBody ].Min.y )		g_aModelBody[ nCntModelBody ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aModelBody[ nCntModelBody ].Max.y )		g_aModelBody[ nCntModelBody ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aModelBody[ nCntModelBody ].Min.z )		g_aModelBody[ nCntModelBody ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aModelBody[ nCntModelBody ].Max.z )		g_aModelBody[ nCntModelBody ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aModelBody[ nCntModelBody ].pMeshModelBody->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aModelBody[ nCntModelBody ].Size.x = ( fabs( g_aModelBody[ nCntModelBody ].Min.x ) + fabs( g_aModelBody[ nCntModelBody ].Max.x ) ) / 2;
		g_aModelBody[ nCntModelBody ].Size.y = ( fabs( g_aModelBody[ nCntModelBody ].Min.y ) + fabs( g_aModelBody[ nCntModelBody ].Max.y ) ) / 2;
		g_aModelBody[ nCntModelBody ].Size.z = ( fabs( g_aModelBody[ nCntModelBody ].Min.z ) + fabs( g_aModelBody[ nCntModelBody ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aModelBody[ nCntModelBody ].Size.x < g_aModelBody[ nCntModelBody ].Size.z )
		{
			g_aModelBody[ nCntModelBody ].Collisoin = g_aModelBody[ nCntModelBody ].Size.z;
		}
		else
		{
			g_aModelBody[ nCntModelBody ].Collisoin = g_aModelBody[ nCntModelBody ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelBody[ nCntModelBody ].bUse = false;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelBody関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitModelBody( void )
{
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++ )
	{
		// メッシュ情報の開放
		if( g_aModelBody[ nCntModelBody ].pMeshModelBody != NULL )
		{
			g_aModelBody[ nCntModelBody ].pMeshModelBody->Release();
			g_aModelBody[ nCntModelBody ].pMeshModelBody = NULL;
		}

		// バッファの開放
		if( g_aModelBody[ nCntModelBody ].pBuffMatModelBody != NULL )
		{
			g_aModelBody[ nCntModelBody ].pBuffMatModelBody->Release();
			g_aModelBody[ nCntModelBody ].pBuffMatModelBody = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelBody関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateModelBody( void )
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
	PROPMODELGROUP *pPropModelBody_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelBody_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelBody_03 = GetPropModel_03 ();

	MODELLEGL *pModelLegL = GetModelLegL ();

	MODELLEGR *pModelLegR = GetModelLegR ();

	RUNLEG *pRunleg = GetRunLeg();

	MONEY *pMoney = GetMoney();

	OBSTACLE *pObstacle_Cat_01 = GetObstacle_Cat_01();

	SCORE *pScoreCheck = GetScore();
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++)
	{
		if(g_aModelBody[ nCntModelBody ].bUse == true)
		{
			//SetExplosion(g_aModelBody[ nCntModelBody ].pos);
	g_aModelBody[ nCntModelBody ].Rand = rand()%25+41;		//乱数
	//ModelBody八方向移動
	ModelBodyMove(
			&camera.rot,	//向き
			g_aModelBody[ nCntModelBody ].fPosMove,				//移動量
			DIK_UP,				//上ボタン
			DIK_DOWN,			//下ボタン
			DIK_LEFT,			//左ボタン
			DIK_RIGHT			//右ボタン
	);

		//ModelBody旋回
		//if( GetKeyboardPress( DIK_LSHIFT ) )		//左旋回
		//{
		//	g_aModelBody[ nCntModelBody ].rot.y		-= D3DX_PI * 0.025f;
		//	g_aModelBody[ nCntModelBody ].OldRot.y	 = g_aModelBody[ nCntModelBody ].rot.y;
		//}
		//else if( GetKeyboardPress( DIK_RSHIFT ) )	//右旋回
		//{
		//g_aModelBody[ nCntModelBody ].rot.y		+= D3DX_PI * 0.025f;
		//g_aModelBody[ nCntModelBody ].OldRot.y	 = g_aModelBody[ nCntModelBody ].rot.y;
		//}

	//向き角度のチェック
	if( g_aModelBody[ nCntModelBody ].rot.y > D3DX_PI )
	{
		g_aModelBody[ nCntModelBody ].rot.y		-= D3DX_PI * 2.0f;
	}
	else if( g_aModelBody[ nCntModelBody ].rot.y < - D3DX_PI )
	{
		g_aModelBody[ nCntModelBody ].rot.y		+= D3DX_PI * 2.0f;
	}

	//Y軸移動操作
	//if( GetKeyboardPress( DIK_I ) )
	//{
	//	g_aModelBody[ nCntModelBody ].pos.y		+= g_aModelBody[ nCntModelBody ].fPosMove;
	//}
	//else if( GetKeyboardPress( DIK_K ) )
	//{
	//	g_aModelBody[ nCntModelBody ].pos.y		-= g_aModelBody[ nCntModelBody ].fPosMove;
	//}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelBody[ nCntModelBody ].OldPos.x - g_aModelBody[ nCntModelBody ].Collisoin ) )
		{	// 左の壁
			g_aModelBody[ nCntModelBody ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelBody[ nCntModelBody ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelBody[ nCntModelBody ].OldPos.x + g_aModelBody[ nCntModelBody ].Collisoin ) )
		{	// 右の壁
			g_aModelBody[ nCntModelBody ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelBody[ nCntModelBody ].Collisoin;
		}

		if(( g_aModelBody[ nCntModelBody ].OldPos.z - g_aModelBody[ nCntModelBody ].Collisoin ) >= 20550.0f )
		{	// 前の壁
			  g_aModelBody[ nCntModelBody ].OldPos.z = 20550.0f + g_aModelBody[ nCntModelBody ].Collisoin;
			  //if(pScoreCheck->bCheck == true)
			  //{
			  SetFade(FADE_OUT,MODE_RESULT);
	/*		  }*/
		}
		else if( -300.0f >= ( g_aModelBody[ nCntModelBody ].OldPos.z + g_aModelBody[ nCntModelBody ].Collisoin ) )
		{	// 奥の壁
			g_aModelBody[ nCntModelBody ].OldPos.z =-300.0f  - g_aModelBody[ nCntModelBody ].Collisoin;
		}
		if( GROUND >  g_aModelBody[ nCntModelBody ].OldPos.y)
		{	// 床
			g_aModelBody[ nCntModelBody ].OldPos.y = 1.0f;
		}
		if( pProw->bUse == true )
		{
			g_aModelBody[ nCntModelBody ].time ++;
			if ( g_aModelBody[ nCntModelBody ].time >= (66+g_aModelBody[ nCntModelBody ].Rand ) )
			{
				pProw->bProwUse = true;
				g_aModelBody[ nCntModelBody ].time = 0;
			}
		}

		// ツールとの衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
		{

		if((pProp+nCntProp)->pos.z < g_aModelBody[ nCntModelBody ].pos.z+ g_aModelBody[ nCntModelBody ].Collisoin
			&& ((pProp+nCntProp)->pos.x+30.0f) >  g_aModelBody[ nCntModelBody ].pos.x- g_aModelBody[ nCntModelBody ].Collisoin
			&& ((pProp+nCntProp)->pos.x-30.0f) <  g_aModelBody[ nCntModelBody ].pos.x+ g_aModelBody[ nCntModelBody ].Collisoin
			&& (pProp+nCntProp)->pos.z > g_aModelBody[ nCntModelBody ].pos.z- g_aModelBody[ nCntModelBody ].Collisoin
			&& (pProp+nCntProp)->bUse == true )
		{
			(pProp+nCntProp)->bUse = false;
			pProw->bUse = true;
			pProw->bProwUse = false;
			pPropMp->bUse = true;
			pPropMpLife->bUse = true;
			InitPropModel_Group();
			
		}

		}
		// Moneyとの衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
		{

			if((pMoney+nCntMoney)->pos.z < g_aModelBody[ nCntModelBody ].pos.z+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->pos.x >  g_aModelBody[ nCntModelBody ].pos.x- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->pos.x <  g_aModelBody[ nCntModelBody ].pos.x+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->pos.z > g_aModelBody[ nCntModelBody ].pos.z- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->bUse == true )
			{
				(pMoney+nCntMoney)->bUse = false;
				if(!g_aModelBody[ nCntModelBody ].bUseCheck )
				{
					AddScore(500);
					g_aModelBody[ nCntModelBody ].bUseCheck = true;
				}
			}
			else
			{
				g_aModelBody[ nCntModelBody ].bUseCheck = false;
			}
		}
		// Cat1との衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntCat_01 = 0; nCntCat_01 < MAX_OBSTACLE_CAT_01; nCntCat_01++ )
		{

			if((pObstacle_Cat_01+nCntCat_01)->pos.z < g_aModelBody[ nCntModelBody ].pos.z+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->pos.x >  g_aModelBody[ nCntModelBody ].pos.x- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->pos.x <  g_aModelBody[ nCntModelBody ].pos.x+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->pos.z > g_aModelBody[ nCntModelBody ].pos.z- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->bUse == true 
				)
			{
				(pObstacle_Cat_01+nCntCat_01)->bRot = true;

				if(!g_aModelBody[ nCntModelBody ].bUseCheckCat && (pObstacle_Cat_01+nCntCat_01)->bCatRotCheck == false)
				{
					AddScore(-1000);
					g_aModelBody[ nCntModelBody ].bUseCheckCat = true;
					(pObstacle_Cat_01+nCntCat_01)->bCatRotCheck = true; 
				}
			}
			else 
			{
				g_aModelBody[ nCntModelBody ].bUseCheckCat = false;
				(pObstacle_Cat_01+nCntCat_01)->bCatRotCheck = false; 
			}
			
		}
		//影
		SetShadow( g_aModelBody[ nCntModelBody ].pos, 20.0f, 20.0f, 0, true );

		//effect
		SetEffect(g_aModelBody[ nCntModelBody ].pos,D3DXCOLOR(200,0,152,255),10,70,EFFECTYPE_COLOR );
	}
	}
}

//================================================================================================================================================================================================
// DrawModelBody関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawModelBody( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );
	// レンダーステートの設定（zテスト）
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z値の更新
	// レンダーステートの設定（アルファテスト）
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// アルファ値を判定して、該当のピクセルを描画するようにする。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// 下の値よりアルファ値が大きければ描画する。
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// アルファ値。0で透明な部分。
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aModelBody[ nCntModelBody ].scl.x, g_aModelBody[ nCntModelBody ].scl.y, g_aModelBody[ nCntModelBody ].scl.z );
		D3DXMatrixMultiply( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelBody[ nCntModelBody ].rot.y, g_aModelBody[ nCntModelBody ].rot.x, g_aModelBody[ nCntModelBody ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aModelBody[ nCntModelBody ].pos.x, g_aModelBody[ nCntModelBody ].pos.y, g_aModelBody[ nCntModelBody ].pos.z );
		D3DXMatrixMultiply( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aModelBody[ nCntModelBody ].pBuffMatModelBody->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelBody[ nCntModelBody ].nNumMatModelBody; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aModelBody[ nCntModelBody ].pMeshModelBody->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelBody関数
// 引数 void
// 戻り値 
// 説明 ModelBodyを取得する。
//================================================================================================================================================================================================
MODELBODY *GetModelBody( void )
{
	return &g_aModelBody[ 0 ];
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
void ModelBodyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELBODY *pModelBody = GetModelBody();
	pModelBody -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else											//前移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
		pModelBody->bKeyUse = true;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else											//後移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + 0.0f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
		pModelBody->bKeyUse = true;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//左上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//左下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else											//左移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
		pModelBody->bKeyUse = true;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//右上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//右下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//右移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
	}
	else 
	{
			pModelBody->bAutoRot = false;
			pModelBody->bKeyUse = false;
	}

	//座標を更新（慣性）
	pModelBody -> pos.x += ( pModelBody->OldPos.x - pModelBody -> pos.x ) * MODELBODY_INERTIA_MOVE;
	pModelBody -> pos.z += ( pModelBody->OldPos.z - pModelBody -> pos.z ) * MODELBODY_INERTIA_MOVE;
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
void ModelBodyMovejoystick( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELBODY *pModelBody = GetModelBody();
	pModelBody -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetJoysticksTrigger( UP_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//左上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//右上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else											//前移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
			pModelBody->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( DOWN_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//左下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//右下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//後移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + 0.0f;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( LEFT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//左上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//左下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//左移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( RIGHT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//右上移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//右下移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//右移動
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
			pModelBody->bAutoRot = true;
	}
	else 
	{
			pModelBody->bAutoRot = false;
	}
	//座標を更新（慣性）
	//pModelBody -> pos.x += ( pModelBody->OldPos.x - pModelBody -> pos.x ) * MODELBODY_INERTIA_MOVE;
	//pModelBody -> pos.z += ( pModelBody->OldPos.z - pModelBody -> pos.z ) * MODELBODY_INERTIA_MOVE;
}
void ModelJump(void)
{
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++)
	{

		if(g_aModelBody[ nCntModelBody ].bJump == true)
		{
			g_aModelBody[ nCntModelBody ].vel = D3DXVECTOR3( SHELL_FIRST_VEL * cosf( g_aModelBody[ nCntModelBody ].rot.y),
								  SHELL_FIRST_VEL * sinf(g_aModelBody[ nCntModelBody ].rot.y ),
								  SHELL_FIRST_VEL * cosf( g_aModelBody[ nCntModelBody ].rot.y ));
			g_aModelBody[ nCntModelBody ].pos.x += g_aModelBody[ nCntModelBody ].vel.x;
			g_aModelBody[ nCntModelBody ].pos.y += g_aModelBody[ nCntModelBody ].vel.y;
			g_aModelBody[ nCntModelBody ].pos.z += g_aModelBody[ nCntModelBody ].vel.z;
			g_aModelBody[ nCntModelBody ].vel.y -= GR;
		}
		if(g_aModelBody[ nCntModelBody ].pos.y >= 80.0f)
		{
			g_aModelBody[ nCntModelBody ].bJump = false;
		}
	}
}