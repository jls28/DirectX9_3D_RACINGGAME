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
#include "main.h"
#include "sky.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
SKY g_aSky[MAX_SKY];		// 建物の情報

//================================================================================================================================================================================================
// InitSky関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitSky( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
		for( int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\sky000.jpg",&g_aSky[nCntSky].pTextureSky);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\sky.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aSky[nCntSky].pBuffMatSky,		// マテリアル情報
									   NULL,
									   &g_aSky[nCntSky].nNumMatSky,			// マテリアル数
									   &g_aSky[nCntSky].pMeshSky ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aSky[nCntSky].pMeshSky->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aSky[nCntSky].pMeshSky->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aSky[nCntSky].pMeshSky->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aSky[nCntSky].Min.x )		g_aSky[nCntSky].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aSky[nCntSky].Max.x )		g_aSky[nCntSky].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aSky[nCntSky].Min.y )		g_aSky[nCntSky].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aSky[nCntSky].Max.y )		g_aSky[nCntSky].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aSky[nCntSky].Min.z )		g_aSky[nCntSky].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aSky[nCntSky].Max.z )		g_aSky[nCntSky].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aSky[nCntSky].pMeshSky->UnlockVertexBuffer();

		// 建物の半径の設定。絶対値をabs関数で求める。
		g_aSky[nCntSky].Size.x = ( fabs( g_aSky[nCntSky].Min.x ) + fabs( g_aSky[nCntSky].Max.x ) ) / 2;
		g_aSky[nCntSky].Size.y = ( fabs( g_aSky[nCntSky].Min.y ) + fabs( g_aSky[nCntSky].Max.y ) ) / 2;
		g_aSky[nCntSky].Size.z = ( fabs( g_aSky[nCntSky].Min.z ) + fabs( g_aSky[nCntSky].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aSky[nCntSky].Size.x < g_aSky[nCntSky].Size.z )
		{
			g_aSky[nCntSky].Collisoin = g_aSky[nCntSky].Size.z;
		}
		else
		{
			g_aSky[nCntSky].Collisoin = g_aSky[nCntSky].Size.x;
		}
		g_aSky[nCntSky].pos = D3DXVECTOR3( 0.0f,  -500.0f, 100000.0f );
		g_aSky[nCntSky].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aSky[nCntSky].scl = D3DXVECTOR3( 5.f,  5.0f, 5.0f );
		g_aSky[nCntSky].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aSky[nCntSky].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );

		g_aSky[nCntSky].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitSky関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitSky( void )
{
	for( int nCntSky = 0; nCntSky <MAX_SKY; nCntSky++ )
	{
		// メッシュ情報の開放
		if( g_aSky[nCntSky].pMeshSky != NULL )
		{
			g_aSky[nCntSky].pMeshSky->Release();
			g_aSky[nCntSky].pMeshSky = NULL;
		}

		// バッファの開放
		if( g_aSky[nCntSky].pBuffMatSky != NULL )
		{
			g_aSky[nCntSky].pBuffMatSky->Release();
			g_aSky[nCntSky].pBuffMatSky = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateSky関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateSky( void )
{

}
//================================================================================================================================================================================================
// DrawSky関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawSky( void )
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
		for( int nCntSky = 0; nCntSky <MAX_SKY; nCntSky++ )
	{
		if(g_aSky[nCntSky].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aSky[nCntSky].mtxWorldSky );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aSky[nCntSky].scl.x, g_aSky[nCntSky].scl.y, g_aSky[nCntSky].scl.z );
		D3DXMatrixMultiply( &g_aSky[nCntSky].mtxWorldSky, &g_aSky[nCntSky].mtxWorldSky, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aSky[nCntSky].rot.y, g_aSky[nCntSky].rot.x, g_aSky[nCntSky].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aSky[nCntSky].mtxWorldSky, &g_aSky[nCntSky].mtxWorldSky, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aSky[nCntSky].pos.x, g_aSky[nCntSky].pos.y, g_aSky[nCntSky].pos.z );
		D3DXMatrixMultiply( &g_aSky[nCntSky].mtxWorldSky, &g_aSky[nCntSky].mtxWorldSky, &mtxTrans );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aSky[nCntSky].mtxWorldSky );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aSky[nCntSky].pBuffMatSky->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aSky[nCntSky].nNumMatSky; nCntMat++ )
		{
			pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
			pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
			pDevice->SetTexture( 1 , NULL );
			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aSky[nCntMat].pTextureSky );

			// メッシュの描画
			g_aSky[nCntSky].pMeshSky->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// SKY *GetSky関数
// 引数 void
// 戻り値 
// 説明 Skyを取得する。
//================================================================================================================================================================================================
SKY *GetSky( void )
{
	return &g_aSky[0];
}
