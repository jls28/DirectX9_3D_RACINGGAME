/*******************************************************************************
* �^�C�g���F ���f��body�`��֐�
* �t�@�C�����F modelhandL.cpp
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
#include "modelhandL.h"
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
#include "modelarmL.h"
#include "fade.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MODELHANDL_INERTIA_MOVE	( 0.025f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELHANDL g_aModelHandL[ MAX_MODELHANDL ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelHandL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelHandL( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelhandL.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL,		// �}�e���A�����
									   NULL,
									   &g_aModelHandL[ nCntModelHandL ].nNumMatModelHandL,			// �}�e���A����
									   &g_aModelHandL[ nCntModelHandL ].pMeshModelHandL ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelHandL[ nCntModelHandL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelHandL[ nCntModelHandL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelHandL[ nCntModelHandL ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelHandL[ nCntModelHandL ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandL[ nCntModelHandL ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandL[ nCntModelHandL ].fPosMove = POSMOVE_MODELHANDL;
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelHandL[ nCntModelHandL ].Min.x )		g_aModelHandL[ nCntModelHandL ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelHandL[ nCntModelHandL ].Max.x )		g_aModelHandL[ nCntModelHandL ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelHandL[ nCntModelHandL ].Min.y )		g_aModelHandL[ nCntModelHandL ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelHandL[ nCntModelHandL ].Max.y )		g_aModelHandL[ nCntModelHandL ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelHandL[ nCntModelHandL ].Min.z )		g_aModelHandL[ nCntModelHandL ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelHandL[ nCntModelHandL ].Max.z )		g_aModelHandL[ nCntModelHandL ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelHandL[ nCntModelHandL ].Size.x = ( fabs( g_aModelHandL[ nCntModelHandL ].Min.x ) + fabs( g_aModelHandL[ nCntModelHandL ].Max.x ) ) / 2;
		g_aModelHandL[ nCntModelHandL ].Size.y = ( fabs( g_aModelHandL[ nCntModelHandL ].Min.y ) + fabs( g_aModelHandL[ nCntModelHandL ].Max.y ) ) / 2;
		g_aModelHandL[ nCntModelHandL ].Size.z = ( fabs( g_aModelHandL[ nCntModelHandL ].Min.z ) + fabs( g_aModelHandL[ nCntModelHandL ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelHandL[ nCntModelHandL ].Size.x < g_aModelHandL[ nCntModelHandL ].Size.z )
		{
			g_aModelHandL[ nCntModelHandL ].Collisoin = g_aModelHandL[ nCntModelHandL ].Size.z;
		}
		else
		{
			g_aModelHandL[ nCntModelHandL ].Collisoin = g_aModelHandL[ nCntModelHandL ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelHandL[ nCntModelHandL ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelHandL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelHandL( void )
{
	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++ )
	{
		// ���b�V�����̊J��
		if( g_aModelHandL[ nCntModelHandL ].pMeshModelHandL != NULL )
		{
			g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->Release();
			g_aModelHandL[ nCntModelHandL ].pMeshModelHandL = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL != NULL )
		{
			g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL->Release();
			g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelHandL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelHandL( void )
{
//	srand((unsigned)time(NULL));

	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelHandL_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelHandL_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelHandL_03 = GetPropModel_03 ();

	MODELARML *pModelArmL = GetModelarmL();

	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++)
	{
		if(pModelBody->bKeyUse == true)
		{
		g_aModelHandL[ nCntModelHandL ].pos = D3DXVECTOR3(  pModelBody->pos.x, pModelArmL->pos.y,  pModelBody->pos.z );
		g_aModelHandL[ nCntModelHandL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelHandL[ nCntModelHandL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelHandL[ nCntModelHandL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelHandL[ nCntModelHandL ].OldPos.x - g_aModelHandL[ nCntModelHandL ].Collisoin ) )
		{	// ���̕�
			g_aModelHandL[ nCntModelHandL ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelHandL[ nCntModelHandL ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelHandL[ nCntModelHandL ].OldPos.x + g_aModelHandL[ nCntModelHandL ].Collisoin ) )
		{	// �E�̕�
			g_aModelHandL[ nCntModelHandL ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelHandL[ nCntModelHandL ].Collisoin;
		}
		if(( g_aModelHandL[ nCntModelHandL ].OldPos.z - g_aModelHandL[ nCntModelHandL ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelHandL[ nCntModelHandL ].OldPos.z = 20550.0f + g_aModelHandL[ nCntModelHandL ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}

	}

}

//================================================================================================================================================================================================
// DrawModelHandL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelHandL( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntModelHandL = 0; nCntModelHandL < MAX_MODELHANDL; nCntModelHandL++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelHandL[ nCntModelHandL ].scl.x, g_aModelHandL[ nCntModelHandL ].scl.y, g_aModelHandL[ nCntModelHandL ].scl.z );
		D3DXMatrixMultiply( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelHandL[ nCntModelHandL ].rot.y, g_aModelHandL[ nCntModelHandL ].rot.x, g_aModelHandL[ nCntModelHandL ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelHandL[ nCntModelHandL ].pos.x, g_aModelHandL[ nCntModelHandL ].pos.y, g_aModelHandL[ nCntModelHandL ].pos.z );
		D3DXMatrixMultiply( &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelHandL[ nCntModelHandL ].mtxWorldModelHandL );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelHandL[ nCntModelHandL ].pBuffMatModelHandL->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelHandL[ nCntModelHandL ].nNumMatModelHandL; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelHandL[ nCntModelHandL ].pMeshModelHandL->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelHandL�֐�
// ���� void
// �߂�l 
// ���� ModelHandL���擾����B
//================================================================================================================================================================================================
MODELHANDL *GetModelHandL( void )
{
	return &g_aModelHandL[ 0 ];
}
