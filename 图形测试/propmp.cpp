#include "main.h"
#include "propmp.h"
#include "propshow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PROPMP		"data\\TEXTURE\\propmp000.png"	// 読み込むテクスチャファイル名
#define	PROPMP_SIZE_X		(10.0f)							// ツールの数字の幅
#define	PROPMP_SIZE_Y		(100.0f)							// ツールの数字の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPropMp(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPropMp(int nPropMpID);
void SetColorPropMp(int nPropMpID, D3DXCOLOR col);
void SetTexturePropMp(int nPropMpID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePropMp = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPropMp = NULL;	// 頂点バッファへのポインタ

PROPMP				g_aPropMp[MAX_PROP_MP];	// ツールのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPropMp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PROW *pProw = GetProw();

	for(int nCntPropMp = 0; nCntPropMp < MAX_PROP_MP; nCntPropMp++)
	{
		g_aPropMp[nCntPropMp].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT), PROW_POS_Y, 0.0f);
		g_aPropMp[nCntPropMp].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMp[nCntPropMp].bUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_PROPMP,		// ファイルの名前
								&g_pTexturePropMp);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexPropMp(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPropMp(void)
{

		if(g_pTexturePropMp != NULL)
		{// テクスチャの開放
			g_pTexturePropMp->Release();
			g_pTexturePropMp = NULL;
		}

		if(g_pVtxBuffPropMp != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffPropMp->Release();
			g_pVtxBuffPropMp = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePropMp(void)
{

}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorPropMp(int nPropMpID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPropMp->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpID * 4);

	// 頂点カラーの設定
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = col;

	// 頂点データをアンロックする
	g_pVtxBuffPropMp->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPropMp(void)
{
	PROPMP *pPropMp;

	pPropMp = &g_aPropMp[0];
	for(int nCntPropMp = 0; nCntPropMp < MAX_PROP_MP; nCntPropMp++, pPropMp++)
	{
		if(pPropMp->bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffPropMp, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePropMp);

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
HRESULT MakeVertexPropMp(LPDIRECT3DDEVICE9 pDevice)
{
	PROW *pProw = GetProw();
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PROP_MP	,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffPropMp,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffPropMp->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPropMp = 0; nCntPropMp < NUM_PLACE_PROW; nCntPropMp++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH), PROW_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH) + PROP_WIDTH, PROW_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH), PROW_POS_Y + PROW_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH) + PROP_WIDTH, PROW_POS_Y + PROW_SIZE_Y, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		g_pVtxBuffPropMp->Unlock();
	}

	return S_OK;
}


//=============================================================================
// ツールのリセット
//=============================================================================
void ResetPropMp(void)
{
	for(int nCntPropMp = 0; nCntPropMp < MAX_PROP_MP; nCntPropMp++)
	{
		g_aPropMp[nCntPropMp].pos = D3DXVECTOR3((PROW_POS_X-PROP_LEFT), PROW_POS_Y, 0.0f);
		g_aPropMp[nCntPropMp].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPropMp[nCntPropMp].bUse = false;
	}
}
PROPMP *GetPropMp( void )
{
	return &g_aPropMp[ 0 ];
}
