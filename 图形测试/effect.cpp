//=============================================================================

// エフェクトの処理 [effect.cpp]
// 

//=============================================================================//
#include <time.h>
#include "effect.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT		"data\\TEXTURE\\effect000.jpg"	// 読み込むテクスチャファイル名

#define	NUM_VERTEX_CIRCLE	(4)			// 頂点数
#define	NUM_POLYGON_CIRCLE	(2)			// ポリゴン数


#define	MAX_EFFECT			(7000)		// エフェクトの最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 posBase;	// 基準位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXCOLOR col;			// 色
	D3DXVECTOR3 scl;		//拡大縮小
	float fColAlphaValue;	// 色変化量
	float fAngle;			// 角度
	float fRadius;			// 半径
	float fRadiusValue;		// 半径変化量
	D3DXVECTOR3 swingRate;	// 揺れ係数
	D3DXVECTOR3 swingWidth;	// 揺れ幅
	D3DXVECTOR3 swingValue;	// 揺れ幅変化量
	int nLife;				// ライフ
	int nType;				// 種類
	bool bUse;				// 使用しているかどうか
	D3DXMATRIX				mtxWorld;					//ワールドマトリックス
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//拡大縮小、向き、位置マトリックス
} EFFECT;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade);
void SetRadiusEffect(int nEffectID, float fRadius);
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// 頂点バッファへのポインタ
EFFECT					g_aEffect[MAX_EFFECT];		// エフェクトのワーク
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffect(void)
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice	= GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fColAlphaValue = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].fRadius = 30.0f;
		g_aEffect[nCntEffect].fRadiusValue = 0.0f;
		g_aEffect[nCntEffect].nType = EFFECTTYPE_RANDOMCOLOR;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
								TEXTURE_EFFECT,			// ファイルの名前
								&g_pTextureEffect);		// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexEffect(pDevice);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitEffect(void)
{
	if(g_pTextureEffect != NULL)
	{// テクスチャの開放
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	if(g_pVtxBuffEffect != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == true)
		{// エフェクトが使用中なら描画
			pEffect->nLife--;
			if(pEffect->nLife <= 0)
			{// エフェクトを消滅させる
				pEffect->bUse = false;
			}
			else
			{// エフェクトを調整
				// 色の設定
				pEffect->col.a -= pEffect->fColAlphaValue;
				if(pEffect->col.a <= 0.0f)
				{
					pEffect->col.a = 0.0f;
				}
				SetColorEffect(nCntEffect, pEffect->col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

				// 半径の設定
				//pEffect->fRadius -= pEffect->fRadiusValue;
				//if(pEffect->fRadius <= 0.0f)
				//{
				//	pEffect->fRadius = 0.0f;
				//}
				//SetRadiusEffect(nCntEffect, pEffect->fRadius);

				// 揺れ(X方向)の設定
				//pEffect->swingRate.x += D3DX_PI * pEffect->swingValue.x;
				//if(pEffect->swingRate.x > D3DX_PI)
				//{
				//	pEffect->swingRate.x -= D3DX_PI * 2.0f;
				//}
				//pEffect->pos.x = pEffect->pos.x + sinf(pEffect->swingRate.x) * pEffect->swingWidth.x;

				//// 揺れ(Y方向)の設定
				//pEffect->swingRate.z += D3DX_PI * pEffect->swingValue.z;
				//if(pEffect->swingRate.z > D3DX_PI)
				//{
				//	pEffect->swingRate.z -= D3DX_PI * 2.0f;
				//}
				//pEffect->pos.z = pEffect->pos.z + sinf(pEffect->swingRate.z) * pEffect->swingWidth.z;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEffect(void)
{

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// カメラで設定したビューマトリックスを受け取るための変数

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// ビューマトリックスを取得
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	//// ライト消灯。どの角度から見ても同じようにするため、ビルボードの陰影を無くす。
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ブレンド加算処理
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// αデスティネーションカラーの指定

	// ポリゴンの描画
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == true)
		{// エフェクトが使用中なら描画

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_aEffect[nCntEffect].mtxWorld );

			// ビューマトリックスの逆行列を求める。
			D3DXMatrixInverse( &g_aEffect[nCntEffect].mtxWorld, NULL, &mtxView );

			g_aEffect[nCntEffect].mtxWorld._41 = 0.0f;		// 移動に関する変数をクリア
			g_aEffect[nCntEffect].mtxWorld._42 = 0.0f;		// 移動に関する変数をクリア
			g_aEffect[nCntEffect].mtxWorld._43 = 0.0f;		// 移動に関する変数をクリア
			// スケールを反映
			D3DXMatrixScaling( &mtxScl, g_aEffect[nCntEffect].scl.x, g_aEffect[nCntEffect].scl.y, g_aEffect[nCntEffect].scl.z );
			D3DXMatrixMultiply( &g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxScl );

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// ビルボードは常に正面をカメラに向ける2Dポリゴンだから、オール0.0の初期値でいい。
			D3DXMatrixMultiply( &g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxRot );

			// 位置を反映
			D3DXMatrixTranslation( &mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z );
			D3DXMatrixMultiply( &g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans );

			// ワールドマトリックスを設定
			pDevice->SetTransform( D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld );

			// 頂点バッファをデータストリームにバインド
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));		//sizeof( VERTEX_2D )はデータの間隔

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEffect * NUM_VERTEX_CIRCLE), NUM_POLYGON_CIRCLE);
		}
	}
	// レンダーステートの設定をデフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// デフォルトに戻す。
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// デフォルトに戻す。
	// 通常ブレンド
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定

	// ライト点灯
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX_CIRCLE * MAX_EFFECT,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,								// 頂点バッファの使用法
												FVF_VERTEX_3D,									// 使用する頂点フォーマット
												D3DPOOL_MANAGED,								// リソースのバッファを保持するメモリクラスを指定
												&g_pVtxBuffEffect,								// 頂点バッファインターフェースへのポインタ
												NULL)))											// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;
	//const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	g_pVtxBuffEffect -> Lock( 0, 0, ( void** ) &pVtx, 0 );


		for(int cntTarget = 0; cntTarget < MAX_EFFECT; cntTarget++, pVtx += 4)
		{
			//法線
			pVtx[0].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[1].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[2].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[3].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}

	return S_OK;
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade)
{
	g_aEffect[nEffectID].col = col;
	
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffectID * NUM_VERTEX_CIRCLE);


		pVtx->col = col;
		pVtx++;

		// 頂点カラーの設定
		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			pVtx->col = D3DXCOLOR(col.r * colFade.r, col.g * colFade.g, col.b * colFade.b, col.a * colFade.a);
		}


		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// サイズ設定
//=============================================================================
void SetRadiusEffect(int nEffectID, float fRadius)
{
	g_aEffect[nEffectID].fRadius = fRadius;

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nEffectID * NUM_VERTEX_CIRCLE;


		pVtx[0].pos.x =-fRadius * 0.5f;
		pVtx[0].pos.y = fRadius * 0.5f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = fRadius * 0.5f;
		pVtx[1].pos.y = fRadius * 0.5f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = -fRadius * 0.5f;
		pVtx[2].pos.y = -fRadius * 0.5f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = fRadius * 0.5f;
		pVtx[3].pos.y = -fRadius * 0.5f;
		pVtx[3].pos.z = 0.0f;


		// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// エフェクト設定
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == false)
		{
			// 頂点座標の設定
			pEffect->pos = pos;
			// ライフの設定
			pEffect->nLife = nLife;

			// タイプの設定
			pEffect->nType = nType;

			// 移動量の設定
		//	pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 反射光の設定
			if(pEffect->nType == EFFECTTYPE_RANDOMCOLOR)
			{// ランダムカラーの場合
				col.r = (float)(rand() % 50 + 1) / 100.0f;		// [(※)この数値を変更すると赤の要素が増減する(1～100)]
				col.g = (float)(rand() % 50 + 1) / 100.0f;		// [(※)この数値を変更すると緑の要素が増減する(1～100)]
				col.b = (float)(rand() % 50 + 1) / 100.0f;		// [(※)この数値を変更すると青の要素が増減する(1～100)]
				col.a = 1.0f;
			}
			if(pEffect->nType == EFFECTYPE_COLOR)
			{
				// ランダムカラーの場合
				col.r = (float)(rand() % 255 + 1) / 100.0f;		// [(※)この数値を変更すると赤の要素が増減する(1～100)]
				col.g = (float)(rand() % 255 + 1) / 100.0f;		// [(※)この数値を変更すると緑の要素が増減する(1～100)]
				col.b = (float)(rand() % 255 + 1) / 100.0f;		// [(※)この数値を変更すると青の要素が増減する(1～100)]
				col.a = 1.0f;
			}
			
			pEffect->fColAlphaValue = 1.0f / nLife;
			SetColorEffect(nCntEffect, col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

			// 半径の設定
			pEffect->fRadius = fRadius;
			pEffect->fRadiusValue = (fRadius * 0.55f) / nLife;
			SetRadiusEffect(nCntEffect, fRadius);

			switch(pEffect->nType)
			{
			case EFFECTTYPE_NORMAL:				// 通常エフェクト
			case EFFECTTYPE_RANDOMCOLOR:		// ランダムカラーエフェクト
				pEffect->swingRate.x = 
				pEffect->swingWidth.x = 
				pEffect->swingRate.x = 0.0f;
				pEffect->swingRate.y = 
				pEffect->swingWidth.y = 
				pEffect->swingRate.y = 0.0f;
				break;
			case EFFECTYPE_COLOR:		
				srand((unsigned)time(NULL));
				pEffect->swingRate.x = 
				pEffect->swingWidth.x = 
				pEffect->swingRate.x = 0.0f;
				pEffect->swingRate.y = 
				pEffect->swingWidth.y = 
				pEffect->swingRate.y = 0.0f;
				break;
			}
			pEffect->bUse = true;
			break;
			// 頂点データをアンロックする
		g_pVtxBuffEffect->Unlock();
		}
	}
}
