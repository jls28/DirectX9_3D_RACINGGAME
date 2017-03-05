/*******************************************************************************
* タイトル： 敵モデル描画関数
* ファイル名： model.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/05
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/

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
#include "enemy.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define ENEMY_INERTIA_MOVE	( 0.029f )					//慣性調整係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void EnemyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY );
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
ENEMY g_aEnemy[ MAX_ENEMY ];		// モデルの情報
int RandEnemy;
//================================================================================================================================================================================================
// InitEnemy関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitEnemy( void )
{

	RandEnemy = 0;
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++ )
	{
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\enemy.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aEnemy[ nCntEnemy ].pBuffMat,		// マテリアル情報
									   NULL,
									   &g_aEnemy[ nCntEnemy ].nNumMat,			// マテリアル数
									   &g_aEnemy[ nCntEnemy ].pMesh ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}

		// モデルの初期設定
		g_aEnemy[ nCntEnemy ].pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].scl = D3DXVECTOR3( 5.0f,  5.0f, 5.0f );
		g_aEnemy[ nCntEnemy ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].fPosMove = POSMOVE_ENEMY;
		g_aEnemy[ nCntEnemy ].time = 0;

		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aEnemy[ nCntEnemy ].pMesh->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aEnemy[ nCntEnemy ].pMesh->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aEnemy[ nCntEnemy ].pMesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aEnemy[ nCntEnemy ].Min.x )		g_aEnemy[ nCntEnemy ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aEnemy[ nCntEnemy ].Max.x )		g_aEnemy[ nCntEnemy ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aEnemy[ nCntEnemy ].Min.y )		g_aEnemy[ nCntEnemy ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aEnemy[ nCntEnemy ].Max.y )		g_aEnemy[ nCntEnemy ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aEnemy[ nCntEnemy ].Min.z )		g_aEnemy[ nCntEnemy ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aEnemy[ nCntEnemy ].Max.z )		g_aEnemy[ nCntEnemy ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aEnemy[ nCntEnemy ].pMesh->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		g_aEnemy[ nCntEnemy ].Size.x = ( fabs( g_aEnemy[ nCntEnemy ].Min.x ) + fabs( g_aEnemy[ nCntEnemy ].Max.x ) ) / 2;
		g_aEnemy[ nCntEnemy ].Size.y = ( fabs( g_aEnemy[ nCntEnemy ].Min.y ) + fabs( g_aEnemy[ nCntEnemy ].Max.y ) ) / 2;
		g_aEnemy[ nCntEnemy ].Size.z = ( fabs( g_aEnemy[ nCntEnemy ].Min.z ) + fabs( g_aEnemy[ nCntEnemy ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aEnemy[ nCntEnemy ].Size.x < g_aEnemy[ nCntEnemy ].Size.z )
		{
			g_aEnemy[ nCntEnemy ].Collisoin = g_aEnemy[ nCntEnemy ].Size.z;
		}
		else
		{
			g_aEnemy[ nCntEnemy ].Collisoin = g_aEnemy[ nCntEnemy ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aEnemy[ nCntEnemy ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitEnemy関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitEnemy( void )
{
	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++ )
	{
		// メッシュ情報の開放
		if( g_aEnemy[ nCntEnemy ].pMesh != NULL )
		{
			g_aEnemy[ nCntEnemy ].pMesh->Release();
			g_aEnemy[ nCntEnemy ].pMesh = NULL;
		}

		// バッファの開放
		if( g_aEnemy[ nCntEnemy ].pBuffMat != NULL )
		{
			g_aEnemy[ nCntEnemy ].pBuffMat->Release();
			g_aEnemy[ nCntEnemy ].pBuffMat = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateEnemy関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateEnemy( void )
{

//	srand((unsigned)time(NULL));
	RandEnemy = rand()%25+41;		//乱数
	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropEnemy_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropEnemy_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropEnemy_03 = GetPropModel_03 ();


	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	// 弾の発射
	//if( GetKeyboardTrigger( DIK_SPACE ) )
	//{
	//	SetBullet( g_aEnemy[ nCntEnemy ].pos, g_aEnemy[ nCntEnemy ].rot, LIFE_BULLET );
	//}

	//Enemy八方向移動
	EnemyMove(
			&g_aEnemy[ nCntEnemy ].rot,	//向き
			g_aEnemy[ nCntEnemy ].fPosMove,				//移動量
			DIK_UP,				//上ボタン
			DIK_DOWN,			//下ボタン
			DIK_LEFT,			//左ボタン
			DIK_RIGHT			//右ボタン
	);



	//向き角度のチェック
	if( g_aEnemy[ nCntEnemy ].rot.y > D3DX_PI )
	{
		g_aEnemy[ nCntEnemy ].rot.y		-= D3DX_PI * 2.0f;
	}
	else if( g_aEnemy[ nCntEnemy ].rot.y < - D3DX_PI )
	{
		g_aEnemy[ nCntEnemy ].rot.y		+= D3DX_PI * 2.0f;
	}


	//Y軸移動のチェック
	if( g_aEnemy[ nCntEnemy ].pos.y >= 100.0f )
	{
		g_aEnemy[ nCntEnemy ].pos.y		 = 100.0f;
	}
	else if( g_aEnemy[ nCntEnemy ].pos.y <= 1.0f )
	{
		g_aEnemy[ nCntEnemy ].pos.y		 = 1.0f;
	}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if( (pWall + WALL_FRONT)->pos.z < ( g_aEnemy[ nCntEnemy ].pos.z + g_aEnemy[ nCntEnemy ].Collisoin ) )
	//	{	// 奥の壁
	//		g_aEnemy[ nCntEnemy ].pos.z =( pWall + WALL_FRONT)->pos.z  - g_aEnemy[ nCntEnemy ].Collisoin;
	//	}
	//	else if( (pWall + WALL_BACK)->pos.z > ( g_aEnemy[ nCntEnemy ].pos.z - g_aEnemy[ nCntEnemy ].Collisoin ) )
	//	{	// 前の壁
	//		g_aEnemy[ nCntEnemy ].pos.z = (pWall + WALL_BACK)->pos.z + g_aEnemy[ nCntEnemy ].Collisoin;
	//	}
		if( (pWall + WALL_LEFT)->pos.x > ( g_aEnemy[ nCntEnemy ].pos.x - g_aEnemy[ nCntEnemy ].Collisoin ) )
		{	// 左の壁
			g_aEnemy[ nCntEnemy ].pos.x =  (pWall + WALL_LEFT)->pos.x + g_aEnemy[ nCntEnemy ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aEnemy[ nCntEnemy ].pos.x + g_aEnemy[ nCntEnemy ].Collisoin ) )
		{	// 右の壁
			g_aEnemy[ nCntEnemy ].pos.x =  (pWall + WALL_RIGHT)->pos.x - g_aEnemy[ nCntEnemy ].Collisoin;
		}
	//	if( CEILING < ( g_aEnemy[ nCntEnemy ].pos.y + g_aEnemy[ nCntEnemy ].Size.y ) )
	//	{	// 天井
	//		g_aEnemy[ nCntEnemy ].pos.y = CEILING - g_aEnemy[ nCntEnemy ].Size.y;
	//	}
		
		if( GROUND > ( g_aEnemy[ nCntEnemy ].pos.y - g_aEnemy[ nCntEnemy ].Size.y ) )
		{	// 床
			g_aEnemy[ nCntEnemy ].pos.y = GROUND + g_aEnemy[ nCntEnemy ].Size.y;
		}
		//if( pProw->bUse == true )
		//{
		//	g_aEnemy[ nCntEnemy ].time ++;
		//	if ( g_aEnemy[ nCntEnemy ].time >= (66+RandEnemy ) )
		//	{
		//		pProw->bProwUse = true;
		//		g_aEnemy[ nCntEnemy ].time = 0;
		//	}
		//}

		// ツールとの衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
		{

		if((pProp+nCntProp)->pos.z < g_aEnemy[ nCntEnemy ].pos.z+ g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->pos.x >  g_aEnemy[ nCntEnemy ].pos.x- g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->pos.x <  g_aEnemy[ nCntEnemy ].pos.x+ g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->pos.z > g_aEnemy[ nCntEnemy ].pos.z- g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->bUse == true )
		{
			//(pProp+nCntProp)->bUse = false;
		//	pProw->bUse = true;
		//	pProw->bProwUse = false;
		//	pPropMp->bUse = true;
		//	pPropMpLife->bUse = true;
			
		}

		}
		//影
		SetShadow( g_aEnemy[ nCntEnemy ].pos, 20.0f, 20.0f, 0, true );

		//effect
		//SetEffect(g_aEnemy[ nCntEnemy ].pos,D3DXCOLOR(200,0,152,255),10,70,EFFECTYPE_COLOR );
	}

}

//================================================================================================================================================================================================
// DrawEnemy関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawEnemy( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aEnemy[ nCntEnemy ].mtxWorld );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aEnemy[ nCntEnemy ].scl.x, g_aEnemy[ nCntEnemy ].scl.y, g_aEnemy[ nCntEnemy ].scl.z );
		D3DXMatrixMultiply( &g_aEnemy[ nCntEnemy ].mtxWorld, &g_aEnemy[ nCntEnemy ].mtxWorld, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aEnemy[ nCntEnemy ].rot.y, g_aEnemy[ nCntEnemy ].rot.x, g_aEnemy[ nCntEnemy ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aEnemy[ nCntEnemy ].mtxWorld, &g_aEnemy[ nCntEnemy ].mtxWorld, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aEnemy[ nCntEnemy ].pos.x, g_aEnemy[ nCntEnemy ].pos.y, g_aEnemy[ nCntEnemy ].pos.z );
		D3DXMatrixMultiply( &g_aEnemy[ nCntEnemy ].mtxWorld, &g_aEnemy[ nCntEnemy ].mtxWorld, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aEnemy[ nCntEnemy ].mtxWorld );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aEnemy[ nCntEnemy ].pBuffMat->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aEnemy[ nCntEnemy ].nNumMat; nCntMat++ )
		{
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない。これがないと前に使われたテクスチャの設定が生きていて、モデルが暗くなったりする。

			// メッシュの描画
			g_aEnemy[ nCntEnemy ].pMesh->DrawSubset( nCntMat );
		}
	}

	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetEnemy関数
// 引数 void
// 戻り値 
// 説明 Enemyを取得する。
//================================================================================================================================================================================================
ENEMY *GetEnemy( void )
{
	return &g_aEnemy[ 0 ];
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
void EnemyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{

	ENEMY *pEnemy = GetEnemy();
	pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pEnemy -> fPosMove;
	/*自動移動*/
	pEnemy -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左上移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右上移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else											//前移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
			pEnemy->bAutoRot = true;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左下移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右下移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else											//後移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + 0.0f;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
		pEnemy->bAutoRot = true;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//左上移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//左下移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else											//左移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
		pEnemy->bAutoRot = true;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//右上移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//右下移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else											//右移動
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
			pEnemy->bAutoRot = true;
	}
	else 
	{
			pEnemy->bAutoRot = false;
	}

	//座標を更新（慣性）
	pEnemy -> pos.x += ( pEnemy->OldPos.x - pEnemy -> pos.x ) * ENEMY_INERTIA_MOVE;
	pEnemy -> pos.z += ( pEnemy->OldPos.z - pEnemy -> pos.z ) * ENEMY_INERTIA_MOVE;
}
