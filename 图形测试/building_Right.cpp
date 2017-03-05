/*******************************************************************************
* タイトル： 建物描画関数
* ファイル名： building_Right.cpp
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
#include "building_Right.h"
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
BUILDING_RIGHT g_aBuilding_Right[MAX_BUILDING_RIGHT];		// 建物の情報

//================================================================================================================================================================================================
// InitBuilding_Right関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitBuilding_Right( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESHWALL *pWall = GetMeshWall();
		for( int nCntBuilding_Right = 0; nCntBuilding_Right < MAX_BUILDING_RIGHT; nCntBuilding_Right++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\building_Left.png",&g_aBuilding_Right[nCntBuilding_Right].pTextureBuilding_Right);// テクスチャ読み込み
		// Xファイルの読み込み
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\building_Left.x",
									   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
									   pDevice,
									   NULL,
									   &g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right,		// マテリアル情報
									   NULL,
									   &g_aBuilding_Right[nCntBuilding_Right].nNumMatBuilding_Right,			// マテリアル数
									   &g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right ) ) )		// メッシュ情報
		{
			return E_FAIL;
		}
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aBuilding_Right[nCntBuilding_Right].Min.x )		g_aBuilding_Right[nCntBuilding_Right].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > g_aBuilding_Right[nCntBuilding_Right].Max.x )		g_aBuilding_Right[nCntBuilding_Right].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < g_aBuilding_Right[nCntBuilding_Right].Min.y )		g_aBuilding_Right[nCntBuilding_Right].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > g_aBuilding_Right[nCntBuilding_Right].Max.y )		g_aBuilding_Right[nCntBuilding_Right].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < g_aBuilding_Right[nCntBuilding_Right].Min.z )		g_aBuilding_Right[nCntBuilding_Right].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > g_aBuilding_Right[nCntBuilding_Right].Max.z )		g_aBuilding_Right[nCntBuilding_Right].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->UnlockVertexBuffer();

		// 建物の半径の設定。絶対値をabs関数で求める。
		g_aBuilding_Right[nCntBuilding_Right].Size.x = ( fabs( g_aBuilding_Right[nCntBuilding_Right].Min.x ) + fabs( g_aBuilding_Right[nCntBuilding_Right].Max.x ) ) / 2;
		g_aBuilding_Right[nCntBuilding_Right].Size.y = ( fabs( g_aBuilding_Right[nCntBuilding_Right].Min.y ) + fabs( g_aBuilding_Right[nCntBuilding_Right].Max.y ) ) / 2;
		g_aBuilding_Right[nCntBuilding_Right].Size.z = ( fabs( g_aBuilding_Right[nCntBuilding_Right].Min.z ) + fabs( g_aBuilding_Right[nCntBuilding_Right].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( g_aBuilding_Right[nCntBuilding_Right].Size.x < g_aBuilding_Right[nCntBuilding_Right].Size.z )
		{
			g_aBuilding_Right[nCntBuilding_Right].Collisoin = g_aBuilding_Right[nCntBuilding_Right].Size.z;
		}
		else
		{
			g_aBuilding_Right[nCntBuilding_Right].Collisoin = g_aBuilding_Right[nCntBuilding_Right].Size.x;
		}
		g_aBuilding_Right[nCntBuilding_Right].pos = D3DXVECTOR3( (pWall + WALL_RIGHT)->pos.x + g_aBuilding_Right[nCntBuilding_Right].Size.x,  0.0f, g_aBuilding_Right[nCntBuilding_Right].pos.z + (g_aBuilding_Right[nCntBuilding_Right].Size.z * nCntBuilding_Right)*2);
		g_aBuilding_Right[nCntBuilding_Right].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Right[nCntBuilding_Right].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aBuilding_Right[nCntBuilding_Right].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Right[nCntBuilding_Right].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );

		g_aBuilding_Right[nCntBuilding_Right].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitBuilding_Right関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitBuilding_Right( void )
{
	for( int nCntBuilding_Right = 0; nCntBuilding_Right <MAX_BUILDING_RIGHT; nCntBuilding_Right++ )
	{
		// メッシュ情報の開放
		if( g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right != NULL )
		{
			g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->Release();
			g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right = NULL;
		}

		// バッファの開放
		if( g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right != NULL )
		{
			g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right->Release();
			g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateBuilding_Right関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateBuilding_Right( void )
{

}
//================================================================================================================================================================================================
// DrawBuilding_Right関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawBuilding_Right( void )
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
		for( int nCntBuilding_Right = 0; nCntBuilding_Right <MAX_BUILDING_RIGHT; nCntBuilding_Right++ )
	{
		if(g_aBuilding_Right[nCntBuilding_Right].bUse == true)
		{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aBuilding_Right[nCntBuilding_Right].scl.x, g_aBuilding_Right[nCntBuilding_Right].scl.y, g_aBuilding_Right[nCntBuilding_Right].scl.z );
		D3DXMatrixMultiply( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aBuilding_Right[nCntBuilding_Right].rot.y, g_aBuilding_Right[nCntBuilding_Right].rot.x, g_aBuilding_Right[nCntBuilding_Right].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aBuilding_Right[nCntBuilding_Right].pos.x, g_aBuilding_Right[nCntBuilding_Right].pos.y, g_aBuilding_Right[nCntBuilding_Right].pos.z );
		D3DXMatrixMultiply( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &mtxTrans );
		// ライト点灯
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right );

		// キャスト変換
		pMat = ( D3DXMATERIAL* )g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aBuilding_Right[nCntBuilding_Right].nNumMatBuilding_Right; nCntMat++ )
		{

			// マテリアルの設定
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aBuilding_Right[nCntMat].pTextureBuilding_Right );

			// メッシュの描画
			g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// BUILDING_RIGHT *GetBuilding_Right関数
// 引数 void
// 戻り値 
// 説明 Building_Rightを取得する。
//================================================================================================================================================================================================
BUILDING_RIGHT *GetBuilding_Right( void )
{
	return &g_aBuilding_Right[0];
}
