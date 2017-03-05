#include "main.h"

#include "light.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define LIGHT_MAX ( 4 )

/*******************************************************************************
* グローバル変数
********************************************************************************/
D3DLIGHT9	g_aLight[ LIGHT_MAX ];		//ライト情報
LIGHT		g_Light[ LIGHT_MAX ];		//光の方向と光の強さの構造体

/*******************************************************************************
* 関数名: ライトの初期化関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void InitLight( void )
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[ LIGHT_MAX ];

	g_Light[ 0 ].diffuse	= D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	g_Light[ 1 ].diffuse	= D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f );
	g_Light[ 2 ].diffuse	= D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f );
	g_Light[ 3 ].diffuse	= D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	g_Light[ 0 ].vecDir		= D3DXVECTOR3( 2.0f, -1.0f, -1.0f );
	g_Light[ 1 ].vecDir		= D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
	g_Light[ 2 ].vecDir		= D3DXVECTOR3( 0.0f, -1.0f, -2.0f );
	g_Light[ 3 ].vecDir		= D3DXVECTOR3( 1.0f, 400.0f, -2.0f );

	for( int nCntLight = 0; nCntLight < LIGHT_MAX; nCntLight++ )
	{
		ZeroMemory( &g_aLight[ nCntLight ],sizeof( D3DLIGHT9 ) );

		//平行光源
		g_aLight[ nCntLight ].Type		= D3DLIGHT_DIRECTIONAL;

		//拡散光
		g_aLight[ nCntLight ].Diffuse	= g_Light[ nCntLight ].diffuse;

		//光の方向
		vecDir[ nCntLight ]				= g_Light[ nCntLight ].vecDir;

		//正規化
		D3DXVec3Normalize( ( D3DXVECTOR3 * ) &g_aLight[ nCntLight ].Direction, &vecDir[ nCntLight ] );

		//ライトの設定
		pDevice -> SetLight( nCntLight, &g_aLight[ nCntLight ] );

		//ライトを有効する
		pDevice -> LightEnable( nCntLight, TRUE );
	}
}

/*******************************************************************************
* 関数名: ライトの終了関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UninitLight( void )
{
}

/*******************************************************************************
* 関数名: ライトの更新関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UpdateLight( void )
{
}

/*******************************************************************************
* 関数名: ライトの描画関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void DrawLight( void )
{
}