//=============================================================================
//
// �|���v���� [countdown.h]
// 2016/02/24 LIHAOSHENG
//
//=============================================================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	�}�N����`
//------------------------------------------------------------------------------*/
#define MAX_COUNTDOWN	(1) //�|���v�̐���
#define	COUNTDOWN_SIZE_X		(450.0f)							// �|���v�̐����̕�
#define	COUNTDOWN_SIZE_Y		(350.0f)							// �|���v�̐����̍���
#define	COUNTDOWN_INTERVAL_X	(0.0f)							// �|���v�̐����̕\���Ԋu

#define	NUM_PLACE_COUNTDOWN			(1)								// �|���v�̌���

#define	NUM_PATTERN_COUNTDOWN			(3)						// �A�j���[�V�����̃p�^�[����

#define	TEXTURE_SIZE_X_COUNTDOWN		(1.0f / NUM_PATTERN_COUNTDOWN)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y_COUNTDOWN		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

#define	COUNTDOWN_POS_X			(430.0f)	// �|���v�̕\����ʒu�w���W
#define	COUNTDOWN_POS_Y			(200.0f)																	// �|���v�̕\����ʒu�x���W

#define	INTERVAL_PATTERN_COUNTDOWN	(60)						// �A�j���[�V�����̐؂�ւ��Ԋu
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 move;	// �ړ���
	D3DXCOLOR col;		// �F
	int nCount;			// �J�E���^
	int nPattern;		// �p�^�[��No.
	bool bUse;			// �g�p���Ă��邩�ǂ���
} COUNTDOWN;
//�v���g�^�C�v�錾
HRESULT InitCountdown (void);
void UninitCountdown (void);
void UpdateCountdown (void);
void DrawCountdown (void);
COUNTDOWN *GetCountdown( void );
#endif