#include "main.h"
#include "score.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE	"data\\TEXTURE\\score.png"	// 読み込むテクスチャファイル名
#define	SCORE_POS_X		(10.0f)							// SCOREの表示基準位置Ｘ座標
#define	SCORE_POS_Y		(0.0f)							// SCOREの表示基準位置Ｙ座標
#define	SCORE_WIDTH		(20.0f)							// SCOREの幅
#define	SCORE_HEIGHT	(40.0f)							// SCOREの高さ

#define	MAX_SCORE		(5)					// SCOREの最大数

#define	NUM_PATTERN			(8)						// アニメーションのパターン数
#define	TEXTURE_SIZE_X		(1.0f / NUM_PATTERN)	// テクスチャ内の１パターンの幅
#define	TEXTURE_SIZE_Y		(1.0f)					// テクスチャ内の１パターンの高さ

//*****************************************************************************
// グローバル変数
//*****************************************************************************

LPDIRECT3DTEXTURE9 g_pTextureScore =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore =NULL;	//頂点パッファへのポインタ
int nScore [MAX_SCORE];
SCORE g_Score[MAX_SCORE];

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);
//=============================================================================
//  関数名　：InitScore
//  機能概要：スコアの初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitScore(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++)
	{
		g_Score[cntscore].pos = D3DXVECTOR3(SCORE_POS_X + cntscore * SCORE_WIDTH , SCORE_POS_Y + SCORE_HEIGHT/2, 0.0f);

		g_Score[cntscore].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

		g_Score[cntscore].scl= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );	//拡大縮小

		g_Score[cntscore].bCheck = false;

		g_Score[cntscore].g_nScore = 1000;
	}

	//テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			TEXTURE_SCORE,
		&g_pTextureScore);

	// 頂点情報の作成
	MakeVertexScore(pDevice);

	return S_OK;
}
//=============================================================================
//  関数名　：UninitScore
//  機能概要：スコアの終了処理
//  戻り値　：
//=============================================================================
void UninitScore(void)
{

	if(g_pVtxBuffScore!=NULL)
	{
		g_pVtxBuffScore->Release();		//頂点バッファの開放
		g_pVtxBuffScore=NULL;
	}
	if(g_pTextureScore!=NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore=NULL;
	}
}
//=============================================================================
//  関数名　：DrawScore
//  機能概要：スコアの描画処理
//  戻り値　：
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureScore);

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffScore,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<MAX_SCORE;i++)
	{
	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  (0+4*i),		// 最初の頂点のインデックス
							  2			// 描画するプリミティブ数
							);
	}
}
//=============================================================================
//  関数名　：UpdateScore
//  機能概要：スコアの更新処理
//  戻り値　：
//=============================================================================
void UpdateScore(void)
{
	//if(GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	AddScore(1);
	//}
	//nScore[0] =g_nScore / 10000000 % 100;		//千万
	//nScore[1] =g_nScore / 1000000 % 10;		//100万
	//nScore[2] =g_nScore / 100000 % 10;		//10万
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++)
	{
	nScore[0] = g_Score[cntscore].g_nScore / 10000 % 10;		//1万
	nScore[1] = g_Score[cntscore].g_nScore / 1000 % 10;		//1千
	nScore[2] = g_Score[cntscore].g_nScore / 100 % 10;		//100
	nScore[3] = g_Score[cntscore].g_nScore / 10 % 10;		//10
	nScore[4] = g_Score[cntscore].g_nScore / 1 % 10;		//1
	}
	VERTEX_2D *pVtx;
	g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得

	for(int i= 0;i<MAX_SCORE;i++)
	{

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,1.0f);

	}
		g_pVtxBuffScore ->Unlock();	//LOCK
}
/*******************************************************************************
* 関数名:AddScore
* 
* 引数  : value
* 戻り値: ナシ
*******************************************************************************/
void AddScore(int value)
{	
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++)
	{
		g_Score[cntscore].g_nScore +=value;
		if(g_Score[cntscore].g_nScore<=0)
		{
			g_Score[cntscore].g_nScore = 0;
		}
		if(g_Score[cntscore].g_nScore>=4000)
		{
			g_Score[cntscore].bCheck = true;
		}
	}
}
SCORE *GetScore(void)
{
	return &g_Score[0];
}
int *GetScoreNum(void)
{
	return &nScore[0];
}
//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*MAX_SCORE),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffScore,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
	g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++,pVtx += 4 )
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1].tex = D3DXVECTOR2(0.1f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0].pos = D3DXVECTOR3( g_Score[cntscore].pos.x - SCORE_WIDTH/2,  g_Score[cntscore].pos.y - SCORE_HEIGHT/2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( g_Score[cntscore].pos.x + SCORE_WIDTH/2,  g_Score[cntscore].pos.y - SCORE_HEIGHT/2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3( g_Score[cntscore].pos.x - SCORE_WIDTH/2,  g_Score[cntscore].pos.y + SCORE_HEIGHT/2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( g_Score[cntscore].pos.x + SCORE_WIDTH/2,  g_Score[cntscore].pos.y + SCORE_HEIGHT/2, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 );	//頂点情報格納ワーク
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	g_pVtxBuffScore ->Unlock();	//LOCK

	return S_OK;
}
