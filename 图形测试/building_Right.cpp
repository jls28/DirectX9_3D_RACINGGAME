/*******************************************************************************
* �^�C�g���F �����`��֐�
* �t�@�C�����F building_Right.cpp
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
#include "building_Right.h"
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
BUILDING_RIGHT g_aBuilding_Right[MAX_BUILDING_RIGHT];		// �����̏��

//================================================================================================================================================================================================
// InitBuilding_Right�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitBuilding_Right( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESHWALL *pWall = GetMeshWall();
		for( int nCntBuilding_Right = 0; nCntBuilding_Right < MAX_BUILDING_RIGHT; nCntBuilding_Right++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\building_Left.png",&g_aBuilding_Right[nCntBuilding_Right].pTextureBuilding_Right);// �e�N�X�`���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\building_Left.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right,		// �}�e���A�����
									   NULL,
									   &g_aBuilding_Right[nCntBuilding_Right].nNumMatBuilding_Right,			// �}�e���A����
									   &g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aBuilding_Right[nCntBuilding_Right].Min.x )		g_aBuilding_Right[nCntBuilding_Right].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aBuilding_Right[nCntBuilding_Right].Max.x )		g_aBuilding_Right[nCntBuilding_Right].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aBuilding_Right[nCntBuilding_Right].Min.y )		g_aBuilding_Right[nCntBuilding_Right].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aBuilding_Right[nCntBuilding_Right].Max.y )		g_aBuilding_Right[nCntBuilding_Right].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aBuilding_Right[nCntBuilding_Right].Min.z )		g_aBuilding_Right[nCntBuilding_Right].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aBuilding_Right[nCntBuilding_Right].Max.z )		g_aBuilding_Right[nCntBuilding_Right].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->UnlockVertexBuffer();

		// �����̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aBuilding_Right[nCntBuilding_Right].Size.x = ( fabs( g_aBuilding_Right[nCntBuilding_Right].Min.x ) + fabs( g_aBuilding_Right[nCntBuilding_Right].Max.x ) ) / 2;
		g_aBuilding_Right[nCntBuilding_Right].Size.y = ( fabs( g_aBuilding_Right[nCntBuilding_Right].Min.y ) + fabs( g_aBuilding_Right[nCntBuilding_Right].Max.y ) ) / 2;
		g_aBuilding_Right[nCntBuilding_Right].Size.z = ( fabs( g_aBuilding_Right[nCntBuilding_Right].Min.z ) + fabs( g_aBuilding_Right[nCntBuilding_Right].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aBuilding_Right[nCntBuilding_Right].Size.x < g_aBuilding_Right[nCntBuilding_Right].Size.z )
		{
			g_aBuilding_Right[nCntBuilding_Right].Collisoin = g_aBuilding_Right[nCntBuilding_Right].Size.z;
		}
		else
		{
			g_aBuilding_Right[nCntBuilding_Right].Collisoin = g_aBuilding_Right[nCntBuilding_Right].Size.x;
		}
		g_aBuilding_Right[nCntBuilding_Right].pos = D3DXVECTOR3( (pWall + WALL_RIGHT)->pos.x + g_aBuilding_Right[nCntBuilding_Right].Size.x,  0.0f, g_aBuilding_Right[nCntBuilding_Right].pos.z + (g_aBuilding_Right[nCntBuilding_Right].Size.z * nCntBuilding_Right)*2);
		g_aBuilding_Right[nCntBuilding_Right].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Right[nCntBuilding_Right].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aBuilding_Right[nCntBuilding_Right].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aBuilding_Right[nCntBuilding_Right].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );

		g_aBuilding_Right[nCntBuilding_Right].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitBuilding_Right�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitBuilding_Right( void )
{
	for( int nCntBuilding_Right = 0; nCntBuilding_Right <MAX_BUILDING_RIGHT; nCntBuilding_Right++ )
	{
		// ���b�V�����̊J��
		if( g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right != NULL )
		{
			g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->Release();
			g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right != NULL )
		{
			g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right->Release();
			g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateBuilding_Right�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateBuilding_Right( void )
{

}
//================================================================================================================================================================================================
// DrawBuilding_Right�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawBuilding_Right( void )
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
		for( int nCntBuilding_Right = 0; nCntBuilding_Right <MAX_BUILDING_RIGHT; nCntBuilding_Right++ )
	{
		if(g_aBuilding_Right[nCntBuilding_Right].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aBuilding_Right[nCntBuilding_Right].scl.x, g_aBuilding_Right[nCntBuilding_Right].scl.y, g_aBuilding_Right[nCntBuilding_Right].scl.z );
		D3DXMatrixMultiply( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aBuilding_Right[nCntBuilding_Right].rot.y, g_aBuilding_Right[nCntBuilding_Right].rot.x, g_aBuilding_Right[nCntBuilding_Right].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aBuilding_Right[nCntBuilding_Right].pos.x, g_aBuilding_Right[nCntBuilding_Right].pos.y, g_aBuilding_Right[nCntBuilding_Right].pos.z );
		D3DXMatrixMultiply( &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right, &mtxTrans );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aBuilding_Right[nCntBuilding_Right].mtxWorldBuilding_Right );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aBuilding_Right[nCntBuilding_Right].pBuffMatBuilding_Right->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aBuilding_Right[nCntBuilding_Right].nNumMatBuilding_Right; nCntMat++ )
		{

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aBuilding_Right[nCntMat].pTextureBuilding_Right );

			// ���b�V���̕`��
			g_aBuilding_Right[nCntBuilding_Right].pMeshBuilding_Right->DrawSubset( nCntMat );

		}

		}
	}
}

//================================================================================================================================================================================================
// BUILDING_RIGHT *GetBuilding_Right�֐�
// ���� void
// �߂�l 
// ���� Building_Right���擾����B
//================================================================================================================================================================================================
BUILDING_RIGHT *GetBuilding_Right( void )
{
	return &g_aBuilding_Right[0];
}
