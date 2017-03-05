/*******************************************************************************
* �^�C�g���F ���f��body�`��֐�
* �t�@�C�����F modellegR.cpp
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
#include "modelLegR.h"
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
#define MODELLEGR_INERTIA_MOVE	( 0.025f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELLEGR g_aModelLegR[ MAX_MODELLEGR ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelLegR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelLegR( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modellegR.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR,		// �}�e���A�����
									   NULL,
									   &g_aModelLegR[ nCntModelLegR ].nNumMatModelLegR,			// �}�e���A����
									   &g_aModelLegR[ nCntModelLegR ].pMeshModelLegR ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelLegR[ nCntModelLegR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegR[ nCntModelLegR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelLegR[ nCntModelLegR ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelLegR[ nCntModelLegR ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegR[ nCntModelLegR ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelLegR[ nCntModelLegR ].fPosMove = POSMOVE_MODELLEGR;
		g_aModelLegR[ nCntModelLegR ].fAngle = 0.0f;
		g_aModelLegR[ nCntModelLegR ].propR = 1.0f;		//���a
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelLegR[ nCntModelLegR ].Min.x )		g_aModelLegR[ nCntModelLegR ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelLegR[ nCntModelLegR ].Max.x )		g_aModelLegR[ nCntModelLegR ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelLegR[ nCntModelLegR ].Min.y )		g_aModelLegR[ nCntModelLegR ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelLegR[ nCntModelLegR ].Max.y )		g_aModelLegR[ nCntModelLegR ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelLegR[ nCntModelLegR ].Min.z )		g_aModelLegR[ nCntModelLegR ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelLegR[ nCntModelLegR ].Max.z )		g_aModelLegR[ nCntModelLegR ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelLegR[ nCntModelLegR ].Size.x = ( fabs( g_aModelLegR[ nCntModelLegR ].Min.x ) + fabs( g_aModelLegR[ nCntModelLegR ].Max.x ) ) / 2;
		g_aModelLegR[ nCntModelLegR ].Size.y = ( fabs( g_aModelLegR[ nCntModelLegR ].Min.y ) + fabs( g_aModelLegR[ nCntModelLegR ].Max.y ) ) / 2;
		g_aModelLegR[ nCntModelLegR ].Size.z = ( fabs( g_aModelLegR[ nCntModelLegR ].Min.z ) + fabs( g_aModelLegR[ nCntModelLegR ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelLegR[ nCntModelLegR ].Size.x < g_aModelLegR[ nCntModelLegR ].Size.z )
		{
			g_aModelLegR[ nCntModelLegR ].Collisoin = g_aModelLegR[ nCntModelLegR ].Size.z;
		}
		else
		{
			g_aModelLegR[ nCntModelLegR ].Collisoin = g_aModelLegR[ nCntModelLegR ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelLegR[ nCntModelLegR ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelLegR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelLegR( void )
{
	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++ )
	{
		// ���b�V�����̊J��
		if( g_aModelLegR[ nCntModelLegR ].pMeshModelLegR != NULL )
		{
			g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->Release();
			g_aModelLegR[ nCntModelLegR ].pMeshModelLegR = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR != NULL )
		{
			g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR->Release();
			g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelLegR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelLegR( void )
{


	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelLegR_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelLegR_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelLegR_03 = GetPropModel_03 ();

	MODELBODY *pModelBody = GetModelBody();

	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelLegR[ nCntModelLegR ].pos.x = pModelBody->pos.x ;
			g_aModelLegR[ nCntModelLegR ].pos.z = pModelBody->pos.z ;
			g_aModelLegR[ nCntModelLegR ].pos.y = pModelBody->pos.y+ g_aModelLegR[ nCntModelLegR ].propR * sinf( g_aModelLegR[ nCntModelLegR ].fAngle );
			g_aModelLegR[ nCntModelLegR ].fAngle += 20.0f * D3DX_PI / 120.0f;					// �p�̌ʂ𑝂���

		g_aModelLegR[ nCntModelLegR ].pos = D3DXVECTOR3( g_aModelLegR[ nCntModelLegR ].pos.x, g_aModelLegR[ nCntModelLegR ].pos.y, g_aModelLegR[ nCntModelLegR ].pos.z );
		g_aModelLegR[ nCntModelLegR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelLegR[ nCntModelLegR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelLegR[ nCntModelLegR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelLegR[ nCntModelLegR ].OldPos.x - g_aModelLegR[ nCntModelLegR ].Collisoin ) )
		{	// ���̕�
			g_aModelLegR[ nCntModelLegR ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelLegR[ nCntModelLegR ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelLegR[ nCntModelLegR ].pos.x + g_aModelLegR[ nCntModelLegR ].Collisoin ) )
		{	// �E�̕�
			g_aModelLegR[ nCntModelLegR ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelLegR[ nCntModelLegR ].Collisoin;
		}
		if(( g_aModelLegR[ nCntModelLegR ].OldPos.z - g_aModelLegR[ nCntModelLegR ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelLegR[ nCntModelLegR ].OldPos.z = 20550.0f + g_aModelLegR[ nCntModelLegR ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}
	}

}

//================================================================================================================================================================================================
// DrawModelLegR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelLegR( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntModelLegR = 0; nCntModelLegR < MAX_MODELLEGR; nCntModelLegR++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelLegR[ nCntModelLegR ].scl.x, g_aModelLegR[ nCntModelLegR ].scl.y, g_aModelLegR[ nCntModelLegR ].scl.z );
		D3DXMatrixMultiply( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelLegR[ nCntModelLegR ].rot.y, g_aModelLegR[ nCntModelLegR ].rot.x, g_aModelLegR[ nCntModelLegR ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelLegR[ nCntModelLegR ].pos.x, g_aModelLegR[ nCntModelLegR ].pos.y, g_aModelLegR[ nCntModelLegR ].pos.z );
		D3DXMatrixMultiply( &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelLegR[ nCntModelLegR ].mtxWorldModelLegR );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelLegR[ nCntModelLegR ].pBuffMatModelLegR->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelLegR[ nCntModelLegR ].nNumMatModelLegR; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelLegR[ nCntModelLegR ].pMeshModelLegR->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelLegR�֐�
// ���� void
// �߂�l 
// ���� ModelLegR���擾����B
//================================================================================================================================================================================================
MODELLEGR *GetModelLegR( void )
{
	return &g_aModelLegR[ 0 ];
}
