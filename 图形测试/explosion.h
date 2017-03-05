//=============================================================================
//
// �������� [explosion.h]
// 2015/11/24 LIHAOSHENG
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	D3DXVECTOR3 scl;	//�g��k��
	D3DXCOLOR col;		// �Fz
	int nCount;			// �J�E���^
	int nPattern;		// �p�^�[��No.
	bool bUse;			// �g�p���Ă��邩�ǂ���
	D3DXMATRIX mtxWorldExplosion;					// ���[���h�}�g���b�N�X�B�r���[�}�g���b�N�X�̋t�s�������B

} EXPLOSION;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos);
void ResetExplosion(void);
EXPLOSION *GetExplosion(void);
#endif
