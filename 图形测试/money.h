/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_MONEY_H_
#define	_MONEY_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_MONEY ( 8 )                     // �c�[���̐�
#define LIFE_MONEY (100)
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
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
	int nLife;
	D3DXMATRIX				mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//�g��k���A�����A�ʒu�}�g���b�N�X
	LPDIRECT3DTEXTURE9			pTextureMoney ;			//�e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffMoney ;			//���_�o�b�t�@�ւ̃|�C���^
} MONEY;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitMoney( void );
void UninitMoney( void );
void UpdateMoney( void );
void DrawMoney( void );

MONEY *GetMoney( void );
void SetMoney( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
#endif