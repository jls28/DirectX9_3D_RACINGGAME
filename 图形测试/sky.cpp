/*******************************************************************************
* �^�C�g���F �����`��֐�
* �t�@�C�����F building_Left.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/11
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
//2015/11/20/14:09:37 // �����̈ړ� //
/*******************************************************************************
		�C���N���[�h�t�@�C��
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "sky.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
SKY g_aSky[MAX_SKY];		// �����̏��

//================================================================================================================================================================================================
// InitSky�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitSky( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
		for( int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\sky000.jpg",&g_aSky[nCntSky].pTextureSky);// �e�N�X�`���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\sky.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aSky[nCntSky].pBuffMatSky,		// �}�e���A�����
									   NULL,
									   &g_aSky[nCntSky].nNumMatSky,			// �}�e���A����
									   &g_aSky[nCntSky].pMeshSky ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aSky[nCntSky].pMeshSky->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aSky[nCntSky].pMeshSky->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aSky[nCntSky].pMeshSky->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aSky[nCntSky].Min.x )		g_aSky[nCntSky].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aSky[nCntSky].Max.x )		g_aSky[nCntSky].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aSky[nCntSky].Min.y )		g_aSky[nCntSky].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aSky[nCntSky].Max.y )		g_aSky[nCntSky].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aSky[nCntSky].Min.z )		g_aSky[nCntSky].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aSky[nCntSky].Max.z )		g_aSky[nCntSky].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aSky[nCntSky].pMeshSky->UnlockVertexBuffer();

		// �����̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aSky[nCntSky].Size.x = ( fabs( g_aSky[nCntSky].Min.x ) + fabs( g_aSky[nCntSky].Max.x ) ) / 2;
		g_aSky[nCntSky].Size.y = ( fabs( g_aSky[nCntSky].Min.y ) + fabs( g_aSky[nCntSky].Max.y ) ) / 2;
		g_aSky[nCntSky].Size.z = ( fabs( g_aSky[nCntSky].Min.z ) + fabs( g_aSky[nCntSky].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aSky[nCntSky].Size.x < g_aSky[nCntSky].Size.z )
		{
			g_aSky[nCntSky].Collisoin = g_aSky[nCntSky].Size.z;
		}
		else
		{
			g_aSky[nCntSky].Collisoin = g_aSky[nCntSky].Size.x;
		}
		g_aSky[nCntSky].pos = D3DXVECTOR3( 0.0f,  -500.0f, 100000.0f );
		g_aSky[nCntSky].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aSky[nCntSky].scl = D3DXVECTOR3( 5.f,  5.0f, 5.0f );
		g_aSky[nCntSky].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aSky[nCntSky].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );

		g_aSky[nCntSky].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitSky�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitSky( void )
{
	for( int nCntSky = 0; nCntSky <MAX_SKY; nCntSky++ )
	{
		// ���b�V�����̊J��
		if( g_aSky[nCntSky].pMeshSky != NULL )
		{
			g_aSky[nCntSky].pMeshSky->Release();
			g_aSky[nCntSky].pMeshSky = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aSky[nCntSky].pBuffMatSky != NULL )
		{
			g_aSky[nCntSky].pBuffMatSky->Release();
			g_aSky[nCntSky].pBuffMatSky = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateSky�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateSky( void )
{

}
//================================================================================================================================================================================================
// DrawSky�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawSky( void )
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
		for( int nCntSky = 0; nCntSky <MAX_SKY; nCntSky++ )
	{
		if(g_aSky[nCntSky].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aSky[nCntSky].mtxWorldSky );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aSky[nCntSky].scl.x, g_aSky[nCntSky].scl.y, g_aSky[nCntSky].scl.z );
		D3DXMatrixMultiply( &g_aSky[nCntSky].mtxWorldSky, &g_aSky[nCntSky].mtxWorldSky, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aSky[nCntSky].rot.y, g_aSky[nCntSky].rot.x, g_aSky[nCntSky].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aSky[nCntSky].mtxWorldSky, &g_aSky[nCntSky].mtxWorldSky, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aSky[nCntSky].pos.x, g_aSky[nCntSky].pos.y, g_aSky[nCntSky].pos.z );
		D3DXMatrixMultiply( &g_aSky[nCntSky].mtxWorldSky, &g_aSky[nCntSky].mtxWorldSky, &mtxTrans );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aSky[nCntSky].mtxWorldSky );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aSky[nCntSky].pBuffMatSky->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aSky[nCntSky].nNumMatSky; nCntMat++ )
		{
			pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
			pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
			pDevice->SetTexture( 1 , NULL );
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aSky[nCntMat].pTextureSky );

			// ���b�V���̕`��
			g_aSky[nCntSky].pMeshSky->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// SKY *GetSky�֐�
// ���� void
// �߂�l 
// ���� Sky���擾����B
//================================================================================================================================================================================================
SKY *GetSky( void )
{
	return &g_aSky[0];
}
