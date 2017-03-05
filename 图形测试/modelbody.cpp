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
#include "modelbody.h"
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
#include "modellegL.h"
#include "modellegR.h"
#include "runleg.h"
#include "money.h"
#include "score.h"
#include "obstacle.h"
#include "boxscore.h"
#include "fade.h"
#include "boxscore.h"
#include "score.h"
#include "explosion.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MODELBODY_INERTIA_MOVE	( 0.025f )					//���������W��
#define GR							0.002f				// �d�͉����x
#define SHELL_FIRST_VEL				0.15f				// �C�e����
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void ModelBodyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY );
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
MODELBODY g_aModelBody[ MAX_MODELBODY ];		// ���f���̏��

//================================================================================================================================================================================================
// InitModelBody�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitModelBody( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++ )
	{
		// X�t�@�C���̓ǂݍ���
		if( FAILED( D3DXLoadMeshFromX( "data\\MODEL\\model.x",
									   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
									   pDevice,
									   NULL,
									   &g_aModelBody[ nCntModelBody ].pBuffMatModelBody,		// �}�e���A�����
									   NULL,
									   &g_aModelBody[ nCntModelBody ].nNumMatModelBody,			// �}�e���A����
									   &g_aModelBody[ nCntModelBody ].pMeshModelBody ) ) )		// ���b�V�����
		{
			return E_FAIL;
		}

		// ���f���̏����ݒ�
		g_aModelBody[ nCntModelBody ].pos = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].OldPos = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].rot = D3DXVECTOR3( 0.0f,  3.14f, 0.0f );
		g_aModelBody[ nCntModelBody ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aModelBody[ nCntModelBody ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aModelBody[ nCntModelBody ].fPosMove = POSMOVE_MODELBODY;
		g_aModelBody[ nCntModelBody ].time = 0;
		g_aModelBody[ nCntModelBody ].Rand = 0;
		g_aModelBody[ nCntModelBody ].bKeyUse = false;
		g_aModelBody[ nCntModelBody ].bJump = false;
		g_aModelBody[ nCntModelBody ].bMove = false;
		g_aModelBody[ nCntModelBody ].bUseCheck = false;
		g_aModelBody[ nCntModelBody ].bUseCheckCat = false;
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = g_aModelBody[ nCntModelBody ].pMeshModelBody->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( g_aModelBody[ nCntModelBody ].pMeshModelBody->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		g_aModelBody[ nCntModelBody ].pMeshModelBody->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < g_aModelBody[ nCntModelBody ].Min.x )		g_aModelBody[ nCntModelBody ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > g_aModelBody[ nCntModelBody ].Max.x )		g_aModelBody[ nCntModelBody ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < g_aModelBody[ nCntModelBody ].Min.y )		g_aModelBody[ nCntModelBody ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > g_aModelBody[ nCntModelBody ].Max.y )		g_aModelBody[ nCntModelBody ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < g_aModelBody[ nCntModelBody ].Min.z )		g_aModelBody[ nCntModelBody ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > g_aModelBody[ nCntModelBody ].Max.z )		g_aModelBody[ nCntModelBody ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		g_aModelBody[ nCntModelBody ].pMeshModelBody->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		g_aModelBody[ nCntModelBody ].Size.x = ( fabs( g_aModelBody[ nCntModelBody ].Min.x ) + fabs( g_aModelBody[ nCntModelBody ].Max.x ) ) / 2;
		g_aModelBody[ nCntModelBody ].Size.y = ( fabs( g_aModelBody[ nCntModelBody ].Min.y ) + fabs( g_aModelBody[ nCntModelBody ].Max.y ) ) / 2;
		g_aModelBody[ nCntModelBody ].Size.z = ( fabs( g_aModelBody[ nCntModelBody ].Min.z ) + fabs( g_aModelBody[ nCntModelBody ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
		if( g_aModelBody[ nCntModelBody ].Size.x < g_aModelBody[ nCntModelBody ].Size.z )
		{
			g_aModelBody[ nCntModelBody ].Collisoin = g_aModelBody[ nCntModelBody ].Size.z;
		}
		else
		{
			g_aModelBody[ nCntModelBody ].Collisoin = g_aModelBody[ nCntModelBody ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		g_aModelBody[ nCntModelBody ].bUse = false;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitModelBody�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitModelBody( void )
{
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++ )
	{
		// ���b�V�����̊J��
		if( g_aModelBody[ nCntModelBody ].pMeshModelBody != NULL )
		{
			g_aModelBody[ nCntModelBody ].pMeshModelBody->Release();
			g_aModelBody[ nCntModelBody ].pMeshModelBody = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_aModelBody[ nCntModelBody ].pBuffMatModelBody != NULL )
		{
			g_aModelBody[ nCntModelBody ].pBuffMatModelBody->Release();
			g_aModelBody[ nCntModelBody ].pBuffMatModelBody = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdateModelBody�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateModelBody( void )
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
	PROPMODELGROUP *pPropModelBody_01 = GetPropModel_01 ();

	PROPMODELGROUP *pPropModelBody_02 = GetPropModel_02 ();

	PROPMODELGROUP *pPropModelBody_03 = GetPropModel_03 ();

	MODELLEGL *pModelLegL = GetModelLegL ();

	MODELLEGR *pModelLegR = GetModelLegR ();

	RUNLEG *pRunleg = GetRunLeg();

	MONEY *pMoney = GetMoney();

	OBSTACLE *pObstacle_Cat_01 = GetObstacle_Cat_01();

	SCORE *pScoreCheck = GetScore();
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++)
	{
		if(g_aModelBody[ nCntModelBody ].bUse == true)
		{
			//SetExplosion(g_aModelBody[ nCntModelBody ].pos);
	g_aModelBody[ nCntModelBody ].Rand = rand()%25+41;		//����
	//ModelBody�������ړ�
	ModelBodyMove(
			&camera.rot,	//����
			g_aModelBody[ nCntModelBody ].fPosMove,				//�ړ���
			DIK_UP,				//��{�^��
			DIK_DOWN,			//���{�^��
			DIK_LEFT,			//���{�^��
			DIK_RIGHT			//�E�{�^��
	);

		//ModelBody����
		//if( GetKeyboardPress( DIK_LSHIFT ) )		//������
		//{
		//	g_aModelBody[ nCntModelBody ].rot.y		-= D3DX_PI * 0.025f;
		//	g_aModelBody[ nCntModelBody ].OldRot.y	 = g_aModelBody[ nCntModelBody ].rot.y;
		//}
		//else if( GetKeyboardPress( DIK_RSHIFT ) )	//�E����
		//{
		//g_aModelBody[ nCntModelBody ].rot.y		+= D3DX_PI * 0.025f;
		//g_aModelBody[ nCntModelBody ].OldRot.y	 = g_aModelBody[ nCntModelBody ].rot.y;
		//}

	//�����p�x�̃`�F�b�N
	if( g_aModelBody[ nCntModelBody ].rot.y > D3DX_PI )
	{
		g_aModelBody[ nCntModelBody ].rot.y		-= D3DX_PI * 2.0f;
	}
	else if( g_aModelBody[ nCntModelBody ].rot.y < - D3DX_PI )
	{
		g_aModelBody[ nCntModelBody ].rot.y		+= D3DX_PI * 2.0f;
	}

	//Y���ړ�����
	//if( GetKeyboardPress( DIK_I ) )
	//{
	//	g_aModelBody[ nCntModelBody ].pos.y		+= g_aModelBody[ nCntModelBody ].fPosMove;
	//}
	//else if( GetKeyboardPress( DIK_K ) )
	//{
	//	g_aModelBody[ nCntModelBody ].pos.y		-= g_aModelBody[ nCntModelBody ].fPosMove;
	//}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if( (pWall + WALL_LEFT)->pos.x > ( g_aModelBody[ nCntModelBody ].OldPos.x - g_aModelBody[ nCntModelBody ].Collisoin ) )
		{	// ���̕�
			g_aModelBody[ nCntModelBody ].OldPos.x =  (pWall + WALL_LEFT)->pos.x + g_aModelBody[ nCntModelBody ].Collisoin;
		}
		else if(  (pWall + WALL_RIGHT)->pos.x < ( g_aModelBody[ nCntModelBody ].OldPos.x + g_aModelBody[ nCntModelBody ].Collisoin ) )
		{	// �E�̕�
			g_aModelBody[ nCntModelBody ].OldPos.x =  (pWall + WALL_RIGHT)->pos.x - g_aModelBody[ nCntModelBody ].Collisoin;
		}

		if(( g_aModelBody[ nCntModelBody ].OldPos.z - g_aModelBody[ nCntModelBody ].Collisoin ) >= 20550.0f )
		{	// �O�̕�
			  g_aModelBody[ nCntModelBody ].OldPos.z = 20550.0f + g_aModelBody[ nCntModelBody ].Collisoin;
			  //if(pScoreCheck->bCheck == true)
			  //{
			  SetFade(FADE_OUT,MODE_RESULT);
	/*		  }*/
		}
		else if( -300.0f >= ( g_aModelBody[ nCntModelBody ].OldPos.z + g_aModelBody[ nCntModelBody ].Collisoin ) )
		{	// ���̕�
			g_aModelBody[ nCntModelBody ].OldPos.z =-300.0f  - g_aModelBody[ nCntModelBody ].Collisoin;
		}
		if( GROUND >  g_aModelBody[ nCntModelBody ].OldPos.y)
		{	// ��
			g_aModelBody[ nCntModelBody ].OldPos.y = 1.0f;
		}
		if( pProw->bUse == true )
		{
			g_aModelBody[ nCntModelBody ].time ++;
			if ( g_aModelBody[ nCntModelBody ].time >= (66+g_aModelBody[ nCntModelBody ].Rand ) )
			{
				pProw->bProwUse = true;
				g_aModelBody[ nCntModelBody ].time = 0;
			}
		}

		// �c�[���Ƃ̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntProp = 0; nCntProp < MAX_PROP; nCntProp++ )
		{

		if((pProp+nCntProp)->pos.z < g_aModelBody[ nCntModelBody ].pos.z+ g_aModelBody[ nCntModelBody ].Collisoin
			&& ((pProp+nCntProp)->pos.x+30.0f) >  g_aModelBody[ nCntModelBody ].pos.x- g_aModelBody[ nCntModelBody ].Collisoin
			&& ((pProp+nCntProp)->pos.x-30.0f) <  g_aModelBody[ nCntModelBody ].pos.x+ g_aModelBody[ nCntModelBody ].Collisoin
			&& (pProp+nCntProp)->pos.z > g_aModelBody[ nCntModelBody ].pos.z- g_aModelBody[ nCntModelBody ].Collisoin
			&& (pProp+nCntProp)->bUse == true )
		{
			(pProp+nCntProp)->bUse = false;
			pProw->bUse = true;
			pProw->bProwUse = false;
			pPropMp->bUse = true;
			pPropMpLife->bUse = true;
			InitPropModel_Group();
			
		}

		}
		// Money�Ƃ̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntMoney = 0; nCntMoney < MAX_MONEY; nCntMoney++ )
		{

			if((pMoney+nCntMoney)->pos.z < g_aModelBody[ nCntModelBody ].pos.z+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->pos.x >  g_aModelBody[ nCntModelBody ].pos.x- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->pos.x <  g_aModelBody[ nCntModelBody ].pos.x+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->pos.z > g_aModelBody[ nCntModelBody ].pos.z- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pMoney+nCntMoney)->bUse == true )
			{
				(pMoney+nCntMoney)->bUse = false;
				if(!g_aModelBody[ nCntModelBody ].bUseCheck )
				{
					AddScore(500);
					g_aModelBody[ nCntModelBody ].bUseCheck = true;
				}
			}
			else
			{
				g_aModelBody[ nCntModelBody ].bUseCheck = false;
			}
		}
		// Cat1�Ƃ̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for( int nCntCat_01 = 0; nCntCat_01 < MAX_OBSTACLE_CAT_01; nCntCat_01++ )
		{

			if((pObstacle_Cat_01+nCntCat_01)->pos.z < g_aModelBody[ nCntModelBody ].pos.z+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->pos.x >  g_aModelBody[ nCntModelBody ].pos.x- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->pos.x <  g_aModelBody[ nCntModelBody ].pos.x+ g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->pos.z > g_aModelBody[ nCntModelBody ].pos.z- g_aModelBody[ nCntModelBody ].Collisoin
				&& (pObstacle_Cat_01+nCntCat_01)->bUse == true 
				)
			{
				(pObstacle_Cat_01+nCntCat_01)->bRot = true;

				if(!g_aModelBody[ nCntModelBody ].bUseCheckCat && (pObstacle_Cat_01+nCntCat_01)->bCatRotCheck == false)
				{
					AddScore(-1000);
					g_aModelBody[ nCntModelBody ].bUseCheckCat = true;
					(pObstacle_Cat_01+nCntCat_01)->bCatRotCheck = true; 
				}
			}
			else 
			{
				g_aModelBody[ nCntModelBody ].bUseCheckCat = false;
				(pObstacle_Cat_01+nCntCat_01)->bCatRotCheck = false; 
			}
			
		}
		//�e
		SetShadow( g_aModelBody[ nCntModelBody ].pos, 20.0f, 20.0f, 0, true );

		//effect
		SetEffect(g_aModelBody[ nCntModelBody ].pos,D3DXCOLOR(200,0,152,255),10,70,EFFECTYPE_COLOR );
	}
	}
}

//================================================================================================================================================================================================
// DrawModelBody�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawModelBody( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );
	// �����_�[�X�e�[�g�̐ݒ�iz�e�X�g�j
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z�l�̍X�V
	// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// ���̒l���A���t�@�l���傫����Ε`�悷��B
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// �A���t�@�l�B0�œ����ȕ����B
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aModelBody[ nCntModelBody ].scl.x, g_aModelBody[ nCntModelBody ].scl.y, g_aModelBody[ nCntModelBody ].scl.z );
		D3DXMatrixMultiply( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aModelBody[ nCntModelBody ].rot.y, g_aModelBody[ nCntModelBody ].rot.x, g_aModelBody[ nCntModelBody ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aModelBody[ nCntModelBody ].pos.x, g_aModelBody[ nCntModelBody ].pos.y, g_aModelBody[ nCntModelBody ].pos.z );
		D3DXMatrixMultiply( &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aModelBody[ nCntModelBody ].mtxWorldModelBody );

		// �L���X�g�ϊ�
		pMat = ( D3DXMATERIAL* )g_aModelBody[ nCntModelBody ].pBuffMatModelBody->GetBufferPointer();

		for( int nCntMat = 0; nCntMat < ( int )g_aModelBody[ nCntModelBody ].nNumMatModelBody; nCntMat++ )
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ��B���ꂪ�Ȃ��ƑO�Ɏg��ꂽ�e�N�X�`���̐ݒ肪�����Ă��āA���f�����Â��Ȃ����肷��B

			// ���b�V���̕`��
			g_aModelBody[ nCntModelBody ].pMeshModelBody->DrawSubset( nCntMat );
		}
	}

	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}

//================================================================================================================================================================================================
// *GetModelBody�֐�
// ���� void
// �߂�l 
// ���� ModelBody���擾����B
//================================================================================================================================================================================================
MODELBODY *GetModelBody( void )
{
	return &g_aModelBody[ 0 ];
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
void ModelBodyMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELBODY *pModelBody = GetModelBody();
	pModelBody -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E��ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else											//�O�ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
		pModelBody->bKeyUse = true;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//�����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E���ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else											//��ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + 0.0f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
		pModelBody->bKeyUse = true;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else											//���ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
		pModelBody->bKeyUse = true;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//�E��ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�E���ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//�E�ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
			pModelBody->bAutoRot = true;
			pModelBody->bKeyUse = true;
	}
	else 
	{
			pModelBody->bAutoRot = false;
			pModelBody->bKeyUse = false;
	}

	//���W���X�V�i�����j
	pModelBody -> pos.x += ( pModelBody->OldPos.x - pModelBody -> pos.x ) * MODELBODY_INERTIA_MOVE;
	pModelBody -> pos.z += ( pModelBody->OldPos.z - pModelBody -> pos.z ) * MODELBODY_INERTIA_MOVE;
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
void ModelBodyMovejoystick( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	MODELBODY *pModelBody = GetModelBody();
	pModelBody -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetJoysticksTrigger( UP_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//�E��ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else											//�O�ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
			pModelBody->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( DOWN_KEY ) )
	{
		if( GetJoysticksTrigger( LEFT_KEY ) )				//�����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( RIGHT_KEY ) ) )	//�E���ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//��ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + 0.0f;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( LEFT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//�����ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//���ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
		pModelBody->bAutoRot = true;
	}
	else if( GetJoysticksTrigger( RIGHT_KEY ) )
	{
		if( GetJoysticksTrigger( UP_KEY ) )				//�E��ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
			pModelBody->bAutoRot = true;
		}
		else if( ( GetJoysticksTrigger( DOWN_KEY ) ) )		//�E���ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
			pModelBody->bAutoRot = true;
		}
		else											//�E�ړ�
		{
			pModelBody -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pModelBody -> fPosMove;
			pModelBody -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
			pModelBody->bAutoRot = true;
		}
		pModelBody -> rot.y			 = pModelBody ->OldRot.y;
			pModelBody->bAutoRot = true;
	}
	else 
	{
			pModelBody->bAutoRot = false;
	}
	//���W���X�V�i�����j
	//pModelBody -> pos.x += ( pModelBody->OldPos.x - pModelBody -> pos.x ) * MODELBODY_INERTIA_MOVE;
	//pModelBody -> pos.z += ( pModelBody->OldPos.z - pModelBody -> pos.z ) * MODELBODY_INERTIA_MOVE;
}
void ModelJump(void)
{
	for( int nCntModelBody = 0; nCntModelBody < MAX_MODELBODY; nCntModelBody++)
	{

		if(g_aModelBody[ nCntModelBody ].bJump == true)
		{
			g_aModelBody[ nCntModelBody ].vel = D3DXVECTOR3( SHELL_FIRST_VEL * cosf( g_aModelBody[ nCntModelBody ].rot.y),
								  SHELL_FIRST_VEL * sinf(g_aModelBody[ nCntModelBody ].rot.y ),
								  SHELL_FIRST_VEL * cosf( g_aModelBody[ nCntModelBody ].rot.y ));
			g_aModelBody[ nCntModelBody ].pos.x += g_aModelBody[ nCntModelBody ].vel.x;
			g_aModelBody[ nCntModelBody ].pos.y += g_aModelBody[ nCntModelBody ].vel.y;
			g_aModelBody[ nCntModelBody ].pos.z += g_aModelBody[ nCntModelBody ].vel.z;
			g_aModelBody[ nCntModelBody ].vel.y -= GR;
		}
		if(g_aModelBody[ nCntModelBody ].pos.y >= 80.0f)
		{
			g_aModelBody[ nCntModelBody ].bJump = false;
		}
	}
}