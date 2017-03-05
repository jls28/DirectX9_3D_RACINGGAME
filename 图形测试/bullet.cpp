//************************************************************************************************************************************************************************************************
// インクルードファイル
//************************************************************************************************************************************************************************************************
#include <stdlib.h>
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "explosion.h"
#include "meshWall.h"
#include "effect.h"
//************************************************************************************************************************************************************************************************
// マクロ定義
//************************************************************************************************************************************************************************************************
#define BULLET_TEXTURE_FILE	"data\\TEXTURE\\bullet000.png"	//弾のテクスチャファイル位置
#define POSMOVE_BULLET		(   15.00f )		// 弾の移動量
#define CEILING				(  200.0f )		// 天井
#define GROUND				(    1.0f )		// 地面
#define XPOS_BULLET			(   20.0f )		// Xの中心座標
#define YPOS_BULLET			(   20.0f )		// Yの中心座標
#define ZPOS_BULLET			(  -30.0f )		// Zの中心座標
#define XPOS_LEFT_VERTEX	(   -10.0f )		// 左Xの頂点座標
#define XPOS_RIGHT_VERTEX	(    10.0f )		// 右Xの頂点座標
#define YPOS_UP_VERTEX		(    10.0f )		// 上Yの頂点座標
#define YPOS_DOWN_VERTEX	(   -10.0f )		// 下Yの頂点座標
#define MAX_VERTEX			( 4 )			// ポリゴンの頂点の数
//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
BULLET g_aBullet[ MAX_BULLET ];		// 弾の情報
//================================================================================================================================================================================================
// InitBullet関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitBullet( void )
{
	// Direct3Dデバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 弾のポインタを取得
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	VERTEX_3D *pVtx;

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		if( pBullet->bUse == false )
		{
			pBullet->pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			pBullet->rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			pBullet->scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			pBullet->collisoin = ( fabs( XPOS_LEFT_VERTEX ) + fabs( XPOS_RIGHT_VERTEX ) ) / 2;
			pBullet->nLife = LIFE_BULLET;
			pBullet->nType = BULLETTYPE_PLAYER_HOMING;

			// テクスチャの読み込み
			D3DXCreateTextureFromFile( pDevice, BULLET_TEXTURE_FILE, &pBullet->pTextureBullet );

			// 頂点バッファの生成
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_BULLET * 4 ),	// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// 使用する頂点フォーマット
													 D3DPOOL_MANAGED,
													 &pBullet->pVtxBuffBullet,
													 NULL ) ) )
			{
				return E_FAIL;
			}

			// 頂点情報の設定//////////////////////////////////////////////////////////////////////////////
			// 頂点情報へのポインタを取得
			pBullet->pVtxBuffBullet->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntBullet * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_VERTEX,  YPOS_UP_VERTEX,   0.0f );	// 頂点座標
			pVtx[ ( nCntBullet * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_VERTEX, YPOS_UP_VERTEX,   0.0f );
			pVtx[ ( nCntBullet * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_VERTEX,  YPOS_DOWN_VERTEX, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_VERTEX, YPOS_DOWN_VERTEX, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// 法線の向き
			pVtx[ ( nCntBullet * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// 頂点カラー
			pVtx[ ( nCntBullet * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBullet * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBullet * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBullet * 4 ) + 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );					// テクスチャ座標
			pVtx[ ( nCntBullet * 4 ) + 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ ( nCntBullet * 4 ) + 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
			pBullet->pVtxBuffBullet->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// 使用してない状態にする。
			pBullet->bUse = false;
		}
		pBullet++;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitBullet関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitBullet( void )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		// テクスチャの開放
		if( pBullet->pTextureBullet != NULL )
		{
			pBullet->pTextureBullet->Release();
			pBullet->pTextureBullet = NULL;
		}

		// 頂点バッファの開放
		if( pBullet->pVtxBuffBullet != NULL )
		{
			pBullet->pVtxBuffBullet->Release();
			pBullet->pVtxBuffBullet = NULL;
		}
		pBullet++;
	}
}

//================================================================================================================================================================================================
// UpdateBullet関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdateBullet( void )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++,pBullet++)
	{
		if( pBullet->bUse == true )
		{
			// 位置の更新
			pBullet->pos.x += sinf( D3DX_PI + pBullet->rot.y ) * POSMOVE_BULLET;		// 角度 * 移動量
			pBullet->pos.z += cosf( D3DX_PI + pBullet->rot.y ) * POSMOVE_BULLET;		// 角度 * 移動量
			// 寿命の更新
			pBullet->nLife--;
			// 弾の寿命がくれば消す。
			if( pBullet->nLife <= 0 )
			{
				pBullet->bUse = false;
			}
			MESHWALL *pWall = GetMeshWall();
			// 壁と床と天井の衝突判定//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//if( (pWall + WALL_FRONT)->pos.z < ( pBullet->pos.z + pBullet->collisoin ) )
			//{	// 奥の壁
			//	SetExplosion( pBullet->pos);
			//	pBullet->bUse = false;
			//}
			//else if( (pWall + WALL_BACK)->pos.z > ( pBullet->pos.z - pBullet->collisoin ) )
			//{	// 前の壁
			//	SetExplosion( pBullet->pos);
			//	pBullet->bUse = false;
			//}
			if( (pWall + WALL_LEFT)->pos.x > ( pBullet->pos.x - pBullet->collisoin ) )
			{	// 左の壁
				SetExplosion( pBullet->pos );
				pBullet->bUse = false;
			}
			else if((pWall + WALL_RIGHT)->pos.x < ( pBullet->pos.x + pBullet->collisoin ) )
			{	// 右の壁
				SetExplosion( pBullet->pos );
				pBullet->bUse = false;
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		//影の設定
		SetShadow( pBullet-> pos, BULLET_WIDTH, BULLET_HEIGHT, 1 + nCntBullet, pBullet -> bUse );
	}
}

//================================================================================================================================================================================================
// DrawBullet関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawBullet( void )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ビューマトリックスを取得
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// レンダーステートの設定（アルファテスト）
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// アルファ値を判定して、該当のピクセルを描画するようにする。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// 下の値よりアルファ値が大きければ描画する。
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// アルファ値。0で透明な部分。

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		if( pBullet->bUse == true )
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &pBullet->mtxWorldBullet );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &pBullet->mtxWorldBullet, NULL, &mtxView );

			pBullet->mtxWorldBullet._41 = 0.0f;		// 移動に関する変数をクリア
			pBullet->mtxWorldBullet._42 = 0.0f;		// 移動に関する変数をクリア
			pBullet->mtxWorldBullet._43 = 0.0f;		// 移動に関する変数をクリア

			// スケールを反映
			D3DXMatrixScaling( &mtxScl, pBullet->scl.x, pBullet->scl.y, pBullet->scl.z );
			D3DXMatrixMultiply( &pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
	//		D3DXMatrixRotationYawPitchRoll( &mtxRot, pBullet->rot.y, pBullet->rot.x, pBullet->rot.z );	// y,x,z
			D3DXMatrixMultiply( &pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z );
			D3DXMatrixMultiply( &pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &pBullet->mtxWorldBullet );

			// 頂点バッファをデータストリーム（ベルトコンベア）にバインドする（取り付ける）。
			pDevice->SetStreamSource( 0, pBullet->pVtxBuffBullet, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture( 0, pBullet->pTextureBullet );

			// ポリゴンの描画
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELISTで個別の三角形の描画。TRIANGLESTRIPでつながった三角、そして四角。TRIANGLEFANで円。
									( nCntBullet * 4 ),								// 描画する最初の頂点
									2 );										// 描画するプリミティブ数
		}
		pBullet++;
	}

	// レンダーステートの設定をデフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。

	// ライト点灯
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//================================================================================================================================================================================================
// *GetBullet関数
// 引数 void
// 戻り値 
// 説明 Bulletを取得する。
//================================================================================================================================================================================================
BULLET *GetBullet( void )
{
	return &g_aBullet[ 0 ];
}

//================================================================================================================================================================================================
// *GetBulletPos関数
// 引数 void
// 戻り値 
// 説明 Bulletの座標を取得する。
//================================================================================================================================================================================================
D3DXVECTOR3 *GetBulletPos( void )
{
	return &g_aBullet[ 0 ].pos;
}

//================================================================================================================================================================================================
// SetBullet関数
// 引数 pos 座標, rot 向き, nLife 寿命
// 戻り値 void
// 説明 Bulletをセットする。
//================================================================================================================================================================================================
void SetBullet( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		if( pBullet->bUse == false )
		{
			// 位置の設定
			pBullet->pos = pos;

			// 移動量の設定
			pBullet->rot = rot;

			// 寿命の設定
			pBullet->nLife = nLife;

			// 弾を使用状態にする
			pBullet->bUse = true;
			break;
		}
		pBullet++;
	}
}