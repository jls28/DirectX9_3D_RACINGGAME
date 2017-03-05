#include "main.h"
#include "propmpmax.h"
#include "propmp.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PROPMPMAX		"data\\TEXTURE\\propmpmax.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPropMpMax(LPDIRECT3DDEVICE9 pDevice);
void SetVertexPropMpMax(int nPropMpMaxID);
void SetColorPropMpMax(int nPropMpMaxID, D3DXCOLOR col);
void SetTexturePropMpMax(int nPropMpMaxID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePropMpMax = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPropMpMax = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

PROPMPMAX				g_aPropMpMax[MAX_PROPMPMAX];	// �c�[���̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitPropMpMax(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PROPMP *pPropMp = GetPropMp();
	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++)
	{
		g_aPropMpMax[nCntPropMpMax].pos = D3DXVECTOR3(pPropMp->pos.x, pPropMp->pos.x, 0.0f);
		g_aPropMpMax[nCntPropMpMax].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMpMax[nCntPropMpMax].nCount = 0;
		g_aPropMpMax[nCntPropMpMax].nPattern = 0;
		g_aPropMpMax[nCntPropMpMax].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PROPMPMAX,		// �t�@�C���̖��O
								&g_pTexturePropMpMax);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexPropMpMax(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPropMpMax(void)
{

		if(g_pTexturePropMpMax != NULL)
		{// �e�N�X�`���̊J��
			g_pTexturePropMpMax->Release();
			g_pTexturePropMpMax = NULL;
		}

		if(g_pVtxBuffPropMpMax != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffPropMpMax->Release();
			g_pVtxBuffPropMpMax = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdatePropMpMax(void)
{
	PROPMPMAX *pPropMpMax;

	pPropMpMax = &g_aPropMpMax[0];
	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++, pPropMpMax++)
	{
		if(pPropMpMax->bUse == true)
		{// �g�p���Ă���

			SetColorPropMpMax(nCntPropMpMax, pPropMpMax->col);

				pPropMpMax->nCount++;


			if((pPropMpMax->nCount % INTERVAL_PATTERN_PROPMPMAX) == 0)
			{// �A�j���[�V�����؂�ւ�

				pPropMpMax->nPattern++;
				if(pPropMpMax->nPattern >= NUM_PATTERN_PROPMPMAX)
				{// �A�j���[�V�����p�^�[�����I��
					pPropMpMax->bUse = false;
					pPropMpMax->nPattern = 0;
				}
				SetTexturePropMpMax(nCntPropMpMax);
			}
			g_aPropMpMax[nCntPropMpMax].bUse = true;
		}
	}
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorPropMpMax(int nPropMpMaxID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPropMpMax->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpMaxID * 4);

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPropMpMax->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawPropMpMax(void)
{
	PROPMPMAX *pPropMpMax;

	pPropMpMax = &g_aPropMpMax[0];

	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++, pPropMpMax++)
	{
		if(pPropMpMax->bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffPropMpMax, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePropMpMax);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_PROPMPMAX; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexPropMpMax(LPDIRECT3DDEVICE9 pDevice)
{
	PROPMP *pPropMp = GetPropMp();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_PROPMPMAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffPropMpMax,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffPropMpMax->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntPropMpMax = 0; nCntPropMpMax < NUM_PLACE_PROPMPMAX; nCntPropMpMax++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_WIDTH + PROPMPMAX_INTERVAL_X), pPropMp->pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_INTERVAL_X + PROPMPMAX_WIDTH) + PROPMPMAX_WIDTH, pPropMp->pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_WIDTH + PROPMPMAX_INTERVAL_X), pPropMp->pos.y + PROPMPMAX_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPropMp->pos.x + nCntPropMpMax * (PROPMPMAX_INTERVAL_X + PROPMPMAX_WIDTH) + PROPMPMAX_WIDTH,pPropMp->pos.y + PROPMPMAX_HEIGHT, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROPMPMAX, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_PROPMPMAX);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_PROPMPMAX, TEXTURE_SIZE_Y_PROPMPMAX);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffPropMpMax->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePropMpMax(int nPropMpMaxID)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPropMpMax->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nPropMpMaxID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aPropMpMax[nPropMpMaxID].nPattern * TEXTURE_SIZE_X_PROPMPMAX, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aPropMpMax[nPropMpMaxID].nPattern + 1) * TEXTURE_SIZE_X_PROPMPMAX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPropMpMax[nPropMpMaxID].nPattern * TEXTURE_SIZE_X_PROPMPMAX, TEXTURE_SIZE_Y_PROPMPMAX);
	pVtx[3].tex = D3DXVECTOR2((g_aPropMpMax[nPropMpMaxID].nPattern + 1) * TEXTURE_SIZE_X_PROPMPMAX, TEXTURE_SIZE_Y_PROPMPMAX);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffPropMpMax->Unlock();
}

//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetPropMpMax(void)
{
	PROPMP *pPropMp = GetPropMp();
	for(int nCntPropMpMax = 0; nCntPropMpMax < MAX_PROPMPMAX; nCntPropMpMax++)
	{
		g_aPropMpMax[nCntPropMpMax].pos = D3DXVECTOR3(pPropMp->pos.x, pPropMp->pos.x, 0.0f);
		g_aPropMpMax[nCntPropMpMax].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aPropMpMax[nCntPropMpMax].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aPropMpMax[nCntPropMpMax].nCount = 0;
		g_aPropMpMax[nCntPropMpMax].nPattern = 0;
		g_aPropMpMax[nCntPropMpMax].bUse = false;
	}
}
PROPMPMAX *GetPropMpMax( void )
{
	return &g_aPropMpMax[ 0 ];
}
