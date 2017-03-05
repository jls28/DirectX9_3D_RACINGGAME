/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef _SKIPBG_H_
#define _SKIPBG_H_
#define MAX_SKIPBG	(1) //�c�[���̐���
#define	SKIPBG_SIZE_X		(700.0f)							// �c�[���̐����̕�
#define	SKIPBG_SIZE_Y		(300.0f)							// �c�[���̐����̍���
#define	SKIPBG_INTERVAL_X	(0.0f)							// �c�[���̐����̕\���Ԋu

#define	NUM_PLACE_SKIPBG			(1)								// �c�[���̌���

#define	NUM_PATTERN_SKIPBG			(7)						// �A�j���[�V�����̃p�^�[����

#define	TEXTURE_SIZE_X_SKIPBG		(1.0f / NUM_PATTERN_SKIPBG)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y_SKIPBG		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

#define	SKIPBG_POS_X			(200.0f)	// �c�[���̕\����ʒu�w���W
#define	SKIPBG_POS_Y			(200.0f)																	// �c�[���̕\����ʒu�x���W

#define	INTERVAL_PATTERN_SKIPBG	(65)						// �A�j���[�V�����̐؂�ւ��Ԋu
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
} SKIPBG;
//�v���g�^�C�v�錾
HRESULT InitSkipBg(void);
void UninitSkipBg(void);
void UpdateSkipBg(void);
void DrawSkipBg(void);
#endif