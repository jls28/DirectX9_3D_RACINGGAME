/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_ENEMY_H_
#define	_ENEMY_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_ENEMY ( 1 )                     // �G���f���̐�

#define POSMOVE_ENEMY	(    2.0f )		// �ړ���
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
	LPDIRECT3DTEXTURE9 pTexture;       // �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;             // ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH pMesh;                  // ���b�V���̏��
	DWORD nNumMat;                     // �}�e���A����
	D3DXMATRIX mtxWorld;               // ���[���h�}�g���b�N�X

	bool bUse;              // �g�p���Ă��邩�ǂ���

	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 OldRot;     // �ړI�̌���
	D3DXVECTOR3 OldPos;     // �ړI�̈ʒu
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // Max��Min�̐�Βl�𑫂��ĂQ�Ŋ��������́B�܂��Փ˔���Ŏg�����f���̔��a�Bx:�� y:���� z:���s���B
	float Collisoin;        // �Փ˔���Ŏg�������Bsize��x��z�ŁA�傫�����������Փ˔���Ɏg���B
	float			fPosMove;	//�ړ���
	bool bAutoRot;
	float time;
} ENEMY;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitEnemy( void );
void UninitEnemy( void );
void UpdateEnemy( void );
void DrawEnemy( void );

ENEMY *GetEnemy( void );

#endif