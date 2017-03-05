/*******************************************************************************
* �^�C�g���F boxscore�`��֐�
* �t�@�C�����F boxscore.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/01
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
#ifndef _BOXSCORE01_H_
#define _BOXSCORE01_H_

#include "main.h"
//*------------------------------------------------------------------------------
//|	�}�N����`
//------------------------------------------------------------------------------*/
#define MAX_BOXSCORE01	(256) //BOXSCORE01�̐���

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posBase;	// ��ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	D3DXVECTOR3 scl;		//�g��k��
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;				// �g�p���Ă��邩�ǂ���
	int nLife;
	D3DXMATRIX				mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//�g��k���A�����A�ʒu�}�g���b�N�X
	LPDIRECT3DTEXTURE9			pTextureBoxScore01 ;			//�e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffBoxScore01 ;			//���_�o�b�t�@�ւ̃|�C���^
} BOXSCORE01;
//�v���g�^�C�v�錾
HRESULT InitBoxScore01 (void);
void UninitBoxScore01 (void);
void UpdateBoxScore01 (void);
void DrawBoxScore01 (void);
BOXSCORE01 *GetBoxScore01( void );
void SetBoxScore01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
#endif