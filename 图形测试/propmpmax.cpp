#include "main.h"
#include "propmpmax.h"
#include "propmp.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PROPMPMAX		"data\\TEXTURE\\propmpmax.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPropMpMax(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPropMpMax(int nPropMpMaxID);
void SetColorPropMpMax(int nPropMpMaxID, D3DXCOLOR col);
void SetTexturePropMpMax(int nPropMpMaxID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePropMpMax = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPropMpMax = NULL;	// 頂点バッファへのポインタ

PROPMPMAX				g_aPropMpMax[MAX_PROPMPMAX];	// ツールのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPropMpMax(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PROPMP *pPropMp = GetPropMp();
	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++)
	{
		g_aPropMpMax[nCntPropMpMax].pos = D3DXVECTOR3(pPropMp->pos.x, pPropMp->pos.x, 0.0f);
		g_aPropMpMax[nCntPropMpMax].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMpMax[nCntPropMpMax].nCount = 0;
		g_aPropMpMax[nCntPropMpMax].nPattern = 0;
		g_aPropMpMax[nCntPropMpMax].bUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_PROPMPMAX,		// ファイルの名前
								&g_pTexturePropMpMax);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexPropMpMax(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPropMpMax(void)
{

		if(g_pTexturePropMpMax != NULL)
		{// テクスチャの開放
			g_pTexturePropMpMax->Release();
			g_pTexturePropMpMax = NULL;
		}

		if(g_pVtxBuffPropMpMax != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffPropMpMax->Release();
			g_pVtxBuffPropMpMax = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePropMpMax(void)
{
	PROPMPMAX *pPropMpMax;

	pPropMpMax = &g_aPropMpMax[0];
	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++, pPropMpMax++)
	{
		if(pPropMpMax->bUse == true)
		{// 使用している

			SetColorPropMpMax(nCntPropMpMax, pPropMpMax->col);

				pPropMpMax->nCount++;


			if((pPropMpMax->nCount % INTERVAL_PATTERN_PROPMPMAX) == 0)
			{// アニメーション切り替え

				pPropMpMax->nPattern++;
				if(pPropMpMax->nPattern >= NUM_PATTERN_PROPMPMAX)
				{// アニメーションパターンが終了
					pPropMpMax->bUse = false;
					pPropMpMax->nPattern = 0;
				}
				SetTexturePropMpMax(nCntPropMpMax);
			}
			g_aPropMpMax[nCntPropMpMax].bUse = true;
		}
	}
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorPropMpMax(int nPropMpMaxID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPropMpMax->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpMaxID * 4);

	// 頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	// 頂点データをアンロックする
	g_pVtxBuffPropMpMax->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPropMpMax(void)
{
	PROPMPMAX *pPropMpMax;

	pPropMpMax = &g_aPropMpMax[0];

	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++, pPropMpMax++)
	{
		if(pPropMpMax->bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffPropMpMax, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePropMpMax);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_PROPMPMAX; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// 頂点座標の作成
//=============================================================================
HRESULT MakeVertexPropMpMax(LPDIRECT3DDEVICE9 pDevice)
{
	PROPMP *pPropMp = GetPropMp();
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_PROPMPMAX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffPropMpMax,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffPropMpMax->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPropMpMax = 0; nCntPropMpMax < NUM_PLACE_PROPMPMAX; nCntPropMpMax++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_WIDTH + PROPMPMAX_INTERVAL_X), pPropMp->pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_INTERVAL_X + PROPMPMAX_WIDTH) + PROPMPMAX_WIDTH, pPropMp->pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_WIDTH + PROPMPMAX_INTERVAL_X), pPropMp->pos.y + PROPMPMAX_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_INTERVAL_X + PROPMPMAX_WIDTH) + PROPMPMAX_WIDTH,pPropMp->pos.y + PROPMPMAX_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROPMPMAX, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_PROPMPMAX);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROPMPMAX, TEXTURE_SIZE_Y_PROPMPMAX);
		}

		// 頂点データをアンロックする
		g_pVtxBuffPropMpMax->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePropMpMax(int nPropMpMaxID)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPropMpMax->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpMaxID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPropMpMax[nPropMpMaxID].nPattern * TEXTURE_SIZE_X_PROPMPMAX, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aPropMpMax[nPropMpMaxID].nPattern + 1) * TEXTURE_SIZE_X_PROPMPMAX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPropMpMax[nPropMpMaxID].nPattern * TEXTURE_SIZE_X_PROPMPMAX, TEXTURE_SIZE_Y_PROPMPMAX);
	pVtx[3].tex = D3DXVECTOR2((g_aPropMpMax[nPropMpMaxID].nPattern + 1) * TEXTURE_SIZE_X_PROPMPMAX, TEXTURE_SIZE_Y_PROPMPMAX);

	// 頂点データをアンロックする
	g_pVtxBuffPropMpMax->Unlock();
}

//=============================================================================
// ツールのリセット
//=============================================================================
void ResetPropMpMax(void)
{
	PROPMP *pPropMp = GetPropMp();
	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++)
	{
		g_aPropMpMax[nCntPropMpMax].pos = D3DXVECTOR3(pPropMp->pos.x, pPropMp->pos.x, 0.0f);
		g_aPropMpMax[nCntPropMpMax].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMpMax[nCntPropMpMax].nCount = 0;
		g_aPropMpMax[nCntPropMpMax].nPattern = 0;
		g_aPropMpMax[nCntPropMpMax].bUse = false;
	}
}
PROPMPMAX *GetPropMpMax( void )
{
	return &g_aPropMpMax[ 0 ];
}
