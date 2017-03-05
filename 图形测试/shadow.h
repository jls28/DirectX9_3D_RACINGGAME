/*******************************************************************************
* �^�C�g���F �e�`��֐�
* �t�@�C�����F shadow.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/17
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
#ifndef _SHADOW_H_
#define _SHADOW_H_

//�C���N���[�h�t�@�C��

//�}�N����`

//�V���h�[�\����
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9	pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		pTexture;					//�e�N�X�`���|���S���ւ̃|�C���^
	D3DXMATRIX				mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//�g��k���A�����A�ʒu�}�g���b�N�X
	D3DXVECTOR3				pos;						//�ʒu
	D3DXVECTOR3				rot;						//����
	D3DXVECTOR3				scl;						//�g��k��
	bool					bUse;						//�e���g�p���Ă��邩�ǂ���
}SHADOW;

//�v���g�^�C�v�̐錾
HRESULT		InitShadow();
void		UninitShadow();
void		DrawShadow();
void		SetShadow( D3DXVECTOR3 pos, float fWIDTH, float fHEIGHT, int nCntShadow, bool bUse );
SHADOW		*GetShadow();

#endif