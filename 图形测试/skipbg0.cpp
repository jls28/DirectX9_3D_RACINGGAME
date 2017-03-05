#include "main.h"
#include "skipbg0.h"
//�O���[�o���ϐ�
VERTEX_2D g_SkipBg0[4];
LPDIRECT3DTEXTURE9 g_pTextureSkipBg0 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkipBg0 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitSkipBg0
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitSkipBg0(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffSkipBg0,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *SkipBg0;
		g_pVtxBuffSkipBg0 ->Lock(0,0,(void **)&SkipBg0,0);		//���_���ւ̃|�C���^���擾

		SkipBg0[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		SkipBg0[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		SkipBg0[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		SkipBg0[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		SkipBg0[0].rhw = 1.0f;
		SkipBg0[1].rhw = 1.0f;
		SkipBg0[2].rhw = 1.0f;
		SkipBg0[3].rhw = 1.0f;
		SkipBg0[0].col=D3DCOLOR_RGBA(255,255,255,255);	//���_���i�[���[�N
		SkipBg0[1].col=D3DCOLOR_RGBA(255,255,255,255);
		SkipBg0[2].col=D3DCOLOR_RGBA(255,255,255,255);
		SkipBg0[3].col=D3DCOLOR_RGBA(255,255,255,255);

		SkipBg0[0].tex = D3DXVECTOR2(0.0f,0.0f);
		SkipBg0[1].tex = D3DXVECTOR2(1.0f,0.0f);
		SkipBg0[2].tex = D3DXVECTOR2(0.0f,1.0f);
		SkipBg0[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffSkipBg0 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitSkipBg0
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitSkipBg0(void)
{
	if(g_pTextureSkipBg0!=NULL)
	{
		g_pTextureSkipBg0->Release();
		g_pTextureSkipBg0=NULL;
	}
	if(g_pVtxBuffSkipBg0!=NULL)
	{
		g_pVtxBuffSkipBg0->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffSkipBg0=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawSkipBg0
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawSkipBg0(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureSkipBg0);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffSkipBg0,
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
//  �֐����@�FUpdateSkipBg0
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateSkipBg0(void)
{

}
