/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_PROPMODEL_GROUP_H_
#define	_PROPMODEL_GROUP_H_

/*******************************************************************************
* �}�N����`
*******************************************************************************/

#define POSMOVE_PROPMODEL_01	(    10.0f )		// �ړ���

#define POSMOVE_PROPMODEL_02	(    10.0f )		// �ړ���

#define POSMOVE_PROPMODEL_03	(    10.0f )		// �ړ���


#define POSMOVE_PROPMODEL_SPEED	(    40.0f)		//+��speed


//*************************************
// �c�[���̎��
//*************************************
typedef enum
{
	PROWT_0 = -1,		// �c�[���Ȃ�
	PROWT_1,	// �c�[��1
	PROWT_2,	// �c�[��2
	PROWT_3,	// �c�[��3
	PROWT_MAX
} PROWTYPE;

//*************************************
// �c�[���̏��(��]/�e)
//*************************************
typedef enum
{
	PROWT_TYPE = -1,		// �c�[���Ȃ�
	PROWT_SPIN,	// �c�[����]
	PROWT_BULLET,	// �c�[���e
	PROWT_STATEMAX
} PROWSTATE;

/*******************************************************************************
* �\���̐錾
*******************************************************************************/
typedef struct
{
	LPDIRECT3DTEXTURE9 pTexturePropModel;       // �e�N�X�`���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatPropModel;             // ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH pMeshPropModel;                  // ���b�V���̏��
	DWORD nNumMatPropModel;                     // �}�e���A����
	D3DXMATRIX mtxWorldPropModel;               // ���[���h�}�g���b�N�X

	bool bUse;              // �g�p���Ă��邩�ǂ���
	bool bRotUse;			//	��]�g�p���Ă��邩�ǂ���
	bool bUseCheck;
	int nLife;
	D3DXVECTOR3 pos;        // �ʒu
	D3DXVECTOR3 v3Vel;	// ���x
	D3DXVECTOR3 rot;        // ���݂̌���
	D3DXVECTOR3 OldRot;     // �ړI�̌���
	D3DXVECTOR3 OldPos;     // �ړI�̈ʒu
	D3DXVECTOR3 scl;        // �X�P�[���l
	D3DXVECTOR3 Max;        // ���_���W�̍ő�l
	D3DXVECTOR3 Min;        // ���_���W�̍ŏ��l
	D3DXVECTOR3 Size;       // Max��Min�̐�Βl�𑫂��ĂQ�Ŋ��������́B�܂��Փ˔���Ŏg�����f���̔��a�Bx:�� y:���� z:���s���B
	float Collisoin;        // �Փ˔���Ŏg�������Bsize��x��z�ŁA�傫�����������Փ˔���Ɏg���B
	float			fPosMove;	//�ړ���
	float			fAngle;							// �p�x
	float			propR;//���a
	float			time;
	int cnt;
	PROWTYPE Type;
	PROWSTATE state;

	bool				bActive;							// �L���t���O


} PROPMODELGROUP;
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitPropModel_Group( void );
void UninitPropModel_Group( void );
void UpdatePropModel_Group( void );
void DrawPropModel_Group( void );

PROPMODELGROUP *GetPropModel_01( void );
PROPMODELGROUP *GetPropModel_02( void );
PROPMODELGROUP *GetPropModel_03( void );
void SetPropModel_01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
void SetPropModel_02( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
void SetPropModel_03( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
void HitPropModel_01(void);
void HitPropModel_02(void);
int MoveShellModel01( void );
int MoveShellModel02( void );
#endif