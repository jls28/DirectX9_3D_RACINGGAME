/*******************************************************************************
* �^�C�g���F �J�����֐�
* �t�@�C�����F camera.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/16
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/

//************************************************************************************************************************************************************************************************
// �C���N���[�h�t�@�C��
//************************************************************************************************************************************************************************************************
#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "camera.h"

#include "use.h"
#include "time.h"
#include "modelbody.h"
//************************************************************************************************************************************************************************************************
// �}�N����`
//************************************************************************************************************************************************************************************************
#define POSMOVE_CAMERA	(    2.00f )	// �J�������W�̈ړ���
#define ROTMOVE_CAMERA	(    0.01f )	// �J������]�̈ړ���
#define ZOOM			(   10.00f )	// �Y�[���B���_(posV)�ƒ����_(posR)�̋�������ԒZ���B
#define WIDE			( 1000.00f )	// ���C�h�B���_(posV)�ƒ����_(posR)�̋�������ԉ����B
#define CORRECTION_X		(0.0f)
#define CORRECTION_Z		(100.0f)
#define TIME_CAMERA			(1)
//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
CAMERA g_camera;	// �J�������

float Camera_Move;		//�J�����̈ړ���
//================================================================================================================================================================================================
// InitCamera�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void InitCamera( void )
{
	// ���_�i�����j
	g_camera.posV = D3DXVECTOR3( 0.0f, 80.0f, -200.0f );	// 0, 100~200, -100~-300

	// �����_�i���Ă��j
	g_camera.posR = D3DXVECTOR3( 0.0f,   60.0f,    0.0f );

	// ������x�N�g���i�J�����������j
	g_camera.vecU = D3DXVECTOR3( 0.0f,   1.0f,    0.0f );	// �قڕς��Ȃ��B

	// �����i�p�x�j
	g_camera.rot  = D3DXVECTOR3( 0.0f,   0.0f,    0.0f );

	Camera_Move = POSMOVE_CAMERA;		//�J�����̈ړ��ʂ̏�����

	// posV��posR�̑Ίp���̒���
	g_camera.fDistance = sqrtf( ( ( g_camera.posR.x - g_camera.posV.x ) * ( g_camera.posR.z - g_camera.posV.z ) ) 
							  + ( ( g_camera.posR.z - g_camera.posV.z ) * ( g_camera.posR.z - g_camera.posV.z ) ) );

	g_camera.bRotate = false;

	g_camera.correction_x = CORRECTION_X;

	g_camera.correction_z = CORRECTION_Z;

	g_camera.wait =TIME_CAMERA;
}

//================================================================================================================================================================================================
// UninitCamera�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitCamera( void )
{
}

//================================================================================================================================================================================================
// UpdateCamera�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdateCamera( void )
{
	//float rot;
	// ���f���̃|�C���^���擾
	MODELBODY *pModelBody = GetModelBody();
	//���f���J�����̒Ǐ]
	g_camera.posR.x = pModelBody -> pos.x;														//���f���̍��W����posR(�����_)�����߂�B
	g_camera.posR.z = pModelBody -> pos.z;														//���f���̍��W����posR(�����_)�����߂�B
	g_camera.posV.x = g_camera.posR.x - (sinf( g_camera.rot.y )) * g_camera.fDistance;		//posR(�����_)����posV(���_)�����߂�B
	g_camera.posV.z = g_camera.posR.z - (cosf( g_camera.rot.y )) * g_camera.fDistance;		//posR(�����_)����posV(���_)�����߂�B

	//if( GetKeyboardPress( DIK_F4) )			//�J�����̉�荞�ݎg�p����
	//{
	//	pModel->bAutoRot = false;
	//}
	//else if( GetKeyboardPress( DIK_F5) )			//�J�����̉�荞�ݎg�p���Ȃ�
	//{
	//	pModel->bAutoRot = true;
	//}

	//if(pModel->bAutoRot == false)
	//{
	//	if(g_camera.wait>=0)
	//	{
	//		g_camera.wait--;
	//	}
	//}
	//else
	//{
	//	g_camera.wait =TIME_CAMERA;
	//}
	//if(g_camera.wait <= 0)
	//{
	//	g_camera.RotCheck.y = pModel->rot.y + D3DX_PI;
	//	//�����p�x�̃`�F�b�N
	//	if( g_camera.RotCheck.y > D3DX_PI )
	//	{
	//		g_camera.RotCheck.y -= D3DX_PI * 2.0f;

	//	}
	//	if( g_camera.RotCheck.y < - D3DX_PI )
	//	{
	//		g_camera.RotCheck.y += D3DX_PI * 2.0f;
	//	}
	//	
	//	rot = g_camera.RotCheck.y -g_camera.rot.y;

	//	if( rot > D3DX_PI )
	//	{
	//		rot -= D3DX_PI * 2.0f;
	//	}
	//	if( rot < - D3DX_PI )
	//	{
	//		rot += D3DX_PI * 2.0f;
	//	}
	//	g_camera.rot.y += rot*0.08f;
	//	g_camera.bRotate = true;
	//}
/****************************************************************************************************************************************************************/
	//���_����
	if( GetKeyboardPress( DIK_Z ) )			//������
	{
		g_camera.rot.y += D3DX_PI * 0.01f;
		g_camera.bRotate = true;			//���񒆐S�𒍎��_�ɐݒ�
	}
	else if( GetKeyboardPress( DIK_C ) )	//�E����
	{
		g_camera.rot.y -= D3DX_PI * 0.01f;
		g_camera.bRotate = true;			//���񒆐S�𒍎��_�ɐݒ�
	}

	//�����_����
	if( GetKeyboardPress( DIK_Q ) )			//������
	{
		g_camera.rot.y -= D3DX_PI * 0.01f;
	}
	else if( GetKeyboardPress( DIK_E ) )	//�E����
	{
		g_camera.rot.y += D3DX_PI * 0.01f;
	}

	//���_����
	if( GetKeyboardPress( DIK_Y ) )			//��ړ�
	{
		g_camera.posV.y += 2.5f;
	}
	else if( GetKeyboardPress( DIK_N ) )	//���ړ�
	{
		g_camera.posV.y -= 2.5f;
	}

	//�����_����
	if( GetKeyboardPress( DIK_T ) )			//��ړ�
	{
		g_camera.posR.y += 2.5f;
	}
	else if( GetKeyboardPress( DIK_B ) )	//���ړ�
	{
		g_camera.posR.y -= 2.5f;
	}

	//���_�ƒ����_�̋�������
	if( GetKeyboardPress( DIK_U ) )
	{
		g_camera.fDistance += 2.0f;
		g_camera.bRotate = true;
	}
	else if( GetKeyboardPress( DIK_M ) )
	{
		g_camera.fDistance -= 2.0f;
		g_camera.bRotate = true;
	}

	//���_�ƒ����_�̋����̃`�F�b�N
	if( g_camera.fDistance > 300.0f )
	{
		g_camera.fDistance = 300.0f;
	}
	else if( g_camera.fDistance < 100.0f )
	{
		g_camera.fDistance = 100.0f;
	}
		//�����p�x�̃`�F�b�N
	if( g_camera.rot.y > D3DX_PI )
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	if( g_camera.rot.y < - D3DX_PI )
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���_���S
	if( g_camera.bRotate == true)
	{
		g_camera.posV.x = g_camera.posR.x - g_camera.fDistance * sinf( g_camera.rot.y );
		g_camera.posV.z = g_camera.posR.z - g_camera.fDistance * cosf( g_camera.rot.y );
		g_camera.bRotate = false;
	}

	//�����_���S
	else
	{
		g_camera.posR.x = g_camera.posV.x + g_camera.fDistance * sinf( g_camera.rot.y );
		g_camera.posR.z = g_camera.posV.z + g_camera.fDistance * cosf( g_camera.rot.y );
	}
		MESHWALL *pWall = GetMeshWall();
		// �ǂƏ��ƓV��̏Փ˔���//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if( (pWall + WALL_FRONT)->pos.z < ( g_camera.posR.z + pModel->Collisoin ) )
	//	{	// ���̕�
	//		g_camera.posR.z =( pWall + WALL_FRONT)->pos.z  - pModel->Collisoin;
	//		g_camera.posV.z =g_camera.posR.z-CORRECTION_Z;
	//	}
	//	else if( (pWall + WALL_BACK)->pos.z > ( g_camera.posR.z - pModel->Collisoin ) )
	//	{	// �O�̕�
	//		g_camera.posR.z = (pWall + WALL_BACK)->pos.z + pModel->Collisoin;
	//		g_camera.posV.z =g_camera.posR.z-CORRECTION_Z;
	//	}	
	//	if( (pWall + WALL_LEFT)->pos.x > ( g_camera.posR.x - pModel->Collisoin ) )
	//	{	// ���̕�
	//		g_camera.posR.x =  (pWall + WALL_LEFT)->pos.x + pModel->Collisoin;
	//		g_camera.posV.x =g_camera.posR.x-CORRECTION_X;
	//	}
	//	else if(  (pWall + WALL_RIGHT)->pos.x < ( g_camera.posR.x + pModel->Collisoin ) )
	//	{	// �E�̕�
	//		g_camera.posR.x =  (pWall + WALL_RIGHT)->pos.x - pModel->Collisoin;
	//		g_camera.posV.x =g_camera.posR.x-CORRECTION_X;
	//	}
	//	if( CEILING < ( g_camera.posR.y + pModel->Size.y ) )
	//	{	// �V��
	//		g_camera.posR.y = CEILING - pModel->Size.y;
	//	}
	//	else if( GROUND > ( g_camera.posR.y - pModel->Size.y ) )
	//	{	// ��
	//		g_camera.posR.y = GROUND + pModel->Size.y;
	//	}
}
//================================================================================================================================================================================================
// DrawCamera�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawCamera( void )
{

}

//================================================================================================================================================================================================
// SetCamera�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void SetCamera( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &g_camera.mtxView );

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH( &g_camera.mtxProjection,
							    ( D3DX_PI / 4 ),						// ����p�i�J�����̃����Y�̂悤�ɁA�L�por�]���j
							    ( SCREEN_WIDTH / SCREEN_HEIGHT ),		// �A�X�y�N�g��(16:9)
							    NEAR_Z,									// NearZ�l�i�J�����ɉf���͈͂́A�őO�̋����j
							    FAR_Z );								// Far�l  �i�J�����ɉf���͈͂́A�ŉ��̋����j

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_PROJECTION, &g_camera.mtxProjection );

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &g_camera.mtxView );

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH( &g_camera.mtxView,
					    &g_camera.posV,
					    &g_camera.posR,
					    &g_camera.vecU );

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform( D3DTS_VIEW, &g_camera.mtxView );
}

//================================================================================================================================================================================================
// GetCameraPosV�֐�
// ���� void
// �߂�l D3DXVECTOR3
// ���� 
//================================================================================================================================================================================================
D3DXVECTOR3 GetCameraPosV( void )
{
	return g_camera.posV;
}

//================================================================================================================================================================================================
// GetCameraPosR�֐�
// ���� void
// �߂�l D3DXVECTOR3
// ���� 
//================================================================================================================================================================================================
D3DXVECTOR3 GetCameraPosR( void )
{
	return g_camera.posR;
}

//================================================================================================================================================================================================
// GetCamera�֐�
// ���� void
// �߂�l D3DXVECTOR3
// ���� 
//================================================================================================================================================================================================
CAMERA GetCamera( void )
{
	return g_camera;
}
