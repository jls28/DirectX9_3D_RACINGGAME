#include "main.h"
#include "skipbg.h"
#include "skipbg2.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SKIPBG		"data\\TEXTURE\\skipbg.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSkipBg(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSkipBg(int nSkipBgID);
void SetTextureSkipBg(int nSkipBgID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSkipBg = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkipBg = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

SKIPBG				g_aSkipBg[MAX_SKIPBG];	// �c�[���̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkipBg(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++)
	{
		g_aSkipBg[nCntSkipBg].pos = D3DXVECTOR3(SKIPBG_POS_X, SKIPBG_POS_Y, 0.0f);
		g_aSkipBg[nCntSkipBg].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aSkipBg[nCntSkipBg].nCount = 0;
		g_aSkipBg[nCntSkipBg].nPattern = 0;
		g_aSkipBg[nCntSkipBg].bUse = true;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SKIPBG,		// �t�@�C���̖��O
								&g_pTextureSkipBg);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexSkipBg(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSkipBg(void)
{

		if(g_pTextureSkipBg != NULL)
		{// �e�N�X�`���̊J��
			g_pTextureSkipBg->Release();
			g_pTextureSkipBg = NULL;
		}

		if(g_pVtxBuffSkipBg != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffSkipBg->Release();
			g_pVtxBuffSkipBg = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkipBg(void)
{
	SKIPBG2 *pSkipBg2 = GetSkipBg2();
	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++)
	{
		if(g_aSkipBg[nCntSkipBg].bUse == true)
		{// �g�p���Ă���
			g_aSkipBg[nCntSkipBg].nCount++;
			if((g_aSkipBg[nCntSkipBg].nCount % INTERVAL_PATTERN_SKIPBG) == 0)
			{// �A�j���[�V�����؂�ւ�
				g_aSkipBg[nCntSkipBg].nPattern++;
				if(g_aSkipBg[nCntSkipBg].nPattern >= NUM_PATTERN_SKIPBG)
				{// �A�j���[�V�����p�^�[�����I��
					g_aSkipBg[nCntSkipBg].bUse = false;
					g_aSkipBg[nCntSkipBg].nPattern = 0;
					pSkipBg2->bUse = true;
				}
				SetTextureSkipBg(nCntSkipBg);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkipBg(void)
{
	SKIPBG *pSkipBg;

	pSkipBg = &g_aSkipBg[0];
	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++, pSkipBg++)
	{
		if(pSkipBg->bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffSkipBg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSkipBg);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_SKIPBG; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexSkipBg(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_SKIPBG,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffSkipBg,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffSkipBg->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntSkipBg = 0; nCntSkipBg < NUM_PLACE_SKIPBG; nCntSkipBg++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_SIZE_X + SKIPBG_INTERVAL_X), SKIPBG_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_INTERVAL_X + SKIPBG_SIZE_X) + SKIPBG_SIZE_X, SKIPBG_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_SIZE_X + SKIPBG_INTERVAL_X), SKIPBG_POS_Y + SKIPBG_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SKIPBG_POS_X + nCntSkipBg * (SKIPBG_INTERVAL_X + SKIPBG_SIZE_X) + SKIPBG_SIZE_X, SKIPBG_POS_Y + SKIPBG_SIZE_Y, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_SKIPBG);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG, TEXTURE_SIZE_Y_SKIPBG);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffSkipBg->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSkipBg(int nSkipBgID)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffSkipBg->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nSkipBgID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aSkipBg[nSkipBgID].nPattern * TEXTURE_SIZE_X_SKIPBG, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aSkipBg[nSkipBgID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aSkipBg[nSkipBgID].nPattern * TEXTURE_SIZE_X_SKIPBG, TEXTURE_SIZE_Y_SKIPBG);
	pVtx[3].tex = D3DXVECTOR2((g_aSkipBg[nSkipBgID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG, TEXTURE_SIZE_Y_SKIPBG);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffSkipBg->Unlock();
}

//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetSkipBg(void)
{
	for(int nCntSkipBg = 0; nCntSkipBg < MAX_SKIPBG; nCntSkipBg++)
	{
		g_aSkipBg[nCntSkipBg].pos = D3DXVECTOR3(SKIPBG_POS_X, SKIPBG_POS_Y, 0.0f);
		g_aSkipBg[nCntSkipBg].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg[nCntSkipBg].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSkipBg[nCntSkipBg].nCount = 0;
		g_aSkipBg[nCntSkipBg].nPattern = 0;
		g_aSkipBg[nCntSkipBg].bUse = false;
	}
}
SKIPBG *GetSkipBg( void )
{
	return &g_aSkipBg[ 0 ];
}
