#include "main.h"
#include "result2.h"
#include "input.h"
#include "fade.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
#include "sound.h"
//�O���[�o���ϐ�
VERTEX_2D g_Result2[4];
LPDIRECT3DTEXTURE9 g_pTextureResult2 =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult2 =NULL;	//���_�p�b�t�@�ւ̃|�C���^
//=============================================================================
//  �֐����@�FInitResult2
//  �@�\�T�v�F�v���S���̏�����
//  �߂�l�@�FHResult2
//=============================================================================
HRESULT InitResult2(void)
{
	PlaySound(SOUND_LABEL_BGM002);
	StopSound(SOUND_LABEL_BGM001);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBuffResult2,NULL)))
	{
		return E_FAIL;
	}	
		VERTEX_2D *Result2;
		g_pVtxBuffResult2 ->Lock(0,0,(void **)&Result2,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\result2.png",
		&g_pTextureResult2);
		Result2[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		Result2[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
		Result2[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
		Result2[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		Result2[0].rhw = 1.0f;
		Result2[1].rhw = 1.0f;
		Result2[2].rhw = 1.0f;
		Result2[3].rhw = 1.0f;
		Result2[0].col=D3DCOLOR_RGBA(255,255,255,255);	//���_���i�[���[�N
		Result2[1].col=D3DCOLOR_RGBA(255,255,255,255);
		Result2[2].col=D3DCOLOR_RGBA(255,255,255,255);
		Result2[3].col=D3DCOLOR_RGBA(255,255,255,255);

		Result2[0].tex = D3DXVECTOR2(0.0f,0.0f);
		Result2[1].tex = D3DXVECTOR2(1.0f,0.0f);
		Result2[2].tex = D3DXVECTOR2(0.0f,1.0f);
		Result2[3].tex = D3DXVECTOR2(1.0f,1.0f);
		g_pVtxBuffResult2 ->Unlock();	//LOCK

		return S_OK;

}
//=============================================================================
//  �֐����@�FUninitResult2
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitResult2(void)
{
	if(g_pTextureResult2!=NULL)
	{
		g_pTextureResult2->Release();
		g_pTextureResult2=NULL;
	}
	if(g_pVtxBuffResult2!=NULL)
	{
		g_pVtxBuffResult2->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffResult2=NULL;
	}
}
//=============================================================================
//  �֐����@�FDrawResult2
//  �@�\�T�v�F�v���S���̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawResult2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_2D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureResult2);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffResult2,
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
//  �֐����@�FUpdateResult2
//  �@�\�T�v�F�v���S���̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateResult2(void)
{

}
