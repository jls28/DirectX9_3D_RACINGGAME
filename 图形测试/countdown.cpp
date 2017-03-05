//=============================================================================
//
// �|���v���� [countdown.cpp]
// 2016/02/24 LIHAOSHENG
//
//=============================================================================
#include "countdown.h"
#include "modelbody.h"
#include "timebg.h"
//*****************************************************************************


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_COUNTDOWN		"data\\TEXTURE\\countdown.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCountdown(LPDIRECT3DDEVICE9 pDevice);
void SetVertexCountdown(int nCountdownID);
void SetColorCountdown(int nCountdownID, D3DXCOLOR col);
void SetTextureCountdown(int nCountdownID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureCountdown = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCountdown = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

COUNTDOWN				g_aCountdown[MAX_COUNTDOWN];	// �c�[���̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitCountdown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++)
	{
		g_aCountdown[nCntCountdown].pos = D3DXVECTOR3(COUNTDOWN_POS_X, COUNTDOWN_POS_Y, 0.0f);
		g_aCountdown[nCntCountdown].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aCountdown[nCntCountdown].nCount = 0;
		g_aCountdown[nCntCountdown].nPattern = 0;
		g_aCountdown[nCntCountdown].bUse = true;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_COUNTDOWN,		// �t�@�C���̖��O
								&g_pTextureCountdown);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexCountdown(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCountdown(void)
{

		if(g_pTextureCountdown != NULL)
		{// �e�N�X�`���̊J��
			g_pTextureCountdown->Release();
			g_pTextureCountdown = NULL;
		}

		if(g_pVtxBuffCountdown != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffCountdown->Release();
			g_pVtxBuffCountdown = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateCountdown(void)
{


	COUNTDOWN *pCountdown;
	pCountdown = &g_aCountdown[0];
	TIMEBG *pTimeBg = GetTimeBg();
	MODELBODY *pModelBody = GetModelBody();
	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++, pCountdown++)
	{
		if(pCountdown->bUse == true)
		{// �g�p���Ă���
			pTimeBg->bUse = false;
			pModelBody->bUse = false;
			SetColorCountdown(nCntCountdown, pCountdown->col);

				pCountdown->nCount++;

			if((pCountdown->nCount % INTERVAL_PATTERN_COUNTDOWN) == 0)
			{// �A�j���[�V�����؂�ւ�

				pCountdown->nPattern++;
				if(pCountdown->nPattern >= NUM_PATTERN_COUNTDOWN)
				{// �A�j���[�V�����p�^�[�����I��
					pCountdown->bUse = false;
					pTimeBg->bUse = true;
					pModelBody->bUse = true;
					//pCountdown->nPattern = 0;
				}
				SetTextureCountdown(nCntCountdown);
			}
			}
		}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorCountdown(int nCountdownID, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffCountdown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nCountdownID * 4);

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = col;

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffCountdown->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawCountdown(void)
{
	COUNTDOWN *pCountdown;

	pCountdown = &g_aCountdown[0];
	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++, pCountdown++)
	{
		if(pCountdown->bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffCountdown, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureCountdown);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_COUNTDOWN; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexCountdown(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_COUNTDOWN,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffCountdown,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffCountdown->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntCountdown = 0; nCntCountdown < NUM_PLACE_COUNTDOWN; nCntCountdown++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_SIZE_X + COUNTDOWN_INTERVAL_X), COUNTDOWN_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_INTERVAL_X + COUNTDOWN_SIZE_X) + COUNTDOWN_SIZE_X, COUNTDOWN_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_SIZE_X + COUNTDOWN_INTERVAL_X), COUNTDOWN_POS_Y + COUNTDOWN_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(COUNTDOWN_POS_X + nCntCountdown * (COUNTDOWN_INTERVAL_X + COUNTDOWN_SIZE_X) + COUNTDOWN_SIZE_X, COUNTDOWN_POS_Y + COUNTDOWN_SIZE_Y, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_COUNTDOWN, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_COUNTDOWN);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_COUNTDOWN, TEXTURE_SIZE_Y_COUNTDOWN);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffCountdown->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureCountdown(int nCountdownID)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffCountdown->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nCountdownID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aCountdown[nCountdownID].nPattern * TEXTURE_SIZE_X_COUNTDOWN, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aCountdown[nCountdownID].nPattern + 1) * TEXTURE_SIZE_X_COUNTDOWN, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aCountdown[nCountdownID].nPattern * TEXTURE_SIZE_X_COUNTDOWN, TEXTURE_SIZE_Y_COUNTDOWN);
	pVtx[3].tex = D3DXVECTOR2((g_aCountdown[nCountdownID].nPattern + 1) * TEXTURE_SIZE_X_COUNTDOWN, TEXTURE_SIZE_Y_COUNTDOWN);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffCountdown->Unlock();
}

//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetCountdown(void)
{
	for(int nCntCountdown = 0; nCntCountdown < MAX_COUNTDOWN; nCntCountdown++)
	{
		g_aCountdown[nCntCountdown].pos = D3DXVECTOR3(COUNTDOWN_POS_X, COUNTDOWN_POS_Y, 0.0f);
		g_aCountdown[nCntCountdown].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aCountdown[nCntCountdown].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCountdown[nCntCountdown].nCount = 0;
		g_aCountdown[nCntCountdown].nPattern = 0;
		g_aCountdown[nCntCountdown].bUse = false;
	}
}
COUNTDOWN *GetCountdown( void )
{
	return &g_aCountdown[ 0 ];
}
