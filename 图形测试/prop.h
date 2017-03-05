/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_PROP_H_
#define	_PROP_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_PROP ( 39 )                     // �c�[���̐�
#define LIFE_PROP (100)
//*************************************
// �c�[���̂̏��
//*************************************
typedef enum
{
	PROPSTATE_START = 0,	// �J�n
	PROPSTATE_NORMAL,		// �ʏ�
	PROPSTATE_END,		// �I��
	PROPSTATE_MAX
} PROPSTATE;
/*******************************************************************************
* �\���̐錾
*******************************************************************************/
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
	int nLife;				// ���C�t
	PROPSTATE state;			// ���
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
	D3DXMATRIX				mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//�g��k���A�����A�ʒu�}�g���b�N�X
	LPDIRECT3DTEXTURE9			pTextureProp ;			//�e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffProp ;			//���_�o�b�t�@�ւ̃|�C���^
} PROP;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitProp( void );
void UninitProp( void );
void UpdateProp( void );
void DrawProp( void );

PROP *GetProp( void );

#endif