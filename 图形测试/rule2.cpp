#include "main.h"
#include "rule2.h"
#include "fade.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
//�O���[�o���ϐ�
VERTEX_2D g_Rule2[4];
LPDIRECT3DTEXTURE9 g_pTextureRule2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule2 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitRule2
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffRule2,NULL)))
	{
		return E_FAIL;
	}	
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\rule2.png",
		&g_pTextureRule2);
		VERTEX_2D *Rule2;
		g_pVtxBuffRule2 ->Lock(0,0,(void **)&Rule2,0);		//���_���ւ̃|�C���^���擾

		Rule2[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Rule2[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Rule2[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Rule2[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Rule2[0].rhw = 1.0f;
		Rule2[1].rhw = 1.0f;
		Rule2[2].rhw = 1.0f;
		Rule2[3].rhw = 1.0f;
		Rule2[0].col=D3DCOLOR_RGBA(255,255,255,255);	//���_���i�[���[�N
		Rule2[1].col=D3DCOLOR_RGBA(255,255,255,255);
		Rule2[2].col=D3DCOLOR_RGBA(255,255,255,255);
		Rule2[3].col=D3DCOLOR_RGBA(255,255,255,255);

		Rule2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Rule2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Rule2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Rule2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffRule2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitRule2
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitRule2(void)
{
	if(g_pTextureRule2!=NULL)
	{
		g_pTextureRule2->Release();
		g_pTextureRule2=NULL;
	}
	if(g_pVtxBuffRule2!=NULL)
	{
		g_pVtxBuffRule2->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffRule2=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawRule2
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawRule2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureRule2);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffRule2,
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
//  �֐����@�FUpdateRule2
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateRule2(void)
{
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_GAME);
	}
}
