//=============================================================================
//
// �f�o�b�N�̏��� [debugProc.cpp]
// 
//
//=============================================================================
/*******************************************************************************
* �X�V�����F
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include <stdio.h>
#include <varargs.h>
#include <stdarg.h>
#include "input.h"
#include "debugProc.h"
#include "bullet.h"
#include "modelbody.h"
#include "camera.h"
#include "propmodel_Group.h"
#include "mouse.h"
#include "obstacle.h"
#include "score.h"
#include "player.h"
/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/
#define FONT_MAX	( 1024 )		//�f�o�b�O������̍ő吔
/*******************************************************************************
/* �O���[�o���ϐ�
********************************************************************************/
LPD3DXFONT g_DebugFont = NULL;		//�t�H���g�̃|�C���^

char g_StrDebug [FONT_MAX];		// �f�o�b�N�̕�����̍ő吔
RECT rect = { 0,      0, SCREEN_WIDTH, SCREEN_HEIGHT };
/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
void PrintDebugProc( char *fmt, ... );
/********************************************************************************
�֐���: �f�o�b�N�̏������֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
HRESULT InitDebugProc( void )
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateFont( pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_DebugFont );		//�f�o�C�X�ƃt�H���g�p�̃t�H���g �I�u�W�F�N�g���쐬
	memset(g_StrDebug,		//�^�[�Q�b�g�ւ̃|�C���^�[
			0,		//�ݒ肷�镶��
			sizeof g_StrDebug		//������
			);
	return S_OK;
}
/********************************************************************************
�֐���: �f�o�b�N�̕`��֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void DrawDebugProc(void)
{	
	g_DebugFont -> DrawText(
						 NULL,		//// �f�o�C�X�R���e�L�X�g�̃n���h��
						 &g_StrDebug[ 0 ],		// �`�悷��e�L�X�g
						 -1,		// �e�L�X�g�̒���
						 &rect,		// �e�L�X�g��`�悷�钷���`�̈�
						 DT_LEFT,		//�e�L�X�g���������ɂ��܂�
						 D3DCOLOR_RGBA( 255, 0, 255, 255 )		//�F�A�w�i�F�ŕ`��
						 );

	memset(g_StrDebug,		//�^�[�Q�b�g�ւ̃|�C���^�[
			0,		//�ݒ肷�镶��
			sizeof g_StrDebug		//������
			);
}
/********************************************************************************
�֐���: �ό������X�g�ɃA�N�Z�X���܂�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : 
*******************************************************************************/
void PrintDebugProc (char *fmt,	...)
{
	int font;

	//�������`�F�b�N
	font = strlen( g_StrDebug );

	va_list list;
	va_start( list, fmt );//�������X�g�ւ̃|�C���^���w�肵�܂�
	vsprintf( &g_StrDebug[ font ], fmt, list);
	va_end( list );
}
/********************************************************************************
�֐���: �f�o�b�N�̊J���֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UninitDebugProc(void)
{
	if( g_DebugFont != NULL )
	{
		( g_DebugFont ) -> Release();
		g_DebugFont = NULL;
	}
}
/********************************************************************************
�֐���: �f�o�b�N�̍X�V�֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UpdateDebugProc(void)
{
	//�J�������擾
	CAMERA		pCamera	= GetCamera();

	//���f�����擾
	MODELBODY		*pModelBody		= GetModelBody();

	PROPMODELGROUP		*pPropModel_01		= GetPropModel_01();

	PROPMODELGROUP		*pPropModel_02		= GetPropModel_02();

	PROPMODELGROUP		*pPropModel_03		= GetPropModel_03();

	MSTATE		*pMouse		=GetMouseState();

	OBSTACLE *pObstacle_Box = GetObstacle_Box();

	SCORE *pScore = GetScore();

	MODEL *pModel = GetModel();

	PLAYER *pPlayer = GetPlayer();
	PrintDebugProc( "*** �J�����̏�� ***\n" );
	PrintDebugProc( "[�J�����̎��_       ( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera.posV.x, pCamera.posV.y, pCamera.posV.z );
	PrintDebugProc( "[�J�����̒����_     ( X:%.2f Y:%.2f Z:%.2f )]\n", pCamera.posR.x, pCamera.posR.y, pCamera.posR.z );
	PrintDebugProc( "[�J�����̌���       ( %.2f )]\n", pCamera.rot.y );
	PrintDebugProc( "[���_�ƒ����_�̋��� ( %.2f )]\n\n", pCamera.fDistance );

	PrintDebugProc( "*** ���f���̏�� ***\n" );
	PrintDebugProc( "[���f���̈ʒu       ( X:%.2f Y:%.2f Z:%.2f )]\n", pModelBody ->OldPos .x, pModelBody -> OldPos.y, pModelBody -> OldPos.z );
	PrintDebugProc( "[���f���̌���       ( %.2f )\n", pModelBody -> rot.y );
	PrintDebugProc( "[���f���ړI�̌���   ( %.2f )\n\n", pModelBody -> OldRot.y );

	PrintDebugProc( "*** ���f���̑��� ***\n" );
	PrintDebugProc( "�O�ړ�       -> W\n" );
	PrintDebugProc( "��ړ�       -> S\n" );
	PrintDebugProc( "���ړ�       -> A\n" );
	PrintDebugProc( "�E�ړ�       -> D\n" );
	PrintDebugProc( "�㏸         -> I\n" );
	PrintDebugProc( "���~         -> K\n" );
	PrintDebugProc( "�e����       -> SPACE\n" );
	PrintDebugProc( "������       -> LSHIFT\n" );
	PrintDebugProc( "�E����       -> RSHIFT\n" );
	PrintDebugProc( "�ʒu���Z�b�g -> ENTER\n\n" );
	PrintDebugProc( "�}�E�X�ʒu:x:%d,y:%d\n",pMouse->x,pMouse->y);
	PrintDebugProc( "score:%d\n",pScore->g_nScore);

	PrintDebugProc( "0model:x:%.2f y:%.2f z:%.2f \n",(pModel+0)->pos.x,(pModel+0)->pos.y,(pModel+0)->pos.z);
	PrintDebugProc( "1model:x:%.2f y:%.2f z:%.2f \n",(pModel+1)->pos.x,(pModel+1)->pos.y,(pModel+1)->pos.z);
	PrintDebugProc( "2model:x:%.2f y:%.2f z:%.2f \n",(pModel+2)->pos.x,(pModel+2)->pos.y,(pModel+2)->pos.z);
	PrintDebugProc( "3model:x:%.2f y:%.2f z:%.2f \n",(pModel+3)->pos.x,(pModel+3)->pos.y,(pModel+3)->pos.z);
	PrintDebugProc( "4model:x:%.2f y:%.2f z:%.2f \n",(pModel+4)->pos.x,(pModel+4)->pos.y,(pModel+4)->pos.z);
	PrintDebugProc( "5model:x:%.2f y:%.2f z:%.2f \n",(pModel+5)->pos.x,(pModel+5)->pos.y,(pModel+5)->pos.z);

	PrintDebugProc( "player:x:%.2f y:%.2f z:%.2f \n",pPlayer->pos.x,pPlayer->pos.y,pPlayer->pos.z);
}
