#include "main.h"
#include "score.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "fade.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE	"data\\TEXTURE\\score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SCORE_POS_X		(10.0f)							// SCORE�̕\����ʒu�w���W
#define	SCORE_POS_Y		(0.0f)							// SCORE�̕\����ʒu�x���W
#define	SCORE_WIDTH		(20.0f)							// SCORE�̕�
#define	SCORE_HEIGHT	(40.0f)							// SCORE�̍���

#define	MAX_SCORE		(5)					// SCORE�̍ő吔

#define	NUM_PATTERN			(8)						// �A�j���[�V�����̃p�^�[����
#define	TEXTURE_SIZE_X		(1.0f / NUM_PATTERN)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

LPDIRECT3DTEXTURE9 g_pTextureScore =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore =NULL;	//���_�p�b�t�@�ւ̃|�C���^
int nScore [MAX_SCORE];
SCORE g_Score[MAX_SCORE];

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);
//=============================================================================
//  �֐����@�FInitScore
//  �@�\�T�v�F�X�R�A�̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitScore(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++)
	{
		g_Score[cntscore].pos = D3DXVECTOR3(SCORE_POS_X + cntscore * SCORE_WIDTH , SCORE_POS_Y + SCORE_HEIGHT/2, 0.0f);

		g_Score[cntscore].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);

		g_Score[cntscore].scl= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );	//�g��k��

		g_Score[cntscore].bCheck = false;

		g_Score[cntscore].g_nScore = 1000;
	}

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(
			pDevice,
			TEXTURE_SCORE,
		&g_pTextureScore);

	// ���_���̍쐬
	MakeVertexScore(pDevice);

	return S_OK;
}
//=============================================================================
//  �֐����@�FUninitScore
//  �@�\�T�v�F�X�R�A�̏I������
//  �߂�l�@�F
//=============================================================================
void UninitScore(void)
{

	if(g_pVtxBuffScore!=NULL)
	{
		g_pVtxBuffScore->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffScore=NULL;
	}
	if(g_pTextureScore!=NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawScore
//  �@�\�T�v�F�X�R�A�̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureScore);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffScore,
								0,
								sizeof(VERTEX_2D)
								);
	for(int i=0;i<MAX_SCORE;i++)
	{
	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  (0+4*i),		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);
	}
}
//=============================================================================
//  �֐����@�FUpdateScore
//  �@�\�T�v�F�X�R�A�̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateScore(void)
{
	//if(GetKeyboardTrigger(DIK_SPACE) == true)
	//{
	//	AddScore(1);
	//}
	//nScore[0] =g_nScore / 10000000 % 100;		//�疜
	//nScore[1] =g_nScore / 1000000 % 10;		//100��
	//nScore[2] =g_nScore / 100000 % 10;		//10��
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++)
	{
	nScore[0] = g_Score[cntscore].g_nScore / 10000 % 10;		//1��
	nScore[1] = g_Score[cntscore].g_nScore / 1000 % 10;		//1��
	nScore[2] = g_Score[cntscore].g_nScore / 100 % 10;		//100
	nScore[3] = g_Score[cntscore].g_nScore / 10 % 10;		//10
	nScore[4] = g_Score[cntscore].g_nScore / 1 % 10;		//1
	}
	VERTEX_2D *pVtx;
	g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾

	for(int i= 0;i<MAX_SCORE;i++)
	{

		pVtx[0+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 0.0f );
		pVtx[1+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,0.0f);
		pVtx[2+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i], 1.0f);
		pVtx[3+(4*i)].tex = D3DXVECTOR2(0.1f*nScore[i]+0.1f,1.0f);

	}
		g_pVtxBuffScore ->Unlock();	//LOCK
}
/*******************************************************************************
* �֐���:AddScore
* 
* ����  : value
* �߂�l: �i�V
*******************************************************************************/
void AddScore(int value)
{	
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++)
	{
		g_Score[cntscore].g_nScore +=value;
		if(g_Score[cntscore].g_nScore<=0)
		{
			g_Score[cntscore].g_nScore = 0;
		}
		if(g_Score[cntscore].g_nScore>=4000)
		{
			g_Score[cntscore].bCheck = true;
		}
	}
}
SCORE *GetScore(void)
{
	return &g_Score[0];
}
int *GetScoreNum(void)
{
	return &nScore[0];
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*(4*MAX_SCORE),D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffScore,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_2D *pVtx;
	g_pVtxBuffScore ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	for(int cntscore= 0; cntscore < MAX_SCORE; cntscore ++,pVtx += 4 )
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f );
		pVtx[1].tex = D3DXVECTOR2(0.1f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx[0].pos = D3DXVECTOR3( g_Score[cntscore].pos.x - SCORE_WIDTH/2,  g_Score[cntscore].pos.y - SCORE_HEIGHT/2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( g_Score[cntscore].pos.x + SCORE_WIDTH/2,  g_Score[cntscore].pos.y - SCORE_HEIGHT/2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3( g_Score[cntscore].pos.x - SCORE_WIDTH/2,  g_Score[cntscore].pos.y + SCORE_HEIGHT/2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( g_Score[cntscore].pos.x + SCORE_WIDTH/2,  g_Score[cntscore].pos.y + SCORE_HEIGHT/2, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 );	//���_���i�[���[�N
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	g_pVtxBuffScore ->Unlock();	//LOCK

	return S_OK;
}
