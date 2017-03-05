//=============================================================================

// ツールの処理 [money.cpp]
// 

//=============================================================================//
#include "main.h"
#include "money.h"
#include "shadow.h"
#include "effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_MONEY_FILE		"data\\TEXTURE\\money.png"	// 読み込むテクスチャファイル名
#define XPOS_LEFT_MONEY	(   -10.0f )		// 左Xの頂点座標
#define XPOS_RIGHT_MONEY	(    10.0f )		// 右Xの頂点座標
#define YPOS_UP_MONEY		(   10.0f )		// 上Yの頂点座標
#define YPOS_DOWN_MONEY	(   -10.0f )		// 下Yの頂点座標
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
MONEY g_aMoney[ MAX_MONEY ];		// ツールの情報

//================================================================================================================================================================================================
// InitMoney関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitMoney( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[nCntMoney].bUse == false )
		{
			g_aMoney[nCntMoney].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aMoney[nCntMoney].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aMoney[nCntMoney].nLife = LIFE_MONEY;
			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, TEXTURE_MONEY_FILE, &g_aMoney[nCntMoney].pTextureMoney );

			// 頂点バッファの生成
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_MONEY * 4 ),	// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// 使用する頂点フォーマット
													 D3DPOOL_MANAGED,
													 &g_aMoney[nCntMoney].pVtxBuffMoney,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// 頂点情報の設定//////////////////////////////////////////////////////////////////////////////
			// 頂点情報へのポインタを取得
			g_aMoney[nCntMoney].pVtxBuffMoney->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntMoney * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_MONEY,  YPOS_UP_MONEY,   0.0f );	// 頂点座標
			pVtx[ ( nCntMoney * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_MONEY, YPOS_UP_MONEY,   0.0f );
			pVtx[ ( nCntMoney * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_MONEY,  YPOS_DOWN_MONEY, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_MONEY, YPOS_DOWN_MONEY, 0.0f );

			pVtx[ ( nCntMoney * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// 法線の向き
			pVtx[ ( nCntMoney * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntMoney * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// 頂点カラー
			pVtx[ ( nCntMoney * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntMoney * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntMoney * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			pVtx[ ( nCntMoney * 4 ) + 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );					// テクスチャ座標
			pVtx[ ( nCntMoney * 4 ) + 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ ( nCntMoney * 4 ) + 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

			g_aMoney[nCntMoney].pVtxBuffMoney->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// 使用状態にする。
			g_aMoney[nCntMoney].bUse = false;
		}
	}
	return S_OK;
}
//================================================================================================================================================================================================
// UninitMoney関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitMoney( void )
{
	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		// メッシュ情報の開放
		if( g_aMoney[ nCntMoney ].pVtxBuffMoney != NULL )
		{
			g_aMoney[ nCntMoney ].pVtxBuffMoney->Release();
			g_aMoney[ nCntMoney ].pVtxBuffMoney = NULL;
		}

		// バッファの開放
		if( g_aMoney[ nCntMoney ].pTextureMoney != NULL )
		{
			g_aMoney[ nCntMoney ].pTextureMoney->Release();
			g_aMoney[ nCntMoney ].pTextureMoney = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateMoney関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateMoney( void )
{
	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[ nCntMoney ].bUse == true )
		{
			//影の設定
			SetShadow( g_aMoney[ nCntMoney ].pos, 20.0f, 5.0f, 1 + nCntMoney, g_aMoney[ nCntMoney ].bUse );

			g_aMoney[ nCntMoney ].nLife --;
			if(g_aMoney[ nCntMoney ].nLife <= 0)
			{
				g_aMoney[ nCntMoney ].bUse = false;
			}

		}
	}


}

//================================================================================================================================================================================================
// DrawMoney関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawMoney( void )
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

	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[ nCntMoney ].bUse == true )
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_aMoney[ nCntMoney ].mtxWorld );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &g_aMoney[ nCntMoney ].mtxWorld, NULL, &mtxView );

			g_aMoney[ nCntMoney ].mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			g_aMoney[ nCntMoney ].mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			g_aMoney[ nCntMoney ].mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア

			// スケールを反映
			D3DXMatrixScaling( &mtxScl, g_aMoney[ nCntMoney ].scl.x, g_aMoney[ nCntMoney ].scl.y, g_aMoney[ nCntMoney ].scl.z );
			D3DXMatrixMultiply( &g_aMoney[ nCntMoney ].mtxWorld, &g_aMoney[ nCntMoney ].mtxWorld, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply( &g_aMoney[ nCntMoney ].mtxWorld, &g_aMoney[ nCntMoney ].mtxWorld, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, g_aMoney[ nCntMoney ].pos.x, g_aMoney[ nCntMoney ].pos.y, g_aMoney[ nCntMoney ].pos.z );
			D3DXMatrixMultiply( &g_aMoney[ nCntMoney ].mtxWorld, &g_aMoney[ nCntMoney ].mtxWorld, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &g_aMoney[ nCntMoney ].mtxWorld );

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			pDevice->SetStreamSource( 0, g_aMoney[ nCntMoney ].pVtxBuffMoney, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture( 0,g_aMoney[ nCntMoney ].pTextureMoney );

			// ポリゴンの描画
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
									( nCntMoney * 4 ),								// 描画する最初の頂点
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
// *GetMoney関数
// 引数 void
// 戻り値 
// 説明 Moneyを取得する。
//================================================================================================================================================================================================
MONEY *GetMoney( void )
{
	return &g_aMoney[ 0 ];
}
void SetMoney( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[ nCntMoney ].bUse == false )
		{
			// 位置の設定
			g_aMoney[ nCntMoney ].pos = pos;


			g_aMoney[ nCntMoney ].rot = rot;

			// 寿命の設定
			g_aMoney[ nCntMoney ].nLife = nLife;

			// ツールを使用状態にする
			g_aMoney[ nCntMoney ].bUse = true;

			
		}
	}
	
}

