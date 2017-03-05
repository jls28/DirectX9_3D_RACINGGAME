#include "main.h"
#include "propmp.h"
#include "propshow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PROPMP		"data\\TEXTURE\\propmp000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	PROPMP_SIZE_X		(10.0f)							// �c�[���̐����̕�
#define	PROPMP_SIZE_Y		(100.0f)							// �c�[���̐����̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPropMp(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPropMp(int nPropMpID);
void SetColorPropMp(int nPropMpID, D3DXCOLOR col);
void SetTexturePropMp(int nPropMpID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePropMp = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPropMp = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

PROPMP				g_aPropMp[MAX_PROP_MP];	// �c�[���̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPropMp(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	PROW *pProw = GetProw();

	for(int nCntPropMp = 0; nCntPropMp < MAX_PROP_MP; nCntPropMp++)
	{
		g_aPropMp[nCntPropMp].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT), PROW_POS_Y, 0.0f);
		g_aPropMp[nCntPropMp].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMp[nCntPropMp].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PROPMP,		// �t�@�C���̖��O
								&g_pTexturePropMp);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexPropMp(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPropMp(void)
{

		if(g_pTexturePropMp != NULL)
		{// �e�N�X�`���̊J��
			g_pTexturePropMp->Release();
			g_pTexturePropMp = NULL;
		}

		if(g_pVtxBuffPropMp != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffPropMp->Release();
			g_pVtxBuffPropMp = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePropMp(void)
{

}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorPropMp(int nPropMpID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPropMp->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpID * 4);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = col;

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPropMp->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPropMp(void)
{
	PROPMP *pPropMp;

	pPropMp = &g_aPropMp[0];
	for(int nCntPropMp = 0; nCntPropMp < MAX_PROP_MP; nCntPropMp++, pPropMp++)
	{
		if(pPropMp->bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffPropMp, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePropMp);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_PROW; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexPropMp(LPDIRECT3DDEVICE9 pDevice)
{
	PROW *pProw = GetProw();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PROP_MP	,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffPropMp,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffPropMp->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPropMp = 0; nCntPropMp < NUM_PLACE_PROW; nCntPropMp++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH), PROW_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH) + PROP_WIDTH, PROW_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH), PROW_POS_Y + PROW_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((pProw->pos.x-PROP_LEFT) + nCntPropMp * (PROP_WIDTH) + PROP_WIDTH, PROW_POS_Y + PROW_SIZE_Y, 0.0f);

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
		g_pVtxBuffPropMp->Unlock();
	}

	return S_OK;
}


//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetPropMp(void)
{
	for(int nCntPropMp = 0; nCntPropMp < MAX_PROP_MP; nCntPropMp++)
	{
		g_aPropMp[nCntPropMp].pos = D3DXVECTOR3((PROW_POS_X-PROP_LEFT), PROW_POS_Y, 0.0f);
		g_aPropMp[nCntPropMp].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMp[nCntPropMp].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aPropMp[nCntPropMp].bUse = false;
	}
}
PROPMP *GetPropMp( void )
{
	return &g_aPropMp[ 0 ];
}
