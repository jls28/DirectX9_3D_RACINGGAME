#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//�C���N���[�h�t�@�C��

//�}�N����`
#define MESHFIELD_TEXTURE_FILE	"data\\TEXTURE\\field001.jpg"	//�n�ʃe�N�X�`���t�@�C���ʒu
#define MESHFIELD_WIDTH			( 200.0f )						//�t�B�[���h�̕�
#define MESHFIELD_HEIGHT		( 200.0f )						//�t�B�[���h�̍���

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
	float						fFixedPos;		//�E�H�[���p�O���Œ���W�W��
}MESHFIELD;

//�v���g�^�C�v�̐錾
HRESULT		InitMeshField();
void		UninitMeshField();
void		UpdateMeshField();
void		DrawMeshField();
MESHFIELD	*GetMeshField();

#endif