//=============================================================================
//
// 倒時計処理 [countdown.cpp]
// 2016/02/24 LIHAOSHENG
//
//=============================================================================
#include "countdown.h"
#include "modelbody.h"
#include "timebg.h"
//*****************************************************************************


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_COUNTDOWN		"data\\TEXTURE\\countdown.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexCountdown(LPDIRECT3DDEVICE9 pDevice);
void SetVertexCountdown(int nCountdownID);
void SetColorCountdown(int nCountdownID, D3DXCOLOR col);
void SetTextureCountdown(int nCountdownID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCountdown = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCountdown = NULL;	// 頂点バッファへのポインタ

COUNTDOWN				g_aCountdown[MAX_COUNTDOWN];	// ツールのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCountdown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++)
	{
		g_aCountdown[nCntCountdown].pos = D3DXVECTOR3(COUNTDOWN_POS_X, COUNTDOWN_POS_Y, 0.0f);
		g_aCountdown[nCntCountdown].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aCountdown[nCntCountdown].nCount = 0;
		g_aCountdown[nCntCountdown].nPattern = 0;
		g_aCountdown[nCntCountdown].bUse = true;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_COUNTDOWN,		// ファイルの名前
								&g_pTextureCountdown);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexCountdown(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCountdown(void)
{

		if(g_pTextureCountdown != NULL)
		{// テクスチャの開放
			g_pTextureCountdown->Release();
			g_pTextureCountdown = NULL;
		}

		if(g_pVtxBuffCountdown != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffCountdown->Release();
			g_pVtxBuffCountdown = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateCountdown(void)
{


	COUNTDOWN *pCountdown;
	pCountdown = &g_aCountdown[0];
	TIMEBG *pTimeBg = GetTimeBg();
	MODELBODY *pModelBody = GetModelBody();
	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++, pCountdown++)
	{
		if(pCountdown->bUse == true)
		{// 使用している
			pTimeBg->bUse = false;
			pModelBody->bUse = false;
			SetColorCountdown(nCntCountdown, pCountdown->col);

				pCountdown->nCount++;

			if((pCountdown->nCount % INTERVAL_PATTERN_COUNTDOWN) == 0)
			{// アニメーション切り替え

				pCountdown->nPattern++;
				if(pCountdown->nPattern >= NUM_PATTERN_COUNTDOWN)
				{// アニメーションパターンが終了
					pCountdown->bUse = false;
					pTimeBg->bUse = true;
					pModelBody->bUse = true;
					//pCountdown->nPattern = 0;
				}
				SetTextureCountdown(nCntCountdown);
			}
			}
		}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorCountdown(int nCountdownID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffCountdown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nCountdownID * 4);

	// 頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	// 頂点データをアンロックする
	g_pVtxBuffCountdown->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawCountdown(void)
{
	COUNTDOWN *pCountdown;

	pCountdown = &g_aCountdown[0];
	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++, pCountdown++)
	{
		if(pCountdown->bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffCountdown, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureCountdown);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_COUNTDOWN; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// 頂点座標の作成
//=============================================================================
HRESULT MakeVertexCountdown(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_COUNTDOWN,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffCountdown,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffCountdown->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntCountdown = 0; nCntCountdown < NUM_PLACE_COUNTDOWN; nCntCountdown++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_SIZE_X + COUNTDOWN_INTERVAL_X), COUNTDOWN_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_INTERVAL_X + COUNTDOWN_SIZE_X) + COUNTDOWN_SIZE_X, COUNTDOWN_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_SIZE_X + COUNTDOWN_INTERVAL_X), COUNTDOWN_POS_Y + COUNTDOWN_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_INTERVAL_X + COUNTDOWN_SIZE_X) + COUNTDOWN_SIZE_X, COUNTDOWN_POS_Y + COUNTDOWN_SIZE_Y, 0.0f);

			// rhwの設定
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_COUNTDOWN, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_COUNTDOWN);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_COUNTDOWN, TEXTURE_SIZE_Y_COUNTDOWN);
		}

		// 頂点データをアンロックする
		g_pVtxBuffCountdown->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureCountdown(int nCountdownID)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffCountdown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nCountdownID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aCountdown[nCountdownID].nPattern * TEXTURE_SIZE_X_COUNTDOWN, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aCountdown[nCountdownID].nPattern + 1) * TEXTURE_SIZE_X_COUNTDOWN, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aCountdown[nCountdownID].nPattern * TEXTURE_SIZE_X_COUNTDOWN, TEXTURE_SIZE_Y_COUNTDOWN);
	pVtx[3].tex = D3DXVECTOR2((g_aCountdown[nCountdownID].nPattern + 1) * TEXTURE_SIZE_X_COUNTDOWN, TEXTURE_SIZE_Y_COUNTDOWN);

	// 頂点データをアンロックする
	g_pVtxBuffCountdown->Unlock();
}

//=============================================================================
// ツールのリセット
//=============================================================================
void ResetCountdown(void)
{
	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++)
	{
		g_aCountdown[nCntCountdown].pos = D3DXVECTOR3(COUNTDOWN_POS_X, COUNTDOWN_POS_Y, 0.0f);
		g_aCountdown[nCntCountdown].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCountdown[nCntCountdown].nCount = 0;
		g_aCountdown[nCntCountdown].nPattern = 0;
		g_aCountdown[nCntCountdown].bUse = false;
	}
}
COUNTDOWN *GetCountdown( void )
{
	return &g_aCountdown[ 0 ];
}
