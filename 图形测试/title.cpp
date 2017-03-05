#include "main.h"
#include "title.h"
#include "titlebg.h"
#include "press.h"
#include "fade.h"
#include "keyboard.h"
#include "sound.h"
//=============================================================================
//  �֐����@�FInitTitle
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
void InitTitle (void)
{
	PlaySound(SOUND_LABEL_BGM000);

	InitTitleBg();
	InitPress();
}
//=============================================================================
//  �֐����@�FUninitTitle
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTitle(void)
{
	UninitTitleBg();
	UninitPress();
}
//=============================================================================
//  �֐����@�FDrawTitle
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTitle(void)
{
	DrawTitleBg();
	DrawPress();
}
//=============================================================================
//  �֐����@�FUpdateTitle
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTitle(void)
{
	MODE mode;
	mode = GetMode();
	UpdateTitleBg();
	UpdatePress();
}