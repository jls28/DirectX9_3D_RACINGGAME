#include "main.h"
#include "resultbg.h"
#include "input.h"
#include "fade.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
//グローバル変数
VERTEX_2D g_ResultBg[4];
LPDIRECT3DTEXTURE9 g_pTextureResultBg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBg =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：InitResultBg
//  機能概要：プリゴンの初期化
//  戻り値　：HResultBg
//=============================================================================
HRESULT InitResultBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffResultBg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *ResultBg;
		g_pVtxBuffResultBg ->Lock(0,0,(void **)&ResultBg,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result.png",
		&g_pTextureResultBg);
		ResultBg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		ResultBg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		ResultBg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		ResultBg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		ResultBg[0].rhw = 1.0f;
		ResultBg[1].rhw = 1.0f;
		ResultBg[2].rhw = 1.0f;
		ResultBg[3].rhw = 1.0f;
		ResultBg[0].col=D3DCOLOR_RGBA(255,255,255,255);	//頂点情報格納ワーク
		ResultBg[1].col=D3DCOLOR_RGBA(255,255,255,255);
		ResultBg[2].col=D3DCOLOR_RGBA(255,255,255,255);
		ResultBg[3].col=D3DCOLOR_RGBA(255,255,255,255);

		ResultBg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		ResultBg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		ResultBg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		ResultBg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffResultBg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitResultBg
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitResultBg(void)
{
	if(g_pTextureResultBg!=NULL)
	{
		g_pTextureResultBg->Release();
		g_pTextureResultBg=NULL;
	}
	if(g_pVtxBuffResultBg!=NULL)
	{
		g_pVtxBuffResultBg->Release();		//頂点バッファの開放
		g_pVtxBuffResultBg=NULL;
	}
}
//=============================================================================
//  関数名　：DrawResultBg
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawResultBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureResultBg);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffResultBg,
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
//  関数名　：UpdateResultBg
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateResultBg(void)
{
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_TITLE);
	}
}
