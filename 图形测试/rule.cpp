#include "main.h"
#include "rule.h"
#include "fade.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
#include "sound.h"
//�O���[�o���ϐ�
VERTEX_2D g_Rule[4];
LPDIRECT3DTEXTURE9 g_pTextureRule =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitRule
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitRule(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffRule,NULL)))
	{
		return E_FAIL;
	}	
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\rule.png",
		&g_pTextureRule);
		VERTEX_2D *Rule;
		g_pVtxBuffRule ->Lock(0,0,(void **)&Rule,0);		//���_���ւ̃|�C���^���擾

		Rule[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Rule[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Rule[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Rule[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Rule[0].rhw = 1.0f;
		Rule[1].rhw = 1.0f;
		Rule[2].rhw = 1.0f;
		Rule[3].rhw = 1.0f;
		Rule[0].col=D3DCOLOR_RGBA(255,255,255,255);	//���_���i�[���[�N
		Rule[1].col=D3DCOLOR_RGBA(255,255,255,255);
		Rule[2].col=D3DCOLOR_RGBA(255,255,255,255);
		Rule[3].col=D3DCOLOR_RGBA(255,255,255,255);

		Rule[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Rule[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Rule[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Rule[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffRule ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitRule
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitRule(void)
{
	if(g_pTextureRule!=NULL)
	{
		g_pTextureRule->Release();
		g_pTextureRule=NULL;
	}
	if(g_pVtxBuffRule!=NULL)
	{
		g_pVtxBuffRule->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffRule=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawRule
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureRule);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffRule,
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
//  �֐����@�FUpdateRule
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateRule(void)
{
	if(GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT,MODE_RULE2);
	}
}
