/*******************************************************************************
* タイトル： ランキング処理
* ファイル名： ranking.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/23
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <stdio.h>
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "fade.h"
#include "score.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define	TEXTURE_SCORE	"data\\TEXTURE\\score.png"	// 読み込むテクスチャファイル名


/*******************************************************************************
* グローバル変数
********************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;					//ランキングスコアテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;					//頂点バッファへのポインタ
D3DXVECTOR3 g_posRankingScore[ RANKINGSCORE_MAX ][ RANKING_MAX ];	//ランキングスコアの位置
RANKING *g_pRanking = NULL;											//ランキングへのポインタ
int g_nRankingScoreDigits[ RANKINGSCORE_MAX ][ RANKING_MAX ];		//ランキングスコアの桁の数字格納ワーク
int g_nNumRanking = RANKING_MAX;									//ランキングの総数
int nCnt;															//扱い用変数
bool g_RankingUpdateUse;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

/*******************************************************************************
* 関数名: InitRanking
*******************************************************************************/
HRESULT InitRanking( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice, TEXTURE_SCORE, &g_pTextureRankingScore );

	g_RankingUpdateUse = false;

	// 頂点情報の作成
	MakeVertexRanking(pDevice);
	return S_OK;
}

/*******************************************************************************
* 関数名: UninitRanking
*******************************************************************************/
void UninitRanking( void )
{

	if( g_pTextureRankingScore != NULL )
	{
		g_pTextureRankingScore -> Release();	//ランキングスコアテクスチャの開放
		g_pTextureRankingScore = NULL;
	}

	if( g_pVtxBuffRankingScore != NULL )
	{
		g_pVtxBuffRankingScore -> Release();	//頂点バッファの開放
		g_pVtxBuffRankingScore = NULL;
	}
}

/*******************************************************************************
* 関数名: UpdateRanking
*******************************************************************************/
void UpdateRanking( void )
{
	VERTEX_2D *pVtx;

	g_pVtxBuffRankingScore -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	RANKING *pRanking = g_pRanking;

	for( int nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++ )
	{
		for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX; nCntRankingScore++, pVtx+=4)
		{

			g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] = pRanking -> nScore % Powi( 10, RANKINGSCORE_MAX - nCntRankingScore ) / Powi( 10, RANKINGSCORE_MAX - nCntRankingScore - 1 );

			pVtx[ 0 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f );
			pVtx[ 0 ].tex.y = 0.0f;

			pVtx[ 1 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f + 0.10f );
			pVtx[ 1 ].tex.y = 0.0f;
		 
			pVtx[ 2 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f );
			pVtx[ 2 ].tex.y = 1.0f;

			pVtx[ 3 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f + 0.10f );
			pVtx[ 3 ].tex.y = 1.0f;
		}
		pRanking++;
	}

	g_pVtxBuffRankingScore -> Unlock();
}

/*******************************************************************************
* 関数名: DrawRanking
*******************************************************************************/
void DrawRanking( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource( 0, g_pVtxBuffRankingScore, 0, sizeof( VERTEX_2D ) );

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//ランキングスコアテクスチャの設定
	pDevice -> SetTexture( 0, g_pTextureRankingScore );

	for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX * RANKING_MAX; nCntRankingScore++ )
	{
		//ランキングスコアの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, nCntRankingScore * 4, 2 );
	}
}	

//=============================================================================
// データ書き出し
//=============================================================================
void SaveRanking( void )
{
	FILE *pFile;

	if( g_RankingUpdateUse )
	{
		/*pFile = fopen( RANKING_FILE, "wb" );*/
		fopen_s( &pFile, RANKING_FILE, "wb" );

		if( pFile )
		{
			// プレイヤー数の書き出し
			fwrite( &g_nNumRanking, 4, 1, pFile );

			// プレイヤーデータの書き込み
			fwrite( g_pRanking, sizeof( RANKING ), g_nNumRanking, pFile);

			fclose( pFile );
			g_RankingUpdateUse = false;
		}
	}
}

//=============================================================================
// データ読み込み
//=============================================================================
void LoadRanking( void )
{
	FILE *pFile;

	// ファイルオープン
	/*pFile = fopen( RANKING_FILE, "rb" );*/
	fopen_s( &pFile, RANKING_FILE, "rb" );

	if( pFile )
	{
		// 読み込み
		fread( &g_nNumRanking, 4, 1, pFile );

		if( g_pRanking )
		{
			free( g_pRanking );
			g_pRanking = NULL;
		}
		g_pRanking = ( RANKING * ) malloc ( sizeof( RANKING ) * g_nNumRanking );

		// プレイヤーデータの書き込み
		fread( g_pRanking, sizeof( RANKING ), g_nNumRanking, pFile );
		
		// ファイルクローズ
		fclose( pFile );
	}
	else
	{
		if( g_pRanking )
		{
			free( g_pRanking );
			g_pRanking = NULL;
		}
		g_pRanking = ( RANKING * ) malloc ( sizeof( RANKING ) * g_nNumRanking );

		RANKING *pRanking = g_pRanking;

		for( int nCntRanking = 0; nCntRanking < g_nNumRanking; nCntRanking++ )
		{
			pRanking -> nScore = 500 - 100 * nCntRanking;
			pRanking++;
		}
	}
}

void CompareRanking( void )
{
	SCORE *pScore;
	RANKING *pRanking = g_pRanking;
	pScore = GetScore();

	for( int nCntRanking = 0; nCntRanking < g_nNumRanking; nCntRanking++ )
	{
		if( pScore -> g_nScore >= ( pRanking + ( nCntRanking ) ) -> nScore )
		{
			for( int nCntCompare = 4; nCntCompare > nCntRanking; nCntCompare-- )
			{
				( pRanking + ( nCntCompare ) ) -> nScore = ( pRanking + ( nCntCompare - 1 ) ) -> nScore;
			}
			( pRanking  + ( nCntRanking ) ) -> nScore = pScore -> g_nScore;
			g_RankingUpdateUse = true;
			pScore ->g_nScore = 0;

			VERTEX_2D *pVtx;
			g_pVtxBuffRankingScore -> Lock( 0, 0, ( void** ) &pVtx, 0 );

			for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX ; nCntRankingScore++ ,pVtx+=4)
			{
				//頂点カラーの設定(色変わる)
				pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
				pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
				pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
				pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
			}

			break;
		}
	}
}
/*******************************************************************************
* 関数名: HRESULT Powi
*******************************************************************************/
HRESULT Powi( int x, int y )
{
	return ( int )( powf( ( float )x, ( float )y ) );
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファの生成
	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * ( RANKINGSCORE_MAX * RANKING_MAX + 2 ) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRankingScore, NULL ) ) )
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffRankingScore -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++ )
	{
		for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX; nCntRankingScore++, pVtx+=4 )
		{
			g_posRankingScore[ nCntRankingScore ][ nCntRanking ] = D3DXVECTOR3( RANKINGSCORE_POSX + RANKINGSCORE_WIDTH * nCntRankingScore, RANKINGSCORE_POSY + RANKINGSCORE_HEIGHT * nCntRanking, 0.0f );

			//頂点座標の初期化
			pVtx[ 0 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x - RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 0 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y - RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 0 ].pos.z = 0.0f;

			pVtx[ 1 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x + RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 1 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y - RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 1 ].pos.z = 0.0f;

			pVtx[ 2 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x - RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 2 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y + RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 2 ].pos.z = 0.0f;

			pVtx[ 3 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x + RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 3 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y + RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 3 ].pos.z = 0.0f;

			//頂点座標の設定
			pVtx[ 0 ].pos = D3DXVECTOR3( pVtx[ 0 ].pos.x, pVtx[ 0 ].pos.y, pVtx[ 0 ].pos.z );
			pVtx[ 1 ].pos = D3DXVECTOR3( pVtx[ 1 ].pos.x, pVtx[ 1 ].pos.y, pVtx[ 1 ].pos.z );
			pVtx[ 2 ].pos = D3DXVECTOR3( pVtx[ 2 ].pos.x, pVtx[ 2 ].pos.y, pVtx[ 2 ].pos.z );
			pVtx[ 3 ].pos = D3DXVECTOR3( pVtx[ 3 ].pos.x, pVtx[ 3 ].pos.y, pVtx[ 3 ].pos.z );

			pVtx[ 0 ].rhw = 1.0f;
			pVtx[ 1 ].rhw = 1.0f;
			pVtx[ 2 ].rhw = 1.0f;
			pVtx[ 3 ].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			//テクスチャ座標の設定
			pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
			pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
		}
	}
	g_pVtxBuffRankingScore -> Unlock();

	return S_OK;
}