/*******************************************************************************
* タイトル： 建物SHOP描画関数
* ファイル名： Shop.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/15
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
//2015/11/20/14:09:37 // 建物SHOPの移動 //
/*******************************************************************************
		インクルードファイル
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "Shop.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
SHOP g_aShop[MAX_SHOP];		// 建物SHOPの情報

//================================================================================================================================================================================================
// InitShop関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitShop( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
		for( int nCntShop = 0; nCntShop < MAX_SHOP; nCntShop++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\shop.jpg",&g_aShop[nCntShop].pTextureShop);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\shop.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aShop[nCntShop].pBuffMatShop,		// マテリアル情報
									   NULL,
									   &g_aShop[nCntShop].nNumMatShop,			// マテリアル数
									   &g_aShop[nCntShop].pMeshShop ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aShop[nCntShop].pMeshShop->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aShop[nCntShop].pMeshShop->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aShop[nCntShop].pMeshShop->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aShop[nCntShop].Min.x )		g_aShop[nCntShop].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aShop[nCntShop].Max.x )		g_aShop[nCntShop].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aShop[nCntShop].Min.y )		g_aShop[nCntShop].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aShop[nCntShop].Max.y )		g_aShop[nCntShop].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aShop[nCntShop].Min.z )		g_aShop[nCntShop].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aShop[nCntShop].Max.z )		g_aShop[nCntShop].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aShop[nCntShop].pMeshShop->UnlockVertexBuffer();

		// 建物SHOPの半径の設定。絶対値をabs関数で求める。
		g_aShop[nCntShop].Size.x = ( fabs( g_aShop[nCntShop].Min.x ) + fabs( g_aShop[nCntShop].Max.x ) ) / 2;
		g_aShop[nCntShop].Size.y = ( fabs( g_aShop[nCntShop].Min.y ) + fabs( g_aShop[nCntShop].Max.y ) ) / 2;
		g_aShop[nCntShop].Size.z = ( fabs( g_aShop[nCntShop].Min.z ) + fabs( g_aShop[nCntShop].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aShop[nCntShop].Size.x < g_aShop[nCntShop].Size.z )
		{
			g_aShop[nCntShop].Collisoin = g_aShop[nCntShop].Size.z;
		}
		else
		{
			g_aShop[nCntShop].Collisoin = g_aShop[nCntShop].Size.x;
		}
		g_aShop[nCntShop].pos = D3DXVECTOR3( 0.0f,0.0f,20550.0f);
		g_aShop[nCntShop].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aShop[nCntShop].scl = D3DXVECTOR3( 0.8f,  3.0f, 2.0f );
		g_aShop[nCntShop].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aShop[nCntShop].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		
		g_aShop[nCntShop].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitShop関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitShop( void )
{
	for( int nCntShop = 0; nCntShop <MAX_SHOP; nCntShop++ )
	{
		// メッシュ情報の開放
		if( g_aShop[nCntShop].pMeshShop != NULL )
		{
			g_aShop[nCntShop].pMeshShop->Release();
			g_aShop[nCntShop].pMeshShop = NULL;
		}

		// バッファの開放
		if( g_aShop[nCntShop].pBuffMatShop != NULL )
		{
			g_aShop[nCntShop].pBuffMatShop->Release();
			g_aShop[nCntShop].pBuffMatShop = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateShop関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateShop( void )
{

}
//================================================================================================================================================================================================
// DrawShop関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawShop( void )
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
		for( int nCntShop = 0; nCntShop <MAX_SHOP; nCntShop++ )
	{
		if(g_aShop[nCntShop].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aShop[nCntShop].mtxWorldShop );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aShop[nCntShop].scl.x, g_aShop[nCntShop].scl.y, g_aShop[nCntShop].scl.z );
		D3DXMatrixMultiply( &g_aShop[nCntShop].mtxWorldShop, &g_aShop[nCntShop].mtxWorldShop, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aShop[nCntShop].rot.y, g_aShop[nCntShop].rot.x, g_aShop[nCntShop].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aShop[nCntShop].mtxWorldShop, &g_aShop[nCntShop].mtxWorldShop, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aShop[nCntShop].pos.x, g_aShop[nCntShop].pos.y, g_aShop[nCntShop].pos.z );
		D3DXMatrixMultiply( &g_aShop[nCntShop].mtxWorldShop, &g_aShop[nCntShop].mtxWorldShop, &mtxTrans );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aShop[nCntShop].mtxWorldShop );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aShop[nCntShop].pBuffMatShop->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aShop[nCntShop].nNumMatShop; nCntMat++ )
		{

			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aShop[nCntMat].pTextureShop );

			// メッシュの描画
			g_aShop[nCntShop].pMeshShop->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// SHOP *GetShop関数
// 引数 void
// 戻り値 
// 説明 Shopを取得する。
//================================================================================================================================================================================================
SHOP *GetShop( void )
{
	return &g_aShop[0];
}
