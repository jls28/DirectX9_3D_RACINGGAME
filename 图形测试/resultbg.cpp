#include "main.h"
#include "resultbg.h"
#include "input.h"
#include "fade.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
//�O���[�o���ϐ�
VERTEX_2D g_ResultBg[4];
LPDIRECT3DTEXTURE9 g_pTextureResultBg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBg =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitResultBg
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHResultBg
//=============================================================================
HRESULT InitResultBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffResultBg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *ResultBg;
		g_pVtxBuffResultBg ->Lock(0,0,(void **)&ResultBg,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result.png",
		&g_pTextureResultBg);
		ResultBg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		ResultBg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		ResultBg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		ResultBg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		ResultBg[0].rhw = 1.0f;
		ResultBg[1].rhw = 1.0f;
		ResultBg[2].rhw = 1.0f;
		ResultBg[3].rhw = 1.0f;
		ResultBg[0].col=D3DCOLOR_RGBA(255,255,255,255);	//���_���i�[���[�N
		ResultBg[1].col=D3DCOLOR_RGBA(255,255,255,255);
		ResultBg[2].col=D3DCOLOR_RGBA(255,255,255,255);
		ResultBg[3].col=D3DCOLOR_RGBA(255,255,255,255);

		ResultBg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		ResultBg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		ResultBg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		ResultBg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffResultBg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitResultBg
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitResultBg(void)
{
	if(g_pTextureResultBg!=NULL)
	{
		g_pTextureResultBg->Release();
		g_pTextureResultBg=NULL;
	}
	if(g_pVtxBuffResultBg!=NULL)
	{
		g_pVtxBuffResultBg->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffResultBg=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawResultBg
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawResultBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureResultBg);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffResultBg,
								0,
								sizeof(VERTEX_2D)
								);
	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  0,		// �ŏ��̒��_�̃C���f�b�N�X
							  2			// �`�悷��v���~�e�B�u��
							);

}
//=============================================================================
//  �֐����@�FUpdateResultBg
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateResultBg(void)
{
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_TITLE);
	}
}
