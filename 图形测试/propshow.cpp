#include "main.h"
#include "propshow.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PROW		"data\\TEXTURE\\propshow001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexProw(LPDIRECT3DDEVICE9 pDevice);
void SetVertexProw(int nProwID);
void SetColorProw(int nProwID, D3DXCOLOR col);
void SetTextureProw(int nProwID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureProw = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffProw = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

PROW				g_aProw[MAX_PROW];	// �c�[���̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitProw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++)
	{
		g_aProw[nCntProw].pos = D3DXVECTOR3(PROW_POS_X, PROW_POS_Y, 0.0f);
		g_aProw[nCntProw].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aProw[nCntProw].nCount = 0;
		g_aProw[nCntProw].nPattern = 0;
		g_aProw[nCntProw].bUse = false;
		g_aProw[nCntProw].bProwUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PROW,		// �t�@�C���̖��O
								&g_pTextureProw);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexProw(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitProw(void)
{

		if(g_pTextureProw != NULL)
		{// �e�N�X�`���̊J��
			g_pTextureProw->Release();
			g_pTextureProw = NULL;
		}

		if(g_pVtxBuffProw != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffProw->Release();
			g_pVtxBuffProw = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateProw(void)
{
	PROW *pProw;

	pProw = &g_aProw[0];
	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++, pProw++)
	{
		if(pProw->bUse == true)
		{// �g�p���Ă���

			SetColorProw(nCntProw, pProw->col);

			if(pProw->bProwUse == false)
			{
				pProw->nCount++;
			}

			if((pProw->nCount % INTERVAL_PATTERN_PROW) == 0)
			{// �A�j���[�V�����؂�ւ�
			if(pProw->bProwUse == false)
			{
				pProw->nPattern++;
				if(pProw->nPattern >= NUM_PATTERN_PROW)
				{// �A�j���[�V�����p�^�[�����I��
					pProw->bUse = false;
					pProw->nPattern = 0;
				}
				SetTextureProw(nCntProw);
			}
			}
			g_aProw[nCntProw].bUse = true;
		}
	}
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorProw(int nProwID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffProw->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nProwID * 4);

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffProw->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawProw(void)
{
	PROW *pProw;

	pProw = &g_aProw[0];
	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++, pProw++)
	{
		if(pProw->bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffProw, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureProw);

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
HRESULT MakeVertexProw(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_PROW,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffProw,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffProw->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntProw = 0; nCntProw < NUM_PLACE_PROW; nCntProw++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_SIZE_X + PROW_INTERVAL_X), PROW_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_INTERVAL_X + PROW_SIZE_X) + PROW_SIZE_X, PROW_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_SIZE_X + PROW_INTERVAL_X), PROW_POS_Y + PROW_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PROW_POS_X + nCntProw * (PROW_INTERVAL_X + PROW_SIZE_X) + PROW_SIZE_X, PROW_POS_Y + PROW_SIZE_Y, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROW, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_PROW);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROW, TEXTURE_SIZE_Y_PROW);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffProw->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureProw(int nProwID)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffProw->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nProwID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aProw[nProwID].nPattern * TEXTURE_SIZE_X_PROW, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aProw[nProwID].nPattern + 1) * TEXTURE_SIZE_X_PROW, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aProw[nProwID].nPattern * TEXTURE_SIZE_X_PROW, TEXTURE_SIZE_Y_PROW);
	pVtx[3].tex = D3DXVECTOR2((g_aProw[nProwID].nPattern + 1) * TEXTURE_SIZE_X_PROW, TEXTURE_SIZE_Y_PROW);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffProw->Unlock();
}

//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetProw(void)
{
	for(int nCntProw = 0; nCntProw < MAX_PROW; nCntProw++)
	{
		g_aProw[nCntProw].pos = D3DXVECTOR3(PROW_POS_X, PROW_POS_Y, 0.0f);
		g_aProw[nCntProw].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aProw[nCntProw].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aProw[nCntProw].nCount = 0;
		g_aProw[nCntProw].nPattern = 0;
		g_aProw[nCntProw].bUse = false;
		g_aProw[nCntProw].bProwUse = false;
	}
}
PROW *GetProw( void )
{
	return &g_aProw[ 0 ];
}
