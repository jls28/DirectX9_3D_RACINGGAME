#ifndef _MAIN_H_
#define _MAIN_H_

//�C���N���[�h�t�@�C��
#define  DIRECTINPUT_VERSION ( 0x0800 )
#include <Windows.h>
#include "d3dx9.h"		//�`�揈���ɕK�v
#include "dinput.h"		//���͏����ɕK�v
#include "xaudio2.h"		// XAudio2�֘A�̃w�b�_�[
//���C�u�����̃����N
#pragma comment ( lib, "d3d9.lib" )			//�`�揈���ɕK�v
#pragma comment ( lib, "d3dx9.lib" )		//��L�̊g�����C�u����
#pragma comment ( lib, "dxguid.lib" )		//DirectX�R���|�[�l���g�g�p�ɕK�v
#pragma comment ( lib, "winmm.lib" )		//�}���`���f�B�A�^�C�}�[�g�p�ɕK�v
#pragma comment ( lib, "dinput8.lib" )		//���͏����ɕK�v
#pragma warning ( disable: 4996 )			//

//�}�N����`
#define SCREEN_WIDTH	( 1280 )														//�E�B���h�E�̕�
#define SCREEN_HEIGHT	( 720 )															//�E�C���h�E�̍�
#define SCREEN_CENTER_X	( SCREEN_WIDTH / 2 )		//�E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	( SCREEN_HEIGHT / 2 )		//�E�C���h�E�̒��S�x���W
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//���_���W(3d) | �@�� | ���_�J���[ | �e�N�X�`�����W
#define	NUM_POLYGON		(2)		// �|���S����
//���[�h�̎��
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g�����
	MODE_SKIP,
	MODE_RULE,
	MODE_RULE2,
	MODE_GAME,			//�Q�[�����
	MODE_RANKING,
	MODE_RESULT,		//���U���g���
	MODE_RESULT2,
	MODE_MAX
}MODE;

typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//�\���̒�`
typedef struct
{
	D3DXVECTOR3	pos;	//���_���W
	D3DXVECTOR3	nor;	//�@���x�N�g��( �ʂ̌��� )
	D3DCOLOR	col;	//���_�J���[
	D3DXVECTOR2	tex;	//�e�N�X�`�����W
}VERTEX_3D;

//���b�V���\����
typedef struct
{
	int			nNumVtxV;		//���̒��_��
	int			nNumVtxH;		//�c�̒��_��
	int			nNumVtx;		//�����_��
	int			nNumIdx;		//�C���f�b�N�X��
	int			nNumPrimitive;	//�|���S����
	int			nNumBlock;		//�u���b�N��
	int			nNumIdxEven;	//�C���f�b�N�X�o�b�t�@���_�������̐�(�މ��O�p�`���_�ȊO)
	int			nNumNullTri;	//�k�ރ|���S�����_�̐�
	int			nMultiple;		//�C���f�b�N�X�o�b�t�@�p�W��
	float		fVtxAdjust;		//�e�N�X�`��Y���W�ʒu���炷�W��
	float		fTexAdjust;		//Z���W�ʒu�����炷�W��
}MESH;

//�}�g���b�N�X�\����
typedef struct
{
	D3DXMATRIX	Projection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	World;			//���[���h�}�g���b�N�X
	D3DXMATRIX	View;			//�r���[�}�g���b�N�X
	D3DXMATRIX	Scl;			//�X�P�[���}�g���b�N�X
	D3DXMATRIX	Rot;			//��]�}�g���b�N�X
	D3DXMATRIX	Trans;			//�ʒu�}�g���b�N�X
}MATRIX;

//�v���g�^�C�v�̐錾
LPDIRECT3DDEVICE9	GetDevice();
void SetMode(MODE mode);
MODE GetMode(void);
#endif