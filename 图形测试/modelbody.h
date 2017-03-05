/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_MODELBODY_H_
#define	_MODELBODY_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_MODELBODY ( 1 )                     // ���f���̐�

#define POSMOVE_MODELBODY	(    5.0f )		// �ړ���
#define FRONT_WALL		(  100.0f )		// ���̕�
#define BACK_WALL		( -100.0f )		// ��O�̕�
#define LEFT_WALL		( -100.0f )		// ���̕�
#define RIGHT_WALL		(  100.0f )		// �E�̕�
#define CEILING			(  500.0f )		// �V��
#define GROUND			(    1.0f )		// �n��

/*******************************************************************************
* �\���̐錾
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTextureModelBody;       // �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModelBody;             // ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH pMeshModelBody;                  // ���b�V���̏��
	DWORD nNumMatModelBody;                     // �}�e���A����
	D3DXMATRIX mtxWorldModelBody;               // ���[���h�}�g���b�N�X

	bool bUse;              // �g�p���Ă��邩�ǂ���
	bool bKeyUse;
	bool bAutoRot;
	bool bJump;
	bool bMove;
	bool bUseCheck;
	bool bUseCheckCat;
	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 vel;        // ���x
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 OldRot;     // �ړI�̌���
	D3DXVECTOR3 OldPos;     // �ړI�̈ʒu
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // Max��Min�̐�Βl�𑫂��ĂQ�Ŋ��������́B�܂��Փ˔���Ŏg�����f���̔��a�Bx:�� y:���� z:���s���B
	float Collisoin;        // �Փ˔���Ŏg�������Bsize��x��z�ŁA�傫�����������Փ˔���Ɏg���B
	float			fPosMove;	//�ړ���
	float time;
	int Rand;
} MODELBODY;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitModelBody( void );
void UninitModelBody( void );
void UpdateModelBody( void );
void DrawModelBody( void );
void ModelJump(void);
MODELBODY *GetModelBody( void );

#endif