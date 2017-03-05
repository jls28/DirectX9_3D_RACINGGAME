/*******************************************************************************
* �^�C�g���F ����SHOP�`��֐�
* �t�@�C�����F Shop.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/15
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
//2015/11/20/14:09:37 // ����SHOP�̈ړ� //
/*******************************************************************************
		�C���N���[�h�t�@�C��
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "Shop.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
SHOP g_aShop[MAX_SHOP];		// ����SHOP�̏��

//================================================================================================================================================================================================
// InitShop�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitShop( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
		for( int nCntShop = 0; nCntShop < MAX_SHOP; nCntShop++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\shop.jpg",&g_aShop[nCntShop].pTextureShop);// �e�N�X�`���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\shop.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aShop[nCntShop].pBuffMatShop,		// �}�e���A�����
									   NULL,
									   &g_aShop[nCntShop].nNumMatShop,			// �}�e���A����
									   &g_aShop[nCntShop].pMeshShop ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aShop[nCntShop].pMeshShop->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aShop[nCntShop].pMeshShop->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aShop[nCntShop].pMeshShop->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aShop[nCntShop].Min.x )		g_aShop[nCntShop].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aShop[nCntShop].Max.x )		g_aShop[nCntShop].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aShop[nCntShop].Min.y )		g_aShop[nCntShop].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aShop[nCntShop].Max.y )		g_aShop[nCntShop].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aShop[nCntShop].Min.z )		g_aShop[nCntShop].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aShop[nCntShop].Max.z )		g_aShop[nCntShop].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aShop[nCntShop].pMeshShop->UnlockVertexBuffer();

		// ����SHOP�̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aShop[nCntShop].Size.x = ( fabs( g_aShop[nCntShop].Min.x ) + fabs( g_aShop[nCntShop].Max.x ) ) / 2;
		g_aShop[nCntShop].Size.y = ( fabs( g_aShop[nCntShop].Min.y ) + fabs( g_aShop[nCntShop].Max.y ) ) / 2;
		g_aShop[nCntShop].Size.z = ( fabs( g_aShop[nCntShop].Min.z ) + fabs( g_aShop[nCntShop].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aShop[nCntShop].Size.x < g_aShop[nCntShop].Size.z )
		{
			g_aShop[nCntShop].Collisoin = g_aShop[nCntShop].Size.z;
		}
		else
		{
			g_aShop[nCntShop].Collisoin = g_aShop[nCntShop].Size.x;
		}
		g_aShop[nCntShop].pos = D3DXVECTOR3( 0.0f,0.0f,20550.0f);
		g_aShop[nCntShop].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aShop[nCntShop].scl = D3DXVECTOR3( 0.8f,  3.0f, 2.0f );
		g_aShop[nCntShop].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aShop[nCntShop].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		
		g_aShop[nCntShop].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitShop�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitShop( void )
{
	for( int nCntShop = 0; nCntShop <MAX_SHOP; nCntShop++ )
	{
		// ���b�V�����̊J��
		if( g_aShop[nCntShop].pMeshShop != NULL )
		{
			g_aShop[nCntShop].pMeshShop->Release();
			g_aShop[nCntShop].pMeshShop = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aShop[nCntShop].pBuffMatShop != NULL )
		{
			g_aShop[nCntShop].pBuffMatShop->Release();
			g_aShop[nCntShop].pBuffMatShop = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateShop�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateShop( void )
{

}
//================================================================================================================================================================================================
// DrawShop�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawShop( void )
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );
	//���f���ɔ����ɂȂ�̖��@�R�[�h
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
		for( int nCntShop = 0; nCntShop <MAX_SHOP; nCntShop++ )
	{
		if(g_aShop[nCntShop].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aShop[nCntShop].mtxWorldShop );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aShop[nCntShop].scl.x, g_aShop[nCntShop].scl.y, g_aShop[nCntShop].scl.z );
		D3DXMatrixMultiply( &g_aShop[nCntShop].mtxWorldShop, &g_aShop[nCntShop].mtxWorldShop, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aShop[nCntShop].rot.y, g_aShop[nCntShop].rot.x, g_aShop[nCntShop].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aShop[nCntShop].mtxWorldShop, &g_aShop[nCntShop].mtxWorldShop, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aShop[nCntShop].pos.x, g_aShop[nCntShop].pos.y, g_aShop[nCntShop].pos.z );
		D3DXMatrixMultiply( &g_aShop[nCntShop].mtxWorldShop, &g_aShop[nCntShop].mtxWorldShop, &mtxTrans );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aShop[nCntShop].mtxWorldShop );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aShop[nCntShop].pBuffMatShop->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aShop[nCntShop].nNumMatShop; nCntMat++ )
		{

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aShop[nCntMat].pTextureShop );

			// ���b�V���̕`��
			g_aShop[nCntShop].pMeshShop->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// SHOP *GetShop�֐�
// ���� void
// �߂�l 
// ���� Shop���擾����B
//================================================================================================================================================================================================
SHOP *GetShop( void )
{
	return &g_aShop[0];
}
