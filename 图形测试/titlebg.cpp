#include "main.h"
#include "titlebg.h"
//グローバル変数
VERTEX_2D g_TitleBg[4];
LPDIRECT3DTEXTURE9 g_pTextureTitleBg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBg =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：InitTitleBg
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitTitleBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTitleBg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *TitleBg;
		g_pVtxBuffTitleBg ->Lock(0,0,(void **)&TitleBg,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitleBg);
		TitleBg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		TitleBg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		TitleBg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		TitleBg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		TitleBg[0].rhw = 1.0f;
		TitleBg[1].rhw = 1.0f;
		TitleBg[2].rhw = 1.0f;
		TitleBg[3].rhw = 1.0f;
		TitleBg[0].col=D3DCOLOR_RGBA(255,255,255,255);	//頂点情報格納ワーク
		TitleBg[1].col=D3DCOLOR_RGBA(255,255,255,255);
		TitleBg[2].col=D3DCOLOR_RGBA(255,255,255,255);
		TitleBg[3].col=D3DCOLOR_RGBA(255,255,255,255);

		TitleBg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		TitleBg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		TitleBg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		TitleBg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTitleBg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitTitleBg
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitTitleBg(void)
{
	if(g_pTextureTitleBg!=NULL)
	{
		g_pTextureTitleBg->Release();
		g_pTextureTitleBg=NULL;
	}
	if(g_pVtxBuffTitleBg!=NULL)
	{
		g_pVtxBuffTitleBg->Release();		//頂点バッファの開放
		g_pVtxBuffTitleBg=NULL;
	}
}
//=============================================================================
//  関数名　：DrawTitleBg
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawTitleBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureTitleBg);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTitleBg,
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
//  関数名　：UpdateTitleBg
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateTitleBg(void)
{

}
