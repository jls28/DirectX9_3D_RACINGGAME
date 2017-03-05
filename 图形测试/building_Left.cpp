/*******************************************************************************
* タイトル： 建物描画関数
* ファイル名： building_Left.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/11
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
//2015/11/20/14:09:37 // 建物の移動 //
/*******************************************************************************
		インクルードファイル
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "building_Left.h"
#include "meshwall.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
BUILDING_LEFT g_aBuilding_Left[MAX_BUILDING_LEFT];		// 建物の情報

//================================================================================================================================================================================================
// InitBuilding_Left関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitBuilding_Left( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESHWALL *pWall = GetMeshWall();
		for( int nCntBuilding_Left = 0; nCntBuilding_Left < MAX_BUILDING_LEFT; nCntBuilding_Left++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\building_Left.png",&g_aBuilding_Left[nCntBuilding_Left].pTextureBuilding_Left);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\building_Left.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left,		// マテリアル情報
									   NULL,
									   &g_aBuilding_Left[nCntBuilding_Left].nNumMatBuilding_Left,			// マテリアル数
									   &g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aBuilding_Left[nCntBuilding_Left].Min.x )		g_aBuilding_Left[nCntBuilding_Left].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aBuilding_Left[nCntBuilding_Left].Max.x )		g_aBuilding_Left[nCntBuilding_Left].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aBuilding_Left[nCntBuilding_Left].Min.y )		g_aBuilding_Left[nCntBuilding_Left].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aBuilding_Left[nCntBuilding_Left].Max.y )		g_aBuilding_Left[nCntBuilding_Left].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aBuilding_Left[nCntBuilding_Left].Min.z )		g_aBuilding_Left[nCntBuilding_Left].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aBuilding_Left[nCntBuilding_Left].Max.z )		g_aBuilding_Left[nCntBuilding_Left].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->UnlockVertexBuffer();

		// 建物の半径の設定。絶対値をabs関数で求める。
		g_aBuilding_Left[nCntBuilding_Left].Size.x = ( fabs( g_aBuilding_Left[nCntBuilding_Left].Min.x ) + fabs( g_aBuilding_Left[nCntBuilding_Left].Max.x ) ) / 2;
		g_aBuilding_Left[nCntBuilding_Left].Size.y = ( fabs( g_aBuilding_Left[nCntBuilding_Left].Min.y ) + fabs( g_aBuilding_Left[nCntBuilding_Left].Max.y ) ) / 2;
		g_aBuilding_Left[nCntBuilding_Left].Size.z = ( fabs( g_aBuilding_Left[nCntBuilding_Left].Min.z ) + fabs( g_aBuilding_Left[nCntBuilding_Left].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aBuilding_Left[nCntBuilding_Left].Size.x < g_aBuilding_Left[nCntBuilding_Left].Size.z )
		{
			g_aBuilding_Left[nCntBuilding_Left].Collisoin = g_aBuilding_Left[nCntBuilding_Left].Size.z;
		}
		else
		{
			g_aBuilding_Left[nCntBuilding_Left].Collisoin = g_aBuilding_Left[nCntBuilding_Left].Size.x;
		}
		g_aBuilding_Left[nCntBuilding_Left].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aBuilding_Left[nCntBuilding_Left].Size.x,  0.0f, g_aBuilding_Left[nCntBuilding_Left].pos.z + (g_aBuilding_Left[nCntBuilding_Left].Size.z * nCntBuilding_Left)*2);
		g_aBuilding_Left[nCntBuilding_Left].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Left[nCntBuilding_Left].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aBuilding_Left[nCntBuilding_Left].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Left[nCntBuilding_Left].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );

		g_aBuilding_Left[nCntBuilding_Left].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitBuilding_Left関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitBuilding_Left( void )
{
	for( int nCntBuilding_Left = 0; nCntBuilding_Left <MAX_BUILDING_LEFT; nCntBuilding_Left++ )
	{
		// メッシュ情報の開放
		if( g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left != NULL )
		{
			g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->Release();
			g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left = NULL;
		}

		// バッファの開放
		if( g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left != NULL )
		{
			g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left->Release();
			g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateBuilding_Left関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateBuilding_Left( void )
{

}
//================================================================================================================================================================================================
// DrawBuilding_Left関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawBuilding_Left( void )
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
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(4, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		for( int nCntBuilding_Left = 0; nCntBuilding_Left <MAX_BUILDING_LEFT; nCntBuilding_Left++ )
	{
		if(g_aBuilding_Left[nCntBuilding_Left].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aBuilding_Left[nCntBuilding_Left].scl.x, g_aBuilding_Left[nCntBuilding_Left].scl.y, g_aBuilding_Left[nCntBuilding_Left].scl.z );
		D3DXMatrixMultiply( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aBuilding_Left[nCntBuilding_Left].rot.y, g_aBuilding_Left[nCntBuilding_Left].rot.x, g_aBuilding_Left[nCntBuilding_Left].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aBuilding_Left[nCntBuilding_Left].pos.x, g_aBuilding_Left[nCntBuilding_Left].pos.y, g_aBuilding_Left[nCntBuilding_Left].pos.z );
		D3DXMatrixMultiply( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &mtxTrans );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aBuilding_Left[nCntBuilding_Left].nNumMatBuilding_Left; nCntMat++ )
		{

			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aBuilding_Left[nCntMat].pTextureBuilding_Left );

			// メッシュの描画
			g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// BUILDING_LEFT *GetBuilding_Left関数
// 引数 void
// 戻り値 
// 説明 Building_Leftを取得する。
//================================================================================================================================================================================================
BUILDING_LEFT *GetBuilding_Left( void )
{
	return &g_aBuilding_Left[0];
}
