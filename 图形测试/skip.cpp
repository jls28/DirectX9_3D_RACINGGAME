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
//  �֐����@�FInitSkip
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitSkip (void)
{
	InitSkipBg0();
	InitSkipBg();
	InitSkipBg2();

}
//=============================================================================
//  �֐����@�FUninitSkip
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitSkip(void)
{
	UninitSkipBg0();
	UninitSkipBg();
	UninitSkipBg2();
}
//=============================================================================
//  �֐����@�FDrawSkip
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawSkip(void)
{
	DrawSkipBg0();
	DrawSkipBg();
	DrawSkipBg2();
}
//=============================================================================
//  �֐����@�FUpdateSkip
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
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