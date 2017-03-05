//************************************************************************************************************************************************************************************************
// �C���N���[�h�t�@�C��
//************************************************************************************************************************************************************************************************
#include <stdlib.h>
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "camera.h"
#include "shadow.h"
#include "explosion.h"
#include "meshWall.h"
#include "effect.h"
//************************************************************************************************************************************************************************************************
// �}�N����`
//************************************************************************************************************************************************************************************************
#define BULLET_TEXTURE_FILE	"data\\TEXTURE\\bullet000.png"	//�e�̃e�N�X�`���t�@�C���ʒu
#define POSMOVE_BULLET		(   15.00f )		// �e�̈ړ���
#define CEILING				(  200.0f )		// �V��
#define GROUND				(    1.0f )		// �n��
#define XPOS_BULLET			(   20.0f )		// X�̒��S���W
#define YPOS_BULLET			(   20.0f )		// Y�̒��S���W
#define ZPOS_BULLET			(  -30.0f )		// Z�̒��S���W
#define XPOS_LEFT_VERTEX	(   -10.0f )		// ��X�̒��_���W
#define XPOS_RIGHT_VERTEX	(    10.0f )		// �EX�̒��_���W
#define YPOS_UP_VERTEX		(    10.0f )		// ��Y�̒��_���W
#define YPOS_DOWN_VERTEX	(   -10.0f )		// ��Y�̒��_���W
#define MAX_VERTEX			( 4 )			// �|���S���̒��_�̐�
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
BULLET g_aBullet[ MAX_BULLET ];		// �e�̏��
//================================================================================================================================================================================================
// InitBullet�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitBullet( void )
{
	// Direct3D�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�̃|�C���^���擾
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	VERTEX_3D *pVtx;

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		if( pBullet->bUse == false )
		{
			pBullet->pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			pBullet->rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
			pBullet->scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );
			pBullet->collisoin = ( fabs( XPOS_LEFT_VERTEX ) + fabs( XPOS_RIGHT_VERTEX ) ) / 2;
			pBullet->nLife = LIFE_BULLET;
			pBullet->nType = BULLETTYPE_PLAYER_HOMING;

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile( pDevice, BULLET_TEXTURE_FILE, &pBullet->pTextureBullet );

			// ���_�o�b�t�@�̐���
			if( FAILED( pDevice->CreateVertexBuffer( sizeof( VERTEX_3D ) * ( MAX_BULLET * 4 ),	// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
													 D3DUSAGE_WRITEONLY,
													 FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
													 D3DPOOL_MANAGED,
													 &pBullet->pVtxBuffBullet,
													 NULL ) ) )
			{
				return E_FAIL;
			}

			// ���_���̐ݒ�//////////////////////////////////////////////////////////////////////////////
			// ���_���ւ̃|�C���^���擾
			pBullet->pVtxBuffBullet->Lock( 0, 0, ( void** )&pVtx, 0 );
			pVtx[ ( nCntBullet * 4 ) + 0 ].pos = D3DXVECTOR3( XPOS_LEFT_VERTEX,  YPOS_UP_VERTEX,   0.0f );	// ���_���W
			pVtx[ ( nCntBullet * 4 ) + 1 ].pos = D3DXVECTOR3( XPOS_RIGHT_VERTEX, YPOS_UP_VERTEX,   0.0f );
			pVtx[ ( nCntBullet * 4 ) + 2 ].pos = D3DXVECTOR3( XPOS_LEFT_VERTEX,  YPOS_DOWN_VERTEX, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 3 ].pos = D3DXVECTOR3( XPOS_RIGHT_VERTEX, YPOS_DOWN_VERTEX, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );			// �@���̌���
			pVtx[ ( nCntBullet * 4 ) + 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );		// ���_�J���[
			pVtx[ ( nCntBullet * 4 ) + 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBullet * 4 ) + 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBullet * 4 ) + 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ ( nCntBullet * 4 ) + 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );					// �e�N�X�`�����W
			pVtx[ ( nCntBullet * 4 ) + 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ ( nCntBullet * 4 ) + 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ ( nCntBullet * 4 ) + 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
			pBullet->pVtxBuffBullet->Unlock();
			///////////////////////////////////////////////////////////////////////////////////////////////

			// �g�p���ĂȂ���Ԃɂ���B
			pBullet->bUse = false;
		}
		pBullet++;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitBullet�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitBullet( void )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		// �e�N�X�`���̊J��
		if( pBullet->pTextureBullet != NULL )
		{
			pBullet->pTextureBullet->Release();
			pBullet->pTextureBullet = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if( pBullet->pVtxBuffBullet != NULL )
		{
			pBullet->pVtxBuffBullet->Release();
			pBullet->pVtxBuffBullet = NULL;
		}
		pBullet++;
	}
}

//================================================================================================================================================================================================
// UpdateBullet�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateBullet( void )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++,pBullet++)
	{
		if( pBullet->bUse == true )
		{
			// �ʒu�̍X�V
			pBullet->pos.x += sinf( D3DX_PI + pBullet->rot.y ) * POSMOVE_BULLET;		// �p�x * �ړ���
			pBullet->pos.z += cosf( D3DX_PI + pBullet->rot.y ) * POSMOVE_BULLET;		// �p�x * �ړ���
			// �����̍X�V
			pBullet->nLife--;
			// �e�̎���������Ώ����B
			if( pBullet->nLife <= 0 )
			{
				pBullet->bUse = false;
			}
			MESHWALL *pWall = GetMeshWall();
			// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//if( (pWall + WALL_FRONT)->pos.z < ( pBullet->pos.z + pBullet->collisoin ) )
			//{	// ���̕�
			//	SetExplosion( pBullet->pos);
			//	pBullet->bUse = false;
			//}
			//else if( (pWall + WALL_BACK)->pos.z > ( pBullet->pos.z - pBullet->collisoin ) )
			//{	// �O�̕�
			//	SetExplosion( pBullet->pos);
			//	pBullet->bUse = false;
			//}
			if( (pWall + WALL_LEFT)->pos.x > ( pBullet->pos.x - pBullet->collisoin ) )
			{	// ���̕�
				SetExplosion( pBullet->pos );
				pBullet->bUse = false;
			}
			else if((pWall + WALL_RIGHT)->pos.x < ( pBullet->pos.x + pBullet->collisoin ) )
			{	// �E�̕�
				SetExplosion( pBullet->pos );
				pBullet->bUse = false;
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		//�e�̐ݒ�
		SetShadow( pBullet-> pos, BULLET_WIDTH, BULLET_HEIGHT, 1 + nCntBullet, pBullet -> bUse );
	}
}

//================================================================================================================================================================================================
// DrawBullet�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawBullet( void )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// �J�����Őݒ肵���r���[�}�g���b�N�X���󂯎�邽�߂̕ϐ�

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	// ���C�g�����B�ǂ̊p�x���猩�Ă������悤�ɂ��邽�߁A�r���{�[�h�̉A�e�𖳂����B
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// ���̒l���A���t�@�l���傫����Ε`�悷��B
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// �A���t�@�l�B0�œ����ȕ����B

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		if( pBullet->bUse == true )
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &pBullet->mtxWorldBullet );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &pBullet->mtxWorldBullet, NULL, &mtxView );

			pBullet->mtxWorldBullet._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			pBullet->mtxWorldBullet._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			pBullet->mtxWorldBullet._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, pBullet->scl.x, pBullet->scl.y, pBullet->scl.z );
			D3DXMatrixMultiply( &pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
	//		D3DXMatrixRotationYawPitchRoll( &mtxRot, pBullet->rot.y, pBullet->rot.x, pBullet->rot.z );	// y,x,z
			D3DXMatrixMultiply( &pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z );
			D3DXMatrixMultiply( &pBullet->mtxWorldBullet, &pBullet->mtxWorldBullet, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &pBullet->mtxWorldBullet );

			// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
			pDevice->SetStreamSource( 0, pBullet->pVtxBuffBullet, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, pBullet->pTextureBullet );

			// �|���S���̕`��
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,						// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
									( nCntBullet * 4 ),								// �`�悷��ŏ��̒��_
									2 );										// �`�悷��v���~�e�B�u��
		}
		pBullet++;
	}

	// �����_�[�X�e�[�g�̐ݒ���f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );			// �f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );			// �f�t�H���g�ɖ߂��B

	// ���C�g�_��
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//================================================================================================================================================================================================
// *GetBullet�֐�
// ���� void
// �߂�l 
// ���� Bullet���擾����B
//================================================================================================================================================================================================
BULLET *GetBullet( void )
{
	return &g_aBullet[ 0 ];
}

//================================================================================================================================================================================================
// *GetBulletPos�֐�
// ���� void
// �߂�l 
// ���� Bullet�̍��W���擾����B
//================================================================================================================================================================================================
D3DXVECTOR3 *GetBulletPos( void )
{
	return &g_aBullet[ 0 ].pos;
}

//================================================================================================================================================================================================
// SetBullet�֐�
// ���� pos ���W, rot ����, nLife ����
// �߂�l void
// ���� Bullet���Z�b�g����B
//================================================================================================================================================================================================
void SetBullet( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	BULLET *pBullet;
	pBullet = &g_aBullet[ 0 ];

	for( int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++ )
	{
		if( pBullet->bUse == false )
		{
			// �ʒu�̐ݒ�
			pBullet->pos = pos;

			// �ړ��ʂ̐ݒ�
			pBullet->rot = rot;

			// �����̐ݒ�
			pBullet->nLife = nLife;

			// �e���g�p��Ԃɂ���
			pBullet->bUse = true;
			break;
		}
		pBullet++;
	}
}