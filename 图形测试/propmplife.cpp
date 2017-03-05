#include "main.h"
#include "propmp.h"
#include "propshow.h"
#include "propmplife.h"
#include "propmpmax.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_PROPMPLIFE		"data\\TEXTURE\\propmplife000.png"	// 読み込むテクスチャファイル名
#define	PROPMP_SIZE_X		(10.0f)							// ツールの数字の幅
#define	PROPMP_SIZE_Y		(100.0f)							// ツールの数字の高さ
#define	PROPMPLIFE_SPEED		(1)		//maxの速さ
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPropMpLife(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPropMpLife(int nPropMpLifeID);
void SetColorPropMpLife(int nPropMpLifeID, D3DXCOLOR col);
void SetTexturePropMpLife(int nPropMpLifeID);

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePropMpLife = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPropMpLife = NULL;	// 頂点バッファへのポインタ

PROPMPLIFE				g_aPropMpLife[MAX_PROPMPLIFE];	// ツールのワーク
int time;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPropMpLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PROW *pProw = GetProw();

	for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++)
	{
		g_aPropMpLife[nCntPropMpLife].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT), (PROW_POS_Y+PROP_HEIGHT)  , 0.0f);
		g_aPropMpLife[nCntPropMpLife].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMpLife[nCntPropMpLife].time = 0;
		g_aPropMpLife[nCntPropMpLife].frame = 0;
		g_aPropMpLife[nCntPropMpLife].bUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_PROPMPLIFE,		// ファイルの名前
								&g_pTexturePropMpLife);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexPropMpLife(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPropMpLife(void)
{

		if(g_pTexturePropMpLife != NULL)
		{// テクスチャの開放
			g_pTexturePropMpLife->Release();
			g_pTexturePropMpLife = NULL;
		}

		if(g_pVtxBuffPropMpLife != NULL)
		{// 頂点バッファの開放
			g_pVtxBuffPropMpLife->Release();
			g_pVtxBuffPropMpLife = NULL;
		}

}
//=============================================================================
// 更新処理
//=============================================================================
void UpdatePropMpLife(void)
{
	
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorPropMpLife(int nPropMpLifeID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffPropMpLife->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpLifeID * 4);

	// 頂点カラーの設定
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = col;

	// 頂点データをアンロックする
	g_pVtxBuffPropMpLife->Unlock();
}
//=============================================================================
// 描画処理
//=============================================================================
void DrawPropMpLife(void)
{
	PROPMPLIFE *pPropMpLife;

	pPropMpLife = &g_aPropMpLife[0];
	PROPMPMAX *pPropMpMax = GetPropMpMax();
	for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++, pPropMpLife++)
	{
		if(pPropMpLife->bUse == true)
		{// 使用している
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffPropMpLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePropMpLife);

	if( pPropMpLife->frame >= PROPMPLIFE_SPEED)
	{
		pPropMpLife->time ++;
		pPropMpLife->frame = 0;
	}
	else
	{
		if(pPropMpMax->bUse == false)
		{
		pPropMpLife->frame++;
		}
	}

	if(pPropMpLife->time >= 100)
	{
		pPropMpMax->bUse = true;
		pPropMpLife->time =0;
	}
	// ポリゴンの描画
	for(int nCntPlace = 0; nCntPlace < pPropMpLife->time; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}

}

//=============================================================================
// 頂点座標の作成
//=============================================================================
HRESULT MakeVertexPropMpLife(LPDIRECT3DDEVICE9 pDevice)
{
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PROPMPLIFE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_2D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffPropMpLife,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_2D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffPropMpLife->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++, pVtx += 4)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT),(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife+1) * PROPMPLIFE_HEIGHT,0.0f);
			pVtx[1].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + PROPMPLIFE_WIDTH ,(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife+1) * PROPMPLIFE_HEIGHT,0.0f);
			pVtx[2].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT),(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife-1) * PROPMPLIFE_HEIGHT,0.0f);
			pVtx[3].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + PROPMPLIFE_WIDTH ,(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife-1) * PROPMPLIFE_HEIGHT,0.0f);
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
		g_pVtxBuffPropMpLife->Unlock();
	}

	return S_OK;
}


//=============================================================================
// ツールのリセット
//=============================================================================
void ResetPropMpLife(void)
{
	for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++)
	{
		g_aPropMpLife[nCntPropMpLife].pos = D3DXVECTOR3((PROW_POS_X-PROP_LEFT), PROW_POS_Y, 0.0f);
		g_aPropMpLife[nCntPropMpLife].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPropMpLife[nCntPropMpLife].bUse = false;
	}
}
PROPMPLIFE *GetPropMpLife( void )
{
	return &g_aPropMpLife[ 0 ];
}
