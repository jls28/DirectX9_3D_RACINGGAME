/*******************************************************************************
* �^�C�g���F ���f��body�`��֐�
* �t�@�C�����F modellegL.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/08
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
//2016-2-8 09:40:06
/*******************************************************************************
		�C���N���[�h�t�@�C��
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "modelLegL.h"
#include "camera.h"
#include "meshWall.h"
#include "meshField.h"
#include "bullet.h"
#include "shadow.h"
#include "use.h"
#include "effect.h"
#include "prop.h"
#include "propshow.h"
#include "propmodel_Group.h"
#include "propmp.h"
#include "propmplife.h"
#include "propmpmax.h"
#include "modelbody.h"
#include "fade.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MODELLEGL_INERTIA_MOVE	( 0.025f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELLEGL g_aModelLegL[ MAX_MODELLEGL ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelLegL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelLegL( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modellegL.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL,		// �}�e���A�����
									   NULL,
									   &g_aModelLegL[ nCntModelLegL ].nNumMatModelLegL,			// �}�e���A����
									   &g_aModelLegL[ nCntModelLegL ].pMeshModelLegL ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelLegL[ nCntModelLegL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegL[ nCntModelLegL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelLegL[ nCntModelLegL ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelLegL[ nCntModelLegL ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegL[ nCntModelLegL ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegL[ nCntModelLegL ].fPosMove = POSMOVE_MODELLEGL;
		g_aModelLegL[ nCntModelLegL ].fAngle = 0.0f;
		g_aModelLegL[ nCntModelLegL ].propR = 1.0f;		//���a
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelLegL[ nCntModelLegL ].Min.x )		g_aModelLegL[ nCntModelLegL ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelLegL[ nCntModelLegL ].Max.x )		g_aModelLegL[ nCntModelLegL ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelLegL[ nCntModelLegL ].Min.y )		g_aModelLegL[ nCntModelLegL ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelLegL[ nCntModelLegL ].Max.y )		g_aModelLegL[ nCntModelLegL ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelLegL[ nCntModelLegL ].Min.z )		g_aModelLegL[ nCntModelLegL ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelLegL[ nCntModelLegL ].Max.z )		g_aModelLegL[ nCntModelLegL ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelLegL[ nCntModelLegL ].Size.x = ( fabs( g_aModelLegL[ nCntModelLegL ].Min.x ) + fabs( g_aModelLegL[ nCntModelLegL ].Max.x ) ) / 2;
		g_aModelLegL[ nCntModelLegL ].Size.y = ( fabs( g_aModelLegL[ nCntModelLegL ].Min.y ) + fabs( g_aModelLegL[ nCntModelLegL ].Max.y ) ) / 2;
		g_aModelLegL[ nCntModelLegL ].Size.z = ( fabs( g_aModelLegL[ nCntModelLegL ].Min.z ) + fabs( g_aModelLegL[ nCntModelLegL ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelLegL[ nCntModelLegL ].Size.x < g_aModelLegL[ nCntModelLegL ].Size.z )
		{
			g_aModelLegL[ nCntModelLegL ].Collisoin = g_aModelLegL[ nCntModelLegL ].Size.z;
		}
		else
		{
			g_aModelLegL[ nCntModelLegL ].Collisoin = g_aModelLegL[ nCntModelLegL ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelLegL[ nCntModelLegL ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelLegL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelLegL( void )
{
	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++ )
	{
		// ���b�V�����̊J��
		if( g_aModelLegL[ nCntModelLegL ].pMeshModelLegL != NULL )
		{
			g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->Release();
			g_aModelLegL[ nCntModelLegL ].pMeshModelLegL = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL != NULL )
		{
			g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL->Release();
			g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelLegL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelLegL( void )
{

	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelLegL_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelLegL_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelLegL_03 = GetPropModel_03 ();

	MODELBODY *pModelBody = GetModelBody();

	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelLegL[ nCntModelLegL ].pos.x = pModelBody->pos.x ;
			g_aModelLegL[ nCntModelLegL ].pos.z = pModelBody->pos.z ;
			g_aModelLegL[ nCntModelLegL ].pos.y = pModelBody->pos.y+ g_aModelLegL[ nCntModelLegL ].propR * sinf( g_aModelLegL[ nCntModelLegL ].fAngle );
			g_aModelLegL[ nCntModelLegL ].fAngle += 20.0f * D3DX_PI / 120.0f;					// �p�̌ʂ𑝂���

		g_aModelLegL[ nCntModelLegL ].pos = D3DXVECTOR3( g_aModelLegL[ nCntModelLegL ].pos.x, g_aModelLegL[ nCntModelLegL ].pos.y, g_aModelLegL[ nCntModelLegL ].pos.z );
		g_aModelLegL[ nCntModelLegL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelLegL[ nCntModelLegL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegL[ nCntModelLegL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelLegL[ nCntModelLegL ].OldPos.x - g_aModelLegL[ nCntModelLegL ].Collisoin ) )
		{	// ���̕�
			g_aModelLegL[ nCntModelLegL ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelLegL[ nCntModelLegL ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelLegL[ nCntModelLegL ].OldPos.x + g_aModelLegL[ nCntModelLegL ].Collisoin ) )
		{	// �E�̕�
			g_aModelLegL[ nCntModelLegL ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelLegL[ nCntModelLegL ].Collisoin;
		}
		if(( g_aModelLegL[ nCntModelLegL ].OldPos.z - g_aModelLegL[ nCntModelLegL ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelLegL[ nCntModelLegL ].OldPos.z = 20550.0f + g_aModelLegL[ nCntModelLegL ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}

	}

}

//================================================================================================================================================================================================
// DrawModelLegL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelLegL( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntModelLegL = 0; nCntModelLegL < MAX_MODELLEGL; nCntModelLegL++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelLegL[ nCntModelLegL ].scl.x, g_aModelLegL[ nCntModelLegL ].scl.y, g_aModelLegL[ nCntModelLegL ].scl.z );
		D3DXMatrixMultiply( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelLegL[ nCntModelLegL ].rot.y, g_aModelLegL[ nCntModelLegL ].rot.x, g_aModelLegL[ nCntModelLegL ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelLegL[ nCntModelLegL ].pos.x, g_aModelLegL[ nCntModelLegL ].pos.y, g_aModelLegL[ nCntModelLegL ].pos.z );
		D3DXMatrixMultiply( &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelLegL[ nCntModelLegL ].mtxWorldModelLegL );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelLegL[ nCntModelLegL ].pBuffMatModelLegL->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelLegL[ nCntModelLegL ].nNumMatModelLegL; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelLegL[ nCntModelLegL ].pMeshModelLegL->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelLegL�֐�
// ���� void
// �߂�l 
// ���� ModelLegL���擾����B
//================================================================================================================================================================================================
MODELLEGL *GetModelLegL( void )
{
	return &g_aModelLegL[ 0 ];
}
