#include "main.h"
#include "resultbg.h"
#include "result.h"
#include "fade.h"
#include "keyboard.h"
#include "sound.h"
//=============================================================================
//  関数名　：InitResult
//  機能概要：プリゴンの初期化
//  戻り値　：
//=============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM001);
	InitResultBg();
}
//=============================================================================
//  関数名　：UninitResult
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitResult(void)
{
	UninitResultBg();
}
//=============================================================================
//  関数名　：DrawResult
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawResult(void)
{
	DrawResultBg();
}
//=============================================================================
//  関数名　：UpdateResult
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateResult(void)
{
	UpdateResultBg();
	MODE mode;
	mode = GetMode();
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_TITLE);
	}
}
