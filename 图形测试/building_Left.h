/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_BUILDING_LEFT_H_
#define	_BUILDING_LEFT_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_BUILDING_LEFT ( 20 )                     // �����̐�
#define POSMOVE_BUILDING_LEFT	( 0.0f )		// �����ړ���
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
	LPDIRECT3DTEXTURE9 pTextureBuilding_Left;       // �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatBuilding_Left;             // ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH pMeshBuilding_Left;                  // ���b�V���̏��
	DWORD nNumMatBuilding_Left;                     // �}�e���A����
	D3DXMATRIX mtxWorldBuilding_Left;               // ���[���h�}�g���b�N�X

	bool bUse;              // �g�p���Ă��邩�ǂ���

	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // Max��Min�̐�Βl�𑫂��ĂQ�Ŋ��������́B�܂��Փ˔���Ŏg�����f���̔��a�Bx:�� y:���� z:���s���B
	float Collisoin;        // �Փ˔���Ŏg�������Bsize��x��z�ŁA�傫�����������Փ˔���Ɏg���B
	float			fPosMove;	//�ړ���
} BUILDING_LEFT;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitBuilding_Left( void );
void UninitBuilding_Left( void );
void UpdateBuilding_Left( void );
void DrawBuilding_Left( void );

BUILDING_LEFT *GetBuilding_Left( void );
#endif