#include "main.h"
#include "input.h"
#include "use.h"

#include "meshField.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* グローバル変数
********************************************************************************/
MESHFIELD	g_Field;	//フィルド構造体

/*******************************************************************************
* 関数名: メッシュフィールドの初期化関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
HRESULT InitMeshField( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//メッシュフィールド構造体の初期化
	g_Field.pTexture = NULL;														//テクスチャバッファへのポインタ
	g_Field.pVtxBuff = NULL;														//頂点バッファへのポインタ
	g_Field.pIdxBuff = NULL;														//インデックスバッファへのポインタ

	g_Field.mesh.nNumVtxV		= 2;												//横の頂点数
	g_Field.mesh.nNumVtxH		= 210;												//縦の頂点数
	g_Field.mesh.nNumVtx		= g_Field.mesh.nNumVtxV * g_Field.mesh.nNumVtxH;	//総頂点数
	g_Field.mesh.nNumIdx		= g_Field.mesh.nNumVtx * 2 - 4;						//インデックス数

	g_Field.mesh.nNumBlock		= g_Field.mesh.nNumVtxV - 1;						//ブロック数
	g_Field.mesh.nNumPrimitive	= g_Field.mesh.nNumIdx - 2;							//ポリゴン数

	g_Field.mesh.fTexAdjust		= 0.0f;												//テクスチャY座標ずらす係数
	g_Field.mesh.nNumVtxH		= g_Field.mesh.nNumVtxH / 2;						//原点以上縦の頂点数
	g_Field.mesh.nNumIdxEven	= 0;												//インデックスバッファ頂点が偶数の数(退化三角形頂点以外)
	g_Field.mesh.nNumNullTri	= 0;												//縮退ポリゴン頂点の数
	g_Field.mesh.nMultiple		= 2;												//インデックスバッファ用係数

	//頂点バッファの生成
	if( FAILED ( pDevice -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * g_Field.mesh.nNumVtx,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_Field.pVtxBuff,
												NULL
	) ) )
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice, MESHFIELD_TEXTURE_FILE, &g_Field.pTexture );

	//フィールド頂点バッファの初期化
	MeshFieldVtx(
					g_Field.pVtxBuff,
					&g_Field,							//フィールドの構造体
					D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),	//フィールドの原点位置
					D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),	//フィールドの回転
					D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),	//フィールドの拡大縮小
					MESHFIELD_WIDTH,					//フィールドの幅
					MESHFIELD_HEIGHT					//フィールドの高さ
	);

	//インデックスバッファを確保
	if( FAILED ( pDevice -> CreateIndexBuffer(
									sizeof( WORD ) * g_Field.mesh.nNumIdx,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&g_Field.pIdxBuff,
									NULL
	) ) )
	{
		return E_FAIL;
	}

	//フィールドインデックスバッファの初期化
	MeshIdx(
			g_Field.pIdxBuff,	//インデックスバッファへのポインター
			&g_Field.mesh		//フィールド構造体
	);
	return S_OK;
}

/*******************************************************************************
* 関数名: メッシュフィールドの終了関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UninitMeshField( void )
{
	if( g_Field.pTexture != NULL )
	{
		g_Field.pTexture -> Release();	//テクスチャバッファの開放
		g_Field.pTexture = NULL;
	}

	if( g_Field.pVtxBuff != NULL )		//頂点バッファの開放
	{
		g_Field.pVtxBuff -> Release();
		g_Field.pVtxBuff = NULL;
	}

	if( g_Field.pIdxBuff != NULL )		//インデックスバッファの開放
	{
		g_Field.pIdxBuff -> Release();
		g_Field.pIdxBuff = NULL;
	}
}

/*******************************************************************************
* 関数名: メッシュフィールドの更新関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UpdateMeshField( void )
{
}

/*******************************************************************************
* 関数名: メッシュフィールドの描画関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void DrawMeshField( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity( &g_Field.mtx.World );

	//スケールを反映
	D3DXMatrixScaling(
						&g_Field.mtx.Scl,
						g_Field.scl.x,
						g_Field.scl.y,
						g_Field.scl.z
	);
	D3DXMatrixMultiply(
						&g_Field.mtx.World,
						&g_Field.mtx.World,
						&g_Field.mtx.Scl
	);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(
						&g_Field.mtx.Rot,
						g_Field.rot.y,
						g_Field.rot.x,
						g_Field.rot.z
	);
	D3DXMatrixMultiply(
						&g_Field.mtx.World,
						&g_Field.mtx.World,
						&g_Field.mtx.Rot
	);

	//位置を反映
	D3DXMatrixTranslation(
						&g_Field.mtx.Trans,
						g_Field.pos.x,
						g_Field.pos.y,
						g_Field.pos.z
	);
	D3DXMatrixMultiply(
						&g_Field.mtx.World,
						&g_Field.mtx.World,
						&g_Field.mtx.Trans
	);

	//ワールドマトリックスを設定
	pDevice -> SetTransform( D3DTS_WORLD, &g_Field.mtx.World );

	//頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource( 0, g_Field.pVtxBuff, 0, sizeof( VERTEX_3D ) );

	//インデックスバッファをデータストリームにバインドする
	pDevice -> SetIndices( g_Field.pIdxBuff );

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_3D );

	//テクスチャの設定
	pDevice -> SetTexture( 0, g_Field.pTexture );

	//ポリゴンの描画
	pDevice -> DrawIndexedPrimitive(
									D3DPT_TRIANGLESTRIP,
									0,
									0,
									g_Field.mesh.nNumVtx,		//頂点数
									0,
									g_Field.mesh.nNumPrimitive	//プリミティブ数
	);
}

/*******************************************************************************
* 関数名: GetMeshField
*******************************************************************************/
MESHFIELD *GetMeshField( void )
{
	return &g_Field;
}