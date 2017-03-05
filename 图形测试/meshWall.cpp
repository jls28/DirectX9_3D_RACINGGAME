#include "main.h"
#include "input.h"
#include "meshField.h"
#include "use.h"

#include "meshWall.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define MESHWALL_TEXTURE_FILE	"data\\TEXTURE\\fence000.jpg"	//壁テクスチャファイル位置
#define MESHWALL_WIDTH			( 50.0f )						//ウォールの幅
#define MESHWALL_HEIGHT			( 20.0f )						//ウォールの高さ

/*******************************************************************************
* グローバル変数
********************************************************************************/
MESHWALL	g_Wall[ WALL_MAX ];									//ウォール構造体

/*******************************************************************************
* 関数名: メッシュウォールの初期化関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
HRESULT InitMeshWall( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESHFIELD *pField;
	pField = GetMeshField();

	for( int nCntMeshWall = 0; nCntMeshWall < WALL_MAX; nCntMeshWall++ )
	{
		//メッシュウォール構造体の初期化
		g_Wall[ nCntMeshWall ].pTexture = NULL;													//テクスチャバッファへのポインタ
		g_Wall[ nCntMeshWall ].pIdxBuff = NULL;													//頂点バッファへのポインタ
		g_Wall[ nCntMeshWall ].pIdxBuff = NULL;													//インデックスバッファへのポインタ

		g_Wall[ nCntMeshWall ].mesh.nNumVtxV		= 100;					//横の頂点数
		g_Wall[ nCntMeshWall ].mesh.nNumVtxH		= 2;										//縦の頂点数

		//総頂点数
		g_Wall[ nCntMeshWall ].mesh.nNumVtx			= g_Wall[ nCntMeshWall ].mesh.nNumVtxV * g_Wall[ nCntMeshWall ].mesh.nNumVtxH;

		//インデックス数
		g_Wall[ nCntMeshWall ].mesh.nNumIdx			= ( g_Wall[ nCntMeshWall ].mesh.nNumVtx - g_Wall[ nCntMeshWall ].mesh.nNumVtxV + g_Wall[ nCntMeshWall ].mesh.nNumVtxH - 2 ) * 2;

		g_Wall[ nCntMeshWall ].mesh.nNumBlock		= g_Wall[ nCntMeshWall ].mesh.nNumVtxV - 1;	//ブロック数
		g_Wall[ nCntMeshWall ].mesh.nNumPrimitive	= g_Wall[ nCntMeshWall ].mesh.nNumIdx - 2;	//ポリゴン数
		g_Wall[ nCntMeshWall ].mesh.fTexAdjust		= 0.0f;										//テクスチャY座標ずらす係数
		g_Wall[ nCntMeshWall ].mesh.nNumIdxEven		= 0;										//インデックスバッファ頂点が偶数の数(退化三角形頂点以外)
		g_Wall[ nCntMeshWall ].mesh.nNumNullTri		= 0;										//縮退ポリゴン頂点の数
		g_Wall[ nCntMeshWall ].mesh.nMultiple		= 2;										//インデックスバッファ用係数


		//頂点バッファの生成
		if( FAILED ( pDevice -> CreateVertexBuffer(
													sizeof( VERTEX_3D ) * g_Wall[ nCntMeshWall ].mesh.nNumVtx,
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_3D,
													D3DPOOL_MANAGED,
													&g_Wall[ nCntMeshWall ].pVtxBuff,
													NULL
		) ) )
		{
			return E_FAIL;
		}

		//テクスチャの読み込み
		D3DXCreateTextureFromFile( pDevice, MESHWALL_TEXTURE_FILE, &g_Wall[ nCntMeshWall ].pTexture );
	}
	///*0番目壁の頂点情報作成*/
	//MeshWallVtx(
	//			 g_Wall[ 0 ].pVtxBuff,
	//			&g_Wall[ 0 ],											//ウォールの構造体
	//			D3DXVECTOR3( 0.0f, 0.0f, pField -> fFixedPos ),			//ウォールの中心位置
	//			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//ウォールの回転
	//			D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//ウォールの拡大縮小
	//			WALL_FRONT,												//ウォールの向き情報
	//			MESHWALL_WIDTH,											//ウォールの幅
	//			MESHWALL_HEIGHT											//ウォールの高さ
	//);
	///*1番目壁の頂点情報作成*/
	//MeshWallVtx(
	//			 g_Wall[ 1 ].pVtxBuff,
	//			&g_Wall[ 1 ],											//ウォールの構造体
	//			D3DXVECTOR3( 0.0f, 0.0f, -( pField -> fFixedPos ) ),	//ウォールの中心位置
	//			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//ウォールの回転
	//			D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//ウォールの拡大縮小
	//			WALL_BACK,												//ウォールの向き情報
	//			MESHWALL_WIDTH,												//ウォールの幅
	//			MESHWALL_HEIGHT											//ウォールの高さ
	//);
	/*2番目壁の頂点情報作成*/
	MeshWallVtx(
				 g_Wall[ 2 ].pVtxBuff,
				&g_Wall[ 2 ],											//ウォールの構造体
				D3DXVECTOR3(/* -( pField -> fFixedPos )*/TRACK_WIDTH_LEFT, 0.0f, 0.0f ),	//ウォールの中心位置
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//ウォールの回転
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//ウォールの拡大縮小
				WALL_LEFT,												//ウォールの向き情報
				MESHWALL_WIDTH,											//ウォールの幅
				MESHWALL_HEIGHT											//ウォールの高さ
	);
	/*3番目壁の頂点情報作成*/
	MeshWallVtx(
				 g_Wall[ 3 ].pVtxBuff,
				&g_Wall[ 3 ],											//ウォールの構造体
				D3DXVECTOR3( /*pField -> fFixedPos*/TRACK_WIDTH_RIGHT, 0.0f, 0.0f ),			//ウォールの中心位置
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//ウォールの回転
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//ウォールの拡大縮小
				WALL_RIGHT,												//ウォールの向き情報
				MESHWALL_WIDTH,											//ウォールの幅
				MESHWALL_HEIGHT											//ウォールの高さ
	);

	for( int nCntIdxWall = 0; nCntIdxWall < WALL_MAX; nCntIdxWall++ )
	{
		//インデックスバッファを確保
		if( FAILED ( pDevice -> CreateIndexBuffer(
										sizeof( WORD ) * g_Wall[ nCntIdxWall ].mesh.nNumIdx,
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&g_Wall[ nCntIdxWall ].pIdxBuff,
										NULL
		) ) )
		{
			return E_FAIL;
		}

		MeshIdx(
				g_Wall[ nCntIdxWall ].pIdxBuff,	//インデックスバッファへのポインター
				&g_Wall[ nCntIdxWall ].mesh		//ウォールのメッシュ情報
		);
	}

	return S_OK;
}

/*******************************************************************************
* 関数名: メッシュウォールの終了関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UninitMeshWall( void )
{
	for( int nCntMeshWall = 0; nCntMeshWall < WALL_MAX; nCntMeshWall++ )
	{
		if( g_Wall[ nCntMeshWall ].pTexture != NULL )
		{
			g_Wall[ nCntMeshWall ].pTexture -> Release();	//テクスチャバッファの開放
			g_Wall[ nCntMeshWall ].pTexture = NULL;
		}

		if( g_Wall[ nCntMeshWall ].pVtxBuff != NULL )		//頂点バッファの開放
		{
			g_Wall[ nCntMeshWall ].pVtxBuff -> Release();
			g_Wall[ nCntMeshWall ].pVtxBuff = NULL;
		}

		if( g_Wall[ nCntMeshWall ].pIdxBuff != NULL )		//インデックスバッファの開放
		{
			g_Wall[ nCntMeshWall ].pIdxBuff -> Release();
			g_Wall[ nCntMeshWall ].pIdxBuff = NULL;
		}
	}
}

/*******************************************************************************
* 関数名: メッシュウォールの更新関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UpdateMeshWall( void )
{

}

/*******************************************************************************
* 関数名: メッシュウォールの描画関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void DrawMeshWall( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntMeshWall = 0; nCntMeshWall < WALL_MAX; nCntMeshWall++ )
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_Wall[ nCntMeshWall ].mtx.World );

		//スケールを反映
		D3DXMatrixScaling(
							&g_Wall[ nCntMeshWall ].mtx.Scl,
							g_Wall[ nCntMeshWall ].scl.x,
							g_Wall[ nCntMeshWall ].scl.y,
							g_Wall[ nCntMeshWall ].scl.z
		);
		D3DXMatrixMultiply(
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.Scl
		);

		//回転を反映
		D3DXMatrixRotationYawPitchRoll(
							&g_Wall[ nCntMeshWall ].mtx.Rot,
							g_Wall[ nCntMeshWall ].rot.y,
							g_Wall[ nCntMeshWall ].rot.x,
							g_Wall[ nCntMeshWall ].rot.z
		);
		D3DXMatrixMultiply(
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.Rot
		);

		//位置を反映
		D3DXMatrixTranslation(
							&g_Wall[ nCntMeshWall ].mtx.Trans,
							g_Wall[ nCntMeshWall ].pos.x,
							g_Wall[ nCntMeshWall ].pos.y,
							g_Wall[ nCntMeshWall ].pos.z
		);
		D3DXMatrixMultiply(
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.Trans
		);

		//ワールドマトリックスを設定
		pDevice -> SetTransform( D3DTS_WORLD, &g_Wall[ nCntMeshWall ].mtx.World );

		//頂点バッファをデータストリームにバインドする
		pDevice -> SetStreamSource( 0, g_Wall[ nCntMeshWall ].pVtxBuff, 0, sizeof( VERTEX_3D ) );

		//インデックスバッファをデータストリームにバインドする
		pDevice -> SetIndices( g_Wall[ nCntMeshWall ].pIdxBuff );

		//頂点フォーマットの設定
		pDevice -> SetFVF( FVF_VERTEX_3D );

		//テクスチャの設定
		pDevice -> SetTexture( 0, g_Wall[ nCntMeshWall ].pTexture );

		//ポリゴンの描画
		pDevice -> DrawIndexedPrimitive(
										D3DPT_TRIANGLESTRIP,
										0,
										0,
										g_Wall[ nCntMeshWall ].mesh.nNumVtx,					//頂点数
										0,
										g_Wall[ nCntMeshWall ].mesh.nNumPrimitive			//プリミティブ数
		);
	}
}

/*******************************************************************************
* 関数名: GetMeshWall
*******************************************************************************/
MESHWALL *GetMeshWall( void )
{
	return &g_Wall[ 0 ];
}