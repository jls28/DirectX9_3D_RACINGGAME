#include "main.h"
#include "propshow.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PROW		"data\\TEXTURE\\propshow001.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexProw(LPDIRECT3DDEVICE9 pDevice);
void SetVertexProw(int nProwID);
void SetColorProw(int nProwID, D3DXCOLOR col);
void SetTextureProw(int nProwID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureProw = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffProw = NULL;	// 頂点バッファへのポインタ

PROW				g_aProw[MAX_PROW];	// ツールのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitProw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++)
	{
		g_aProw[nCntProw].pos = D3DXVECTOR3(PROW_POS_X, PROW_POS_Y, 0.0f);
		g_aProw[nCntProw].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aProw[nCntProw].nCount = 0;
		g_aProw[nCntProw].nPattern = 0;
		g_aProw[nCntProw].bUse = false;
		g_aProw[nCntProw].bProwUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_PROW,		// ファイルの名前
								&g_pTextureProw);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexProw(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitProw(void)
{

		if(g_pTextureProw != NULL)
		{// テクスチャの開放
			g_pTextureProw->Release();
			g_pTextureProw = NULL;
		}

		if(g_pVtxBuffProw != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffProw->Release();
			g_pVtxBuffProw = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateProw(void)
{
	PROW *pProw;

	pProw = &g_aProw[0];
	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++, pProw++)
	{
		if(pProw->bUse == true)
		{// 使用している

			SetColorProw(nCntProw, pProw->col);

			if(pProw->bProwUse == false)
			{
				pProw->nCount++;
			}

			if((pProw->nCount % INTERVAL_PATTERN_PROW) == 0)
			{// アニメーション切り替え
			if(pProw->bProwUse == false)
			{
				pProw->nPattern++;
				if(pProw->nPattern >= NUM_PATTERN_PROW)
				{// アニメーションパターンが終了
					pProw->bUse = false;
					pProw->nPattern = 0;
				}
				SetTextureProw(nCntProw);
			}
			}
			g_aProw[nCntProw].bUse = true;
		}
	}
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorProw(int nProwID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffProw->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nProwID * 4);

	// 頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	// 頂点データをアンロックする
	g_pVtxBuffProw->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawProw(void)
{
	PROW *pProw;

	pProw = &g_aProw[0];
	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++, pProw++)
	{
		if(pProw->bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffProw, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureProw);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_PROW; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// 頂点座標の作成
//=============================================================================
HRESULT MakeVertexProw(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_PROW,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffProw,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffProw->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntProw = 0; nCntProw < NUM_PLACE_PROW; nCntProw++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_SIZE_X + PROW_INTERVAL_X), PROW_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_INTERVAL_X + PROW_SIZE_X) + PROW_SIZE_X, PROW_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_SIZE_X + PROW_INTERVAL_X), PROW_POS_Y + PROW_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_INTERVAL_X + PROW_SIZE_X) + PROW_SIZE_X, PROW_POS_Y + PROW_SIZE_Y, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROW, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_PROW);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROW, TEXTURE_SIZE_Y_PROW);
		}

		// 頂点データをアンロックする
		g_pVtxBuffProw->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureProw(int nProwID)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffProw->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nProwID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aProw[nProwID].nPattern * TEXTURE_SIZE_X_PROW, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aProw[nProwID].nPattern + 1) * TEXTURE_SIZE_X_PROW, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aProw[nProwID].nPattern * TEXTURE_SIZE_X_PROW, TEXTURE_SIZE_Y_PROW);
	pVtx[3].tex = D3DXVECTOR2((g_aProw[nProwID].nPattern + 1) * TEXTURE_SIZE_X_PROW, TEXTURE_SIZE_Y_PROW);

	// 頂点データをアンロックする
	g_pVtxBuffProw->Unlock();
}

//=============================================================================
// ツールのリセット
//=============================================================================
void ResetProw(void)
{
	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++)
	{
		g_aProw[nCntProw].pos = D3DXVECTOR3(PROW_POS_X, PROW_POS_Y, 0.0f);
		g_aProw[nCntProw].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aProw[nCntProw].nCount = 0;
		g_aProw[nCntProw].nPattern = 0;
		g_aProw[nCntProw].bUse = false;
		g_aProw[nCntProw].bProwUse = false;
	}
}
PROW *GetProw( void )
{
	return &g_aProw[ 0 ];
}
