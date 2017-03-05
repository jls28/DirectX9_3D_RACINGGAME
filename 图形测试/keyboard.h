/*------------------------------------------------------------------------------
|	�^�C�g���F		�L�[�{�[�h�����̃w�b�_�[
|	�t�@�C�����F	keyboard.cpp
|	�쐬�ҁF		AT12A244 46 LI HAOSHENG
|	�쐬���F		2015/06/12
------------------------------------------------------------------------------*/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT	InitKeyboard( HINSTANCE hInstance, HWND hWnd );
void	UninitKeyboard( void );
void	UpdateKeyboard( void );
bool	GetKeyboardPress( int key );
bool	GetKeyboardTrigger( int key );
bool	GetKeyboardRelease( int key );
bool	GetKeyboardRepeat( int key );

#endif