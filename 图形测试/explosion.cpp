#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EXPLOSION	"data\\TEXTURE\\attackeffect.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	EXPLOSION_POS_X		(0.0f)							// �����̕\����ʒu�w���W
#define	EXPLOSION_POS_Y		(0.0f)							// �����̕\����ʒu�x���W
#define	EXPLOSION_WIDTH		(35.0f)							// �����̕�
#define	EXPLOSION_HEIGHT	(35.0f)							// �����̍���

#define	MAX_EXPLOSION		(256)					// �����̍ő吔

#define	NUM_PATTERN			(7)						// �A�j���[�V�����̃p�^�[����
#define	TEXTURE_SIZE_X		(1.0f / NUM_PATTERN)	// �e�N�X�`�����̂P�p�^�[���̕�
#define	TEXTURE_SIZE_Y		(1.0f)					// �e�N�X�`�����̂P�p�^�[���̍���

#define	INTERVAL_PATTERN	(3)						// �A�j���[�V�����̐؂�ւ��Ԋu


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetTextureExplosion(int nExplosionID);
//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

EXPLOSION				g_aExplosion[MAX_EXPLOSION];	// �����̃��[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitExplosion(void)
{
		//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].scl= D3DXVECTOR3( 1.0f, 1.0f, 1.0f );	//�g��k��
		g_aExplosion[nCntExplosion].nCount = 0;
		g_aExplosion[nCntExplosion].nPattern = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
								pDevice,			// �f�o�C�X�ւ̃|�C���^
								TEXTURE_EXPLOSION,		// �t�@�C���̖��O
								&g_pTextureExplosion);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexExplosion(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitExplosion(void)
{
	if(g_pTextureExplosion != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	if(g_pVtxBuffExplosion != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateExplosion(void)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if(g_aExplosion[nCntExplosion].bUse == true)
		{// �������g�p���Ă���
			g_aExplosion[nCntExplosion].nCount++;
			if((g_aExplosion[nCntExplosion].nCount % INTERVAL_PATTERN) == 0)
			{// �A�j���[�V�����؂�ւ�
				g_aExplosion[nCntExplosion].nPattern++;
				if(g_aExplosion[nCntExplosion].nPattern >= NUM_PATTERN  )
				{// �A�j���[�V�����p�^�[�����I��
					ResetExplosion();
				}
				SetTextureExplosion(nCntExplosion);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawExplosion(void)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[ 0 ];

	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATRIX mtxView;		// �J�����Őݒ肵���r���[�}�g���b�N�X���󂯎�邽�߂̕ϐ�

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform( D3DTS_VIEW, &mtxView );

	// ���C�g�����B�ǂ̊p�x���猩�Ă������悤�ɂ��邽�߁A�r���{�[�h�̉A�e�𖳂����B
	pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// �A���t�@�e�X�g�̐ݒ�
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );		// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );	// ���̒l���A���t�@�l���傫����Ε`�悷��B
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );				// �A���t�@�l�B0�œ����ȕ����B

	// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );				// Z�e�X�g������B
	pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );	// ������`�悷����̂��A���ɕ`�悳��Ă�����̈ȉ���Z�l�ł���΁A�`�悷��B
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//	// Z�l�̍X�V

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF( FVF_VERTEX_3D );

	for( int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++ )
	{
		if( pExplosion->bUse == true )
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &pExplosion->mtxWorldExplosion );

			// �r���[�}�g���b�N�X�̋t�s������߂�B
			D3DXMatrixInverse( &pExplosion->mtxWorldExplosion, NULL, &mtxView );

			pExplosion->mtxWorldExplosion._41 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			pExplosion->mtxWorldExplosion._42 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A
			pExplosion->mtxWorldExplosion._43 = 0.0f;		// �ړ��Ɋւ���ϐ����N���A

			// �X�P�[���𔽉f
			D3DXMatrixScaling( &mtxScl, pExplosion->scl.x, pExplosion->scl.y, pExplosion->scl.z );
			D3DXMatrixMultiply( &pExplosion->mtxWorldExplosion, &pExplosion->mtxWorldExplosion, &mtxScl );

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll( &mtxRot, 0.0f, 0.0f, 0.0f );	// �r���{�[�h�͏�ɐ��ʂ��J�����Ɍ�����2D�|���S��������A�I�[��0.0�̏����l�ł����B
	//		D3DXMatrixRotationYawPitchRoll( &mtxRot, pExplosion->rot.y, pExplosion->rot.x, pExplosion->rot.z );	// y,x,z
			D3DXMatrixMultiply( &pExplosion->mtxWorldExplosion, &pExplosion->mtxWorldExplosion, &mtxRot );

			// �ʒu�𔽉f
			D3DXMatrixTranslation( &mtxTrans, pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z );
			D3DXMatrixMultiply( &pExplosion->mtxWorldExplosion, &pExplosion->mtxWorldExplosion, &mtxTrans );

			// ���[���h�}�g���b�N�X��ݒ�
			pDevice->SetTransform( D3DTS_WORLD, &pExplosion->mtxWorldExplosion );

			// ���_�o�b�t�@���f�[�^�X�g���[���i�x���g�R���x�A�j�Ƀo�C���h����i���t����j�B
			pDevice->SetStreamSource( 0, g_pVtxBuffExplosion, 0, sizeof( VERTEX_3D ) );			//sizeof( VERTEX_2D )�̓f�[�^�̊Ԋu

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, g_pTextureExplosion );

			// �|���S���̕`��
			pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,		// TRIANGLELIST�Ōʂ̎O�p�`�̕`��BTRIANGLESTRIP�łȂ������O�p�A�����Ďl�p�BTRIANGLEFAN�ŉ~�B
									( nCntExplosion * 4 ),		// �`�悷��ŏ��̒��_
									2 );						// �`�悷��v���~�e�B�u��
		}

		pExplosion++;
	}

	// �A���t�@�e�X�g���f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );	// �f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );	// �f�t�H���g�ɖ߂��B

	// Z�e�X�g���f�t�H���g�ɖ߂��B
	pDevice->SetRenderState( D3DRS_ZENABLE, FALSE );			// Z�e�X�g������B
	pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );	// ������`�悷����̂��A���ɕ`�悳��Ă�����̈ȉ���Z�l�ł���΁A�`�悷��B

	// ���C�g�_��
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexExplosion( LPDIRECT3DDEVICE9 pDevice )
{
	//���_�o�b�t�@�̐���
	if( FAILED ( pDevice -> CreateVertexBuffer(
												sizeof( VERTEX_3D ) * 4 * MAX_EXPLOSION,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&g_pVtxBuffExplosion,
												NULL
	) ) )
	{
		return E_FAIL;
	}

	//���_�o�b�t�@
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffExplosion -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4 )
	{
		//���_���W�̐ݒ�
		pVtx[ 0 ].pos	= D3DXVECTOR3( -EXPLOSION_WIDTH * 0.5f, EXPLOSION_HEIGHT, 0.0f );
		pVtx[ 1 ].pos	= D3DXVECTOR3(  EXPLOSION_WIDTH * 0.5f, EXPLOSION_HEIGHT, 0.0f );
		pVtx[ 2 ].pos	= D3DXVECTOR3( -EXPLOSION_WIDTH * 0.5f, - EXPLOSION_HEIGHT, 0.0f );
		pVtx[ 3 ].pos	= D3DXVECTOR3(  EXPLOSION_WIDTH * 0.5f, - EXPLOSION_HEIGHT, 0.0f );

		//�@���̐ݒ�
		pVtx[ 0 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 1 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 2 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 3 ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		//���_�J���[�̐ݒ�
		pVtx[ 0 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 1 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 2 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );
		pVtx[ 3 ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(TEXTURE_SIZE_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, TEXTURE_SIZE_Y);
		pVtx[3].tex = D3DXVECTOR2(TEXTURE_SIZE_X, TEXTURE_SIZE_Y);
	}

	//���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion -> Unlock();

	return S_OK;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{	
		if(g_aExplosion[nCntExplosion].bUse == false)
		{
			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].nCount = 0;
			g_aExplosion[nCntExplosion].nPattern = 0;
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �����̃��Z�b�g
//=============================================================================
void ResetExplosion(void)
{
	for(int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].nCount = 0;
		g_aExplosion[nCntExplosion].nPattern = 0;
		g_aExplosion[nCntExplosion].bUse = false;

	}
}
//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureExplosion(int nExplosionID)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nExplosionID * 4);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nExplosionID].nPattern * TEXTURE_SIZE_X, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((g_aExplosion[nExplosionID].nPattern + 1) * TEXTURE_SIZE_X, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nExplosionID].nPattern * TEXTURE_SIZE_X, TEXTURE_SIZE_Y);
	pVtx[3].tex = D3DXVECTOR2((g_aExplosion[nExplosionID].nPattern + 1) * TEXTURE_SIZE_X, TEXTURE_SIZE_Y);

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}
/*------------------------------------------------------------------------------
|	�����̎擾
------------------------------------------------------------------------------*/
EXPLOSION *GetExplosion(void)
{
	return &g_aExplosion[ 0 ];
}