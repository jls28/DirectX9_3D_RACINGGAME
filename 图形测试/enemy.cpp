/*******************************************************************************
* �^�C�g���F �G���f���`��֐�
* �t�@�C�����F model.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/05
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/

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
#include "enemy.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define ENEMY_INERTIA_MOVE	( 0.029f )					//���������W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void EnemyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY );
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
ENEMY g_aEnemy[ MAX_ENEMY ];		// ���f���̏��
int RandEnemy;
//================================================================================================================================================================================================
// InitEnemy�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitEnemy( void )
{

	RandEnemy = 0;
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\enemy.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aEnemy[ nCntEnemy ].pBuffMat,		// �}�e���A�����
									   NULL,
									   &g_aEnemy[ nCntEnemy ].nNumMat,			// �}�e���A����
									   &g_aEnemy[ nCntEnemy ].pMesh ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aEnemy[ nCntEnemy ].pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].scl = D3DXVECTOR3( 5.0f,  5.0f, 5.0f );
		g_aEnemy[ nCntEnemy ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aEnemy[ nCntEnemy ].fPosMove = POSMOVE_ENEMY;
		g_aEnemy[ nCntEnemy ].time = 0;

		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aEnemy[ nCntEnemy ].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aEnemy[ nCntEnemy ].pMesh->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aEnemy[ nCntEnemy ].pMesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aEnemy[ nCntEnemy ].Min.x )		g_aEnemy[ nCntEnemy ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aEnemy[ nCntEnemy ].Max.x )		g_aEnemy[ nCntEnemy ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aEnemy[ nCntEnemy ].Min.y )		g_aEnemy[ nCntEnemy ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aEnemy[ nCntEnemy ].Max.y )		g_aEnemy[ nCntEnemy ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aEnemy[ nCntEnemy ].Min.z )		g_aEnemy[ nCntEnemy ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aEnemy[ nCntEnemy ].Max.z )		g_aEnemy[ nCntEnemy ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aEnemy[ nCntEnemy ].pMesh->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aEnemy[ nCntEnemy ].Size.x = ( fabs( g_aEnemy[ nCntEnemy ].Min.x ) + fabs( g_aEnemy[ nCntEnemy ].Max.x ) ) / 2;
		g_aEnemy[ nCntEnemy ].Size.y = ( fabs( g_aEnemy[ nCntEnemy ].Min.y ) + fabs( g_aEnemy[ nCntEnemy ].Max.y ) ) / 2;
		g_aEnemy[ nCntEnemy ].Size.z = ( fabs( g_aEnemy[ nCntEnemy ].Min.z ) + fabs( g_aEnemy[ nCntEnemy ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aEnemy[ nCntEnemy ].Size.x < g_aEnemy[ nCntEnemy ].Size.z )
		{
			g_aEnemy[ nCntEnemy ].Collisoin = g_aEnemy[ nCntEnemy ].Size.z;
		}
		else
		{
			g_aEnemy[ nCntEnemy ].Collisoin = g_aEnemy[ nCntEnemy ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aEnemy[ nCntEnemy ].bUse = true;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitEnemy�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitEnemy( void )
{
	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++ )
	{
		// ���b�V�����̊J��
		if( g_aEnemy[ nCntEnemy ].pMesh != NULL )
		{
			g_aEnemy[ nCntEnemy ].pMesh->Release();
			g_aEnemy[ nCntEnemy ].pMesh = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aEnemy[ nCntEnemy ].pBuffMat != NULL )
		{
			g_aEnemy[ nCntEnemy ].pBuffMat->Release();
			g_aEnemy[ nCntEnemy ].pBuffMat = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateEnemy�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateEnemy( void )
{

//	srand((unsigned)time(NULL));
	RandEnemy = rand()%25+41;		//����
	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	BULLET *pBullet = GetBullet();
	MESHWALL *pWall = GetMeshWall();
	PROP *pProp = GetProp();
	PROW *pProw = GetProw();
	PROPMP *pPropMp = GetPropMp();
	PROPMPLIFE *pPropMpLife = GetPropMpLife();
	PROPMODELGROUP *pPropEnemy_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropEnemy_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropEnemy_03 = GetPropModel_03 ();


	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
	// �e�̔���
	//if( GetKeyboardTrigger( DIK_SPACE ) )
	//{
	//	SetBullet( g_aEnemy[ nCntEnemy ].pos, g_aEnemy[ nCntEnemy ].rot, LIFE_BULLET );
	//}

	//Enemy�������ړ�
	EnemyMove(
			&g_aEnemy[ nCntEnemy ].rot,	//����
			g_aEnemy[ nCntEnemy ].fPosMove,				//�ړ���
			DIK_UP,				//��{�^��
			DIK_DOWN,			//���{�^��
			DIK_LEFT,			//���{�^��
			DIK_RIGHT			//�E�{�^��
	);



	//�����p�x�̃`�F�b�N
	if( g_aEnemy[ nCntEnemy ].rot.y > D3DX_PI )
	{
		g_aEnemy[ nCntEnemy ].rot.y		-= D3DX_PI * 2.0f;
	}
	else if( g_aEnemy[ nCntEnemy ].rot.y < - D3DX_PI )
	{
		g_aEnemy[ nCntEnemy ].rot.y		+= D3DX_PI * 2.0f;
	}


	//Y���ړ��̃`�F�b�N
	if( g_aEnemy[ nCntEnemy ].pos.y >= 100.0f )
	{
		g_aEnemy[ nCntEnemy ].pos.y		 = 100.0f;
	}
	else if( g_aEnemy[ nCntEnemy ].pos.y <= 1.0f )
	{
		g_aEnemy[ nCntEnemy ].pos.y		 = 1.0f;
	}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if( (pWall + WALL_FRONT)->pos.z < ( g_aEnemy[ nCntEnemy ].pos.z + g_aEnemy[ nCntEnemy ].Collisoin ) )
	//	{	// ���̕�
	//		g_aEnemy[ nCntEnemy ].pos.z =( pWall + WALL_FRONT)->pos.z  - g_aEnemy[ nCntEnemy ].Collisoin;
	//	}
	//	else if( (pWall + WALL_BACK)->pos.z > ( g_aEnemy[ nCntEnemy ].pos.z - g_aEnemy[ nCntEnemy ].Collisoin ) )
	//	{	// �O�̕�
	//		g_aEnemy[ nCntEnemy ].pos.z = (pWall + WALL_BACK)->pos.z + g_aEnemy[ nCntEnemy ].Collisoin;
	//	}
		if( (pWall + WALL_LEFT)->pos.x > ( g_aEnemy[ nCntEnemy ].pos.x - g_aEnemy[ nCntEnemy ].Collisoin ) )
		{	// ���̕�
			g_aEnemy[ nCntEnemy ].pos.x =  (pWall + WALL_LEFT)->pos.x + g_aEnemy[ nCntEnemy ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aEnemy[ nCntEnemy ].pos.x + g_aEnemy[ nCntEnemy ].Collisoin ) )
		{	// �E�̕�
			g_aEnemy[ nCntEnemy ].pos.x =  (pWall + WALL_RIGHT)->pos.x - g_aEnemy[ nCntEnemy ].Collisoin;
		}
	//	if( CEILING < ( g_aEnemy[ nCntEnemy ].pos.y + g_aEnemy[ nCntEnemy ].Size.y ) )
	//	{	// �V��
	//		g_aEnemy[ nCntEnemy ].pos.y = CEILING - g_aEnemy[ nCntEnemy ].Size.y;
	//	}
		
		if( GROUND > ( g_aEnemy[ nCntEnemy ].pos.y - g_aEnemy[ nCntEnemy ].Size.y ) )
		{	// ��
			g_aEnemy[ nCntEnemy ].pos.y = GROUND + g_aEnemy[ nCntEnemy ].Size.y;
		}
		//if( pProw->bUse == true )
		//{
		//	g_aEnemy[ nCntEnemy ].time ++;
		//	if ( g_aEnemy[ nCntEnemy ].time >= (66+RandEnemy ) )
		//	{
		//		pProw->bProwUse = true;
		//		g_aEnemy[ nCntEnemy ].time = 0;
		//	}
		//}

		// �c�[���Ƃ̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
		{

		if((pProp+nCntProp)->pos.z < g_aEnemy[ nCntEnemy ].pos.z+ g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->pos.x >  g_aEnemy[ nCntEnemy ].pos.x- g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->pos.x <  g_aEnemy[ nCntEnemy ].pos.x+ g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->pos.z > g_aEnemy[ nCntEnemy ].pos.z- g_aEnemy[ nCntEnemy ].Collisoin
			&& (pProp+nCntProp)->bUse == true )
		{
			//(pProp+nCntProp)->bUse = false;
		//	pProw->bUse = true;
		//	pProw->bProwUse = false;
		//	pPropMp->bUse = true;
		//	pPropMpLife->bUse = true;
			
		}

		}
		//�e
		SetShadow( g_aEnemy[ nCntEnemy ].pos, 20.0f, 20.0f, 0, true );

		//effect
		//SetEffect(g_aEnemy[ nCntEnemy ].pos,D3DXCOLOR(200,0,152,255),10,70,EFFECTYPE_COLOR );
	}

}

//================================================================================================================================================================================================
// DrawEnemy�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawEnemy( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aEnemy[ nCntEnemy ].mtxWorld );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aEnemy[ nCntEnemy ].scl.x, g_aEnemy[ nCntEnemy ].scl.y, g_aEnemy[ nCntEnemy ].scl.z );
		D3DXMatrixMultiply( &g_aEnemy[ nCntEnemy ].mtxWorld, &g_aEnemy[ nCntEnemy ].mtxWorld, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aEnemy[ nCntEnemy ].rot.y, g_aEnemy[ nCntEnemy ].rot.x, g_aEnemy[ nCntEnemy ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aEnemy[ nCntEnemy ].mtxWorld, &g_aEnemy[ nCntEnemy ].mtxWorld, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aEnemy[ nCntEnemy ].pos.x, g_aEnemy[ nCntEnemy ].pos.y, g_aEnemy[ nCntEnemy ].pos.z );
		D3DXMatrixMultiply( &g_aEnemy[ nCntEnemy ].mtxWorld, &g_aEnemy[ nCntEnemy ].mtxWorld, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aEnemy[ nCntEnemy ].mtxWorld );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aEnemy[ nCntEnemy ].pBuffMat->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aEnemy[ nCntEnemy ].nNumMat; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aEnemy[ nCntEnemy ].pMesh->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetEnemy�֐�
// ���� void
// �߂�l 
// ���� Enemy���擾����B
//================================================================================================================================================================================================
ENEMY *GetEnemy( void )
{
	return &g_aEnemy[ 0 ];
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
void EnemyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{

	ENEMY *pEnemy = GetEnemy();
	pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pEnemy -> fPosMove;
	/*�����ړ�*/
	pEnemy -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//����ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E��ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else											//�O�ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
			pEnemy->bAutoRot = true;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//�����ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E���ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else											//��ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + 0.0f;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
		pEnemy->bAutoRot = true;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//����ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�����ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else											//���ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
		pEnemy->bAutoRot = true;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//�E��ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pEnemy->bAutoRot = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�E���ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pEnemy->bAutoRot = true;
		}
		else											//�E�ړ�
		{
			pEnemy -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pEnemy -> fPosMove;
			pEnemy -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pEnemy->bAutoRot = true;
		}
		pEnemy -> rot.y			 = pEnemy ->OldRot.y;
			pEnemy->bAutoRot = true;
	}
	else 
	{
			pEnemy->bAutoRot = false;
	}

	//���W���X�V�i�����j
	pEnemy -> pos.x += ( pEnemy->OldPos.x - pEnemy -> pos.x ) * ENEMY_INERTIA_MOVE;
	pEnemy -> pos.z += ( pEnemy->OldPos.z - pEnemy -> pos.z ) * ENEMY_INERTIA_MOVE;
}
