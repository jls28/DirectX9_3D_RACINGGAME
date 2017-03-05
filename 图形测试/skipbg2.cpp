#include "main.h"
#include "skipbg2.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SKIPBG2		"data\\TEXTURE\\skipbg2.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexSkipBg2(LPDIRECT3DDEVICE9 pDevice);
void SetVertexSkipBg2(int nSkipBg2ID);
void SetTextureSkipBg2(int nSkipBg2ID);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureSkipBg2 = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSkipBg2 = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

SKIPBG2				g_aSkipBg2[MAX_SKIPBG2];	// �c�[���̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkipBg2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		g_aSkipBg2[nCntSkipBg2].pos = D3DXVECTOR3(SKIPBG2_POS_X, SKIPBG2_POS_Y, 0.0f);
		g_aSkipBg2[nCntSkipBg2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		g_aSkipBg2[nCntSkipBg2].nCount = 0;
		g_aSkipBg2[nCntSkipBg2].nPattern = 0;
		g_aSkipBg2[nCntSkipBg2].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SKIPBG2,		// �t�@�C���̖��O
								&g_pTextureSkipBg2);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexSkipBg2(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSkipBg2(void)
{

		if(g_pTextureSkipBg2 != NULL)
		{// �e�N�X�`���̊J��
			g_pTextureSkipBg2->Release();
			g_pTextureSkipBg2 = NULL;
		}

		if(g_pVtxBuffSkipBg2 != NULL)
		{// ���_�o�b�t�@�̊J��
			g_pVtxBuffSkipBg2->Release();
			g_pVtxBuffSkipBg2 = NULL;
		}

}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkipBg2(void)
{
	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		if(g_aSkipBg2[nCntSkipBg2].bUse == true)
		{// �g�p���Ă���
			g_aSkipBg2[nCntSkipBg2].nCount++;
			if((g_aSkipBg2[nCntSkipBg2].nCount % INTERVAL_PATTERN_SKIPBG2) == 0)
			{// �A�j���[�V�����؂�ւ�
				g_aSkipBg2[nCntSkipBg2].nPattern++;
				if(g_aSkipBg2[nCntSkipBg2].nPattern >= NUM_PATTERN_SKIPBG2)
				{// �A�j���[�V�����p�^�[�����I��
					//g_aSkipBg2[nCntSkipBg2].bUse = false;
					g_aSkipBg2[nCntSkipBg2].nPattern = 0;
					SetFade(FADE_OUT,MODE_RULE);
				}
				SetTextureSkipBg2(nCntSkipBg2);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkipBg2(void)
{
	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		if(g_aSkipBg2[nCntSkipBg2].bUse == true)
		{// �g�p���Ă���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffSkipBg2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSkipBg2);

	// �|���S���̕`��
	for(int nCntPlace = 0; nCntPlace < NUM_PLACE_SKIPBG2; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}
		}
	}
}

//=============================================================================
// ���_���W�̍쐬
//=============================================================================
HRESULT MakeVertexSkipBg2(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE_SKIPBG2,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_2D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffSkipBg2,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffSkipBg2->Lock(0, 0, (void**)&pVtx, 0);

		for(int nCntSkipBg2 = 0; nCntSkipBg2 < NUM_PLACE_SKIPBG2; nCntSkipBg2++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x-SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y-SKIPBG2_SIZE_Y/2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x+SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y-SKIPBG2_SIZE_Y/2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x-SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y+SKIPBG2_SIZE_Y/2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aSkipBg2[nCntSkipBg2].pos.x+SKIPBG2_SIZE_X/2, g_aSkipBg2[nCntSkipBg2].pos.y+SKIPBG2_SIZE_Y/2, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG2, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_SKIPBG2);
			pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X_SKIPBG2, TEXTURE_SIZE_Y_SKIPBG2);
		}

		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffSkipBg2->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureSkipBg2(int nSkipBg2ID)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffSkipBg2->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nSkipBg2ID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aSkipBg2[nSkipBg2ID].nPattern * TEXTURE_SIZE_X_SKIPBG2, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aSkipBg2[nSkipBg2ID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG2, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aSkipBg2[nSkipBg2ID].nPattern * TEXTURE_SIZE_X_SKIPBG2, TEXTURE_SIZE_Y_SKIPBG2);
	pVtx[3].tex = D3DXVECTOR2((g_aSkipBg2[nSkipBg2ID].nPattern + 1) * TEXTURE_SIZE_X_SKIPBG2, TEXTURE_SIZE_Y_SKIPBG2);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffSkipBg2->Unlock();
}

//=============================================================================
// �c�[���̃��Z�b�g
//=============================================================================
void ResetSkipBg2(void)
{
	for(int nCntSkipBg2 = 0; nCntSkipBg2 < MAX_SKIPBG2; nCntSkipBg2++)
	{
		g_aSkipBg2[nCntSkipBg2].pos = D3DXVECTOR3(SKIPBG2_POS_X, SKIPBG2_POS_Y, 0.0f);
		g_aSkipBg2[nCntSkipBg2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkipBg2[nCntSkipBg2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSkipBg2[nCntSkipBg2].nCount = 0;
		g_aSkipBg2[nCntSkipBg2].nPattern = 0;
		g_aSkipBg2[nCntSkipBg2].bUse = false;
	}
}
SKIPBG2 *GetSkipBg2( void )
{
	return &g_aSkipBg2[ 0 ];
}
