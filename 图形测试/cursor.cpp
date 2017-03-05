/*------------------------------------------------------------------------------
|	タイトル：		カーソルの処理
|	ファイル名：	cursor.cpp
|	作成者：		AT12A244 46 LI HAOSHENG
|	作成日：		2016/01/24
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	更新履歴:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "main.h"
#include "input.h"

#include "cursor.h"

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/
#define	CURSOR_TEXTURE_FILE	"data\\TEXTURE\\cursor000.png"	//カーソルのテクスチャファイル位置

/*------------------------------------------------------------------------------
|	グローバル変数
------------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9			g_pTextureCursor = NULL;		//テクスチャポリゴンへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCursor = NULL;		//頂点バッファへのポインタ
CURSOR						g_Cursor;						//カーソルのワーク

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
HRESULT	MakeVertexCursor( LPDIRECT3DDEVICE9 pDevice );
void SetVertexCursor( void );

/*------------------------------------------------------------------------------
|	初期化処理
------------------------------------------------------------------------------*/
HRESULT InitCursor( void )
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//カーソル構造体の初期化
	g_Cursor.bUse = true;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
								pDevice,
								CURSOR_TEXTURE_FILE,	//テクスチャファイル位置
								&g_pTextureCursor		//テクスチャバッファへのポインタ
	);

	//頂点情報の作成
	MakeVertexCursor( pDevice );

	return S_OK;
}

/*------------------------------------------------------------------------------
|	終了処理
------------------------------------------------------------------------------*/
void UninitCursor( void )
{
	// メッシュ情報の開放
		if( g_pTextureCursor != NULL )
		{
			g_pTextureCursor->Release();
			g_pTextureCursor = NULL;
		}

		// バッファの開放
		if( g_pVtxBuffCursor != NULL )
		{
			g_pVtxBuffCursor->Release();
			g_pVtxBuffCursor = NULL;
		}
}

/*------------------------------------------------------------------------------
|	描画処理
------------------------------------------------------------------------------*/
void DrawCursor( void )
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice -> SetStreamSource( 0, g_pVtxBuffCursor, 0, sizeof( VERTEX_2D ) );

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D );

	// レンダーステートの設定（zテスト）
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z値の更新

	// レンダーステートの設定（アルファテスト）
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// アルファ値を判定して、該当のピクセルを描画するようにする。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// 下の値よりアルファ値が大きければ描画する。
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// アルファ値。0で透明な部分。

	//テクスチャの設定
	pDevice -> SetTexture( 0, g_pTextureCursor );

	if( g_Cursor.bUse == true )
	{//カーソル使用中なら
		//ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON );
	}
}

/*------------------------------------------------------------------------------
|	頂点バッファ情報作成
------------------------------------------------------------------------------*/
HRESULT MakeVertexCursor( LPDIRECT3DDEVICE9 pDevice )
{
	//頂点バッファの生成
	if( FAILED ( pDevice -> CreateVertexBuffer
	(
		sizeof( VERTEX_2D ) * 4,	//頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					//頂点バッファの使用法
		FVF_VERTEX_2D,						//使用する頂点フォーマット
		D3DPOOL_MANAGED,					//リソースのバッファを保持するメモリクラスを指定
		&g_pVtxBuffCursor,					//頂点バッファインターフェースへのポインタ
		NULL								//NULLに設定
	) ) )
	{
		return E_FAIL;
	}

//頂点バッファの中身を埋める
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffCursor -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	//頂点座標の設定
	pVtx[ 0 ].pos = D3DXVECTOR3( - CURSOR_WIDTH / 2, - CURSOR_HEIGHT / 2, 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3(   CURSOR_WIDTH / 2, - CURSOR_HEIGHT / 2, 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( - CURSOR_WIDTH / 2,   CURSOR_HEIGHT / 2, 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3(   CURSOR_WIDTH / 2,   CURSOR_HEIGHT / 2, 0.0f );

	//rhwの設定
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[ 0 ].col =
	pVtx[ 1 ].col =
	pVtx[ 2 ].col =
	pVtx[ 3 ].col = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	//テクスチャ座標の設定
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

	//頂点データをアンロックする
	g_pVtxBuffCursor -> Unlock();

	return S_OK;
}

/*------------------------------------------------------------------------------
|	頂点座標設定
------------------------------------------------------------------------------*/
void SetVertexCursor( void )
{
	VERTEX_2D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffCursor -> Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3( g_Cursor.x - CURSOR_WIDTH * 0.5f, g_Cursor.y - CURSOR_HEIGHT * 0.5f, 0.0f );
	pVtx[1].pos = D3DXVECTOR3( g_Cursor.x + CURSOR_WIDTH * 0.5f, g_Cursor.y - CURSOR_HEIGHT * 0.5f, 0.0f );
	pVtx[2].pos = D3DXVECTOR3( g_Cursor.x - CURSOR_WIDTH * 0.5f, g_Cursor.y + CURSOR_HEIGHT * 0.5f, 0.0f );
	pVtx[3].pos = D3DXVECTOR3( g_Cursor.x + CURSOR_WIDTH * 0.5f, g_Cursor.y + CURSOR_HEIGHT * 0.5f, 0.0f );

	// 頂点データをアンロックする
	g_pVtxBuffCursor -> Unlock();
}

/*------------------------------------------------------------------------------
|	カーソル設定
------------------------------------------------------------------------------*/
void SetCursor( int x, int y )
{
	CURSOR *pCursor = &g_Cursor;
	if( pCursor -> bUse == true )
	{
		//位置を設定
		pCursor -> x = x;
		pCursor -> y = y;
		SetVertexCursor();
	}
}
