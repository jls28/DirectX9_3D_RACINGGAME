//=============================================================================

// ツールの処理 [prop.cpp]
// 

//=============================================================================//
#include "main.h"
#include "prop.h"
#include "effect.h"
#include "shadow.h"
//*****************************************************************************
// マクロ定義prop001.png
//*****************************************************************************
#define	TEXTURE_PROP_FILE		"data\\TEXTURE\\prop001.png"	// 読み込むテクスチャファイル名

#define XPOS_LEFT_PROP	(   -30.0f )		// 左Xの頂点座標
#define XPOS_RIGHT_PROP	(    30.0f )		// 右Xの頂点座標
#define YPOS_UP_PROP		(   30.0f )		// 上Yの頂点座標
#define YPOS_DOWN_PROP	(   -30.0f )		// 下Yの頂点座標
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
PROP g_aProp[ MAX_PROP ];		// ツールの情報

//================================================================================================================================================================================================
// InitProp関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitProp( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		if( g_aProp[nCntProp].bUse == false )
		{
			g_aProp[nCntProp].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aProp[nCntProp].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aProp[nCntProp].nLife = LIFE_PROP;
			g_aProp[nCntProp].state = PROPSTATE_START;
			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, TEXTURE_PROP_FILE, &g_aProp[nCntProp].pTextureProp );

			// 頂点バッファの生成
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_PROP * 4 ),	// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// 使用する頂点フォーマット
													 D3DPOOL_MANAGED,
													 &g_aProp[nCntProp].pVtxBuffProp,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// 頂点情報の設定//////////////////////////////////////////////////////////////////////////////
			// 頂点情報へのポインタを取得
			g_aProp[nCntProp].pVtxBuffProp->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntProp * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_PROP,  YPOS_UP_PROP,   0.0f );	// 頂点座標
			pVtx[ ( nCntProp * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_PROP, YPOS_UP_PROP,   0.0f );
			pVtx[ ( nCntProp * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_PROP,  YPOS_DOWN_PROP, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_PROP, YPOS_DOWN_PROP, 0.0f );

			pVtx[ ( nCntProp * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// 法線の向き
			pVtx[ ( nCntProp * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntProp * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// 頂点カラー
			pVtx[ ( nCntProp * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntProp * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntProp * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			pVtx[ ( nCntProp * 4 ) + 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );					// テクスチャ座標
			pVtx[ ( nCntProp * 4 ) + 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ ( nCntProp * 4 ) + 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

			g_aProp[nCntProp].pVtxBuffProp->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// 使用状態にする。
			g_aProp[nCntProp].bUse = true;
		}
	}
	g_aProp[0].pos = D3DXVECTOR3( -60.0f, 20.0f, 500.0f );

	g_aProp[1].pos = D3DXVECTOR3( -40.0f, 20.0f, 1000.0f );

	g_aProp[2].pos = D3DXVECTOR3( 60.0f, 20.0f, 1600.0f );

	g_aProp[3].pos = D3DXVECTOR3( 0.0f, 20.0f, 2000.0f );

	g_aProp[4].pos = D3DXVECTOR3( -60.0f, 20.0f, 2500.0f );

	g_aProp[5].pos = D3DXVECTOR3( 60.0f, 20.0f, 2500.0f );

	g_aProp[6].pos = D3DXVECTOR3( -50.0f, 20.0f, 3000.0f );

	g_aProp[7].pos = D3DXVECTOR3( 70.0f, 20.0f, 3000.0f );

	g_aProp[8].pos = D3DXVECTOR3( -70.0f, 20.0f, 3600.0f );

	g_aProp[9].pos = D3DXVECTOR3( -50.0f, 20.0f, 4000.0f );

	g_aProp[10].pos = D3DXVECTOR3( -10.0f, 20.0f, 4500.0f );

	g_aProp[11].pos = D3DXVECTOR3( 15.0f, 20.0f, 4800.0f );

	g_aProp[12].pos = D3DXVECTOR3( 40.0f, 20.0f, 5000.0f );

	g_aProp[13].pos = D3DXVECTOR3( 70.0f, 20.0f, 5800.0f );

	g_aProp[14].pos = D3DXVECTOR3( 20.0f, 20.0f, 6000.0f );

	g_aProp[15].pos = D3DXVECTOR3( 70.0f, 20.0f, 6300.0f );

	g_aProp[16].pos = D3DXVECTOR3( 0.0f, 20.0f, 6800.0f );

	g_aProp[17].pos = D3DXVECTOR3( -60.0f, 20.0f, 7500.0f );

	g_aProp[18].pos = D3DXVECTOR3( 30.0f, 20.0f, 8000.0f );

	g_aProp[19].pos = D3DXVECTOR3( -50.0f, 20.0f, 8600.0f );

	g_aProp[20].pos = D3DXVECTOR3( 60.0f, 20.0f, 7000.0f );

	g_aProp[21].pos = D3DXVECTOR3( 70.0f, 20.0f, 7700.0f );

	g_aProp[22].pos = D3DXVECTOR3( -80.0f, 20.0f, 8000.0f );

	g_aProp[23].pos = D3DXVECTOR3( 80.0f, 20.0f, 8600.0f );

	g_aProp[24].pos = D3DXVECTOR3( -20.0f, 20.0f, 9300.0f );

	g_aProp[24].pos = D3DXVECTOR3( 60.0f, 20.0f, 9900.0f );

	g_aProp[25].pos = D3DXVECTOR3( 30.0f, 20.0f, 10800.0f );

	g_aProp[26].pos = D3DXVECTOR3( 0.0f, 20.0f, 11600.0f );

	g_aProp[27].pos = D3DXVECTOR3( -70.0f, 20.0f, 12300.0f );

	g_aProp[28].pos = D3DXVECTOR3( 20.0f, 20.0f, 12900.0f );

	g_aProp[29].pos = D3DXVECTOR3( 20.0f, 20.0f, 13800.0f );

	g_aProp[30].pos = D3DXVECTOR3( 70.0f, 20.0f, 14300.0f );

	g_aProp[31].pos = D3DXVECTOR3( -50.0f, 20.0f, 14900.0f );

	g_aProp[32].pos = D3DXVECTOR3( 30.0f, 20.0f, 15300.0f );

	g_aProp[33].pos = D3DXVECTOR3( 80.0f, 20.0f, 15800.0f );

	g_aProp[34].pos = D3DXVECTOR3( -10.0f, 20.0f, 16700.0f );

	g_aProp[35].pos = D3DXVECTOR3( 0.0f, 20.0f, 17500.0f );

	g_aProp[36].pos = D3DXVECTOR3( 60.0f, 20.0f, 18300.0f );

	g_aProp[37].pos = D3DXVECTOR3( 30.0f, 20.0f, 19000.0f );

	g_aProp[38].pos = D3DXVECTOR3( -70.0f, 20.0f, 20000.0f );

	return S_OK;
}
//================================================================================================================================================================================================
// UninitProp関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitProp( void )
{
	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		// メッシュ情報の開放
		if( g_aProp[ nCntProp ].pVtxBuffProp != NULL )
		{
			g_aProp[ nCntProp ].pVtxBuffProp->Release();
			g_aProp[ nCntProp ].pVtxBuffProp = NULL;
		}

		// バッファの開放
		if( g_aProp[ nCntProp ].pTextureProp != NULL )
		{
			g_aProp[ nCntProp ].pTextureProp->Release();
			g_aProp[ nCntProp ].pTextureProp = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateProp関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateProp( void )
{
	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		if( g_aProp[nCntProp].bUse == true )
		{
			//影
			SetShadow( g_aProp[nCntProp].pos, 20.0f, 20.0f, 1 + nCntProp , true );
			//effect
			SetEffect(g_aProp[nCntProp].pos, D3DCOLOR_RGBA(0, 255, 255, 255), 50, 10, EFFECTTYPE_NORMAL);

		}
	}
}

//================================================================================================================================================================================================
// DrawProp関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawProp( void )
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

	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		if( g_aProp[ nCntProp ].bUse == true )
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_aProp[ nCntProp ].mtxWorld );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &g_aProp[ nCntProp ].mtxWorld, NULL, &mtxView );

			g_aProp[ nCntProp ].mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			g_aProp[ nCntProp ].mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			g_aProp[ nCntProp ].mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア

			// スケールを反映
			D3DXMatrixScaling( &mtxScl, g_aProp[ nCntProp ].scl.x, g_aProp[ nCntProp ].scl.y, g_aProp[ nCntProp ].scl.z );
			D3DXMatrixMultiply( &g_aProp[ nCntProp ].mtxWorld, &g_aProp[ nCntProp ].mtxWorld, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply( &g_aProp[ nCntProp ].mtxWorld, &g_aProp[ nCntProp ].mtxWorld, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, g_aProp[ nCntProp ].pos.x, g_aProp[ nCntProp ].pos.y, g_aProp[ nCntProp ].pos.z );
			D3DXMatrixMultiply( &g_aProp[ nCntProp ].mtxWorld, &g_aProp[ nCntProp ].mtxWorld, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &g_aProp[ nCntProp ].mtxWorld );

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			pDevice->SetStreamSource( 0, g_aProp[ nCntProp ].pVtxBuffProp, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aProp[ nCntProp ].pTextureProp );

			// ポリゴンの描画
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
									( nCntProp * 4 ),								// 描画する最初の頂点
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
// *GetProp関数
// 引数 void
// 戻り値 
// 説明 Propを取得する。
//================================================================================================================================================================================================
PROP *GetProp( void )
{
	return &g_aProp[ 0 ];
}


