//=============================================================================
//
// boxscore処理 [BoxScore01.h]
// 2016/02/14 LIHAOSHENG
//
//=============================================================================
#include "main.h"
#include "boxscore.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_BOXSCORE01_FILE		"data\\TEXTURE\\boxscore01.jpg"	// 読み込むテクスチャファイル名
#define XPOS_LEFT_BOXSCORE01	(   -100.0f )		// 左Xの頂点座標
#define XPOS_RIGHT_BOXSCORE01	(    100.0f )		// 右Xの頂点座標
#define YPOS_UP_BOXSCORE01		(   100.0f )		// 上Yの頂点座標
#define YPOS_DOWN_BOXSCORE01	(   -100.0f )		// 下Yの頂点座標
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
BOXSCORE01 g_aBoxScore01[ MAX_BOXSCORE01 ];		// ツールの情報

//================================================================================================================================================================================================
// InitBoxScore01関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitBoxScore01( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[nCntBoxScore01].bUse == false )
		{
			g_aBoxScore01[nCntBoxScore01].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aBoxScore01[nCntBoxScore01].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aBoxScore01[nCntBoxScore01].nLife = 100;
			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, TEXTURE_BOXSCORE01_FILE, &g_aBoxScore01[nCntBoxScore01].pTextureBoxScore01 );

			// 頂点バッファの生成
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_BOXSCORE01 * 4 ),	// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// 使用する頂点フォーマット
													 D3DPOOL_MANAGED,
													 &g_aBoxScore01[nCntBoxScore01].pVtxBuffBoxScore01,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// 頂点情報の設定//////////////////////////////////////////////////////////////////////////////
			// 頂点情報へのポインタを取得
			g_aBoxScore01[nCntBoxScore01].pVtxBuffBoxScore01->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntBoxScore01 * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_BOXSCORE01,  YPOS_UP_BOXSCORE01,   0.0f );	// 頂点座標
			pVtx[ ( nCntBoxScore01 * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_BOXSCORE01, YPOS_UP_BOXSCORE01,   0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_BOXSCORE01,  YPOS_DOWN_BOXSCORE01, 0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_BOXSCORE01, YPOS_DOWN_BOXSCORE01, 0.0f );

			pVtx[ ( nCntBoxScore01 * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// 法線の向き
			pVtx[ ( nCntBoxScore01 * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntBoxScore01 * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// 頂点カラー
			pVtx[ ( nCntBoxScore01 * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBoxScore01 * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBoxScore01 * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			g_aBoxScore01[nCntBoxScore01].pVtxBuffBoxScore01->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// 使用状態にする。
			g_aBoxScore01[nCntBoxScore01].bUse = false;
		}
	}
	return S_OK;
}
//================================================================================================================================================================================================
// UninitBoxScore01関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitBoxScore01( void )
{
	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		// メッシュ情報の開放
		if( g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01 != NULL )
		{
			g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01->Release();
			g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01 = NULL;
		}

		// バッファの開放
		if( g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01 != NULL )
		{
			g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01->Release();
			g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01 = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateBoxScore01関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateBoxScore01( void )
{
	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[ nCntBoxScore01 ].bUse == true )
		{
			g_aBoxScore01[ nCntBoxScore01 ].nLife --;
			if(g_aBoxScore01[ nCntBoxScore01 ].nLife <= 0)
			{
				g_aBoxScore01[ nCntBoxScore01 ].bUse = false;
			}

		}
	}


}

//================================================================================================================================================================================================
// DrawBoxScore01関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawBoxScore01( void )
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

	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[ nCntBoxScore01 ].bUse == true )
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, NULL, &mtxView );

			g_aBoxScore01[ nCntBoxScore01 ].mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			g_aBoxScore01[ nCntBoxScore01 ].mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			g_aBoxScore01[ nCntBoxScore01 ].mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア

			// スケールを反映
			D3DXMatrixScaling( &mtxScl, g_aBoxScore01[ nCntBoxScore01 ].scl.x, g_aBoxScore01[ nCntBoxScore01 ].scl.y, g_aBoxScore01[ nCntBoxScore01 ].scl.z );
			D3DXMatrixMultiply( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, g_aBoxScore01[ nCntBoxScore01 ].pos.x, g_aBoxScore01[ nCntBoxScore01 ].pos.y, g_aBoxScore01[ nCntBoxScore01 ].pos.z );
			D3DXMatrixMultiply( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld );

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			pDevice->SetStreamSource( 0, g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01 );

			// ポリゴンの描画
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
									( nCntBoxScore01 * 4 ),								// 描画する最初の頂点
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
// *GetBoxScore01関数
// 引数 void
// 戻り値 
// 説明 BoxScore01を取得する。
//================================================================================================================================================================================================
BOXSCORE01 *GetBoxScore01( void )
{
	return &g_aBoxScore01[ 0 ];
}
void SetBoxScore01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[ nCntBoxScore01 ].bUse == false )
		{
			// 位置の設定
			g_aBoxScore01[ nCntBoxScore01 ].pos = pos;


			g_aBoxScore01[ nCntBoxScore01 ].rot = rot;

			// 寿命の設定
			g_aBoxScore01[ nCntBoxScore01 ].nLife = nLife;


			// ツールを使用状態にする
			g_aBoxScore01[ nCntBoxScore01 ].bUse = true;

			
		}
	}
	
}
