#include "main.h"
#include "skipbg.h"
#include "skipbg2.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SKIPBG		"data\\TEXTURE\\skipbg.jpg"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSkipBg(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSkipBg(int nSkipBgID);
void SetTextureSkipBg(int nSkipBgID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSkipBg = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkipBg = NULL;	// 頂点バッファへのポインタ

SKIPBG				g_aSkipBg[MAX_SKIPBG];	// ツールのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkipBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++)
	{
		g_aSkipBg[nCntSkipBg].pos = D3DXVECTOR3(SKIPBG_POS_X, SKIPBG_POS_Y, 0.0f);
		g_aSkipBg[nCntSkipBg].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aSkipBg[nCntSkipBg].nCount = 0;
		g_aSkipBg[nCntSkipBg].nPattern = 0;
		g_aSkipBg[nCntSkipBg].bUse = true;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SKIPBG,		// ファイルの名前
								&g_pTextureSkipBg);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexSkipBg(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSkipBg(void)
{

		if(g_pTextureSkipBg != NULL)
		{// テクスチャの開放
			g_pTextureSkipBg->Release();
			g_pTextureSkipBg = NULL;
		}

		if(g_pVtxBuffSkipBg != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffSkipBg->Release();
			g_pVtxBuffSkipBg = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkipBg(void)
{
	SKIPBG2 *pSkipBg2 = GetSkipBg2();
	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++)
	{
		if(g_aSkipBg[nCntSkipBg].bUse == true)
		{// 使用している
			g_aSkipBg[nCntSkipBg].nCount++;
			if((g_aSkipBg[nCntSkipBg].nCount % INTERVAL_PATTERN_SKIPBG) == 0)
			{// アニメーション切り替え
				g_aSkipBg[nCntSkipBg].nPattern++;
				if(g_aSkipBg[nCntSkipBg].nPattern >= NUM_PATTERN_SKIPBG)
				{// アニメーションパターンが終了
					g_aSkipBg[nCntSkipBg].bUse = false;
					g_aSkipBg[nCntSkipBg].nPattern = 0;
					pSkipBg2->bUse = true;
				}
				SetTextureSkipBg(nCntSkipBg);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkipBg(void)
{
	SKIPBG *pSkipBg;

	pSkipBg = &g_aSkipBg[0];
	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++, pSkipBg++)
	{
		if(pSkipBg->bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffSkipBg, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSkipBg);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_SKIPBG; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// 頂点座標の作成
//=============================================================================
HRESULT MakeVertexSkipBg(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_SKIPBG,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffSkipBg,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffSkipBg->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntSkipBg = 0; nCntSkipBg < NUM_PLACE_SKIPBG; nCntSkipBg++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_SIZE_X + SKIPBG_INTERVAL_X), SKIPBG_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_INTERVAL_X + SKIPBG_SIZE_X) + SKIPBG_SIZE_X, SKIPBG_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_SIZE_X + SKIPBG_INTERVAL_X), SKIPBG_POS_Y + SKIPBG_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_INTERVAL_X + SKIPBG_SIZE_X) + SKIPBG_SIZE_X, SKIPBG_POS_Y + SKIPBG_SIZE_Y, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_SKIPBG);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG, TEXTURE_SIZE_Y_SKIPBG);
		}

		// 頂点データをアンロックする
		g_pVtxBuffSkipBg->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureSkipBg(int nSkipBgID)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffSkipBg->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nSkipBgID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aSkipBg[nSkipBgID].nPattern * TEXTURE_SIZE_X_SKIPBG, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aSkipBg[nSkipBgID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aSkipBg[nSkipBgID].nPattern * TEXTURE_SIZE_X_SKIPBG, TEXTURE_SIZE_Y_SKIPBG);
	pVtx[3].tex = D3DXVECTOR2((g_aSkipBg[nSkipBgID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG, TEXTURE_SIZE_Y_SKIPBG);

	// 頂点データをアンロックする
	g_pVtxBuffSkipBg->Unlock();
}

//=============================================================================
// ツールのリセット
//=============================================================================
void ResetSkipBg(void)
{
	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++)
	{
		g_aSkipBg[nCntSkipBg].pos = D3DXVECTOR3(SKIPBG_POS_X, SKIPBG_POS_Y, 0.0f);
		g_aSkipBg[nCntSkipBg].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSkipBg[nCntSkipBg].nCount = 0;
		g_aSkipBg[nCntSkipBg].nPattern = 0;
		g_aSkipBg[nCntSkipBg].bUse = false;
	}
}
SKIPBG *GetSkipBg( void )
{
	return &g_aSkipBg[ 0 ];
}
