/*------------------------------------------------------------------------------
|	タイトル：		マウス処理のヘッダー
|	ファイル名：	mouse.cpp
|	作成者：		AT12A244 46 LI HAOSHENG
|	作成日：		2016/01/24
------------------------------------------------------------------------------*/
#ifndef _MOUSE_H_
#define _MOUSE_H_

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/
//マウスボタンの列挙型
typedef enum
{
	DIM_LEFT		= 0,		//マウス左ボタン
	DIM_RIGHT,					//マウス右ボタン
	DIM_CENTER,					//マウス中ボタン
	DIM_MAX
}MOUSE_BUTTONS;

//マウスポインタ情報の構造体
typedef struct
{
	RECT		moveRect;	//画面上で動ける範囲
	int			x;			//X座標
	int			y;			//Y座標
	int			moveAdd;	//移動量
}MSTATE;

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
HRESULT	InitMouse( HINSTANCE hInstance, HWND hWnd );
void	UninitMouse( void );
void	UpdateMouse( void );
MSTATE	*GetMouseState( void );
bool	GetMousePress( int nKey );
bool	GetMouseTrigger( int nKey );
bool	GetMouseRelease( int key );
bool	GetMouseRepeat( int nKey );

#endif