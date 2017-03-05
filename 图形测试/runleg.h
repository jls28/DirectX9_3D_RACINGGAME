/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_RUNLEG_H_
#define	_RUNLEG_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_RUNLEG ( 2 )                     // �c�[���̐�

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
	bool bUse;				// �g�p���Ă��邩�ǂ���
	D3DXMATRIX				mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//�g��k���A�����A�ʒu�}�g���b�N�X
	LPDIRECT3DTEXTURE9			pTextureRunLeg ;			//�e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffRunLeg ;			//���_�o�b�t�@�ւ̃|�C���^
	int nCount;			// �J�E���^
	int nPattern;		// �p�^�[��No.
} RUNLEG;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitRunLeg( void );
void UninitRunLeg( void );
void UpdateRunLeg( void );
void DrawRunLeg( void );
void ResetRunLeg(void);
RUNLEG *GetRunLeg( void );
void SetTextureRunLeg(int nRunLegID);
#endif