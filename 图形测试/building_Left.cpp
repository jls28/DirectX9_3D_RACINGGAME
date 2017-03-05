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
#include <time.h>
#include "main.h"
#include "building_Left.h"
#include "meshwall.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
BUILDING_LEFT g_aBuilding_Left[MAX_BUILDING_LEFT];		// �����̏��

//================================================================================================================================================================================================
// InitBuilding_Left�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitBuilding_Left( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESHWALL *pWall = GetMeshWall();
		for( int nCntBuilding_Left = 0; nCntBuilding_Left < MAX_BUILDING_LEFT; nCntBuilding_Left++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\building_Left.png",&g_aBuilding_Left[nCntBuilding_Left].pTextureBuilding_Left);// �e�N�X�`���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\building_Left.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left,		// �}�e���A�����
									   NULL,
									   &g_aBuilding_Left[nCntBuilding_Left].nNumMatBuilding_Left,			// �}�e���A����
									   &g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aBuilding_Left[nCntBuilding_Left].Min.x )		g_aBuilding_Left[nCntBuilding_Left].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aBuilding_Left[nCntBuilding_Left].Max.x )		g_aBuilding_Left[nCntBuilding_Left].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aBuilding_Left[nCntBuilding_Left].Min.y )		g_aBuilding_Left[nCntBuilding_Left].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aBuilding_Left[nCntBuilding_Left].Max.y )		g_aBuilding_Left[nCntBuilding_Left].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aBuilding_Left[nCntBuilding_Left].Min.z )		g_aBuilding_Left[nCntBuilding_Left].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aBuilding_Left[nCntBuilding_Left].Max.z )		g_aBuilding_Left[nCntBuilding_Left].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->UnlockVertexBuffer();

		// �����̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aBuilding_Left[nCntBuilding_Left].Size.x = ( fabs( g_aBuilding_Left[nCntBuilding_Left].Min.x ) + fabs( g_aBuilding_Left[nCntBuilding_Left].Max.x ) ) / 2;
		g_aBuilding_Left[nCntBuilding_Left].Size.y = ( fabs( g_aBuilding_Left[nCntBuilding_Left].Min.y ) + fabs( g_aBuilding_Left[nCntBuilding_Left].Max.y ) ) / 2;
		g_aBuilding_Left[nCntBuilding_Left].Size.z = ( fabs( g_aBuilding_Left[nCntBuilding_Left].Min.z ) + fabs( g_aBuilding_Left[nCntBuilding_Left].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aBuilding_Left[nCntBuilding_Left].Size.x < g_aBuilding_Left[nCntBuilding_Left].Size.z )
		{
			g_aBuilding_Left[nCntBuilding_Left].Collisoin = g_aBuilding_Left[nCntBuilding_Left].Size.z;
		}
		else
		{
			g_aBuilding_Left[nCntBuilding_Left].Collisoin = g_aBuilding_Left[nCntBuilding_Left].Size.x;
		}
		g_aBuilding_Left[nCntBuilding_Left].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aBuilding_Left[nCntBuilding_Left].Size.x,  0.0f, g_aBuilding_Left[nCntBuilding_Left].pos.z + (g_aBuilding_Left[nCntBuilding_Left].Size.z * nCntBuilding_Left)*2);
		g_aBuilding_Left[nCntBuilding_Left].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Left[nCntBuilding_Left].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aBuilding_Left[nCntBuilding_Left].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Left[nCntBuilding_Left].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );

		g_aBuilding_Left[nCntBuilding_Left].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitBuilding_Left�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitBuilding_Left( void )
{
	for( int nCntBuilding_Left = 0; nCntBuilding_Left <MAX_BUILDING_LEFT; nCntBuilding_Left++ )
	{
		// ���b�V�����̊J��
		if( g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left != NULL )
		{
			g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->Release();
			g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left != NULL )
		{
			g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left->Release();
			g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateBuilding_Left�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateBuilding_Left( void )
{

}
//================================================================================================================================================================================================
// DrawBuilding_Left�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawBuilding_Left( void )
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
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(3, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(4, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		for( int nCntBuilding_Left = 0; nCntBuilding_Left <MAX_BUILDING_LEFT; nCntBuilding_Left++ )
	{
		if(g_aBuilding_Left[nCntBuilding_Left].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aBuilding_Left[nCntBuilding_Left].scl.x, g_aBuilding_Left[nCntBuilding_Left].scl.y, g_aBuilding_Left[nCntBuilding_Left].scl.z );
		D3DXMatrixMultiply( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aBuilding_Left[nCntBuilding_Left].rot.y, g_aBuilding_Left[nCntBuilding_Left].rot.x, g_aBuilding_Left[nCntBuilding_Left].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aBuilding_Left[nCntBuilding_Left].pos.x, g_aBuilding_Left[nCntBuilding_Left].pos.y, g_aBuilding_Left[nCntBuilding_Left].pos.z );
		D3DXMatrixMultiply( &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left, &mtxTrans );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aBuilding_Left[nCntBuilding_Left].mtxWorldBuilding_Left );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aBuilding_Left[nCntBuilding_Left].pBuffMatBuilding_Left->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aBuilding_Left[nCntBuilding_Left].nNumMatBuilding_Left; nCntMat++ )
		{

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aBuilding_Left[nCntMat].pTextureBuilding_Left );

			// ���b�V���̕`��
			g_aBuilding_Left[nCntBuilding_Left].pMeshBuilding_Left->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// BUILDING_LEFT *GetBuilding_Left�֐�
// ���� void
// �߂�l 
// ���� Building_Left���擾����B
//================================================================================================================================================================================================
BUILDING_LEFT *GetBuilding_Left( void )
{
	return &g_aBuilding_Left[0];
}
