/*******************************************************************************
* �^�C�g���F �c�[���`��֐�
* �t�@�C�����F propmpmax.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/01
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
#ifndef _PROPMPMAX_H_
#define _PROPMPMAX_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	�}�N����`
//------------------------------------------------------------------------------*/
#define MAX_PROPMPMAX	(1) //�c�[���̐���
#define PROPMPMAX_WIDTH ( 15.0f ) //�c�[���̕�
#define PROPMPMAX_HEIGHT ( 100.0f ) //�c�[���̍���
#define	PROPMPMAX_INTERVAL_X	(0.0f)							// �c�[���̐����̕\���Ԋu

#define	NUM_PLACE_PROPMPMAX			(1)								// �c�[���̌���

#define	NUM_PATTERN_PROPMPMAX			(2)						// �A�j���[�V�����̃p�^�[����

#define	TEXTURE_SIZE_X_PROPMPMAX		(1.0f / NUM_PATTERN_PROPMPMAX)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y_PROPMPMAX		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���


#define	INTERVAL_PATTERN_PROPMPMAX	(10)						// �A�j���[�V�����̐؂�ւ��Ԋu
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
} PROPMPMAX;
//�v���g�^�C�v�錾
HRESULT InitPropMpMax (void);
void UninitPropMpMax (void);
void UpdatePropMpMax (void);
void DrawPropMpMax (void);
PROPMPMAX *GetPropMpMax( void );
#endif