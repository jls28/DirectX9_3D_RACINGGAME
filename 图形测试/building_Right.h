/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_BUILDING_RIGHT_H_
#define	_BUILDING_RIGHT_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_BUILDING_RIGHT ( 20 )                     // �����̐�
#define POSMOVE_BUILDING_RIGHT	( 0.0f )		// �����ړ���
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
	LPDIRECT3DTEXTURE9 pTextureBuilding_Right;       // �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatBuilding_Right;             // ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH pMeshBuilding_Right;                  // ���b�V���̏��
	DWORD nNumMatBuilding_Right;                     // �}�e���A����
	D3DXMATRIX mtxWorldBuilding_Right;               // ���[���h�}�g���b�N�X

	bool bUse;              // �g�p���Ă��邩�ǂ���

	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // Max��Min�̐�Βl�𑫂��ĂQ�Ŋ��������́B�܂��Փ˔���Ŏg�����f���̔��a�Bx:�� y:���� z:���s���B
	float Collisoin;        // �Փ˔���Ŏg�������Bsize��x��z�ŁA�傫�����������Փ˔���Ɏg���B
	float			fPosMove;	//�ړ���
} BUILDING_RIGHT;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitBuilding_Right( void );
void UninitBuilding_Right( void );
void UpdateBuilding_Right( void );
void DrawBuilding_Right( void );

BUILDING_RIGHT *GetBuilding_Right( void );
#endif