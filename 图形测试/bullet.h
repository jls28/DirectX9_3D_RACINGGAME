/*******************************************************************************
* �^�C�g���F �e�`��֐�
* �t�@�C�����F bullet.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/20
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
#ifndef _BULLET_H_
#define _BULLET_H_
//*------------------------------------------------------------------------------
//|	�}�N����`
//------------------------------------------------------------------------------*/
#define MAX_BULLET	(256) //�e�̐���
#define BULLET_WIDTH ( 5.0f ) //�e�̕�
#define BULLET_HEIGHT ( 7.0f ) //�e�̍���
#define LIFE_BULLET (100)

//*************************************
// �e�̎��
//*************************************
enum
{
	BULLETTYPE_PLAYER = 0,		// �v���C���[�̒e
	BULLETTYPE_PLAYER_HOMING,	// �v���C���[�̃z�[�~���O�e
	BULLETTYPE_ENEMY,			// �G�̒e
	BULLETTYPE_MAX
};

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;		//�X�P�[���l
	LPDIRECT3DTEXTURE9			pTextureBullet ;			//�e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		pVtxBuffBullet ;			//���_�o�b�t�@�ւ̃|�C���^
	float collisoin;
	int nLife;
	float fRot;		
	float fWidth;		//��
	float fHeight;		//����
	float flength;
	int nType;				// ���
	bool bUse;		//�g���Ă��邩�ǂ���
	D3DXMATRIX mtxWorldBullet;
} BULLET;
//�v���g�^�C�v�錾
HRESULT InitBullet (void);
void UninitBullet (void);
void UpdateBullet (void);
void DrawBullet (void);
void SetBullet( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife );
BULLET *GetBullet(void);
#endif	