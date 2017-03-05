/*******************************************************************************
* �^�C�g���F �e�`��֐�
* �t�@�C�����F shadow.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/18
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "shadow.h"
#include "input.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define SHADOW_TEXTURE_FILE "data\\TEXTURE\\shadow000.jpg"	//�e�̃e�N�X�`���t�@�C���ʒu
#define SHADOW_MAX ( 256 )							//�e�̍ő吔

/*******************************************************************************
* �O���[�o���ϐ�
********************************************************************************/
SHADOW	g_Shadow[ SHADOW_MAX ];									//�e�̍\����

/*******************************************************************************
* �֐���: �V���h�[�̏������֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
HRESULT InitShadow( void )
{
	for( int nCntShadow = 0; nCntShadow < SHADOW_MAX; nCntShadow++ )
	{
		//�f�o�C�X�̃Q�b�^�[
		LPDIRECT3DDEVICE9 pDevice	= GetDevice();

		//�V���h�[�\���̂̏�����
		g_Shadow[ nCntShadow ].pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
		g_Shadow[ nCntShadow ].pTexture = NULL;	//�e�N�X�`���o�b�t�@�ւ̃|�C���^
		g_Shadow[ nCntShadow ].rot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );	//����
		g_Shadow[ nCntShadow ].scl = D3DXVECTOR3( 1.0f, 1.0f, 1.0f );	//�g��k��

		//���_�o�b�t�@�̐���
		if( FAILED ( pDevice -> CreateVertexBuffer(
													sizeof( VERTEX_3D ) * 4,
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_3D,
													D3DPOOL_MANAGED,
													&g_Shadow[ nCntShadow ].pVtxBuff,
													NULL
		) ) )
		{
			return E_FAIL;
		}

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, SHADOW_TEXTURE_FILE, &g_Shadow[ nCntShadow ].pTexture );
	}
	return S_OK;
}

/*******************************************************************************
* �֐���: �V���h�[�̏I���֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UninitShadow( void )
{
	for( int nCntShadow = 0; nCntShadow < SHADOW_MAX; nCntShadow++ )
	{
		if( g_Shadow[ nCntShadow ].pTexture != NULL )
		{
			g_Shadow[ nCntShadow ].pTexture -> Release();	//�e�N�X�`���|���S���̊J��
			g_Shadow[ nCntShadow ].pTexture = NULL;
		}

		if( g_Shadow[ nCntShadow ].pVtxBuff != NULL )		//���_�o�b�t�@�̊J��
		{
			g_Shadow[ nCntShadow ].pVtxBuff -> Release();
			g_Shadow[ nCntShadow ].pVtxBuff = NULL;
		}
	}
}

/*******************************************************************************
* �֐���: �V���h�[�̕`��֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void DrawShadow( void )
{
	for( int nCntShadow = 0; nCntShadow < SHADOW_MAX; nCntShadow++ )
	{
		if( g_Shadow[ nCntShadow ].bUse )
		{
			//�f�o�C�X�̃Q�b�^�[
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_Shadow[ nCntShadow ].mtxWorld );

			//�X�P�[���𔽉f
			D3DXMatrixScaling(
								&g_Shadow[ nCntShadow ].mtxScl,
								g_Shadow[ nCntShadow ].scl.x,
								g_Shadow[ nCntShadow ].scl.y,
								g_Shadow[ nCntShadow ].scl.z
			);
			D3DXMatrixMultiply(
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxScl
			);

			//��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(
								&g_Shadow[ nCntShadow ].mtxRot,
								g_Shadow[ nCntShadow ].rot.y,
								g_Shadow[ nCntShadow ].rot.x,
								g_Shadow[ nCntShadow ].rot.z
			);
			D3DXMatrixMultiply(
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxRot
			);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(
								&g_Shadow[ nCntShadow ].mtxTrans,
								g_Shadow[ nCntShadow ].pos.x,
								g_Shadow[ nCntShadow ].pos.y,
								g_Shadow[ nCntShadow ].pos.z
			);
			D3DXMatrixMultiply(
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxWorld,
								&g_Shadow[ nCntShadow ].mtxTrans
			);

			//�����_�[�X�e�[�g�̐ݒ�
			pDevice -> SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
			pDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

			//���[���h�}�g���b�N�X��ݒ�
			pDevice -> SetTransform( D3DTS_WORLD, &g_Shadow[ nCntShadow ].mtxWorld );

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
			pDevice -> SetStreamSource( 0, g_Shadow[ nCntShadow ].pVtxBuff, 0, sizeof( VERTEX_3D ) );

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice -> SetFVF( FVF_VERTEX_3D );

			//�e�N�X�`���̐ݒ�
			pDevice -> SetTexture( 0, g_Shadow[ nCntShadow ].pTexture );

			//�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

			//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
			pDevice -> SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
			pDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		}
	}
}

/*******************************************************************************
* �֐���: �Z�b�g�V���h�[�̊֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void SetShadow( D3DXVECTOR3 pos, float fWIDTH, float fHEIGHT, int nCntShadow, bool bUse )
{
	float fScl;

	g_Shadow[ nCntShadow ].bUse = bUse;

	if( g_Shadow[ nCntShadow ].bUse == true )
	{
		//�g�嗦
		fScl = 1.0f + pos.y * 0.01f;

		g_Shadow[ nCntShadow ].pos = D3DXVECTOR3( pos.x, 0.01f, pos.z );	//�ʒu
		g_Shadow[ nCntShadow ].scl = D3DXVECTOR3( fScl, fScl, fScl );		//�g��k��

		//���_�o�b�t�@�̏�����
		VERTEX_3D *pVtx;

		g_Shadow[ nCntShadow ].pVtxBuff -> Lock( 0, 0, ( void** ) &pVtx, 0 );

		pVtx[ 0 ].pos = D3DXVECTOR3( -fWIDTH * 0.5f, 0.01f,  fHEIGHT * 0.5f );
		pVtx[ 1 ].pos = D3DXVECTOR3(  fWIDTH * 0.5f, 0.01f,  fHEIGHT * 0.5f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -fWIDTH * 0.5f, 0.01f, -fHEIGHT * 0.5f );
		pVtx[ 3 ].pos = D3DXVECTOR3(  fWIDTH * 0.5f, 0.01f, -fHEIGHT * 0.5f );

		//�@���̐ݒ�
		pVtx[ 0 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 1 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 2 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		pVtx[ 3 ].nor = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		//���_�J���[�̐ݒ�
		pVtx[ 0 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );
		pVtx[ 1 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );
		pVtx[ 2 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );
		pVtx[ 3 ].col = D3DCOLOR_RGBA( 125, 125, 125, 255 );

		//�e�N�X�`�����W�̐ݒ�
		pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

		g_Shadow[ nCntShadow ].pVtxBuff -> Unlock();
	}
}

/*******************************************************************************
* �֐���: �V���h�[�̎擾�֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
SHADOW *GetShadow( void )
{
	return &g_Shadow[ 0 ];
}