#include "main.h"
#include "result2.h"
#include "input.h"
#include "fade.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
#include "sound.h"
//グローバル変数
VERTEX_2D g_Result2[4];
LPDIRECT3DTEXTURE9 g_pTextureResult2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult2 =NULL;	//頂点パッファへのポインタ
//=============================================================================
//  関数名　：InitResult2
//  機能概要：プリゴンの初期化
//  戻り値　：HResult2
//=============================================================================
HRESULT InitResult2(void)
{
	PlaySound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM001);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffResult2,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Result2;
		g_pVtxBuffResult2 ->Lock(0,0,(void **)&Result2,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result2.png",
		&g_pTextureResult2);
		Result2[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Result2[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Result2[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Result2[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Result2[0].rhw = 1.0f;
		Result2[1].rhw = 1.0f;
		Result2[2].rhw = 1.0f;
		Result2[3].rhw = 1.0f;
		Result2[0].col=D3DCOLOR_RGBA(255,255,255,255);	//頂点情報格納ワーク
		Result2[1].col=D3DCOLOR_RGBA(255,255,255,255);
		Result2[2].col=D3DCOLOR_RGBA(255,255,255,255);
		Result2[3].col=D3DCOLOR_RGBA(255,255,255,255);

		Result2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Result2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Result2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Result2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffResult2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  関数名　：UninitResult2
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitResult2(void)
{
	if(g_pTextureResult2!=NULL)
	{
		g_pTextureResult2->Release();
		g_pTextureResult2=NULL;
	}
	if(g_pVtxBuffResult2!=NULL)
	{
		g_pVtxBuffResult2->Release();		//頂点バッファの開放
		g_pVtxBuffResult2=NULL;
	}
}
//=============================================================================
//  関数名　：DrawResult2
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawResult2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureResult2);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffResult2,
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
//  関数名　：UpdateResult2
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateResult2(void)
{

}
