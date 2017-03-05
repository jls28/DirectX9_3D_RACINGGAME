//=============================================================================

// �c�[���̏��� [money.cpp]
// 

//=============================================================================//
#include "main.h"
#include "money.h"
#include "shadow.h"
#include "effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_MONEY_FILE		"data\\TEXTURE\\money.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define XPOS_LEFT_MONEY	(   -10.0f )		// ��X�̒��_���W
#define XPOS_RIGHT_MONEY	(    10.0f )		// �EX�̒��_���W
#define YPOS_UP_MONEY		(   10.0f )		// ��Y�̒��_���W
#define YPOS_DOWN_MONEY	(   -10.0f )		// ��Y�̒��_���W
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MONEY g_aMoney[ MAX_MONEY ];		// �c�[���̏��

//================================================================================================================================================================================================
// InitMoney�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitMoney( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;

	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[nCntMoney].bUse == false )
		{
			g_aMoney[nCntMoney].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			g_aMoney[nCntMoney].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			g_aMoney[nCntMoney].nLife = LIFE_MONEY;
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, TEXTURE_MONEY_FILE, &g_aMoney[nCntMoney].pTextureMoney );

			// ���_�o�b�t�@�̐���
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_MONEY * 4 ),	// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
													 D3DPOOL_MANAGED,
													 &g_aMoney[nCntMoney].pVtxBuffMoney,
													 NULL ) ) )
			{
				return E_FAIL;
			}
			// ���_���̐ݒ�//////////////////////////////////////////////////////////////////////////////
			// ���_���ւ̃|�C���^���擾
			g_aMoney[nCntMoney].pVtxBuffMoney->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntMoney * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_MONEY,  YPOS_UP_MONEY,   0.0f );	// ���_���W
			pVtx[ ( nCntMoney * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_MONEY, YPOS_UP_MONEY,   0.0f );
			pVtx[ ( nCntMoney * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_MONEY,  YPOS_DOWN_MONEY, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_MONEY, YPOS_DOWN_MONEY, 0.0f );

			pVtx[ ( nCntMoney * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// �@���̌���
			pVtx[ ( nCntMoney * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

			pVtx[ ( nCntMoney * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// ���_�J���[
			pVtx[ ( nCntMoney * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntMoney * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntMoney * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			pVtx[ ( nCntMoney * 4 ) + 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );					// �e�N�X�`�����W
			pVtx[ ( nCntMoney * 4 ) + 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ ( nCntMoney * 4 ) + 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ ( nCntMoney * 4 ) + 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

			g_aMoney[nCntMoney].pVtxBuffMoney->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// �g�p��Ԃɂ���B
			g_aMoney[nCntMoney].bUse = false;
		}
	}
	return S_OK;
}
//================================================================================================================================================================================================
// UninitMoney�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitMoney( void )
{
	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		// ���b�V�����̊J��
		if( g_aMoney[ nCntMoney ].pVtxBuffMoney != NULL )
		{
			g_aMoney[ nCntMoney ].pVtxBuffMoney->Release();
			g_aMoney[ nCntMoney ].pVtxBuffMoney = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aMoney[ nCntMoney ].pTextureMoney != NULL )
		{
			g_aMoney[ nCntMoney ].pTextureMoney->Release();
			g_aMoney[ nCntMoney ].pTextureMoney = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateMoney�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateMoney( void )
{
	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[ nCntMoney ].bUse == true )
		{
			//�e�̐ݒ�
			SetShadow( g_aMoney[ nCntMoney ].pos, 20.0f, 5.0f, 1 + nCntMoney, g_aMoney[ nCntMoney ].bUse );

			g_aMoney[ nCntMoney ].nLife --;
			if(g_aMoney[ nCntMoney ].nLife <= 0)
			{
				g_aMoney[ nCntMoney ].bUse = false;
			}

		}
	}


}

//================================================================================================================================================================================================
// DrawMoney�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawMoney( void )
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

	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[ nCntMoney ].bUse == true )
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_aMoney[ nCntMoney ].mtxWorld );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &g_aMoney[ nCntMoney ].mtxWorld, NULL, &mtxView );

			g_aMoney[ nCntMoney ].mtxWorld._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aMoney[ nCntMoney ].mtxWorld._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			g_aMoney[ nCntMoney ].mtxWorld._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, g_aMoney[ nCntMoney ].scl.x, g_aMoney[ nCntMoney ].scl.y, g_aMoney[ nCntMoney ].scl.z );
			D3DXMatrixMultiply( &g_aMoney[ nCntMoney ].mtxWorld, &g_aMoney[ nCntMoney ].mtxWorld, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
			D3DXMatrixMultiply( &g_aMoney[ nCntMoney ].mtxWorld, &g_aMoney[ nCntMoney ].mtxWorld, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, g_aMoney[ nCntMoney ].pos.x, g_aMoney[ nCntMoney ].pos.y, g_aMoney[ nCntMoney ].pos.z );
			D3DXMatrixMultiply( &g_aMoney[ nCntMoney ].mtxWorld, &g_aMoney[ nCntMoney ].mtxWorld, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &g_aMoney[ nCntMoney ].mtxWorld );

			// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
			pDevice->SetStreamSource( 0, g_aMoney[ nCntMoney ].pVtxBuffMoney, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aMoney[ nCntMoney ].pTextureMoney );

			// �|���S���̕`��
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
									( nCntMoney * 4 ),								// �`�悷��ŏ��̒��_
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
// *GetMoney�֐�
// ���� void
// �߂�l 
// ���� Money���擾����B
//================================================================================================================================================================================================
MONEY *GetMoney( void )
{
	return &g_aMoney[ 0 ];
}
void SetMoney( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
	{
		if( g_aMoney[ nCntMoney ].bUse == false )
		{
			// �ʒu�̐ݒ�
			g_aMoney[ nCntMoney ].pos = pos;


			g_aMoney[ nCntMoney ].rot = rot;

			// �����̐ݒ�
			g_aMoney[ nCntMoney ].nLife = nLife;

			// �c�[�����g�p��Ԃɂ���
			g_aMoney[ nCntMoney ].bUse = true;

			
		}
	}
	
}

