/*******************************************************************************
* �^�C�g���F �c�[���`��֐�
* �t�@�C�����F propshow	.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/12/15
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
#ifndef _PROPSHOW_H_
#define _PROPSHOW_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	�}�N����`
//------------------------------------------------------------------------------*/
#define MAX_PROW	(1) //�c�[���̐���
#define PROW_WIDTH ( 30.0f ) //�c�[���̕�
#define PROW_HEIGHT ( 30.0f ) //�c�[���̍���
#define	PROW_SIZE_X		(100.0f)							// �c�[���̐����̕�
#define	PROW_SIZE_Y		(100.0f)							// �c�[���̐����̍���
#define	PROW_INTERVAL_X	(0.0f)							// �c�[���̐����̕\���Ԋu

#define	NUM_PLACE_PROW			(1)								// �c�[���̌���

#define	NUM_PATTERN_PROW			(3)						// �A�j���[�V�����̃p�^�[����

#define	TEXTURE_SIZE_X_PROW		(1.0f / NUM_PATTERN_PROW)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y_PROW		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

#define	PROW_POS_X			(SCREEN_WIDTH - (PROW_INTERVAL_X + PROW_SIZE_X) * NUM_PLACE_PROW - 10.0f)	// �c�[���̕\����ʒu�w���W
#define	PROW_POS_Y			(10.0f)																	// �c�[���̕\����ʒu�x���W

#define	INTERVAL_PATTERN_PROW	(5)						// �A�j���[�V�����̐؂�ւ��Ԋu
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
	bool bProwUse;
} PROW;
//�v���g�^�C�v�錾
HRESULT InitProw (void);
void UninitProw (void);
void UpdateProw (void);
void DrawProw (void);
PROW *GetProw( void );
#endif