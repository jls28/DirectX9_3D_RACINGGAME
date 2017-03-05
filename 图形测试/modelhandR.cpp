/*******************************************************************************
* �^�C�g���F ���f��body�`��֐�
* �t�@�C�����F modelbody.cpp
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
#include "modelhandR.h"
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
#include "modelarmR.h"
#include "fade.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MODELHANDR_INERTIA_MOVE	( 0.025f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELHANDR g_aModelHandR[ MAX_MODELHANDR ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelHandR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelHandR( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelhandR.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR,		// �}�e���A�����
									   NULL,
									   &g_aModelHandR[ nCntModelHandR ].nNumMatModelHandR,			// �}�e���A����
									   &g_aModelHandR[ nCntModelHandR ].pMeshModelHandR ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelHandR[ nCntModelHandR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelHandR[ nCntModelHandR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelHandR[ nCntModelHandR ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelHandR[ nCntModelHandR ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandR[ nCntModelHandR ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelHandR[ nCntModelHandR ].fPosMove = POSMOVE_MODELHANDR;

		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelHandR[ nCntModelHandR ].Min.x )		g_aModelHandR[ nCntModelHandR ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelHandR[ nCntModelHandR ].Max.x )		g_aModelHandR[ nCntModelHandR ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelHandR[ nCntModelHandR ].Min.y )		g_aModelHandR[ nCntModelHandR ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelHandR[ nCntModelHandR ].Max.y )		g_aModelHandR[ nCntModelHandR ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelHandR[ nCntModelHandR ].Min.z )		g_aModelHandR[ nCntModelHandR ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelHandR[ nCntModelHandR ].Max.z )		g_aModelHandR[ nCntModelHandR ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelHandR[ nCntModelHandR ].Size.x = ( fabs( g_aModelHandR[ nCntModelHandR ].Min.x ) + fabs( g_aModelHandR[ nCntModelHandR ].Max.x ) ) / 2;
		g_aModelHandR[ nCntModelHandR ].Size.y = ( fabs( g_aModelHandR[ nCntModelHandR ].Min.y ) + fabs( g_aModelHandR[ nCntModelHandR ].Max.y ) ) / 2;
		g_aModelHandR[ nCntModelHandR ].Size.z = ( fabs( g_aModelHandR[ nCntModelHandR ].Min.z ) + fabs( g_aModelHandR[ nCntModelHandR ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelHandR[ nCntModelHandR ].Size.x < g_aModelHandR[ nCntModelHandR ].Size.z )
		{
			g_aModelHandR[ nCntModelHandR ].Collisoin = g_aModelHandR[ nCntModelHandR ].Size.z;
		}
		else
		{
			g_aModelHandR[ nCntModelHandR ].Collisoin = g_aModelHandR[ nCntModelHandR ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelHandR[ nCntModelHandR ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelHandR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelHandR( void )
{
	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++ )
	{
		// ���b�V�����̊J��
		if( g_aModelHandR[ nCntModelHandR ].pMeshModelHandR != NULL )
		{
			g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->Release();
			g_aModelHandR[ nCntModelHandR ].pMeshModelHandR = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR != NULL )
		{
			g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR->Release();
			g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelHandR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelHandR( void )
{
	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelHandR_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelHandR_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelHandR_03 = GetPropModel_03 ();

	MODELARMR *pModelArmR = GetModelarmR();

	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++)
	{
		if(pModelBody->bKeyUse == true)
		{
		g_aModelHandR[ nCntModelHandR ].pos = D3DXVECTOR3(  pModelBody->pos.x, pModelArmR ->pos.y,  pModelBody->pos.z );
		g_aModelHandR[ nCntModelHandR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelHandR[ nCntModelHandR ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody ->pos.y, pModelBody ->pos.z );
		g_aModelHandR[ nCntModelHandR ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelHandR[ nCntModelHandR ].OldPos.x - g_aModelHandR[ nCntModelHandR ].Collisoin ) )
		{	// ���̕�
			g_aModelHandR[ nCntModelHandR ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelHandR[ nCntModelHandR ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelHandR[ nCntModelHandR ].OldPos.x + g_aModelHandR[ nCntModelHandR ].Collisoin ) )
		{	// �E�̕�
			g_aModelHandR[ nCntModelHandR ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelHandR[ nCntModelHandR ].Collisoin;
		}
		if(( g_aModelHandR[ nCntModelHandR ].OldPos.z - g_aModelHandR[ nCntModelHandR ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelHandR[ nCntModelHandR ].OldPos.z = 20550.0f + g_aModelHandR[ nCntModelHandR ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}
	}

}

//================================================================================================================================================================================================
// DrawModelHandR�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelHandR( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntModelHandR = 0; nCntModelHandR < MAX_MODELHANDR; nCntModelHandR++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelHandR[ nCntModelHandR ].scl.x, g_aModelHandR[ nCntModelHandR ].scl.y, g_aModelHandR[ nCntModelHandR ].scl.z );
		D3DXMatrixMultiply( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelHandR[ nCntModelHandR ].rot.y, g_aModelHandR[ nCntModelHandR ].rot.x, g_aModelHandR[ nCntModelHandR ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelHandR[ nCntModelHandR ].pos.x, g_aModelHandR[ nCntModelHandR ].pos.y, g_aModelHandR[ nCntModelHandR ].pos.z );
		D3DXMatrixMultiply( &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelHandR[ nCntModelHandR ].mtxWorldModelHandR );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelHandR[ nCntModelHandR ].pBuffMatModelHandR->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelHandR[ nCntModelHandR ].nNumMatModelHandR; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelHandR[ nCntModelHandR ].pMeshModelHandR->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelHandR�֐�
// ���� void
// �߂�l 
// ���� ModelHandR���擾����B
//================================================================================================================================================================================================
MODELHANDR *GetModelHandR( void )
{
	return &g_aModelHandR[ 0 ];
}
