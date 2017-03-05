#include "main.h"
#include "skipbg0.h"
//グローバル変数
VERTEX_2D g_SkipBg0[4];
LPDIRECT3DTEXTURE9 g_pTextureSkipBg0 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkipBg0 =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：InitSkipBg0
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitSkipBg0(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffSkipBg0,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *SkipBg0;
		g_pVtxBuffSkipBg0 ->Lock(0,0,(void **)&SkipBg0,0);		//頂点情報へのポインタを取得

		SkipBg0[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		SkipBg0[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		SkipBg0[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		SkipBg0[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		SkipBg0[0].rhw = 1.0f;
		SkipBg0[1].rhw = 1.0f;
		SkipBg0[2].rhw = 1.0f;
		SkipBg0[3].rhw = 1.0f;
		SkipBg0[0].col=D3DCOLOR_RGBA(255,255,255,255);	//頂点情報格納ワーク
		SkipBg0[1].col=D3DCOLOR_RGBA(255,255,255,255);
		SkipBg0[2].col=D3DCOLOR_RGBA(255,255,255,255);
		SkipBg0[3].col=D3DCOLOR_RGBA(255,255,255,255);

		SkipBg0[0].tex = D3DXVECTOR2(0.0f,0.0f);
		SkipBg0[1].tex = D3DXVECTOR2(1.0f,0.0f);
		SkipBg0[2].tex = D3DXVECTOR2(0.0f,1.0f);
		SkipBg0[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffSkipBg0 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitSkipBg0
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitSkipBg0(void)
{
	if(g_pTextureSkipBg0!=NULL)
	{
		g_pTextureSkipBg0->Release();
		g_pTextureSkipBg0=NULL;
	}
	if(g_pVtxBuffSkipBg0!=NULL)
	{
		g_pVtxBuffSkipBg0->Release();		//頂点バッファの開放
		g_pVtxBuffSkipBg0=NULL;
	}
}
//=============================================================================
//  関数名　：DrawSkipBg0
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawSkipBg0(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureSkipBg0);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffSkipBg0,
								0,
								sizeof(VERTEX_2D)
								);
	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  0,		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
}
//=============================================================================
//  関数名　：UpdateSkipBg0
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateSkipBg0(void)
{

}
