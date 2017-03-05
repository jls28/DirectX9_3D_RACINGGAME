//=============================================================================
//
// score���� [score.h]
// 2016/02/20 LIHAOSHENG
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 scl;	//�g��k��
	D3DXCOLOR col;		// �Fz
	bool bUse;			// �g�p���Ă��邩�ǂ���
	bool bCheck;
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X�B�r���[�}�g���b�N�X�̋t�s�������B
	int g_nScore;		//�X�R�A�̐�
} SCORE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int value);
SCORE *GetScore(void);
int *GetScoreNum(void);
#endif
