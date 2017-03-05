#include "main.h"
#include "propmp.h"
#include "propshow.h"
#include "propmplife.h"
#include "propmpmax.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PROPMPLIFE		"data\\TEXTURE\\propmplife000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PROPMP_SIZE_X		(10.0f)							// �c�[���̐����̕�
#define	PROPMP_SIZE_Y		(100.0f)							// �c�[���̐����̍���
#define	PROPMPLIFE_SPEED		(1)		//max�̑���
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPropMpLife(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPropMpLife(int nPropMpLifeID);
void SetColorPropMpLife(int nPropMpLifeID, D3DXCOLOR col);
void SetTexturePropMpLife(int nPropMpLifeID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePropMpLife = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPropMpLife = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

PROPMPLIFE				g_aPropMpLife[MAX_PROPMPLIFE];	// �c�[���̃��[�N
int time;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPropMpLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PROW *pProw = GetProw();

	for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++)
	{
		g_aPropMpLife[nCntPropMpLife].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT), (PROW_POS_Y+PROP_HEIGHT)  , 0.0f);
		g_aPropMpLife[nCntPropMpLife].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMpLife[nCntPropMpLife].time = 0;
		g_aPropMpLife[nCntPropMpLife].frame = 0;
		g_aPropMpLife[nCntPropMpLife].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PROPMPLIFE,		// �t�@�C���̖��O
								&g_pTexturePropMpLife);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexPropMpLife(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPropMpLife(void)
{

		if(g_pTexturePropMpLife != NULL)
		{// �e�N�X�`���̊J��
			g_pTexturePropMpLife->Release();
			g_pTexturePropMpLife = NULL;
		}

		if(g_pVtxBuffPropMpLife != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffPropMpLife->Release();
			g_pVtxBuffPropMpLife = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePropMpLife(void)
{
	
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorPropMpLife(int nPropMpLifeID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPropMpLife->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpLifeID * 4);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = col;

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPropMpLife->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPropMpLife(void)
{
	PROPMPLIFE *pPropMpLife;

	pPropMpLife = &g_aPropMpLife[0];
	PROPMPMAX *pPropMpMax = GetPropMpMax();
	for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++, pPropMpLife++)
	{
		if(pPropMpLife->bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffPropMpLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePropMpLife);

	if( pPropMpLife->frame >= PROPMPLIFE_SPEED)
	{
		pPropMpLife->time ++;
		pPropMpLife->frame = 0;
	}
	else
	{
		if(pPropMpMax->bUse == false)
		{
		pPropMpLife->frame++;
		}
	}

	if(pPropMpLife->time >= 100)
	{
		pPropMpMax->bUse = true;
		pPropMpLife->time =0;
	}
	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < pPropMpLife->time; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}

}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexPropMpLife(LPDIRECT3DDEVICE9 pDevice)
{
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PROPMPLIFE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffPropMpLife,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffPropMpLife->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT),(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife+1) * PROPMPLIFE_HEIGHT,0.0f);
			pVtx[1].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + PROPMPLIFE_WIDTH ,(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife+1) * PROPMPLIFE_HEIGHT,0.0f);
			pVtx[2].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT),(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife-1) * PROPMPLIFE_HEIGHT,0.0f);
			pVtx[3].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + PROPMPLIFE_WIDTH ,(PROW_POS_Y + PROW_SIZE_Y ) - (nCntPropMpLife-1) * PROPMPLIFE_HEIGHT,0.0f);
			// rhw�̐ݒ�
			pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffPropMpLife->Unlock();
	}

	return S_OK;
}


//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetPropMpLife(void)
{
	for(int nCntPropMpLife = 0; nCntPropMpLife < MAX_PROPMPLIFE; nCntPropMpLife++)
	{
		g_aPropMpLife[nCntPropMpLife].pos = D3DXVECTOR3((PROW_POS_X-PROP_LEFT), PROW_POS_Y, 0.0f);
		g_aPropMpLife[nCntPropMpLife].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpLife[nCntPropMpLife].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPropMpLife[nCntPropMpLife].bUse = false;
	}
}
PROPMPLIFE *GetPropMpLife( void )
{
	return &g_aPropMpLife[ 0 ];
}
