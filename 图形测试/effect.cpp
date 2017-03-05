//=============================================================================

// �G�t�F�N�g�̏��� [effect.cpp]
// 

//=============================================================================//
#include <time.h>
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT		"data\\TEXTURE\\effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define	NUM_VERTEX_CIRCLE	(4)			// ���_��
#define	NUM_POLYGON_CIRCLE	(2)			// �|���S����


#define	MAX_EFFECT			(7000)		// �G�t�F�N�g�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 posBase;	// ��ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	D3DXVECTOR3 scl;		//�g��k��
	float fColAlphaValue;	// �F�ω���
	float fAngle;			// �p�x
	float fRadius;			// ���a
	float fRadiusValue;		// ���a�ω���
	D3DXVECTOR3 swingRate;	// �h��W��
	D3DXVECTOR3 swingWidth;	// �h�ꕝ
	D3DXVECTOR3 swingValue;	// �h�ꕝ�ω���
	int nLife;				// ���C�t
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
	D3DXMATRIX				mtxWorld;					//���[���h�}�g���b�N�X
	D3DXMATRIX				mtxScl, mtxRot, mtxTrans;	//�g��k���A�����A�ʒu�}�g���b�N�X
} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade);
void SetRadiusEffect(int nEffectID, float fRadius);
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
EFFECT					g_aEffect[MAX_EFFECT];		// �G�t�F�N�g�̃��[�N
//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect(void)
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice	= GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fColAlphaValue = 0.0f;
		g_aEffect[nCntEffect].fAngle = 0.0f;
		g_aEffect[nCntEffect].fRadius = 30.0f;
		g_aEffect[nCntEffect].fRadiusValue = 0.0f;
		g_aEffect[nCntEffect].nType = EFFECTTYPE_RANDOMCOLOR;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_EFFECT,			// �t�@�C���̖��O
								&g_pTextureEffect);		// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexEffect(pDevice);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void UninitEffect(void)
{
	if(g_pTextureEffect != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	if(g_pVtxBuffEffect != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect(void)
{
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == true)
		{// �G�t�F�N�g���g�p���Ȃ�`��
			pEffect->nLife--;
			if(pEffect->nLife <= 0)
			{// �G�t�F�N�g�����ł�����
				pEffect->bUse = false;
			}
			else
			{// �G�t�F�N�g�𒲐�
				// �F�̐ݒ�
				pEffect->col.a -= pEffect->fColAlphaValue;
				if(pEffect->col.a <= 0.0f)
				{
					pEffect->col.a = 0.0f;
				}
				SetColorEffect(nCntEffect, pEffect->col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

				// ���a�̐ݒ�
				//pEffect->fRadius -= pEffect->fRadiusValue;
				//if(pEffect->fRadius <= 0.0f)
				//{
				//	pEffect->fRadius = 0.0f;
				//}
				//SetRadiusEffect(nCntEffect, pEffect->fRadius);

				// �h��(X����)�̐ݒ�
				//pEffect->swingRate.x += D3DX_PI * pEffect->swingValue.x;
				//if(pEffect->swingRate.x > D3DX_PI)
				//{
				//	pEffect->swingRate.x -= D3DX_PI * 2.0f;
				//}
				//pEffect->pos.x = pEffect->pos.x + sinf(pEffect->swingRate.x) * pEffect->swingWidth.x;

				//// �h��(Y����)�̐ݒ�
				//pEffect->swingRate.z += D3DX_PI * pEffect->swingValue.z;
				//if(pEffect->swingRate.z > D3DX_PI)
				//{
				//	pEffect->swingRate.z -= D3DX_PI * 2.0f;
				//}
				//pEffect->pos.z = pEffect->pos.z + sinf(pEffect->swingRate.z) * pEffect->swingWidth.z;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect(void)
{

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// �J�����Őݒ肵���r���[�}�g���b�N�X���󂯎�邽�߂̕ϐ�

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	//// ���C�g�����B�ǂ̊p�x���猩�Ă������悤�ɂ��邽�߁A�r���{�[�h�̉A�e�𖳂����B
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �u�����h���Z����
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);				// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �|���S���̕`��
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p���Ȃ�`��

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_aEffect[nCntEffect].mtxWorld );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &g_aEffect[nCntEffect].mtxWorld, NULL, &mtxView );

			g_aEffect[nCntEffect].mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aEffect[nCntEffect].mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aEffect[nCntEffect].mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, g_aEffect[nCntEffect].scl.x, g_aEffect[nCntEffect].scl.y, g_aEffect[nCntEffect].scl.z );
			D3DXMatrixMultiply( &g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
			D3DXMatrixMultiply( &g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z );
			D3DXMatrixMultiply( &g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld );

			// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));		//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntEffect * NUM_VERTEX_CIRCLE), NUM_POLYGON_CIRCLE);
		}
	}
	// �����_�[�X�e�[�g�̐ݒ���f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// �f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// �f�t�H���g�ɖ߂��B
	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��

	// ���C�g�_��
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX_CIRCLE * MAX_EFFECT,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@
												FVF_VERTEX_3D,									// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&g_pVtxBuffEffect,								// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_3D *pVtx;
	//const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffEffect -> Lock( 0, 0, ( void** ) &pVtx, 0 );


		for(int cntTarget = 0; cntTarget < MAX_EFFECT; cntTarget++, pVtx += 4)
		{
			//�@��
			pVtx[0].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[1].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[2].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[3].nor =  D3DXVECTOR3(0.0f,1.0f,0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}

	return S_OK;
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEffect(int nEffectID, D3DXCOLOR col, D3DXCOLOR colFade)
{
	g_aEffect[nEffectID].col = col;
	
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nEffectID * NUM_VERTEX_CIRCLE);


		pVtx->col = col;
		pVtx++;

		// ���_�J���[�̐ݒ�
		for(int nCntVtx = 0; nCntVtx <= NUM_POLYGON_CIRCLE; nCntVtx++, pVtx++)
		{
			pVtx->col = D3DXCOLOR(col.r * colFade.r, col.g * colFade.g, col.b * colFade.b, col.a * colFade.a);
		}


		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// �T�C�Y�ݒ�
//=============================================================================
void SetRadiusEffect(int nEffectID, float fRadius)
{
	g_aEffect[nEffectID].fRadius = fRadius;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;
		const float ANGLE = (D3DX_PI * 2.0f) / NUM_POLYGON_CIRCLE;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nEffectID * NUM_VERTEX_CIRCLE;


		pVtx[0].pos.x =-fRadius * 0.5f;
		pVtx[0].pos.y = fRadius * 0.5f;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = fRadius * 0.5f;
		pVtx[1].pos.y = fRadius * 0.5f;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = -fRadius * 0.5f;
		pVtx[2].pos.y = -fRadius * 0.5f;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = fRadius * 0.5f;
		pVtx[3].pos.y = -fRadius * 0.5f;
		pVtx[3].pos.z = 0.0f;


		// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
	}
}

//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nType)
{
	EFFECT *pEffect;
	pEffect = &g_aEffect[0];
	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if(pEffect->bUse == false)
		{
			// ���_���W�̐ݒ�
			pEffect->pos = pos;
			// ���C�t�̐ݒ�
			pEffect->nLife = nLife;

			// �^�C�v�̐ݒ�
			pEffect->nType = nType;

			// �ړ��ʂ̐ݒ�
		//	pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ���ˌ��̐ݒ�
			if(pEffect->nType == EFFECTTYPE_RANDOMCOLOR)
			{// �����_���J���[�̏ꍇ
				col.r = (float)(rand() % 50 + 1) / 100.0f;		// [(��)���̐��l��ύX����ƐԂ̗v�f����������(1�`100)]
				col.g = (float)(rand() % 50 + 1) / 100.0f;		// [(��)���̐��l��ύX����Ɨ΂̗v�f����������(1�`100)]
				col.b = (float)(rand() % 50 + 1) / 100.0f;		// [(��)���̐��l��ύX����Ɛ̗v�f����������(1�`100)]
				col.a = 1.0f;
			}
			if(pEffect->nType == EFFECTYPE_COLOR)
			{
				// �����_���J���[�̏ꍇ
				col.r = (float)(rand() % 255 + 1) / 100.0f;		// [(��)���̐��l��ύX����ƐԂ̗v�f����������(1�`100)]
				col.g = (float)(rand() % 255 + 1) / 100.0f;		// [(��)���̐��l��ύX����Ɨ΂̗v�f����������(1�`100)]
				col.b = (float)(rand() % 255 + 1) / 100.0f;		// [(��)���̐��l��ύX����Ɛ̗v�f����������(1�`100)]
				col.a = 1.0f;
			}
			
			pEffect->fColAlphaValue = 1.0f / nLife;
			SetColorEffect(nCntEffect, col, D3DXCOLOR(0.25f, 0.25f, 0.25f, 0.20f));

			// ���a�̐ݒ�
			pEffect->fRadius = fRadius;
			pEffect->fRadiusValue = (fRadius * 0.55f) / nLife;
			SetRadiusEffect(nCntEffect, fRadius);

			switch(pEffect->nType)
			{
			case EFFECTTYPE_NORMAL:				// �ʏ�G�t�F�N�g
			case EFFECTTYPE_RANDOMCOLOR:		// �����_���J���[�G�t�F�N�g
				pEffect->swingRate.x = 
				pEffect->swingWidth.x = 
				pEffect->swingRate.x = 0.0f;
				pEffect->swingRate.y = 
				pEffect->swingWidth.y = 
				pEffect->swingRate.y = 0.0f;
				break;
			case EFFECTYPE_COLOR:		
				srand((unsigned)time(NULL));
				pEffect->swingRate.x = 
				pEffect->swingWidth.x = 
				pEffect->swingRate.x = 0.0f;
				pEffect->swingRate.y = 
				pEffect->swingWidth.y = 
				pEffect->swingRate.y = 0.0f;
				break;
			}
			pEffect->bUse = true;
			break;
			// ���_�f�[�^���A�����b�N����
		g_pVtxBuffEffect->Unlock();
		}
	}
}
