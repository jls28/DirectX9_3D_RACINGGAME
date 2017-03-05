/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef _SKIPBG2_H_
#define _SKIPBG2_H_
#define MAX_SKIPBG2	(1) //�c�[���̐���
#define	SKIPBG2_SIZE_X		(300.0f)							// �c�[���̐����̕�
#define	SKIPBG2_SIZE_Y		(300.0f)							// �c�[���̐����̍���
#define	SKIPBG2_INTERVAL_X	(0.0f)							// �c�[���̐����̕\���Ԋu

#define	NUM_PLACE_SKIPBG2			(1)								// �c�[���̌���

#define	NUM_PATTERN_SKIPBG2			(7)						// �A�j���[�V�����̃p�^�[����

#define	TEXTURE_SIZE_X_SKIPBG2		(1.0f / NUM_PATTERN_SKIPBG2)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y_SKIPBG2		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

#define	SKIPBG2_POS_X			(200.0f)	// �c�[���̕\����ʒu�w���W
#define	SKIPBG2_POS_Y			(200.0f)																	// �c�[���̕\����ʒu�x���W

#define	INTERVAL_PATTERN_SKIPBG2	(5)						// �A�j���[�V�����̐؂�ւ��Ԋu
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
} SKIPBG2;
//�v���g�^�C�v�錾
HRESULT InitSkipBg2(void);
void UninitSkipBg2(void);
void UpdateSkipBg2(void);
void DrawSkipBg2(void);
SKIPBG2 *GetSkipBg2( void );
#endif