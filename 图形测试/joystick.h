/*------------------------------------------------------------------------------
|	タイトル：		ジョイスティック処理のヘッダー
|	ファイル名：	joystick.cpp
|	作成者：		AT12A244 46 LI HAOSHENG
|	作成日：		2016/01/24
------------------------------------------------------------------------------*/
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/
//ジョイスティックボタンの列挙型
typedef enum
{
	DIJ_BUTTON_X	= 0,	//ジョイスティックボタンX
	DIJ_BUTTON_A,			//ジョイスティックボタンA
	DIJ_BUTTON_B,			//ジョイスティックボタンB
	DIJ_BUTTON_Y,			//ジョイスティックボタンY
	DIJ_BUTTON_LB,			//ジョイスティックボタンLB
	DIJ_BUTTON_RB,			//ジョイスティックボタンRB
	DIJ_BUTTON_LT,			//ジョイスティックボタンLT
	DIJ_BUTTON_RT,			//ジョイスティックボタンRT
	DIJ_BUTTON_BACK,		//ジョイスティックボタンBACK
	DIJ_BUTTON_START,		//ジョイスティックボタンSTART
	DIJ_BUTTON_ROCKER_L,		//ジョイスティックボタンROCKER_L
	DIJ_BUTTON_ROCKER_R,		//ジョイスティックボタンROCKER_R
	DIJ_MAX
}JOYSTICKS_BUTTONS;

//ポインタ情報の構造体
typedef struct
{
	RECT		moveRect;	//画面上で動ける範囲
	int			x;			//X座標
	int			y;			//Y座標
	int			moveAdd;	//移動量
}JSTATE;

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
HRESULT	InitJoysticks( HINSTANCE hInstance, HWND hWnd );
void	UninitJoysticks( void );
void	UpdateJoysticks( void );
JSTATE	*GetJoysticksState( void );
bool	GetJoysticksPress( int nKey );
bool	GetJoysticksTrigger( int nKey );
bool	GetJoysticksRelease( int key );
bool	GetJoysticksRepeat( int nKey );

#endif