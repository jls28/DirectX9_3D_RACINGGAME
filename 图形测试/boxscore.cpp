//=============================================================================
//
// boxscore���� [BoxScore01.h]
// 2016/02/14 LIHAOSHENG
//
//=============================================================================
#include "main.h"
#include "boxscore.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_BOXSCORE01_FILE		"data\\TEXTURE\\boxscore01.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define XPOS_LEFT_BOXSCORE01	(   -100.0f )		// ��X�̒��_���W
#define XPOS_RIGHT_BOXSCORE01	(    100.0f )		// �EX�̒��_���W
#define YPOS_UP_BOXSCORE01		(   100.0f )		// ��Y�̒��_���W
#define YPOS_DOWN_BOXSCORE01	(   -100.0f )		// ��Y�̒��_���W
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
BOXSCORE01 g_aBoxScore01[ MAX_BOXSCORE01 ];		// �c�[���̏��

//================================================================================================================================================================================================
// InitBoxScore01�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitBoxScore01( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[nCntBoxScore01].bUse == false )
		{
			g_aBoxScore01[nCntBoxScore01].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aBoxScore01[nCntBoxScore01].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aBoxScore01[nCntBoxScore01].nLife = 100;
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, TEXTURE_BOXSCORE01_FILE, &g_aBoxScore01[nCntBoxScore01].pTextureBoxScore01 );

			// ���_�o�b�t�@�̐���
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_BOXSCORE01 * 4 ),	// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
													 D3DPOOL_MANAGED,
													 &g_aBoxScore01[nCntBoxScore01].pVtxBuffBoxScore01,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// ���_���̐ݒ�//////////////////////////////////////////////////////////////////////////////
			// ���_���ւ̃|�C���^���擾
			g_aBoxScore01[nCntBoxScore01].pVtxBuffBoxScore01->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntBoxScore01 * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_BOXSCORE01,  YPOS_UP_BOXSCORE01,   0.0f );	// ���_���W
			pVtx[ ( nCntBoxScore01 * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_BOXSCORE01, YPOS_UP_BOXSCORE01,   0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_BOXSCORE01,  YPOS_DOWN_BOXSCORE01, 0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_BOXSCORE01, YPOS_DOWN_BOXSCORE01, 0.0f );

			pVtx[ ( nCntBoxScore01 * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// �@���̌���
			pVtx[ ( nCntBoxScore01 * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBoxScore01 * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntBoxScore01 * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// ���_�J���[
			pVtx[ ( nCntBoxScore01 * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBoxScore01 * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBoxScore01 * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


			g_aBoxScore01[nCntBoxScore01].pVtxBuffBoxScore01->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// �g�p��Ԃɂ���B
			g_aBoxScore01[nCntBoxScore01].bUse = false;
		}
	}
	return S_OK;
}
//================================================================================================================================================================================================
// UninitBoxScore01�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitBoxScore01( void )
{
	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		// ���b�V�����̊J��
		if( g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01 != NULL )
		{
			g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01->Release();
			g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01 = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01 != NULL )
		{
			g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01->Release();
			g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01 = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateBoxScore01�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateBoxScore01( void )
{
	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[ nCntBoxScore01 ].bUse == true )
		{
			g_aBoxScore01[ nCntBoxScore01 ].nLife --;
			if(g_aBoxScore01[ nCntBoxScore01 ].nLife <= 0)
			{
				g_aBoxScore01[ nCntBoxScore01 ].bUse = false;
			}

		}
	}


}

//================================================================================================================================================================================================
// DrawBoxScore01�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawBoxScore01( void )
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

	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[ nCntBoxScore01 ].bUse == true )
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, NULL, &mtxView );

			g_aBoxScore01[ nCntBoxScore01 ].mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aBoxScore01[ nCntBoxScore01 ].mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aBoxScore01[ nCntBoxScore01 ].mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, g_aBoxScore01[ nCntBoxScore01 ].scl.x, g_aBoxScore01[ nCntBoxScore01 ].scl.y, g_aBoxScore01[ nCntBoxScore01 ].scl.z );
			D3DXMatrixMultiply( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
			D3DXMatrixMultiply( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, g_aBoxScore01[ nCntBoxScore01 ].pos.x, g_aBoxScore01[ nCntBoxScore01 ].pos.y, g_aBoxScore01[ nCntBoxScore01 ].pos.z );
			D3DXMatrixMultiply( &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &g_aBoxScore01[ nCntBoxScore01 ].mtxWorld );

			// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
			pDevice->SetStreamSource( 0, g_aBoxScore01[ nCntBoxScore01 ].pVtxBuffBoxScore01, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aBoxScore01[ nCntBoxScore01 ].pTextureBoxScore01 );

			// �|���S���̕`��
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
									( nCntBoxScore01 * 4 ),								// �`�悷��ŏ��̒��_
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
// *GetBoxScore01�֐�
// ���� void
// �߂�l 
// ���� BoxScore01���擾����B
//================================================================================================================================================================================================
BOXSCORE01 *GetBoxScore01( void )
{
	return &g_aBoxScore01[ 0 ];
}
void SetBoxScore01( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	for( int nCntBoxScore01 = 0; nCntBoxScore01 < MAX_BOXSCORE01; nCntBoxScore01++ )
	{
		if( g_aBoxScore01[ nCntBoxScore01 ].bUse == false )
		{
			// �ʒu�̐ݒ�
			g_aBoxScore01[ nCntBoxScore01 ].pos = pos;


			g_aBoxScore01[ nCntBoxScore01 ].rot = rot;

			// �����̐ݒ�
			g_aBoxScore01[ nCntBoxScore01 ].nLife = nLife;


			// �c�[�����g�p��Ԃɂ���
			g_aBoxScore01[ nCntBoxScore01 ].bUse = true;

			
		}
	}
	
}
