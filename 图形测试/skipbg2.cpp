#include "main.h"
#include "skipbg2.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SKIPBG2		"data\\TEXTURE\\skipbg2.jpg"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexSkipBg2(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSkipBg2(int nSkipBg2ID);
void SetTextureSkipBg2(int nSkipBg2ID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSkipBg2 = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkipBg2 = NULL;	// 頂点バッファへのポインタ

SKIPBG2				g_aSkipBg2[MAX_SKIPBG2];	// ツールのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkipBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		g_aSkipBg2[nCntSkipBg2].pos = D3DXVECTOR3(SKIPBG2_POS_X, SKIPBG2_POS_Y, 0.0f);
		g_aSkipBg2[nCntSkipBg2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aSkipBg2[nCntSkipBg2].nCount = 0;
		g_aSkipBg2[nCntSkipBg2].nPattern = 0;
		g_aSkipBg2[nCntSkipBg2].bUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SKIPBG2,		// ファイルの名前
								&g_pTextureSkipBg2);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexSkipBg2(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSkipBg2(void)
{

		if(g_pTextureSkipBg2 != NULL)
		{// テクスチャの開放
			g_pTextureSkipBg2->Release();
			g_pTextureSkipBg2 = NULL;
		}

		if(g_pVtxBuffSkipBg2 != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffSkipBg2->Release();
			g_pVtxBuffSkipBg2 = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkipBg2(void)
{
	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		if(g_aSkipBg2[nCntSkipBg2].bUse == true)
		{// 使用している
			g_aSkipBg2[nCntSkipBg2].nCount++;
			if((g_aSkipBg2[nCntSkipBg2].nCount % INTERVAL_PATTERN_SKIPBG2) == 0)
			{// アニメーション切り替え
				g_aSkipBg2[nCntSkipBg2].nPattern++;
				if(g_aSkipBg2[nCntSkipBg2].nPattern >= NUM_PATTERN_SKIPBG2)
				{// アニメーションパターンが終了
					//g_aSkipBg2[nCntSkipBg2].bUse = false;
					g_aSkipBg2[nCntSkipBg2].nPattern = 0;
					SetFade(FADE_OUT,MODE_RULE);
				}
				SetTextureSkipBg2(nCntSkipBg2);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkipBg2(void)
{
	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		if(g_aSkipBg2[nCntSkipBg2].bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffSkipBg2, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSkipBg2);

	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_SKIPBG2; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// 頂点座標の作成
//=============================================================================
HRESULT MakeVertexSkipBg2(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_SKIPBG2,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffSkipBg2,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffSkipBg2->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntSkipBg2 = 0; nCntSkipBg2 < NUM_PLACE_SKIPBG2; nCntSkipBg2++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x-SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y-SKIPBG2_SIZE_Y/2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x+SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y-SKIPBG2_SIZE_Y/2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x-SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y+SKIPBG2_SIZE_Y/2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x+SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y+SKIPBG2_SIZE_Y/2, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG2, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_SKIPBG2);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG2, TEXTURE_SIZE_Y_SKIPBG2);
		}

		// 頂点データをアンロックする
		g_pVtxBuffSkipBg2->Unlock();
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureSkipBg2(int nSkipBg2ID)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffSkipBg2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nSkipBg2ID * 4);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aSkipBg2[nSkipBg2ID].nPattern * TEXTURE_SIZE_X_SKIPBG2, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aSkipBg2[nSkipBg2ID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG2, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aSkipBg2[nSkipBg2ID].nPattern * TEXTURE_SIZE_X_SKIPBG2, TEXTURE_SIZE_Y_SKIPBG2);
	pVtx[3].tex = D3DXVECTOR2((g_aSkipBg2[nSkipBg2ID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG2, TEXTURE_SIZE_Y_SKIPBG2);

	// 頂点データをアンロックする
	g_pVtxBuffSkipBg2->Unlock();
}

//=============================================================================
// ツールのリセット
//=============================================================================
void ResetSkipBg2(void)
{
	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		g_aSkipBg2[nCntSkipBg2].pos = D3DXVECTOR3(SKIPBG2_POS_X, SKIPBG2_POS_Y, 0.0f);
		g_aSkipBg2[nCntSkipBg2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSkipBg2[nCntSkipBg2].nCount = 0;
		g_aSkipBg2[nCntSkipBg2].nPattern = 0;
		g_aSkipBg2[nCntSkipBg2].bUse = false;
	}
}
SKIPBG2 *GetSkipBg2( void )
{
	return &g_aSkipBg2[ 0 ];
}
