#include "main.h"
#include "rule2.h"
#include "fade.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
//グローバル変数
VERTEX_2D g_Rule2[4];
LPDIRECT3DTEXTURE9 g_pTextureRule2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule2 =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：InitRule2
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffRule2,NULL)))
	{
		return E_FAIL;
	}	
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\rule2.png",
		&g_pTextureRule2);
		VERTEX_2D *Rule2;
		g_pVtxBuffRule2 ->Lock(0,0,(void **)&Rule2,0);		//頂点情報へのポインタを取得

		Rule2[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Rule2[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Rule2[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Rule2[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Rule2[0].rhw = 1.0f;
		Rule2[1].rhw = 1.0f;
		Rule2[2].rhw = 1.0f;
		Rule2[3].rhw = 1.0f;
		Rule2[0].col=D3DCOLOR_RGBA(255,255,255,255);	//頂点情報格納ワーク
		Rule2[1].col=D3DCOLOR_RGBA(255,255,255,255);
		Rule2[2].col=D3DCOLOR_RGBA(255,255,255,255);
		Rule2[3].col=D3DCOLOR_RGBA(255,255,255,255);

		Rule2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Rule2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Rule2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Rule2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffRule2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitRule2
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitRule2(void)
{
	if(g_pTextureRule2!=NULL)
	{
		g_pTextureRule2->Release();
		g_pTextureRule2=NULL;
	}
	if(g_pVtxBuffRule2!=NULL)
	{
		g_pVtxBuffRule2->Release();		//頂点バッファの開放
		g_pVtxBuffRule2=NULL;
	}
}
//=============================================================================
//  関数名　：DrawRule2
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureRule2);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffRule2,
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
//  関数名　：UpdateRule2
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateRule2(void)
{
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_GAME);
	}
}
