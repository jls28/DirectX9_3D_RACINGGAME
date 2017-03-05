/*******************************************************************************
* タイトル： 影描画関数
* ファイル名： shadow.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/18
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "shadow.h"
#include "input.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define SHADOW_TEXTURE_FILE "data\\TEXTURE\\shadow000.jpg"	//影のテクスチャファイル位置
#define SHADOW_MAX ( 256 )							//影の最大数

/*******************************************************************************
* グローバル変数
********************************************************************************/
SHADOW	g_Shadow[ SHADOW_MAX ];									//影の構造体

/*******************************************************************************
* 関数名: シャドーの初期化関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
HRESULT InitShadow( void )
{
	for( int nCntShadow = 0; nCntShadow < SHADOW_MAX; nCntShadow++ )
	{
		//デバイスのゲッター
		LPDIRECT3DDEVICE9 pDevice	= GetDevice();

		//シャドー構造体の初期化
		g_Shadow[ nCntShadow ].pVtxBuff = NULL;	//頂点バッファへのポインタ
		g_Shadow[ nCntShadow ].pTexture = NULL;	//テクスチャバッファへのポインタ
		g_Shadow[ nCntShadow ].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );	//向き
		g_Shadow[ nCntShadow ].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );	//拡大縮小

		//頂点バッファの生成
		if( FAILED ( pDevice -> CreateVertexBuffer(
													sizeof( VERTEX_3D ) * 4,
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_3D,
													D3DPOOL_MANAGED,
													&g_Shadow[ nCntShadow ].pVtxBuff,
													NULL
		) ) )
		{
			return E_FAIL;
		}

		//テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, SHADOW_TEXTURE_FILE, &g_Shadow[ nCntShadow ].pTexture );
	}
	return S_OK;
}

/*******************************************************************************
* 関数名: シャドーの終了関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UninitShadow( void )
{
	for( int nCntShadow = 0; nCntShadow < SHADOW_MAX; nCntShadow++ )
	{
		if( g_Shadow[ nCntShadow ].pTexture != NULL )
		{
			g_Shadow[ nCntShadow ].pTexture -> Release();	//テクスチャポリゴンの開放
			g_Shadow[ nCntShadow ].pTexture = NULL;
		}

		if( g_Shadow[ nCntShadow ].pVtxBuff != NULL )		//頂点バッファの開放
		{
			g_Shadow[ nCntShadow ].pVtxBuff -> Release();
			g_Shadow[ nCntShadow ].pVtxBuff = NULL;
		}
	}
}

/*******************************************************************************
* 関数名: シャドーの描画関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void DrawShadow( void )
{
	for( int nCntShadow = 0; nCntShadow < SHADOW_MAX; nCntShadow++ )
	{
		if( g_Shadow[ nCntShadow ].bUse )
		{
			//デバイスのゲッター
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_Shadow[ nCntShadow ].mtxWorld );

			//スケールを反映
			D3DXMatrixScaling(
								&g_Shadow[ nCntShadow ].mtxScl,
								g_Shadow[ nCntShadow ].scl.x,
								g_Shadow[ nCntShadow ].scl.y,
								g_Shadow[ nCntShadow ].scl.z
			);
			D3DXMatrixMultiply(
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxScl
			);

			//回転を反映
			D3DXMatrixRotationYawPitchRoll(
								&g_Shadow[ nCntShadow ].mtxRot,
								g_Shadow[ nCntShadow ].rot.y,
								g_Shadow[ nCntShadow ].rot.x,
								g_Shadow[ nCntShadow ].rot.z
			);
			D3DXMatrixMultiply(
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxRot
			);

			//位置を反映
			D3DXMatrixTranslation(
								&g_Shadow[ nCntShadow ].mtxTrans,
								g_Shadow[ nCntShadow ].pos.x,
								g_Shadow[ nCntShadow ].pos.y,
								g_Shadow[ nCntShadow ].pos.z
			);
			D3DXMatrixMultiply(
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxTrans
			);

			//レンダーステートの設定
			pDevice -> SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
			pDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

			//ワールドマトリックスを設定
			pDevice -> SetTransform( D3DTS_WORLD, &g_Shadow[ nCntShadow ].mtxWorld );

			//頂点バッファをデータストリームにバインドする
			pDevice -> SetStreamSource( 0, g_Shadow[ nCntShadow ].pVtxBuff, 0, sizeof( VERTEX_3D ) );

			//頂点フォーマットの設定
			pDevice -> SetFVF( FVF_VERTEX_3D );

			//テクスチャの設定
			pDevice -> SetTexture( 0, g_Shadow[ nCntShadow ].pTexture );

			//ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

			//レンダーステートの設定を元に戻す
			pDevice -> SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
			pDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		}
	}
}

/*******************************************************************************
* 関数名: セットシャドーの関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void SetShadow( D3DXVECTOR3 pos, float fWIDTH, float fHEIGHT, int nCntShadow, bool bUse )
{
	float fScl;

	g_Shadow[ nCntShadow ].bUse = bUse;

	if( g_Shadow[ nCntShadow ].bUse == true )
	{
		//拡大率
		fScl = 1.0f + pos.y * 0.01f;

		g_Shadow[ nCntShadow ].pos = D3DXVECTOR3( pos.x, 0.01f, pos.z );	//位置
		g_Shadow[ nCntShadow ].scl = D3DXVECTOR3( fScl, fScl, fScl );		//拡大縮小

		//頂点バッファの初期化
		VERTEX_3D *pVtx;

		g_Shadow[ nCntShadow ].pVtxBuff -> Lock( 0, 0, ( void** ) &pVtx, 0 );

		pVtx[ 0 ].pos = D3DXVECTOR3( -fWIDTH * 0.5f, 0.01f,  fHEIGHT * 0.5f );
		pVtx[ 1 ].pos = D3DXVECTOR3(  fWIDTH * 0.5f, 0.01f,  fHEIGHT * 0.5f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -fWIDTH * 0.5f, 0.01f, -fHEIGHT * 0.5f );
		pVtx[ 3 ].pos = D3DXVECTOR3(  fWIDTH * 0.5f, 0.01f, -fHEIGHT * 0.5f );

		//法線の設定
		pVtx[ 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		//頂点カラーの設定
		pVtx[ 0 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );
		pVtx[ 1 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );
		pVtx[ 2 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );
		pVtx[ 3 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );

		//テクスチャ座標の設定
		pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

		g_Shadow[ nCntShadow ].pVtxBuff -> Unlock();
	}
}

/*******************************************************************************
* 関数名: シャドーの取得関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
SHADOW *GetShadow( void )
{
	return &g_Shadow[ 0 ];
}