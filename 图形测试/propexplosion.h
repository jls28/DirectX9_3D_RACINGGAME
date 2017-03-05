/*******************************************************************************
		�C���N���[�h�̏d���ǂݍ��ݖh�~

*******************************************************************************/
#ifndef	_PROPEXPLOSION_H_
#define	_PROPEXPLOSION_H_

#include <xnamath.h>
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MAX_PROPEXPLOSION ( 1 )                     // ���f���̐�


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
} PROPEXPLOSION;
// ���_�\����
struct CUSTOMVERTEX {
    XMFLOAT4	v4Pos;
	XMFLOAT2	v2UV;
};
// �����\����
struct Explosion {
	int			bActive;						// �L���t���O
	int			nTime;							// �������Ă���̎���
	XMFLOAT3	v3CenterPos;					// ���S�ʒu
	float		fRadius;						// ���a
	float		fAngle;							// �p�x
	XMMATRIX	matMatrix;						// �ϊ��s��
	float		fBright;						// ���邳
};
/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
HRESULT InitPropExplosion( void );
void UninitPropExplosion( void );
void UpdatePropExplosion( void );
void DrawPropExplosion( void );

PROPEXPLOSION *GetPropExplosion( void );
int MakeSphereIndexed( CUSTOMVERTEX *pVertices, int *pVertexNum,
					   WORD *pIndices, int *pIndexNum );		// ���̍쐬(�C���f�b�N�X�t��)
int MoveExplosion( void );
#endif