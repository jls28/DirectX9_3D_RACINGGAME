#include "main.h"
#include "skip.h"
#include "skipbg.h"
#include "skipbg2.h"
#include "fade.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
#include "skipbg0.h"
#include "sound.h"
//=============================================================================
//  関数名　：InitSkip
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitSkip (void)
{
	InitSkipBg0();
	InitSkipBg();
	InitSkipBg2();

}
//=============================================================================
//  関数名　：UninitSkip
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitSkip(void)
{
	UninitSkipBg0();
	UninitSkipBg();
	UninitSkipBg2();
}
//=============================================================================
//  関数名　：DrawSkip
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawSkip(void)
{
	DrawSkipBg0();
	DrawSkipBg();
	DrawSkipBg2();
}
//=============================================================================
//  関数名　：UpdateSkip
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateSkip(void)
{
	UpdateSkipBg0();
	UpdateSkipBg();
	UpdateSkipBg2();
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_RULE);
	}
}