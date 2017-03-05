//=============================================================================
//
// デバックの処理 [debugProc.cpp]
// 
//
//=============================================================================
/*******************************************************************************
* 更新履歴：
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include <stdio.h>
#include <varargs.h>
#include <stdarg.h>
#include "input.h"
#include "debugProc.h"
#include "bullet.h"
#include "modelbody.h"
#include "camera.h"
#include "propmodel_Group.h"
#include "mouse.h"
#include "obstacle.h"
#include "score.h"
#include "player.h"
/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/
#define FONT_MAX	( 1024 )		//デバッグ文字列の最大数
/*******************************************************************************
/* グローバル変数
********************************************************************************/
LPD3DXFONT g_DebugFont = NULL;		//フォントのポインタ

char g_StrDebug [FONT_MAX];		// デバックの文字列の最大数
RECT rect = { 0,      0, SCREEN_WIDTH, SCREEN_HEIGHT };
/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
void PrintDebugProc( char *fmt, ... );
/********************************************************************************
関数名: デバックの初期化関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
HRESULT InitDebugProc( void )
{
	//デバイスのゲッター
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateFont( pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_DebugFont );		//デバイスとフォント用のフォント オブジェクトを作成
	memset(g_StrDebug,		//ターゲットへのポインター
			0,		//設定する文字
			sizeof g_StrDebug		//文字数
			);
	return S_OK;
}
/********************************************************************************
関数名: デバックの描画関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void DrawDebugProc(void)
{	
	g_DebugFont -> DrawText(
						 NULL,		//// デバイスコンテキストのハンドル
						 &g_StrDebug[ 0 ],		// 描画するテキスト
						 -1,		// テキストの長さ
						 &rect,		// テキストを描画する長方形領域
						 DT_LEFT,		//テキストを左揃えにします
						 D3DCOLOR_RGBA( 255, 0, 255, 255 )		//色、背景色で描画
						 );

	memset(g_StrDebug,		//ターゲットへのポインター
			0,		//設定する文字
			sizeof g_StrDebug		//文字数
			);
}
/********************************************************************************
関数名: 可変個引数リストにアクセスします
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : 
*******************************************************************************/
void PrintDebugProc (char *fmt,	...)
{
	int font;

	//文字数チェック
	font = strlen( g_StrDebug );

	va_list list;
	va_start( list, fmt );//引数リストへのポインタを指定します
	vsprintf( &g_StrDebug[ font ], fmt, list);
	va_end( list );
}
/********************************************************************************
関数名: デバックの開放関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UninitDebugProc(void)
{
	if( g_DebugFont != NULL )
	{
		( g_DebugFont ) -> Release();
		g_DebugFont = NULL;
	}
}
/********************************************************************************
関数名: デバックの更新関数
* 
* 引数  : ナシ
* 戻り値: ナシ
* 説明  : ナシ
*******************************************************************************/
void UpdateDebugProc(void)
{
	//カメラを取得
	CAMERA		pCamera	= GetCamera();

	//モデルを取得
	MODELBODY		*pModelBody		= GetModelBody();

	PROPMODELGROUP		*pPropModel_01		= GetPropModel_01();

	PROPMODELGROUP		*pPropModel_02		= GetPropModel_02();

	PROPMODELGROUP		*pPropModel_03		= GetPropModel_03();

	MSTATE		*pMouse		=GetMouseState();

	OBSTACLE *pObstacle_Box = GetObstacle_Box();

	SCORE *pScore = GetScore();

	MODEL *pModel = GetModel();

	PLAYER *pPlayer = GetPlayer();
	PrintDebugProc( "*** カメラの情報 ***\n" );
	PrintDebugProc( "[カメラの視点       ( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera.posV.x, pCamera.posV.y, pCamera.posV.z );
	PrintDebugProc( "[カメラの注視点     ( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera.posR.x, pCamera.posR.y, pCamera.posR.z );
	PrintDebugProc( "[カメラの向き       ( %.2f )]\n", pCamera.rot.y );
	PrintDebugProc( "[視点と注視点の距離 ( %.2f )]\n\n", pCamera.fDistance );

	PrintDebugProc( "*** モデルの情報 ***\n" );
	PrintDebugProc( "[モデルの位置       ( X:%.2f Y:%.2f Z:%.2f )]\n", pModelBody ->OldPos .x, pModelBody -> OldPos.y, pModelBody -> OldPos.z );
	PrintDebugProc( "[モデルの向き       ( %.2f )\n", pModelBody -> rot.y );
	PrintDebugProc( "[モデル目的の向き   ( %.2f )\n\n", pModelBody -> OldRot.y );

	PrintDebugProc( "*** モデルの操作 ***\n" );
	PrintDebugProc( "前移動       -> W\n" );
	PrintDebugProc( "後移動       -> S\n" );
	PrintDebugProc( "左移動       -> A\n" );
	PrintDebugProc( "右移動       -> D\n" );
	PrintDebugProc( "上昇         -> I\n" );
	PrintDebugProc( "下降         -> K\n" );
	PrintDebugProc( "弾発射       -> SPACE\n" );
	PrintDebugProc( "左旋回       -> LSHIFT\n" );
	PrintDebugProc( "右旋回       -> RSHIFT\n" );
	PrintDebugProc( "位置リセット -> ENTER\n\n" );
	PrintDebugProc( "マウス位置:x:%d,y:%d\n",pMouse->x,pMouse->y);
	PrintDebugProc( "score:%d\n",pScore->g_nScore);

	PrintDebugProc( "0model:x:%.2f y:%.2f z:%.2f \n",(pModel+0)->pos.x,(pModel+0)->pos.y,(pModel+0)->pos.z);
	PrintDebugProc( "1model:x:%.2f y:%.2f z:%.2f \n",(pModel+1)->pos.x,(pModel+1)->pos.y,(pModel+1)->pos.z);
	PrintDebugProc( "2model:x:%.2f y:%.2f z:%.2f \n",(pModel+2)->pos.x,(pModel+2)->pos.y,(pModel+2)->pos.z);
	PrintDebugProc( "3model:x:%.2f y:%.2f z:%.2f \n",(pModel+3)->pos.x,(pModel+3)->pos.y,(pModel+3)->pos.z);
	PrintDebugProc( "4model:x:%.2f y:%.2f z:%.2f \n",(pModel+4)->pos.x,(pModel+4)->pos.y,(pModel+4)->pos.z);
	PrintDebugProc( "5model:x:%.2f y:%.2f z:%.2f \n",(pModel+5)->pos.x,(pModel+5)->pos.y,(pModel+5)->pos.z);

	PrintDebugProc( "player:x:%.2f y:%.2f z:%.2f \n",pPlayer->pos.x,pPlayer->pos.y,pPlayer->pos.z);
}
