#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//�C���N���[�h�t�@�C��

//�}�N����`
#define TRACK_WIDTH_LEFT		( -100.0f )
#define TRACK_WIDTH_RIGHT		( 100.0f )
//�ǂ̌���
typedef enum
{
	WALL_FRONT = 0,				// ���̕�
	WALL_BACK,					// �O�̕�
	WALL_LEFT,					// ���̕�
	WALL_RIGHT,					// �E�̕�
	WALL_MAX
}WALLSTATE;

//�E�H�[���̍\����
typedef struct
{
	MESH mesh;
	LPDIRECT3DTEXTURE9			pTexture;		//�e�N�X�`���|���S���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^�[
	MATRIX						mtx;			//�}�g���b�N�X
	D3DXVECTOR3					pos;			//�ʒu
	D3DXVECTOR3					rot;			//����
	D3DXVECTOR3					scl;			//�g��k��
}MESHWALL;

//�v���g�^�C�v�̐錾
HRESULT		InitMeshWall();
void		UninitMeshWall();
void		UpdateMeshWall();
void		DrawMeshWall();
MESHWALL	*GetMeshWall();

#endif