//=============================================================================

// �c�[���̏��� [prop.cpp]
// 

//=============================================================================//
#include "main.h"
#include "runleg.h"
#include "modellegL.h"
#include "modellegR.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RUNLEG_FILE		"data\\TEXTURE\\runleg.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define XPOS_LEFT_RUNLEG	(   -5.0f )		// ��X�̒��_���W
#define XPOS_RIGHT_RUNLEG	(    5.0f )		// �EX�̒��_���W
#define YPOS_UP_RUNLEG		(   5.0f )		// ��Y�̒��_���W
#define YPOS_DOWN_RUNLEG	(   -5.0f )		// ��Y�̒��_���W

#define	NUM_PATTERN_RUNLEG			(4)						// �A�j���[�V�����̃p�^�[����
#define	TEXTURE_SIZE_X_RUNLEG		(1.0f / NUM_PATTERN_RUNLEG)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y_RUNLEG		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

#define	INTERVAL_PATTERN_RUNLEG	(3)						// �A�j���[�V�����̐؂�ւ��Ԋu
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
RUNLEG g_aRunLeg[ MAX_RUNLEG ];		// �c�[���̏��

//================================================================================================================================================================================================
// InitRunLeg�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitRunLeg( void )
{
	MODELLEGL *pModelLegL = GetModelLegL();
	MODELLEGR *pModelLegR = GetModelLegR();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		if( g_aRunLeg[nCntRunLeg].bUse == false )
		{
			g_aRunLeg[nCntRunLeg].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aRunLeg[nCntRunLeg].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aRunLeg[nCntRunLeg].nCount = 0;
			g_aRunLeg[nCntRunLeg].nPattern = 0;
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, TEXTURE_RUNLEG_FILE, &g_aRunLeg[nCntRunLeg].pTextureRunLeg );

			// ���_�o�b�t�@�̐���
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_RUNLEG * 4 ),	// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
													 D3DPOOL_MANAGED,
													 &g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// ���_���̐ݒ�//////////////////////////////////////////////////////////////////////////////
			// ���_���ւ̃|�C���^���擾
			g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_RUNLEG,  YPOS_UP_RUNLEG,   0.0f );	// ���_���W
			pVtx[ ( nCntRunLeg * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_RUNLEG, YPOS_UP_RUNLEG,   0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_RUNLEG,  YPOS_DOWN_RUNLEG, 0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_RUNLEG, YPOS_DOWN_RUNLEG, 0.0f );

			pVtx[ ( nCntRunLeg * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// �@���̌���
			pVtx[ ( nCntRunLeg * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntRunLeg * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntRunLeg * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// ���_�J���[
			pVtx[ ( nCntRunLeg * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntRunLeg * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntRunLeg * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			// �e�N�X�`�����W�̐ݒ�
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(TEXTURE_SIZE_X_RUNLEG, 0.0f);
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y_RUNLEG);
			pVtx[ ( nCntRunLeg * 4 ) + 0 ].tex = D3DXVECTOR2(TEXTURE_SIZE_X_RUNLEG, TEXTURE_SIZE_Y_RUNLEG);

			g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// �g�p��Ԃɂ���B
			g_aRunLeg[nCntRunLeg].bUse = false;
		}
	}
	g_aRunLeg[0].pos = pModelLegL->pos;
	g_aRunLeg[1].pos = pModelLegR->pos;
	return S_OK;
}
//================================================================================================================================================================================================
// UninitRunLeg�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitRunLeg( void )
{
	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		// ���b�V�����̊J��
		if( g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg != NULL )
		{
			g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg->Release();
			g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aRunLeg[ nCntRunLeg ].pTextureRunLeg != NULL )
		{
			g_aRunLeg[ nCntRunLeg ].pTextureRunLeg->Release();
			g_aRunLeg[ nCntRunLeg ].pTextureRunLeg = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateRunLeg�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateRunLeg( void )
{
	MODELLEGL *pModelLegL = GetModelLegL();
	MODELLEGR *pModelLegR = GetModelLegR();
	g_aRunLeg[0].pos = pModelLegL->pos;
	g_aRunLeg[1].pos = pModelLegR->pos;
	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		if( g_aRunLeg[nCntRunLeg].bUse == true )
		{// �������g�p���Ă���
			g_aRunLeg[nCntRunLeg].nCount++;
			if((g_aRunLeg[nCntRunLeg].nCount % INTERVAL_PATTERN_RUNLEG) == 0)
			{// �A�j���[�V�����؂�ւ�
				g_aRunLeg[nCntRunLeg].nPattern++;
				if(g_aRunLeg[nCntRunLeg].nPattern >= NUM_PATTERN_RUNLEG  )
				{// �A�j���[�V�����p�^�[�����I��
					ResetRunLeg();
				}
				SetTextureRunLeg(nCntRunLeg);
			}
		}
	}
}

//================================================================================================================================================================================================
// DrawRunLeg�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawRunLeg( void )
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// �J�����Őݒ肵���r���[�}�g���b�N�X���󂯎�邽�߂̕ϐ�

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	// ���C�g�����B�ǂ̊p�x���猩�Ă������悤�ɂ��邽�߁A�r���{�[�h�̉A�e�𖳂����B
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// �����_�[�X�e�[�g�̐ݒ�iz�e�X�g�j
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z�l�̍X�V
	// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// ���̒l���A���t�@�l���傫����Ε`�悷��B
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// �A���t�@�l�B0�œ����ȕ����B
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++ )
	{
		if( g_aRunLeg[ nCntRunLeg ].bUse == true )
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_aRunLeg[ nCntRunLeg ].mtxWorld );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &g_aRunLeg[ nCntRunLeg ].mtxWorld, NULL, &mtxView );

			g_aRunLeg[ nCntRunLeg ].mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aRunLeg[ nCntRunLeg ].mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aRunLeg[ nCntRunLeg ].mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, g_aRunLeg[ nCntRunLeg ].scl.x, g_aRunLeg[ nCntRunLeg ].scl.y, g_aRunLeg[ nCntRunLeg ].scl.z );
			D3DXMatrixMultiply( &g_aRunLeg[ nCntRunLeg ].mtxWorld, &g_aRunLeg[ nCntRunLeg ].mtxWorld, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
			D3DXMatrixMultiply( &g_aRunLeg[ nCntRunLeg ].mtxWorld, &g_aRunLeg[ nCntRunLeg ].mtxWorld, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, g_aRunLeg[ nCntRunLeg ].pos.x, g_aRunLeg[ nCntRunLeg ].pos.y, g_aRunLeg[ nCntRunLeg ].pos.z );
			D3DXMatrixMultiply( &g_aRunLeg[ nCntRunLeg ].mtxWorld, &g_aRunLeg[ nCntRunLeg ].mtxWorld, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &g_aRunLeg[ nCntRunLeg ].mtxWorld );

			// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
			pDevice->SetStreamSource( 0, g_aRunLeg[ nCntRunLeg ].pVtxBuffRunLeg, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aRunLeg[ nCntRunLeg ].pTextureRunLeg );

			// �|���S���̕`��
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
									( nCntRunLeg * 4 ),								// �`�悷��ŏ��̒��_
									2 );										// �`�悷��v���~�e�B�u��
		}
	}

	// �����_�[�X�e�[�g�̐ݒ���f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// �f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// �f�t�H���g�ɖ߂��B

	// ���C�g�_��
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}


//================================================================================================================================================================================================
// *GetRunLeg�֐�
// ���� void
// �߂�l 
// ���� RunLeg���擾����B
//================================================================================================================================================================================================
RUNLEG *GetRunLeg( void )
{
	return &g_aRunLeg[ 0 ];
}


//=============================================================================
// RUN�̃��Z�b�g
//=============================================================================
void ResetRunLeg(void)
{
	for(int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++)
	{
		g_aRunLeg[nCntRunLeg].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aRunLeg[nCntRunLeg].nCount = 0;
		g_aRunLeg[nCntRunLeg].nPattern = 0;


	}
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureRunLeg(int nRunLegID)
{
	for(int nCntRunLeg = 0; nCntRunLeg < MAX_RUNLEG; nCntRunLeg++)
	{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nRunLegID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aRunLeg[nRunLegID].nPattern * TEXTURE_SIZE_X_RUNLEG, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aRunLeg[nRunLegID].nPattern + 1) * TEXTURE_SIZE_X_RUNLEG, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aRunLeg[nRunLegID].nPattern * TEXTURE_SIZE_X_RUNLEG, TEXTURE_SIZE_Y_RUNLEG);
	pVtx[3].tex = D3DXVECTOR2((g_aRunLeg[nRunLegID].nPattern + 1) * TEXTURE_SIZE_X_RUNLEG, TEXTURE_SIZE_Y_RUNLEG);

	// ���_�f�[�^���A�����b�N����
	g_aRunLeg[nCntRunLeg].pVtxBuffRunLeg->Unlock();
	}
}