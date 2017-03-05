#include "main.h"
#include "titlebg.h"
//�O���[�o���ϐ�
VERTEX_2D g_TitleBg[4];
LPDIRECT3DTEXTURE9 g_pTextureTitleBg =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBg =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitTitleBg
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitTitleBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffTitleBg,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *TitleBg;
		g_pVtxBuffTitleBg ->Lock(0,0,(void **)&TitleBg,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\title.png",
		&g_pTextureTitleBg);
		TitleBg[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		TitleBg[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		TitleBg[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		TitleBg[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		TitleBg[0].rhw = 1.0f;
		TitleBg[1].rhw = 1.0f;
		TitleBg[2].rhw = 1.0f;
		TitleBg[3].rhw = 1.0f;
		TitleBg[0].col=D3DCOLOR_RGBA(255,255,255,255);	//���_���i�[���[�N
		TitleBg[1].col=D3DCOLOR_RGBA(255,255,255,255);
		TitleBg[2].col=D3DCOLOR_RGBA(255,255,255,255);
		TitleBg[3].col=D3DCOLOR_RGBA(255,255,255,255);

		TitleBg[0].tex = D3DXVECTOR2(0.0f,0.0f);
		TitleBg[1].tex = D3DXVECTOR2(1.0f,0.0f);
		TitleBg[2].tex = D3DXVECTOR2(0.0f,1.0f);
		TitleBg[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffTitleBg ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitTitleBg
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitTitleBg(void)
{
	if(g_pTextureTitleBg!=NULL)
	{
		g_pTextureTitleBg->Release();
		g_pTextureTitleBg=NULL;
	}
	if(g_pVtxBuffTitleBg!=NULL)
	{
		g_pVtxBuffTitleBg->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffTitleBg=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawTitleBg
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawTitleBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureTitleBg);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffTitleBg,
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
//  �֐����@�FUpdateTitleBg
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateTitleBg(void)
{

}
