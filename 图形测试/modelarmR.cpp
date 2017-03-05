/*******************************************************************************
* �^�C�g���F ���f��body�`��֐�
* �t�@�C�����F modelarmR.cpp
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
#include "modelarmR.h"
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
#define MODELARMR_INERTIA_MOVE	( 0.025f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELARMR g_aModelarmR[ MAX_MODELARMR ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelarmR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelarmR( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelarmR.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR,		// �}�e���A�����
									   NULL,
									   &g_aModelarmR[ nCntModelarmR ].nNumMatModelarmR,			// �}�e���A����
									   &g_aModelarmR[ nCntModelarmR ].pMeshModelarmR ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelarmR[ nCntModelarmR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelarmR[ nCntModelarmR ].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmR[ nCntModelarmR ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelarmR[ nCntModelarmR ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmR[ nCntModelarmR ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmR[ nCntModelarmR ].fPosMove = POSMOVE_MODELARMR;
		g_aModelarmR[ nCntModelarmR ].fAngle = 0.0f;
		g_aModelarmR[ nCntModelarmR ].propR = 1.0f;		//���a
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelarmR[ nCntModelarmR ].Min.x )		g_aModelarmR[ nCntModelarmR ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelarmR[ nCntModelarmR ].Max.x )		g_aModelarmR[ nCntModelarmR ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelarmR[ nCntModelarmR ].Min.y )		g_aModelarmR[ nCntModelarmR ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelarmR[ nCntModelarmR ].Max.y )		g_aModelarmR[ nCntModelarmR ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelarmR[ nCntModelarmR ].Min.z )		g_aModelarmR[ nCntModelarmR ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelarmR[ nCntModelarmR ].Max.z )		g_aModelarmR[ nCntModelarmR ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelarmR[ nCntModelarmR ].Size.x = ( fabs( g_aModelarmR[ nCntModelarmR ].Min.x ) + fabs( g_aModelarmR[ nCntModelarmR ].Max.x ) ) / 2;
		g_aModelarmR[ nCntModelarmR ].Size.y = ( fabs( g_aModelarmR[ nCntModelarmR ].Min.y ) + fabs( g_aModelarmR[ nCntModelarmR ].Max.y ) ) / 2;
		g_aModelarmR[ nCntModelarmR ].Size.z = ( fabs( g_aModelarmR[ nCntModelarmR ].Min.z ) + fabs( g_aModelarmR[ nCntModelarmR ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelarmR[ nCntModelarmR ].Size.x < g_aModelarmR[ nCntModelarmR ].Size.z )
		{
			g_aModelarmR[ nCntModelarmR ].Collisoin = g_aModelarmR[ nCntModelarmR ].Size.z;
		}
		else
		{
			g_aModelarmR[ nCntModelarmR ].Collisoin = g_aModelarmR[ nCntModelarmR ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelarmR[ nCntModelarmR ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelarmR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelarmR( void )
{
	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++ )
	{
		// ���b�V�����̊J��
		if( g_aModelarmR[ nCntModelarmR ].pMeshModelarmR != NULL )
		{
			g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->Release();
			g_aModelarmR[ nCntModelarmR ].pMeshModelarmR = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR != NULL )
		{
			g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR->Release();
			g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelarmR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelarmR( void )
{
	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelarmR_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelarmR_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelarmR_03 = GetPropModel_03 ();


	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelarmR[ nCntModelarmR ].pos.x = pModelBody->pos.x ;
			g_aModelarmR[ nCntModelarmR ].pos.z = pModelBody->pos.z ;
			g_aModelarmR[ nCntModelarmR ].pos.y = pModelBody->pos.y+ g_aModelarmR[ nCntModelarmR ].propR * sinf( g_aModelarmR[ nCntModelarmR ].fAngle );
			g_aModelarmR[ nCntModelarmR ].fAngle += 20.0f * D3DX_PI / 120.0f;					// �p�̌ʂ𑝂���

		g_aModelarmR[ nCntModelarmR ].pos = D3DXVECTOR3( g_aModelarmR[ nCntModelarmR ].pos.x, g_aModelarmR[ nCntModelarmR ].pos.y, g_aModelarmR[ nCntModelarmR ].pos.z );
		g_aModelarmR[ nCntModelarmR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelarmR[ nCntModelarmR ].pos = D3DXVECTOR3( pModelBody->pos.x,pModelBody->pos.y,pModelBody->pos.z );
		g_aModelarmR[ nCntModelarmR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelarmR[ nCntModelarmR ].OldPos.x - g_aModelarmR[ nCntModelarmR ].Collisoin ) )
		{	// ���̕�
			g_aModelarmR[ nCntModelarmR ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelarmR[ nCntModelarmR ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelarmR[ nCntModelarmR ].OldPos.x + g_aModelarmR[ nCntModelarmR ].Collisoin ) )
		{	// �E�̕�
			g_aModelarmR[ nCntModelarmR ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelarmR[ nCntModelarmR ].Collisoin;
		}
		if(( g_aModelarmR[ nCntModelarmR ].OldPos.z - g_aModelarmR[ nCntModelarmR ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelarmR[ nCntModelarmR ].OldPos.z = 20550.0f + g_aModelarmR[ nCntModelarmR ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}

	}

}

//================================================================================================================================================================================================
// DrawModelarmR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelarmR( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntModelarmR = 0; nCntModelarmR < MAX_MODELARMR; nCntModelarmR++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelarmR[ nCntModelarmR ].scl.x, g_aModelarmR[ nCntModelarmR ].scl.y, g_aModelarmR[ nCntModelarmR ].scl.z );
		D3DXMatrixMultiply( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelarmR[ nCntModelarmR ].rot.y, g_aModelarmR[ nCntModelarmR ].rot.x, g_aModelarmR[ nCntModelarmR ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelarmR[ nCntModelarmR ].pos.x, g_aModelarmR[ nCntModelarmR ].pos.y, g_aModelarmR[ nCntModelarmR ].pos.z );
		D3DXMatrixMultiply( &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelarmR[ nCntModelarmR ].mtxWorldModelarmR );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelarmR[ nCntModelarmR ].pBuffMatModelarmR->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelarmR[ nCntModelarmR ].nNumMatModelarmR; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelarmR[ nCntModelarmR ].pMeshModelarmR->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelarmR�֐�
// ���� void
// �߂�l 
// ���� ModelarmR���擾����B
//================================================================================================================================================================================================
MODELARMR *GetModelarmR( void )
{
	return &g_aModelarmR[ 0 ];
}
