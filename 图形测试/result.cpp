#include "main.h"
#include "resultbg.h"
#include "result.h"
#include "fade.h"
#include "keyboard.h"
#include "sound.h"
//=============================================================================
//  �֐����@�FInitResult
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�F
//=============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM001);
	InitResultBg();
}
//=============================================================================
//  �֐����@�FUninitResult
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitResult(void)
{
	UninitResultBg();
}
//=============================================================================
//  �֐����@�FDrawResult
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawResult(void)
{
	DrawResultBg();
}
//=============================================================================
//  �֐����@�FUpdateResult
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
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
