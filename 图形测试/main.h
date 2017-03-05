#ifndef _MAIN_H_
#define _MAIN_H_

//インクルードファイル
#define  DIRECTINPUT_VERSION ( 0x0800 )
#include <Windows.h>
#include "d3dx9.h"		//描画処理に必要
#include "dinput.h"		//入力処理に必要
#include "xaudio2.h"		// XAudio2関連のヘッダー
//ライブラリのリンク
#pragma comment ( lib, "d3d9.lib" )			//描画処理に必要
#pragma comment ( lib, "d3dx9.lib" )		//上記の拡張ライブラリ
#pragma comment ( lib, "dxguid.lib" )		//DirectXコンポーネント使用に必要
#pragma comment ( lib, "winmm.lib" )		//マルチメディアタイマー使用に必要
#pragma comment ( lib, "dinput8.lib" )		//入力処理に必要
#pragma warning ( disable: 4996 )			//

//マクロ定義
#define SCREEN_WIDTH	( 1280 )														//ウィンドウの幅
#define SCREEN_HEIGHT	( 720 )															//ウインドウの高
#define SCREEN_CENTER_X	( SCREEN_WIDTH / 2 )		//ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	( SCREEN_HEIGHT / 2 )		//ウインドウの中心Ｙ座標
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//頂点座標(3d) | 法線 | 頂点カラー | テクスチャ座標
#define	NUM_POLYGON		(2)		// ポリゴン数
//モードの種類
typedef enum
{
	MODE_TITLE = 0,		//タイトル画面
	MODE_SKIP,
	MODE_RULE,
	MODE_RULE2,
	MODE_GAME,			//ゲーム画面
	MODE_RANKING,
	MODE_RESULT,		//リザルト画面
	MODE_RESULT2,
	MODE_MAX
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// テクスチャのパースペクティブコレクト用
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//構造体定義
typedef struct
{
	D3DXVECTOR3	pos;	//頂点座標
	D3DXVECTOR3	nor;	//法線ベクトル( 面の向き )
	D3DCOLOR	col;	//頂点カラー
	D3DXVECTOR2	tex;	//テクスチャ座標
}VERTEX_3D;

//メッシュ構造体
typedef struct
{
	int			nNumVtxV;		//横の頂点数
	int			nNumVtxH;		//縦の頂点数
	int			nNumVtx;		//総頂点数
	int			nNumIdx;		//インデックス数
	int			nNumPrimitive;	//ポリゴン数
	int			nNumBlock;		//ブロック数
	int			nNumIdxEven;	//インデックスバッファ頂点が偶数の数(退化三角形頂点以外)
	int			nNumNullTri;	//縮退ポリゴン頂点の数
	int			nMultiple;		//インデックスバッファ用係数
	float		fVtxAdjust;		//テクスチャY座標位置ずらす係数
	float		fTexAdjust;		//Z座標位置をずらす係数
}MESH;

//マトリックス構造体
typedef struct
{
	D3DXMATRIX	Projection;		//プロジェクションマトリックス
	D3DXMATRIX	World;			//ワールドマトリックス
	D3DXMATRIX	View;			//ビューマトリックス
	D3DXMATRIX	Scl;			//スケールマトリックス
	D3DXMATRIX	Rot;			//回転マトリックス
	D3DXMATRIX	Trans;			//位置マトリックス
}MATRIX;

//プロトタイプの宣言
LPDIRECT3DDEVICE9	GetDevice();
void SetMode(MODE mode);
MODE GetMode(void);
#endif