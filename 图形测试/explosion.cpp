#include "explosion.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EXPLOSION	"data\\TEXTURE\\attackeffect.png"	// 読み込むテクスチャファイル名
#define	EXPLOSION_POS_X		(0.0f)							// 爆発の表示基準位置Ｘ座標
#define	EXPLOSION_POS_Y		(0.0f)							// 爆発の表示基準位置Ｙ座標
#define	EXPLOSION_WIDTH		(35.0f)							// 爆発の幅
#define	EXPLOSION_HEIGHT	(35.0f)							// 爆発の高さ

#define	MAX_EXPLOSION		(256)					// 爆発の最大数

#define	NUM_PATTERN			(7)						// アニメーションのパターン数
#define	TEXTURE_SIZE_X		(1.0f / NUM_PATTERN)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y		(1.0f)					// テクスチャ内の１パターンの高さ

#define	INTERVAL_PATTERN	(3)						// アニメーションの切り替え間隔


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetTextureExplosion(int nExplosionID);
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// 頂点バッファへのポインタ

EXPLOSION				g_aExplosion[MAX_EXPLOSION];	// 爆発のワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitExplosion(void)
{
		//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].scl= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );	//拡大縮小
		g_aExplosion[nCntExplosion].nCount = 0;
		g_aExplosion[nCntExplosion].nPattern = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
								pDevice,			// デバイスへのポインタ
								TEXTURE_EXPLOSION,		// ファイルの名前
								&g_pTextureExplosion);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexExplosion(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	if(g_pTextureExplosion != NULL)
	{// テクスチャの開放
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	if(g_pVtxBuffExplosion != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == true)
		{// 爆発を使用している
			g_aExplosion[nCntExplosion].nCount++;
			if((g_aExplosion[nCntExplosion].nCount % INTERVAL_PATTERN) == 0)
			{// アニメーション切り替え
				g_aExplosion[nCntExplosion].nPattern++;
				if(g_aExplosion[nCntExplosion].nPattern >= NUM_PATTERN  )
				{// アニメーションパターンが終了
					ResetExplosion();
				}
				SetTextureExplosion(nCntExplosion);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[ 0 ];

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスを取得
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// アルファテストの設定
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );		// アルファ値を判定して、該当のピクセルを描画するようにする。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );	// 下の値よりアルファ値が大きければ描画する。
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );				// アルファ値。0で透明な部分。

	// Zテストの設定
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );				// Zテストをする。
	pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );	// 今から描画するものが、既に描画されているもの以下のZ値であれば、描画する。
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//	// Z値の更新

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++ )
	{
		if( pExplosion->bUse == true )
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &pExplosion->mtxWorldExplosion );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &pExplosion->mtxWorldExplosion, NULL, &mtxView );

			pExplosion->mtxWorldExplosion._41 = 0.0f;		// 移動に関する変数をクリア
			pExplosion->mtxWorldExplosion._42 = 0.0f;		// 移動に関する変数をクリア
			pExplosion->mtxWorldExplosion._43 = 0.0f;		// 移動に関する変数をクリア

			// スケールを反映
			D3DXMatrixScaling( &mtxScl, pExplosion->scl.x, pExplosion->scl.y, pExplosion->scl.z );
			D3DXMatrixMultiply( &pExplosion->mtxWorldExplosion, &pExplosion->mtxWorldExplosion, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
	//		D3DXMatrixRotationYawPitchRoll( &mtxRot, pExplosion->rot.y, pExplosion->rot.x, pExplosion->rot.z );	// y,x,z
			D3DXMatrixMultiply( &pExplosion->mtxWorldExplosion, &pExplosion->mtxWorldExplosion, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z );
			D3DXMatrixMultiply( &pExplosion->mtxWorldExplosion, &pExplosion->mtxWorldExplosion, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &pExplosion->mtxWorldExplosion );

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			pDevice->SetStreamSource( 0, g_pVtxBuffExplosion, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture( 0, g_pTextureExplosion );

			// ポリゴンの描画
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,		// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
									( nCntExplosion * 4 ),		// 描画する最初の頂点
									2 );						// 描画するプリミティブ数
		}

		pExplosion++;
	}

	// アルファテストをデフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );	// デフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );	// デフォルトに戻す。

	// Zテストをデフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );			// Zテストをする。
	pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );	// 今から描画するものが、既に描画されているもの以下のZ値であれば、描画する。

	// ライト点灯
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexExplosion( LPDIRECT3DDEVICE9 pDevice )
{
	//頂点バッファの生成
	if( FAILED ( pDevice -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * 4 * MAX_EXPLOSION,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_pVtxBuffExplosion,
												NULL
	) ) )
	{
		return E_FAIL;
	}

	//頂点バッファ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffExplosion -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4 )
	{
		//頂点座標の設定
		pVtx[ 0 ].pos	= D3DXVECTOR3( -EXPLOSION_WIDTH * 0.5f, EXPLOSION_HEIGHT, 0.0f );
		pVtx[ 1 ].pos	= D3DXVECTOR3(  EXPLOSION_WIDTH * 0.5f, EXPLOSION_HEIGHT, 0.0f );
		pVtx[ 2 ].pos	= D3DXVECTOR3( -EXPLOSION_WIDTH * 0.5f, - EXPLOSION_HEIGHT, 0.0f );
		pVtx[ 3 ].pos	= D3DXVECTOR3(  EXPLOSION_WIDTH * 0.5f, - EXPLOSION_HEIGHT, 0.0f );

		//法線の設定
		pVtx[ 0 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 1 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 2 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 3 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		//頂点カラーの設定
		pVtx[ 0 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 1 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 2 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 3 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y);
		pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X, TEXTURE_SIZE_Y);
	}

	//頂点データをアンロックする
	g_pVtxBuffExplosion -> Unlock();

	return S_OK;
}

//=============================================================================
// 爆発の設定
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{	
		if(g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].nCount = 0;
			g_aExplosion[nCntExplosion].nPattern = 0;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
	}
}

//=============================================================================
// 爆発のリセット
//=============================================================================
void ResetExplosion(void)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCount = 0;
		g_aExplosion[nCntExplosion].nPattern = 0;
		g_aExplosion[nCntExplosion].bUse = false;

	}
}
//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureExplosion(int nExplosionID)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nExplosionID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nExplosionID].nPattern * TEXTURE_SIZE_X, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nExplosionID].nPattern + 1) * TEXTURE_SIZE_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nExplosionID].nPattern * TEXTURE_SIZE_X, TEXTURE_SIZE_Y);
	pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nExplosionID].nPattern + 1) * TEXTURE_SIZE_X, TEXTURE_SIZE_Y);

	// 頂点データをアンロックする
	g_pVtxBuffExplosion->Unlock();
}
/*------------------------------------------------------------------------------
|	爆発の取得
------------------------------------------------------------------------------*/
EXPLOSION *GetExplosion(void)
{
	return &g_aExplosion[ 0 ];
}