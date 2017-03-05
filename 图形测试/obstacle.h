/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_OBSTACLE_H_
#define	_OBSTACLE_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_OBSTACLE_BOX ( 26 )                     // ��Q��1�̐�
#define MAX_OBSTACLE_CAR ( 3 )                     // ��Q��2�̐�
#define MAX_OBSTACLE_CAT_01 ( 14 )                     // ��Q��3�̐�
#define POSMOVE_OBSTACLE_BOX	( 5.0f )		// ��Q��1�ړ���
#define POSMOVE_OBSTACLE_CAR	( 3.0f )		// ��Q��2�ړ���
#define POSMOVE_OBSTACLE_CAT_01	( 0.5f )		// ��Q��2�ړ���
#define FRONT_WALL		(  100.0f )		// ���̕�
#define BACK_WALL		( -100.0f )		// ��O�̕�
#define LEFT_WALL		( -100.0f )		// ���̕�
#define RIGHT_WALL		(  100.0f )		// �E�̕�
#define CEILING			(  500.0f )		// �V��
#define GROUND			(    1.0f )		// �n��

//*************************************
// ��Q���̎��
//*************************************
typedef enum
{
	OBSTACLE_NORMAL = 0,		// ��Q���Ȃ�
	OBSTACLE_BOX,	// ��Q��1
	OBSTACLE_CAR,	// ��Q��2
	OBSTACLE_CAT_01,	// ��Q��3
	OBSTACLE_MAX
} OBSTACLETYPE;
/*******************************************************************************
* �\���̐錾
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTextureObstacle;       // �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatObstacle;             // ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH pMeshObstacle;                  // ���b�V���̏��
	DWORD nNumMatObstacle;                     // �}�e���A����
	D3DXMATRIX mtxWorldObstacle;               // ���[���h�}�g���b�N�X

	bool bUse;              // �g�p���Ă��邩�ǂ���
	bool bMove;
	bool bRot;
	bool bCatRotCheck;
	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 OldRot;     // �ړI�̌���
	D3DXVECTOR3 OldPos;     // �ړI�̈ʒu
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // Max��Min�̐�Βl�𑫂��ĂQ�Ŋ��������́B�܂��Փ˔���Ŏg�����f���̔��a�Bx:�� y:���� z:���s���B
	float Collisoin;        // �Փ˔���Ŏg�������Bsize��x��z�ŁA�傫�����������Փ˔���Ɏg���B
	OBSTACLETYPE Type;
	float			fPosMove;	//�ړ���
	bool bAutoRot;
	float time;
	int nLife;
} OBSTACLE;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitObstacle( void );
void UninitObstacle( void );
void UpdateObstacle( void );
void DrawObstacle( void );
void HitObstacle_Box(void);
OBSTACLE *GetObstacle_Box( void );
OBSTACLE *GetObstacle_Car( void );
OBSTACLE *GetObstacle_Cat_01( void );
#endif