//=============================================================================

// ツールの処理 [prop.cpp]
// 

//=============================================================================//
#include "main.h"
#include "runleg.h"
#include "modellegL.h"
#include "modellegR.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RUNLEG_FILE		"data\\TEXTURE\\runleg.jpg"	// 読み込むテクスチャファイル名

#define XPOS_LEFT_RUNLEG	(   -5.0f )		// 左Xの頂点座標
#define XPOS_RIGHT_RUNLEG	(    5.0f )		// 右Xの頂点座標
#define YPOS_UP_RUNLEG		(   5.0f )		// 上Yの頂点座標
#define YPOS_DOWN_RUNLEG	(   -5.0f )		// 下Yの頂点座標

#define	NUM_PATTERN_RUNLEG			(4)						// アニメーションのパターン数
#define	TEXTURE_SIZE_X_RUNLEG		(1.0f / NUM_PATTERN_RUNLEG)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y_RUNLEG		(1.0f)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN_RUNLEG	(3)						// アニメーションの切り替え間隔
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
RUNLEG g_aRunLeg[ MAX_RUNLEG ];		// ツールの情報

//================================================================================================================================================================================================
// InitRunLeg関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitRunLeg( void )
{
	MODELLEGL *pModelLegL = GetModelLegL();
	MODELLEGR *pModelLegR = GetModelLegR();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		if( g_aRunLeg[nCntRunLeg].bUse == false )
		{
			g_aRunLeg[nCntRunLeg].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aRunLeg[nCntRunLeg].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aRunLeg[nCntRunLeg].nCount = 0;
			g_aRunLeg[nCntRunLeg].nPattern = 0;
			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, TEXTURE_RUNLEG_FILE, &g_aRunLeg[nCntRunLeg].pTextureRunLeg );

			// 頂点バッファの生成
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_RUNLEG * 4 ),	// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// 使用する頂点フォーマット
													 D3DPOOL_MANAGED,
													 &g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// 頂点情報の設定//////////////////////////////////////////////////////////////////////////////
			// 頂点情報へのポインタを取得
			g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_RUNLEG,  YPOS_UP_RUNLEG,   0.0f );	// 頂点座標
			pVtx[ ( nCntRunLeg * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_RUNLEG, YPOS_UP_RUNLEG,   0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_RUNLEG,  YPOS_DOWN_RUNLEG, 0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_RUNLEG, YPOS_DOWN_RUNLEG, 0.0f );

			pVtx[ ( nCntRunLeg * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// 法線の向き
			pVtx[ ( nCntRunLeg * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntRunLeg * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// 頂点カラー
			pVtx[ ( nCntRunLeg * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntRunLeg * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntRunLeg * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			// テクスチャ座標の設定
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(TEXTURE_SIZE_X_RUNLEG, 0.0f);
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_RUNLEG);
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(TEXTURE_SIZE_X_RUNLEG, TEXTURE_SIZE_Y_RUNLEG);

			g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// 使用状態にする。
			g_aRunLeg[nCntRunLeg].bUse = false;
		}
	}
	g_aRunLeg[0].pos = pModelLegL->pos;
	g_aRunLeg[1].pos = pModelLegR->pos;
	return S_OK;
}
//================================================================================================================================================================================================
// UninitRunLeg関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitRunLeg( void )
{
	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		// メッシュ情報の開放
		if( g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg != NULL )
		{
			g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg->Release();
			g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg = NULL;
		}

		// バッファの開放
		if( g_aRunLeg[ nCntRunLeg ].pTextureRunLeg != NULL )
		{
			g_aRunLeg[ nCntRunLeg ].pTextureRunLeg->Release();
			g_aRunLeg[ nCntRunLeg ].pTextureRunLeg = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateRunLeg関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateRunLeg( void )
{
	MODELLEGL *pModelLegL = GetModelLegL();
	MODELLEGR *pModelLegR = GetModelLegR();
	g_aRunLeg[0].pos = pModelLegL->pos;
	g_aRunLeg[1].pos = pModelLegR->pos;
	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		if( g_aRunLeg[nCntRunLeg].bUse == true )
		{// 爆発を使用している
			g_aRunLeg[nCntRunLeg].nCount++;
			if((g_aRunLeg[nCntRunLeg].nCount % INTERVAL_PATTERN_RUNLEG) == 0)
			{// アニメーション切り替え
				g_aRunLeg[nCntRunLeg].nPattern++;
				if(g_aRunLeg[nCntRunLeg].nPattern >= NUM_PATTERN_RUNLEG  )
				{// アニメーションパターンが終了
					ResetRunLeg();
				}
				SetTextureRunLeg(nCntRunLeg);
			}
		}
	}
}

//================================================================================================================================================================================================
// DrawRunLeg関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawRunLeg( void )
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスを取得
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// レンダーステートの設定（zテスト）
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z値の更新
	// レンダーステートの設定（アルファテスト）
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// アルファ値を判定して、該当のピクセルを描画するようにする。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// 下の値よりアルファ値が大きければ描画する。
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// アルファ値。0で透明な部分。
	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		if( g_aRunLeg[ nCntRunLeg ].bUse == true )
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_aRunLeg[ nCntRunLeg ].mtxWorld );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &g_aRunLeg[ nCntRunLeg ].mtxWorld, NULL, &mtxView );

			g_aRunLeg[ nCntRunLeg ].mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			g_aRunLeg[ nCntRunLeg ].mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			g_aRunLeg[ nCntRunLeg ].mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア

			// スケールを反映
			D3DXMatrixScaling( &mtxScl, g_aRunLeg[ nCntRunLeg ].scl.x, g_aRunLeg[ nCntRunLeg ].scl.y, g_aRunLeg[ nCntRunLeg ].scl.z );
			D3DXMatrixMultiply( &g_aRunLeg[ nCntRunLeg ].mtxWorld, &g_aRunLeg[ nCntRunLeg ].mtxWorld, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply( &g_aRunLeg[ nCntRunLeg ].mtxWorld, &g_aRunLeg[ nCntRunLeg ].mtxWorld, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, g_aRunLeg[ nCntRunLeg ].pos.x, g_aRunLeg[ nCntRunLeg ].pos.y, g_aRunLeg[ nCntRunLeg ].pos.z );
			D3DXMatrixMultiply( &g_aRunLeg[ nCntRunLeg ].mtxWorld, &g_aRunLeg[ nCntRunLeg ].mtxWorld, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &g_aRunLeg[ nCntRunLeg ].mtxWorld );

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			pDevice->SetStreamSource( 0, g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aRunLeg[ nCntRunLeg ].pTextureRunLeg );

			// ポリゴンの描画
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
									( nCntRunLeg * 4 ),								// 描画する最初の頂点
									2 );										// 描画するプリミティブ数
		}
	}

	// レンダーステートの設定をデフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。

	// ライト点灯
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}


//================================================================================================================================================================================================
// *GetRunLeg関数
// 引数 void
// 戻り値 
// 説明 RunLegを取得する。
//================================================================================================================================================================================================
RUNLEG *GetRunLeg( void )
{
	return &g_aRunLeg[ 0 ];
}


//=============================================================================
// RUNのリセット
//=============================================================================
void ResetRunLeg(void)
{
	for(int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++)
	{
		g_aRunLeg[nCntRunLeg].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRunLeg[nCntRunLeg].nCount = 0;
		g_aRunLeg[nCntRunLeg].nPattern = 0;


	}
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureRunLeg(int nRunLegID)
{
	for(int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++)
	{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nRunLegID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aRunLeg[nRunLegID].nPattern * TEXTURE_SIZE_X_RUNLEG, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aRunLeg[nRunLegID].nPattern + 1) * TEXTURE_SIZE_X_RUNLEG, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aRunLeg[nRunLegID].nPattern * TEXTURE_SIZE_X_RUNLEG, TEXTURE_SIZE_Y_RUNLEG);
	pVtx[3].tex = D3DXVECTOR2((g_aRunLeg[nRunLegID].nPattern + 1) * TEXTURE_SIZE_X_RUNLEG, TEXTURE_SIZE_Y_RUNLEG);

	// 頂点データをアンロックする
	g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Unlock();
	}
}