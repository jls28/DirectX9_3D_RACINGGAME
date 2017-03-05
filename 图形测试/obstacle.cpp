/*******************************************************************************
* �^�C�g���F ��Q���`��֐�
* �t�@�C�����F Obstacle.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/05
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
//2015/11/20/14:09:37 // ��Q���̈ړ� //
/*******************************************************************************
		�C���N���[�h�t�@�C��
*******************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include "main.h"
#include "obstacle.h"
#include "modelbody.h"
#include "modellegL.h"
#include "modellegR.h"
#include "modelarmL.h"
#include "modelarmR.h"
#include "modelhandL.h"
#include "modelhandR.h"
#include "meshwall.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define GR							0.03f				// �d�͉����x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
OBSTACLE g_aObstacle_Box[MAX_OBSTACLE_BOX];		// ��Q��1�̏��
OBSTACLE g_aObstacle_Car[MAX_OBSTACLE_CAR];		// ��Q��2�̏��
OBSTACLE g_aObstacle_Cat_01[MAX_OBSTACLE_CAT_01];		// ��Q��3�̏��
//================================================================================================================================================================================================
// InitObstacle�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitObstacle( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	MESHWALL *pWall = GetMeshWall();
	g_aObstacle_Box[0].pos = D3DXVECTOR3( -60.0f, 0.0f, 700.0f );

	g_aObstacle_Box[1].pos = D3DXVECTOR3( 0.0f, 0.0f, 1100.0f );

	g_aObstacle_Box[2].pos = D3DXVECTOR3( 50.0f, 0.0f, 1800.0f );

	g_aObstacle_Box[3].pos = D3DXVECTOR3( 50.0f, 0.0f, 2500.0f );

	g_aObstacle_Box[4].pos = D3DXVECTOR3( 0.0f, 0.0f, 2900.0f );

	g_aObstacle_Box[5].pos = D3DXVECTOR3( 0.0f, 0.0f, 3500.0f );

	g_aObstacle_Box[6].pos = D3DXVECTOR3( -60.0f, 0.0f, 4000.0f );

	g_aObstacle_Box[7].pos = D3DXVECTOR3( 60.0f, 0.0f, 4800.0f );

	g_aObstacle_Box[8].pos = D3DXVECTOR3( 60.0f, 0.0f, 5300.0f );

	g_aObstacle_Box[9].pos = D3DXVECTOR3( 0.0f, 0.0f, 6000.0f );

	g_aObstacle_Box[10].pos = D3DXVECTOR3( 30.0f, 0.0f, 7200.0f );

	g_aObstacle_Box[11].pos = D3DXVECTOR3( -70.0f, 0.0f, 8600.0f );

	g_aObstacle_Box[12].pos = D3DXVECTOR3( 60.0f, 0.0f, 8600.0f );

	g_aObstacle_Box[13].pos = D3DXVECTOR3( 0.0f, 0.0f, 9300.0f );

	g_aObstacle_Box[14].pos = D3DXVECTOR3( -30.0f, 0.0f, 10000.0f );

	g_aObstacle_Box[15].pos = D3DXVECTOR3( 40.0f, 0.0f, 11900.0f );

	g_aObstacle_Box[16].pos = D3DXVECTOR3( 20.0f, 0.0f, 12800.0f );

	g_aObstacle_Box[17].pos = D3DXVECTOR3( 0.0f, 0.0f, 13900.0f );

	g_aObstacle_Box[18].pos = D3DXVECTOR3( 70.0f, 0.0f, 14800.0f );

	g_aObstacle_Box[19].pos = D3DXVECTOR3( -50.0f, 0.0f, 15700.0f );

	g_aObstacle_Box[20].pos = D3DXVECTOR3( 10.0f, 0.0f, 16900.0f );

	g_aObstacle_Box[21].pos = D3DXVECTOR3( 60.0f, 0.0f, 17800.0f );

	g_aObstacle_Box[22].pos = D3DXVECTOR3( 30.0f, 0.0f, 18900.0f );

	g_aObstacle_Box[23].pos = D3DXVECTOR3( 0.0f, 0.0f, 19200.0f );

	g_aObstacle_Box[24].pos = D3DXVECTOR3( -10.0f, 0.0f, 19900.0f );

	g_aObstacle_Box[25].pos = D3DXVECTOR3( -50.0f, 0.0f, 20300.0f );
		for( int nCntObstacleBox = 0; nCntObstacleBox < MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\box.jpg",&g_aObstacle_Box[nCntObstacleBox].pTextureObstacle);// �e�N�X�`���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\obstacle_box.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle,		// �}�e���A�����
									   NULL,
									   &g_aObstacle_Box[nCntObstacleBox].nNumMatObstacle,			// �}�e���A����
									   &g_aObstacle_Box[nCntObstacleBox].pMeshObstacle ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ��Q���̏����ݒ�

		g_aObstacle_Box[nCntObstacleBox].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Box[nCntObstacleBox].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aObstacle_Box[nCntObstacleBox].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Box[nCntObstacleBox].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Box[nCntObstacleBox].fPosMove = POSMOVE_OBSTACLE_BOX;
		g_aObstacle_Box[nCntObstacleBox].time = 0;
		g_aObstacle_Box[nCntObstacleBox].nLife = 100;
		g_aObstacle_Box[nCntObstacleBox].Type = OBSTACLE_BOX;
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aObstacle_Box[nCntObstacleBox].Min.x )		g_aObstacle_Box[nCntObstacleBox].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aObstacle_Box[nCntObstacleBox].Max.x )		g_aObstacle_Box[nCntObstacleBox].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aObstacle_Box[nCntObstacleBox].Min.y )		g_aObstacle_Box[nCntObstacleBox].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aObstacle_Box[nCntObstacleBox].Max.y )		g_aObstacle_Box[nCntObstacleBox].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aObstacle_Box[nCntObstacleBox].Min.z )		g_aObstacle_Box[nCntObstacleBox].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aObstacle_Box[nCntObstacleBox].Max.z )		g_aObstacle_Box[nCntObstacleBox].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->UnlockVertexBuffer();

		// ��Q���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aObstacle_Box[nCntObstacleBox].Size.x = ( fabs( g_aObstacle_Box[nCntObstacleBox].Min.x ) + fabs( g_aObstacle_Box[nCntObstacleBox].Max.x ) ) / 2;
		g_aObstacle_Box[nCntObstacleBox].Size.y = ( fabs( g_aObstacle_Box[nCntObstacleBox].Min.y ) + fabs( g_aObstacle_Box[nCntObstacleBox].Max.y ) ) / 2;
		g_aObstacle_Box[nCntObstacleBox].Size.z = ( fabs( g_aObstacle_Box[nCntObstacleBox].Min.z ) + fabs( g_aObstacle_Box[nCntObstacleBox].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aObstacle_Box[nCntObstacleBox].Size.x < g_aObstacle_Box[nCntObstacleBox].Size.z )
		{
			g_aObstacle_Box[nCntObstacleBox].Collisoin = g_aObstacle_Box[nCntObstacleBox].Size.z;
		}
		else
		{
			g_aObstacle_Box[nCntObstacleBox].Collisoin = g_aObstacle_Box[nCntObstacleBox].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aObstacle_Box[nCntObstacleBox].bUse = true;
		}
/***************************************************************************************************************************************************************/
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\obstacle_car.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle,		// �}�e���A�����
									   NULL,
									   &g_aObstacle_Car[nCntObstacleCar].nNumMatObstacle,			// �}�e���A����
									   &g_aObstacle_Car[nCntObstacleCar].pMeshObstacle ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ��Q���̏����ݒ�
		g_aObstacle_Car[nCntObstacleCar].rot = D3DXVECTOR3( 0.0f,  3.14f, 0.0f );
		g_aObstacle_Car[nCntObstacleCar].scl = D3DXVECTOR3( 3.0f,  3.0f, 3.0f );
		g_aObstacle_Car[nCntObstacleCar].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Car[nCntObstacleCar].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Car[nCntObstacleCar].fPosMove = POSMOVE_OBSTACLE_CAR;
		g_aObstacle_Car[nCntObstacleCar].time = 0;
		g_aObstacle_Car[nCntObstacleCar].nLife = 100;
		g_aObstacle_Car[nCntObstacleCar].Type = OBSTACLE_CAR;
		g_aObstacle_Car[nCntObstacleCar].bMove = true;
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aObstacle_Car[nCntObstacleCar].Min.x )		g_aObstacle_Car[nCntObstacleCar].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aObstacle_Car[nCntObstacleCar].Max.x )		g_aObstacle_Car[nCntObstacleCar].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aObstacle_Car[nCntObstacleCar].Min.y )		g_aObstacle_Car[nCntObstacleCar].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aObstacle_Car[nCntObstacleCar].Max.y )		g_aObstacle_Car[nCntObstacleCar].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aObstacle_Car[nCntObstacleCar].Min.z )		g_aObstacle_Car[nCntObstacleCar].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aObstacle_Car[nCntObstacleCar].Max.z )		g_aObstacle_Car[nCntObstacleCar].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->UnlockVertexBuffer();

		// ��Q���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aObstacle_Car[nCntObstacleCar].Size.x = ( fabs( g_aObstacle_Car[nCntObstacleCar].Min.x ) + fabs( g_aObstacle_Car[nCntObstacleCar].Max.x ) ) / 2;
		g_aObstacle_Car[nCntObstacleCar].Size.y = ( fabs( g_aObstacle_Car[nCntObstacleCar].Min.y ) + fabs( g_aObstacle_Car[nCntObstacleCar].Max.y ) ) / 2;
		g_aObstacle_Car[nCntObstacleCar].Size.z = ( fabs( g_aObstacle_Car[nCntObstacleCar].Min.z ) + fabs( g_aObstacle_Car[nCntObstacleCar].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aObstacle_Car[nCntObstacleCar].Size.x < g_aObstacle_Car[nCntObstacleCar].Size.z )
		{
			g_aObstacle_Car[nCntObstacleCar].Collisoin = g_aObstacle_Car[nCntObstacleCar].Size.z;
		}
		else
		{
			g_aObstacle_Car[nCntObstacleCar].Collisoin = g_aObstacle_Car[nCntObstacleCar].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aObstacle_Car[nCntObstacleCar].bUse = true;
		}
		g_aObstacle_Car[0].pos = D3DXVECTOR3( -30.0f, 0.0f, 20000.0f );
		g_aObstacle_Car[1].pos = D3DXVECTOR3( 60.0f, 0.0f, 12300.0f );
		g_aObstacle_Car[2].pos = D3DXVECTOR3( -70.0f, 0.0f, 5300.0f );
/***************************************************************************************************************************************************************/
		for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 < MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\cat_01.png",&g_aObstacle_Cat_01[nCntObstacleCat_01].pTextureObstacle);// �e�N�X�`���ǂݍ���
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\cat_01.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle,		// �}�e���A�����
									   NULL,
									   &g_aObstacle_Cat_01[nCntObstacleCat_01].nNumMatObstacle,			// �}�e���A����
									   &g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ��Q���̏����ݒ�

		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aObstacle_Cat_01[nCntObstacleCat_01].Min.x )		g_aObstacle_Cat_01[nCntObstacleCat_01].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aObstacle_Cat_01[nCntObstacleCat_01].Max.x )		g_aObstacle_Cat_01[nCntObstacleCat_01].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aObstacle_Cat_01[nCntObstacleCat_01].Min.y )		g_aObstacle_Cat_01[nCntObstacleCat_01].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aObstacle_Cat_01[nCntObstacleCat_01].Max.y )		g_aObstacle_Cat_01[nCntObstacleCat_01].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aObstacle_Cat_01[nCntObstacleCat_01].Min.z )		g_aObstacle_Cat_01[nCntObstacleCat_01].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aObstacle_Cat_01[nCntObstacleCat_01].Max.z )		g_aObstacle_Cat_01[nCntObstacleCat_01].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->UnlockVertexBuffer();

		// ��Q���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x = ( fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Min.x ) + fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Max.x ) ) / 2;
		g_aObstacle_Cat_01[nCntObstacleCat_01].Size.y = ( fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Min.y ) + fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Max.y ) ) / 2;
		g_aObstacle_Cat_01[nCntObstacleCat_01].Size.z = ( fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Min.z ) + fabs( g_aObstacle_Cat_01[nCntObstacleCat_01].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x < g_aObstacle_Cat_01[nCntObstacleCat_01].Size.z )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].Collisoin = g_aObstacle_Cat_01[nCntObstacleCat_01].Size.z;
		}
		else
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].Collisoin = g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_aObstacle_Cat_01[nCntObstacleCat_01].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aObstacle_Cat_01[nCntObstacleCat_01].time = 0;
		g_aObstacle_Cat_01[nCntObstacleCat_01].nLife = 1000;
		g_aObstacle_Cat_01[nCntObstacleCat_01].Type = OBSTACLE_CAT_01;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bUse = true;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bMove = true;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bRot = false;
		g_aObstacle_Cat_01[nCntObstacleCat_01].bCatRotCheck = false;
		}
		g_aObstacle_Cat_01[0].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[0].Size.x,0.0f,1100.0f);
		g_aObstacle_Cat_01[0].fPosMove = 0.5f;

		g_aObstacle_Cat_01[1].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[1].Size.x,0.0f,2300.0f);
		g_aObstacle_Cat_01[1].fPosMove = 0.8f;

		g_aObstacle_Cat_01[2].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[2].Size.x,0.0f,2800.0f);
		g_aObstacle_Cat_01[2].fPosMove = 0.2f;

		g_aObstacle_Cat_01[3].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[3].Size.x,0.0f,3900.0f);
		g_aObstacle_Cat_01[3].fPosMove = 0.7f;

		g_aObstacle_Cat_01[4].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[4].Size.x,0.0f,4700.0f);
		g_aObstacle_Cat_01[4].fPosMove = 0.1f;

		g_aObstacle_Cat_01[5].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[5].Size.x,0.0f,6000.0f);
		g_aObstacle_Cat_01[5].fPosMove = 0.9f;

		g_aObstacle_Cat_01[6].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[6].Size.x,0.0f,8000.0f);
		g_aObstacle_Cat_01[6].fPosMove = 0.1f;

		g_aObstacle_Cat_01[6].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[6].Size.x,0.0f,11200.0f);
		g_aObstacle_Cat_01[6].fPosMove = 0.2f;


		g_aObstacle_Cat_01[7].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[7].Size.x,0.0f,12000.0f);
		g_aObstacle_Cat_01[7].fPosMove = 0.5f;


		g_aObstacle_Cat_01[8].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[8].Size.x,0.0f,13000.0f);
		g_aObstacle_Cat_01[8].fPosMove = 0.5f;


		g_aObstacle_Cat_01[9].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[9].Size.x,0.0f,14200.0f);
		g_aObstacle_Cat_01[9].fPosMove = 0.5f;


		g_aObstacle_Cat_01[10].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[10].Size.x,0.0f,15700.0f);
		g_aObstacle_Cat_01[10].fPosMove = 1.0f;


		g_aObstacle_Cat_01[11].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[11].Size.x,0.0f,16900.0f);
		g_aObstacle_Cat_01[11].fPosMove = 0.7f;

		g_aObstacle_Cat_01[12].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[12].Size.x,0.0f,18000.0f);
		g_aObstacle_Cat_01[12].fPosMove = 0.6f;

		g_aObstacle_Cat_01[13].pos = D3DXVECTOR3( (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[13].Size.x,0.0f,20000.0f);
		g_aObstacle_Cat_01[13].fPosMove = 1.0f;

	return S_OK;
}

//================================================================================================================================================================================================
// UninitObstacle�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitObstacle( void )
{
	for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		// ���b�V�����̊J��
		if( g_aObstacle_Box[nCntObstacleBox].pMeshObstacle != NULL )
		{
			g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->Release();
			g_aObstacle_Box[nCntObstacleBox].pMeshObstacle = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle != NULL )
		{
			g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle->Release();
			g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle = NULL;
		}
	}
/***************************************************************************************/
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		// ���b�V�����̊J��
		if( g_aObstacle_Car[nCntObstacleCar].pMeshObstacle != NULL )
		{
			g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->Release();
			g_aObstacle_Car[nCntObstacleCar].pMeshObstacle = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle != NULL )
		{
			g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle->Release();
			g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle = NULL;
		}
	}

/***************************************************************************************/
		for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 < MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		// ���b�V�����̊J��
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle != NULL )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->Release();
			g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle != NULL )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle->Release();
			g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle = NULL;
		}
	}
	
}

//================================================================================================================================================================================================
// UpdateObstacle�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateObstacle( void )
{
	MESHWALL *pWall = GetMeshWall();
	for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 < MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		if(g_aObstacle_Cat_01[nCntObstacleCat_01].bRot == true)
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].fPosMove = 0.0f;
			g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x+=0.05f;
			if(g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x>=1.57f)
			{
				g_aObstacle_Cat_01[nCntObstacleCat_01].bCatRotCheck = true;
				g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x = 1.57f;
				g_aObstacle_Cat_01[nCntObstacleCat_01].nLife --;

				if(g_aObstacle_Cat_01[nCntObstacleCat_01].nLife<=0)
				{
					g_aObstacle_Cat_01[nCntObstacleCat_01].bUse = false;
				}
			}
		}
		if( g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x <= (pWall + WALL_LEFT)->pos.x - g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].bMove =true;
		}
	else if(g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x >= (pWall + WALL_RIGHT)->pos.x + g_aObstacle_Cat_01[nCntObstacleCat_01].Size.x )
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].bMove =false;
		}
		if(g_aObstacle_Cat_01[nCntObstacleCat_01].bMove == true)
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x += g_aObstacle_Cat_01[nCntObstacleCat_01].fPosMove;
		}
		else if(g_aObstacle_Cat_01[nCntObstacleCat_01].bMove ==	false)
		{
			g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x -= g_aObstacle_Cat_01[nCntObstacleCat_01].fPosMove;

		}
	}
/*******************************************************************************************************************************/
	for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		if(g_aObstacle_Car[nCntObstacleCar].bUse == true)
		{
			if( g_aObstacle_Car[nCntObstacleCar].pos.z <= 0.0f )
			{
				g_aObstacle_Car[nCntObstacleCar].rot = D3DXVECTOR3( 0.0f,  3.14f, 0.0f );
				g_aObstacle_Car[nCntObstacleCar].bMove =true;
			}
		else if(g_aObstacle_Car[nCntObstacleCar].pos.z >= 21000.0f )
			{
				g_aObstacle_Car[nCntObstacleCar].rot = D3DXVECTOR3( 0.0f,  0.00f, 0.0f );
				g_aObstacle_Car[nCntObstacleCar].bMove =false;
			}
			if(g_aObstacle_Car[nCntObstacleCar].bMove == true)
			{
				g_aObstacle_Car[nCntObstacleCar].pos.z += g_aObstacle_Car[nCntObstacleCar].fPosMove;
			}
			else if(g_aObstacle_Car[nCntObstacleCar].bMove ==	false)
			{
				g_aObstacle_Car[nCntObstacleCar].pos.z -= g_aObstacle_Car[nCntObstacleCar].fPosMove;
			}
		}
	}
}
//================================================================================================================================================================================================
// DrawObstacle�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawObstacle( void )
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
	// �����_�[�X�e�[�g�̐ݒ�iz�e�X�g�j
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z�l�̍X�V
	// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// ���̒l���A���t�@�l���傫����Ε`�悷��B
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// �A���t�@�l�B0�œ����ȕ����B
		for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		if(g_aObstacle_Box[nCntObstacleBox].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aObstacle_Box[nCntObstacleBox].scl.x, g_aObstacle_Box[nCntObstacleBox].scl.y, g_aObstacle_Box[nCntObstacleBox].scl.z );
		D3DXMatrixMultiply( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aObstacle_Box[nCntObstacleBox].rot.y, g_aObstacle_Box[nCntObstacleBox].rot.x, g_aObstacle_Box[nCntObstacleBox].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aObstacle_Box[nCntObstacleBox].pos.x, g_aObstacle_Box[nCntObstacleBox].pos.y, g_aObstacle_Box[nCntObstacleBox].pos.z );
		D3DXMatrixMultiply( &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle, &mtxTrans );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aObstacle_Box[nCntObstacleBox].mtxWorldObstacle );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aObstacle_Box[nCntObstacleBox].pBuffMatObstacle->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aObstacle_Box[nCntObstacleBox].nNumMatObstacle; nCntMat++ )
		{

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aObstacle_Box[nCntObstacleBox].pTextureObstacle );

			// ���b�V���̕`��
			g_aObstacle_Box[nCntObstacleBox].pMeshObstacle->DrawSubset( nCntMat );

		}

		}
	}
/********************************************************************************************************************/


	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );
	//���f���ɔ����ɂȂ�̖��@�R�[�h
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		if(g_aObstacle_Car[nCntObstacleCar].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aObstacle_Car[nCntObstacleCar].scl.x, g_aObstacle_Car[nCntObstacleCar].scl.y, g_aObstacle_Car[nCntObstacleCar].scl.z );
		D3DXMatrixMultiply( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aObstacle_Car[nCntObstacleCar].rot.y, g_aObstacle_Car[nCntObstacleCar].rot.x, g_aObstacle_Car[nCntObstacleCar].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aObstacle_Car[nCntObstacleCar].pos.x, g_aObstacle_Car[nCntObstacleCar].pos.y, g_aObstacle_Car[nCntObstacleCar].pos.z );
		D3DXMatrixMultiply( &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aObstacle_Car[nCntObstacleCar].mtxWorldObstacle );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aObstacle_Car[nCntObstacleCar].pBuffMatObstacle->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aObstacle_Car[nCntObstacleCar].nNumMatObstacle; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, 0 );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA��Q�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aObstacle_Car[nCntObstacleCar].pMeshObstacle->DrawSubset( nCntMat );
		}
			// �}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}

	}
/********************************************************************************************************************/
		for( int nCntObstacleCat_01 = 0; nCntObstacleCat_01 <MAX_OBSTACLE_CAT_01; nCntObstacleCat_01++ )
	{
		if(g_aObstacle_Cat_01[nCntObstacleCat_01].bUse == true)
		{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aObstacle_Cat_01[nCntObstacleCat_01].scl.x, g_aObstacle_Cat_01[nCntObstacleCat_01].scl.y, g_aObstacle_Cat_01[nCntObstacleCat_01].scl.z );
		D3DXMatrixMultiply( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aObstacle_Cat_01[nCntObstacleCat_01].rot.y, g_aObstacle_Cat_01[nCntObstacleCat_01].rot.x, g_aObstacle_Cat_01[nCntObstacleCat_01].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aObstacle_Cat_01[nCntObstacleCat_01].pos.x, g_aObstacle_Cat_01[nCntObstacleCat_01].pos.y, g_aObstacle_Cat_01[nCntObstacleCat_01].pos.z );
		D3DXMatrixMultiply( &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle, &mtxTrans );
		// ���C�g�_��
		pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aObstacle_Cat_01[nCntObstacleCat_01].mtxWorldObstacle );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aObstacle_Cat_01[nCntObstacleCat_01].pBuffMatObstacle->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aObstacle_Cat_01[nCntObstacleCat_01].nNumMatObstacle; nCntMat++ )
		{

			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0,g_aObstacle_Cat_01[nCntObstacleCat_01].pTextureObstacle );

			// ���b�V���̕`��
			g_aObstacle_Cat_01[nCntObstacleCat_01].pMeshObstacle->DrawSubset( nCntMat );

		}

		}

	}


}

//================================================================================================================================================================================================
// OBSTACLE *GetObstacle_Box�֐�
// ���� void
// �߂�l 
// ���� Obstacle_Box���擾����B
//================================================================================================================================================================================================
OBSTACLE *GetObstacle_Box( void )
{
	return &g_aObstacle_Box[0];
}
//================================================================================================================================================================================================
//OBSTACLE *GetObstacle_Car�֐�
// ���� void
// �߂�l 
// ���� g_aObstacle_Car[nCntObstacleCar]���擾����B
//================================================================================================================================================================================================
OBSTACLE *GetObstacle_Car( void )
{
	return &g_aObstacle_Car[0];
}
//================================================================================================================================================================================================
//OBSTACLE *GetObstacle_Cat_01�֐�
// ���� void
// �߂�l 
// ���� g_aObstacle_Car[nCntObstacleCar]���擾����B
//================================================================================================================================================================================================
OBSTACLE *GetObstacle_Cat_01( void )
{
	return &g_aObstacle_Cat_01[0];
}

void SetObstacle_Box( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
	for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{
		if(g_aObstacle_Box[nCntObstacleBox].bUse == false )
		{
			// �ʒu�̐ݒ�
			g_aObstacle_Box[nCntObstacleBox].pos = pos;

			// �ړ��ʂ̐ݒ�
			g_aObstacle_Box[nCntObstacleBox].rot = rot;

			// �����̐ݒ�
			g_aObstacle_Box[nCntObstacleBox].nLife = nLife;

			// �c�[�����g�p��Ԃɂ���
			g_aObstacle_Box[nCntObstacleBox].bUse = true;
			
		}
	}
	
}
void SetObstacle_Car( D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife )
{
		for( int nCntObstacleCar = 0; nCntObstacleCar < MAX_OBSTACLE_CAR; nCntObstacleCar++ )
	{
		if(g_aObstacle_Car[nCntObstacleCar].bUse == false )
		{
			// �ʒu�̐ݒ�
			g_aObstacle_Car[nCntObstacleCar].pos = pos;

			// �ړ��ʂ̐ݒ�
			g_aObstacle_Car[nCntObstacleCar].rot = rot;

			// �����̐ݒ�
			g_aObstacle_Car[nCntObstacleCar].nLife = nLife;

			// �c�[�����g�p��Ԃɂ���
			g_aObstacle_Car[nCntObstacleCar].bUse = true;
			
		}
		}
	
}

//================================================================================================================================================================================================
// void HitObstacle_Box(void)�֐�
// ���� void
// �߂�l 
// ���� ��Q��1�����蔻��p
//================================================================================================================================================================================================
void HitObstacle_Box(void)
{
	MODELBODY *pModelBody = GetModelBody();
	MODELLEGL *pModelLegL = GetModelLegL();
	MODELLEGR *pModelLegR = GetModelLegR();
	MODELHANDL *pModelHandL = GetModelHandL();
	MODELHANDR *pModelHandR = GetModelHandR();
	MODELARML *pModelArmL = GetModelarmL();
	MODELARMR *pModelArmR = GetModelarmR();
	for( int nCntObstacleBox = 0; nCntObstacleBox <MAX_OBSTACLE_BOX; nCntObstacleBox++ )
	{		//�����蔻���{�v�Z`(������E)(bdoy)
		if ( pModelBody -> OldPos.x + pModelBody->Collisoin >= (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin  )
			&& (pModelBody -> OldPos.z+  pModelBody -> Collisoin) >= (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin )
			&& (pModelBody -> OldPos.z-  pModelBody -> Collisoin) <= (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin  )
			//&&  pModelBody -> OldPos.x - pModelBody->Collisoin < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin *4 )
			)
		{
			pModelBody -> OldPos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin ) - pModelBody->Collisoin ;
		}
//			//�����蔻���{�v�Z`(������E)(handL)
//		if ( pModelHandL -> pos.x + pModelHandL->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandL -> pos.z+  pModelHandL -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandL -> pos.z-  pModelHandL -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelHandL -> pos.x - pModelHandL->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelHandL -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelHandL->Collisoin*2 ;
//		}
//
//			//�����蔻���{�v�Z`(������E)(handR)
//		if ( pModelHandR -> pos.x + pModelHandR->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandR -> pos.z+  pModelHandR -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelHandR -> pos.z-  pModelHandR -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& pModelHandR -> pos.x - pModelHandR->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelHandR -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelHandR->Collisoin*2 ;
//		}
//
//
//			//�����蔻���{�v�Z`(������E)(LegL)
//		if ( pModelLegL -> pos.x + pModelLegL->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegL -> pos.z+  pModelLegL -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegL -> pos.z-  pModelLegL -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelLegL -> pos.x - pModelLegL->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelLegL -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelLegL->Collisoin*2 ;
//		}
//
//			//�����蔻���{�v�Z`(������E)(LegR)
//		if ( pModelLegR -> pos.x + pModelLegR->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegR -> pos.z+  pModelLegR -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelLegR -> pos.z-  pModelLegR -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelLegR -> pos.x + pModelLegR->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelLegR -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelLegR->Collisoin*2 ;
//		}
//
//
//			//�����蔻���{�v�Z`(������E)(ArmL)
//		if ( pModelArmL -> pos.x + pModelArmL->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmL -> pos.z+  pModelArmL -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmL -> pos.z-  pModelArmL -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& pModelArmL -> pos.x + pModelArmL->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelArmL -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelArmL->Collisoin*2 ;
//		}
//
//
//			//�����蔻���{�v�Z`(������E)(ArmR)
//		if ( pModelArmR -> pos.x + pModelArmR->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmR -> pos.z+  pModelArmR -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelArmR -> pos.z-  pModelArmR -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&&  pModelArmR -> pos.x + pModelArmR->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelArmR -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin) - pModelArmR->Collisoin*2 ;
//		}
///************************************************************************************************************************************************************/
//
//		//�����蔻���{�v�Z`(�E���獶)(bdoy)
//		if ( pModelBody -> pos.x - pModelBody->Collisoin*2 < (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelBody -> pos.z + pModelBody -> Collisoin*2) > (g_aObstacle_Box[nCntObstacleBox].pos.z - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& (pModelBody -> pos.z - pModelBody -> Collisoin*2) < (g_aObstacle_Box[nCntObstacleBox].pos.z + g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			&& pModelBody -> pos.x + pModelBody->Collisoin*2 > (g_aObstacle_Box[nCntObstacleBox].pos.x - g_aObstacle_Box[nCntObstacleBox].Collisoin)
//			)
//		{
//			pModelBody -> pos.x=  (g_aObstacle_Box[nCntObstacleBox].pos.x + g_aObstacle_Box[nCntObstacleBox].Collisoin) + pModelBody->Collisoin*2 ;
//		}
	}
}