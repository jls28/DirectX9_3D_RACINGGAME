//=============================================================================

// �c�[���̏��� [prop.cpp]
// 

//=============================================================================//
#include "main.h"
#include "prop.h"
#include "effect.h"
#include "shadow.h"
//*****************************************************************************
// �}�N����`prop001.png
//*****************************************************************************
#define	TEXTURE_PROP_FILE		"data\\TEXTURE\\prop001.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define XPOS_LEFT_PROP	(   -30.0f )		// ��X�̒��_���W
#define XPOS_RIGHT_PROP	(    30.0f )		// �EX�̒��_���W
#define YPOS_UP_PROP		(   30.0f )		// ��Y�̒��_���W
#define YPOS_DOWN_PROP	(   -30.0f )		// ��Y�̒��_���W
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
PROP g_aProp[ MAX_PROP ];		// �c�[���̏��

//================================================================================================================================================================================================
// InitProp�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitProp( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		if( g_aProp[nCntProp].bUse == false )
		{
			g_aProp[nCntProp].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aProp[nCntProp].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aProp[nCntProp].nLife = LIFE_PROP;
			g_aProp[nCntProp].state = PROPSTATE_START;
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, TEXTURE_PROP_FILE, &g_aProp[nCntProp].pTextureProp );

			// ���_�o�b�t�@�̐���
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_PROP * 4 ),	// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
													 D3DPOOL_MANAGED,
													 &g_aProp[nCntProp].pVtxBuffProp,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// ���_���̐ݒ�//////////////////////////////////////////////////////////////////////////////
			// ���_���ւ̃|�C���^���擾
			g_aProp[nCntProp].pVtxBuffProp->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntProp * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_PROP,  YPOS_UP_PROP,   0.0f );	// ���_���W
			pVtx[ ( nCntProp * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_PROP, YPOS_UP_PROP,   0.0f );
			pVtx[ ( nCntProp * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_PROP,  YPOS_DOWN_PROP, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_PROP, YPOS_DOWN_PROP, 0.0f );

			pVtx[ ( nCntProp * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// �@���̌���
			pVtx[ ( nCntProp * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntProp * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// ���_�J���[
			pVtx[ ( nCntProp * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntProp * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntProp * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			pVtx[ ( nCntProp * 4 ) + 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );					// �e�N�X�`�����W
			pVtx[ ( nCntProp * 4 ) + 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ ( nCntProp * 4 ) + 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ ( nCntProp * 4 ) + 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

			g_aProp[nCntProp].pVtxBuffProp->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// �g�p��Ԃɂ���B
			g_aProp[nCntProp].bUse = true;
		}
	}
	g_aProp[0].pos = D3DXVECTOR3( -60.0f, 20.0f, 500.0f );

	g_aProp[1].pos = D3DXVECTOR3( -40.0f, 20.0f, 1000.0f );

	g_aProp[2].pos = D3DXVECTOR3( 60.0f, 20.0f, 1600.0f );

	g_aProp[3].pos = D3DXVECTOR3( 0.0f, 20.0f, 2000.0f );

	g_aProp[4].pos = D3DXVECTOR3( -60.0f, 20.0f, 2500.0f );

	g_aProp[5].pos = D3DXVECTOR3( 60.0f, 20.0f, 2500.0f );

	g_aProp[6].pos = D3DXVECTOR3( -50.0f, 20.0f, 3000.0f );

	g_aProp[7].pos = D3DXVECTOR3( 70.0f, 20.0f, 3000.0f );

	g_aProp[8].pos = D3DXVECTOR3( -70.0f, 20.0f, 3600.0f );

	g_aProp[9].pos = D3DXVECTOR3( -50.0f, 20.0f, 4000.0f );

	g_aProp[10].pos = D3DXVECTOR3( -10.0f, 20.0f, 4500.0f );

	g_aProp[11].pos = D3DXVECTOR3( 15.0f, 20.0f, 4800.0f );

	g_aProp[12].pos = D3DXVECTOR3( 40.0f, 20.0f, 5000.0f );

	g_aProp[13].pos = D3DXVECTOR3( 70.0f, 20.0f, 5800.0f );

	g_aProp[14].pos = D3DXVECTOR3( 20.0f, 20.0f, 6000.0f );

	g_aProp[15].pos = D3DXVECTOR3( 70.0f, 20.0f, 6300.0f );

	g_aProp[16].pos = D3DXVECTOR3( 0.0f, 20.0f, 6800.0f );

	g_aProp[17].pos = D3DXVECTOR3( -60.0f, 20.0f, 7500.0f );

	g_aProp[18].pos = D3DXVECTOR3( 30.0f, 20.0f, 8000.0f );

	g_aProp[19].pos = D3DXVECTOR3( -50.0f, 20.0f, 8600.0f );

	g_aProp[20].pos = D3DXVECTOR3( 60.0f, 20.0f, 7000.0f );

	g_aProp[21].pos = D3DXVECTOR3( 70.0f, 20.0f, 7700.0f );

	g_aProp[22].pos = D3DXVECTOR3( -80.0f, 20.0f, 8000.0f );

	g_aProp[23].pos = D3DXVECTOR3( 80.0f, 20.0f, 8600.0f );

	g_aProp[24].pos = D3DXVECTOR3( -20.0f, 20.0f, 9300.0f );

	g_aProp[24].pos = D3DXVECTOR3( 60.0f, 20.0f, 9900.0f );

	g_aProp[25].pos = D3DXVECTOR3( 30.0f, 20.0f, 10800.0f );

	g_aProp[26].pos = D3DXVECTOR3( 0.0f, 20.0f, 11600.0f );

	g_aProp[27].pos = D3DXVECTOR3( -70.0f, 20.0f, 12300.0f );

	g_aProp[28].pos = D3DXVECTOR3( 20.0f, 20.0f, 12900.0f );

	g_aProp[29].pos = D3DXVECTOR3( 20.0f, 20.0f, 13800.0f );

	g_aProp[30].pos = D3DXVECTOR3( 70.0f, 20.0f, 14300.0f );

	g_aProp[31].pos = D3DXVECTOR3( -50.0f, 20.0f, 14900.0f );

	g_aProp[32].pos = D3DXVECTOR3( 30.0f, 20.0f, 15300.0f );

	g_aProp[33].pos = D3DXVECTOR3( 80.0f, 20.0f, 15800.0f );

	g_aProp[34].pos = D3DXVECTOR3( -10.0f, 20.0f, 16700.0f );

	g_aProp[35].pos = D3DXVECTOR3( 0.0f, 20.0f, 17500.0f );

	g_aProp[36].pos = D3DXVECTOR3( 60.0f, 20.0f, 18300.0f );

	g_aProp[37].pos = D3DXVECTOR3( 30.0f, 20.0f, 19000.0f );

	g_aProp[38].pos = D3DXVECTOR3( -70.0f, 20.0f, 20000.0f );

	return S_OK;
}
//================================================================================================================================================================================================
// UninitProp�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitProp( void )
{
	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		// ���b�V�����̊J��
		if( g_aProp[ nCntProp ].pVtxBuffProp != NULL )
		{
			g_aProp[ nCntProp ].pVtxBuffProp->Release();
			g_aProp[ nCntProp ].pVtxBuffProp = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aProp[ nCntProp ].pTextureProp != NULL )
		{
			g_aProp[ nCntProp ].pTextureProp->Release();
			g_aProp[ nCntProp ].pTextureProp = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateProp�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateProp( void )
{
	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		if( g_aProp[nCntProp].bUse == true )
		{
			//�e
			SetShadow( g_aProp[nCntProp].pos, 20.0f, 20.0f, 1 + nCntProp , true );
			//effect
			SetEffect(g_aProp[nCntProp].pos, D3DCOLOR_RGBA(0, 255, 255, 255), 50, 10, EFFECTTYPE_NORMAL);

		}
	}
}

//================================================================================================================================================================================================
// DrawProp�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawProp( void )
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

	for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
	{
		if( g_aProp[ nCntProp ].bUse == true )
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_aProp[ nCntProp ].mtxWorld );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &g_aProp[ nCntProp ].mtxWorld, NULL, &mtxView );

			g_aProp[ nCntProp ].mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aProp[ nCntProp ].mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aProp[ nCntProp ].mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, g_aProp[ nCntProp ].scl.x, g_aProp[ nCntProp ].scl.y, g_aProp[ nCntProp ].scl.z );
			D3DXMatrixMultiply( &g_aProp[ nCntProp ].mtxWorld, &g_aProp[ nCntProp ].mtxWorld, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
			D3DXMatrixMultiply( &g_aProp[ nCntProp ].mtxWorld, &g_aProp[ nCntProp ].mtxWorld, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, g_aProp[ nCntProp ].pos.x, g_aProp[ nCntProp ].pos.y, g_aProp[ nCntProp ].pos.z );
			D3DXMatrixMultiply( &g_aProp[ nCntProp ].mtxWorld, &g_aProp[ nCntProp ].mtxWorld, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &g_aProp[ nCntProp ].mtxWorld );

			// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
			pDevice->SetStreamSource( 0, g_aProp[ nCntProp ].pVtxBuffProp, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aProp[ nCntProp ].pTextureProp );

			// �|���S���̕`��
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
									( nCntProp * 4 ),								// �`�悷��ŏ��̒��_
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
// *GetProp�֐�
// ���� void
// �߂�l 
// ���� Prop���擾����B
//================================================================================================================================================================================================
PROP *GetProp( void )
{
	return &g_aProp[ 0 ];
}


