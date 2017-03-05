/*------------------------------------------------------------------------------
|	タイトル：		キーボード処理のヘッダー
|	ファイル名：	keyboard.cpp
|	作成者：		AT12A244 46 LI HAOSHENG
|	作成日：		2015/06/12
------------------------------------------------------------------------------*/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
HRESULT	InitKeyboard( HINSTANCE hInstance, HWND hWnd );
void	UninitKeyboard( void );
void	UpdateKeyboard( void );
bool	GetKeyboardPress( int key );
bool	GetKeyboardTrigger( int key );
bool	GetKeyboardRelease( int key );
bool	GetKeyboardRepeat( int key );

#endif