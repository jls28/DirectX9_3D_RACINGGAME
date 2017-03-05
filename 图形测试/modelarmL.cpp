/*******************************************************************************
* �^�C�g���F ���f��body�`��֐�
* �t�@�C�����F modelarmL.cpp
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
#include "modelarmL.h"
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
#define MODELARML_INERTIA_MOVE	( 0.025f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELARML g_aModelarmL[ MAX_MODELARML ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelarmL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelarmL( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\modelarmL.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL,		// �}�e���A�����
									   NULL,
									   &g_aModelarmL[ nCntModelarmL ].nNumMatModelarmL,			// �}�e���A����
									   &g_aModelarmL[ nCntModelarmL ].pMeshModelarmL ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelarmL[ nCntModelarmL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y, pModelBody->pos.z );
		g_aModelarmL[ nCntModelarmL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		g_aModelarmL[ nCntModelarmL ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelarmL[ nCntModelarmL ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmL[ nCntModelarmL ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelarmL[ nCntModelarmL ].fPosMove = POSMOVE_MODELARML;
		g_aModelarmL[ nCntModelarmL ].fAngle = 0.0f;
		g_aModelarmL[ nCntModelarmL ].propR = 1.0f;		//���a
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelarmL[ nCntModelarmL ].Min.x )		g_aModelarmL[ nCntModelarmL ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelarmL[ nCntModelarmL ].Max.x )		g_aModelarmL[ nCntModelarmL ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelarmL[ nCntModelarmL ].Min.y )		g_aModelarmL[ nCntModelarmL ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelarmL[ nCntModelarmL ].Max.y )		g_aModelarmL[ nCntModelarmL ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelarmL[ nCntModelarmL ].Min.z )		g_aModelarmL[ nCntModelarmL ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelarmL[ nCntModelarmL ].Max.z )		g_aModelarmL[ nCntModelarmL ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelarmL[ nCntModelarmL ].Size.x = ( fabs( g_aModelarmL[ nCntModelarmL ].Min.x ) + fabs( g_aModelarmL[ nCntModelarmL ].Max.x ) ) / 2;
		g_aModelarmL[ nCntModelarmL ].Size.y = ( fabs( g_aModelarmL[ nCntModelarmL ].Min.y ) + fabs( g_aModelarmL[ nCntModelarmL ].Max.y ) ) / 2;
		g_aModelarmL[ nCntModelarmL ].Size.z = ( fabs( g_aModelarmL[ nCntModelarmL ].Min.z ) + fabs( g_aModelarmL[ nCntModelarmL ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelarmL[ nCntModelarmL ].Size.x < g_aModelarmL[ nCntModelarmL ].Size.z )
		{
			g_aModelarmL[ nCntModelarmL ].Collisoin = g_aModelarmL[ nCntModelarmL ].Size.z;
		}
		else
		{
			g_aModelarmL[ nCntModelarmL ].Collisoin = g_aModelarmL[ nCntModelarmL ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelarmL[ nCntModelarmL ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelarmL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelarmL( void )
{
	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++ )
	{
		// ���b�V�����̊J��
		if( g_aModelarmL[ nCntModelarmL ].pMeshModelarmL != NULL )
		{
			g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->Release();
			g_aModelarmL[ nCntModelarmL ].pMeshModelarmL = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL != NULL )
		{
			g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL->Release();
			g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelarmL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelarmL( void )
{

	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropModelarmL_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelarmL_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelarmL_03 = GetPropModel_03 ();


	MODELBODY *pModelBody = GetModelBody();
	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++)
	{
		if(pModelBody->bKeyUse == true)
		{
			g_aModelarmL[ nCntModelarmL ].pos.x = pModelBody->pos.x ;
			g_aModelarmL[ nCntModelarmL ].pos.z = pModelBody->pos.z ;
			g_aModelarmL[ nCntModelarmL ].pos.y = pModelBody->pos.y+ g_aModelarmL[ nCntModelarmL ].propR * sinf( g_aModelarmL[ nCntModelarmL ].fAngle );
			g_aModelarmL[ nCntModelarmL ].fAngle += 20.0f * D3DX_PI / 120.0f;					// �p�̌ʂ𑝂���

		g_aModelarmL[ nCntModelarmL ].pos = D3DXVECTOR3( g_aModelarmL[ nCntModelarmL ].pos.x, g_aModelarmL[ nCntModelarmL ].pos.y, g_aModelarmL[ nCntModelarmL ].pos.z );
		g_aModelarmL[ nCntModelarmL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		else
		{
		g_aModelarmL[ nCntModelarmL ].pos = D3DXVECTOR3( pModelBody->pos.x, pModelBody->pos.y,  pModelBody->pos.z );
		g_aModelarmL[ nCntModelarmL ].rot = D3DXVECTOR3( pModelBody->rot.x,  pModelBody->rot.y, pModelBody->rot.z );
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelarmL[ nCntModelarmL ].OldPos.x - g_aModelarmL[ nCntModelarmL ].Collisoin ) )
		{	// ���̕�
			g_aModelarmL[ nCntModelarmL ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelarmL[ nCntModelarmL ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelarmL[ nCntModelarmL ].OldPos.x + g_aModelarmL[ nCntModelarmL ].Collisoin ) )
		{	// �E�̕�
			g_aModelarmL[ nCntModelarmL ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelarmL[ nCntModelarmL ].Collisoin;
		}
		if(( g_aModelarmL[ nCntModelarmL ].OldPos.z - g_aModelarmL[ nCntModelarmL ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelarmL[ nCntModelarmL ].OldPos.z = 20550.0f + g_aModelarmL[ nCntModelarmL ].Collisoin;
			  SetFade(FADE_OUT,MODE_RESULT);
		}
	}

}

//================================================================================================================================================================================================
// DrawModelarmL�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelarmL( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntModelarmL = 0; nCntModelarmL < MAX_MODELARML; nCntModelarmL++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelarmL[ nCntModelarmL ].scl.x, g_aModelarmL[ nCntModelarmL ].scl.y, g_aModelarmL[ nCntModelarmL ].scl.z );
		D3DXMatrixMultiply( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelarmL[ nCntModelarmL ].rot.y, g_aModelarmL[ nCntModelarmL ].rot.x, g_aModelarmL[ nCntModelarmL ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelarmL[ nCntModelarmL ].pos.x, g_aModelarmL[ nCntModelarmL ].pos.y, g_aModelarmL[ nCntModelarmL ].pos.z );
		D3DXMatrixMultiply( &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelarmL[ nCntModelarmL ].mtxWorldModelarmL );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelarmL[ nCntModelarmL ].pBuffMatModelarmL->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelarmL[ nCntModelarmL ].nNumMatModelarmL; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelarmL[ nCntModelarmL ].pMeshModelarmL->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelarmL�֐�
// ���� void
// �߂�l 
// ���� ModelarmL���擾����B
//================================================================================================================================================================================================
MODELARML *GetModelarmL( void )
{
	return &g_aModelarmL[ 0 ];
}
/*******************************************************************************
* �֐���: �������ړ��֐�
* 
* ����  : D3DXVECTOR3	*pos		//�ʒu
		  D3DXVECTOR3	*rot		//����
		  float			fPosmove	//�ړ���
		  int			UP			//��{�^��
		  int			DOWN		//���{�^��
		  int			LEFT		//���{�^��
		  int			RIGHT		//�E�{�^��
* �߂�l: �i�V
* ����: �i�V
*******************************************************************************/
void ModelarmLMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELARML *pModelarmL = GetModelarmL();
	pModelarmL -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E��ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
		}
		else											//�O�ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//�����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E���ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
		}
		else											//��ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + 0.0f;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else											//���ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//�E��ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�E���ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
		}
		else											//�E�ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
	}

	//���W���X�V�i�����j
	pModelarmL -> pos.x += ( pModelarmL->OldPos.x - pModelarmL -> pos.x ) * MODELARML_INERTIA_MOVE;
	pModelarmL -> pos.z += ( pModelarmL->OldPos.z - pModelarmL -> pos.z ) * MODELARML_INERTIA_MOVE;
}

/*******************************************************************************
* �֐���: �W���C�X�e�B�b�N�������ړ��֐�
* 
* ����  : D3DXVECTOR3	*pos		//�ʒu
		  D3DXVECTOR3	*rot		//����
		  float			fPosmove	//�ړ���
		  int			UP			//��{�^��
		  int			DOWN		//���{�^��
		  int			LEFT		//���{�^��
		  int			RIGHT		//�E�{�^��
* �߂�l: �i�V
* ����: �i�V
*******************************************************************************/
void ModelarmLMovejoystick( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELARML *pModelarmL = GetModelarmL();
	pModelarmL -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetJoysticksTrigger( UP_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//�E��ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else											//�O�ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
			pModelarmL->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( DOWN_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//�����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//�E���ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else											//��ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + 0.0f;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
		pModelarmL->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( LEFT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//�����ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else											//���ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
		pModelarmL->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( RIGHT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//�E��ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pModelarmL->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//�E���ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pModelarmL->bAutoRot = true;
		}
		else											//�E�ړ�
		{
			pModelarmL -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelarmL -> fPosMove;
			pModelarmL -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pModelarmL->bAutoRot = true;
		}
		pModelarmL -> rot.y			 = pModelarmL ->OldRot.y;
			pModelarmL->bAutoRot = true;
	}
	else 
	{
			pModelarmL->bAutoRot = false;
	}

	//���W���X�V�i�����j
	pModelarmL -> pos.x += ( pModelarmL->OldPos.x - pModelarmL -> pos.x ) * MODELARML_INERTIA_MOVE;
	pModelarmL -> pos.z += ( pModelarmL->OldPos.z - pModelarmL -> pos.z ) * MODELARML_INERTIA_MOVE;
}
