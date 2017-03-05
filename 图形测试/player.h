/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_PLAYER_H_
#define	_PLAYER_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_PLAYER ( 1 )                     // �v���C���[�̐�
#define MAX_MODEL ( 6 )                     // ���f���̐�
#define MAX_PARTS ( 60 )                     // �p�[�c�̐�
#define MAX_KEY ( 5 )                     // �L�[�̐�
#define MAX_MOTION ( 5 )                     // ���[�V�����̐�
/*******************************************************************************
* �L�[�\���̐錾
*******************************************************************************/
typedef struct
{
	float fPosX;			//x���ʒu
	float fPosY;			//y���ʒu
	float fPosZ;			//z���ʒu

	float fRotX;			//x����]�p
	float fRotY;			//y����]�p
	float fRotZ;			//z����]�p
} KEY;

/*******************************************************************************
* �L�[���\���̐錾
*******************************************************************************/
typedef struct
{
	int nFrame;			//�Đ��t���[��
	KEY aKey [ MAX_MODEL ];			//�e���f���̃L�[�v�f
} KEY_INFO;

/*******************************************************************************
* ���[�V�������\���̐錾
*******************************************************************************/
typedef struct
{
	bool bLoop;		//���[�v���邪�ǂ���
	int nNumKey;		//�L�[��
	KEY_INFO akeyInfo [ MAX_KEY ];		//�e�L�[�̃L�[�v�f
} MOTION_INFO;
/*******************************************************************************
* ���f���\���̐錾
*******************************************************************************/
typedef struct
{
	LPD3DXMESH pMesh;                  // ���b�V���̏��
	LPD3DXBUFFER pBuffMat;             // ���_�o�b�t�@�ւ̃|�C���^
	DWORD nNumMat;                     // �}�e���A����
	LPDIRECT3DTEXTURE9 pTexture;       // �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxWorld;               // ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 OldRot;     // �ړI�̌���
	D3DXVECTOR3 OldPos;     // �ړI�̈ʒu
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // �Փ˔���Ŏg�����f���̔��a�B
	float Collisoin;        // �Փ˔���Ŏg������
	float fPosMove;        //�ړ���
	int nIndexModelDarent; //�e���f���̃C���f�b�N�X
	bool bUse;              // �g�p���Ă��邩�ǂ���
} MODEL;

/*******************************************************************************
* �v���C���[�\���̐錾
*******************************************************************************/
typedef struct
{
	D3DXMATRIX mtxWorld;               // ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 OldRot;     // �ړI�̌���
	D3DXVECTOR3 OldPos;     // �ړI�̈ʒu
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // �Փ˔���Ŏg�����f���̔��a�B
	float Collisoin;        // �Փ˔���Ŏg������
	float fPosMove;        //�ړ���
	MODEL aModel[ MAX_MODEL ];
	MOTION_INFO aMotionInfo [ MAX_MOTION ];
	int nNumParts;         //�p�[�c��
	int aIndexParent [ MAX_PARTS ];//�e�C���f�b�N�X�f�[�^
	bool bUse;             // �g�p���Ă��邩�ǂ���
} PLAYER;


/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitPlayer( void );
void UninitPlayer( void );
void UpdatePlayer( void );
void DrawPlayer( void );
MODEL *GetModel( void );
PLAYER *GetPlayer( void );
#endif