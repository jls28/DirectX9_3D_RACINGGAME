/*------------------------------------------------------------------------------
|	�^�C�g���F		�W���C�X�e�B�b�N�����̃w�b�_�[
|	�t�@�C�����F	joystick.cpp
|	�쐬�ҁF		AT12A244 46 LI HAOSHENG
|	�쐬���F		2016/01/24
------------------------------------------------------------------------------*/
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/
//�W���C�X�e�B�b�N�{�^���̗񋓌^
typedef enum
{
	DIJ_BUTTON_X	= 0,	//�W���C�X�e�B�b�N�{�^��X
	DIJ_BUTTON_A,			//�W���C�X�e�B�b�N�{�^��A
	DIJ_BUTTON_B,			//�W���C�X�e�B�b�N�{�^��B
	DIJ_BUTTON_Y,			//�W���C�X�e�B�b�N�{�^��Y
	DIJ_BUTTON_LB,			//�W���C�X�e�B�b�N�{�^��LB
	DIJ_BUTTON_RB,			//�W���C�X�e�B�b�N�{�^��RB
	DIJ_BUTTON_LT,			//�W���C�X�e�B�b�N�{�^��LT
	DIJ_BUTTON_RT,			//�W���C�X�e�B�b�N�{�^��RT
	DIJ_BUTTON_BACK,		//�W���C�X�e�B�b�N�{�^��BACK
	DIJ_BUTTON_START,		//�W���C�X�e�B�b�N�{�^��START
	DIJ_BUTTON_ROCKER_L,		//�W���C�X�e�B�b�N�{�^��ROCKER_L
	DIJ_BUTTON_ROCKER_R,		//�W���C�X�e�B�b�N�{�^��ROCKER_R
	DIJ_MAX
}JOYSTICKS_BUTTONS;

//�|�C���^���̍\����
typedef struct
{
	RECT		moveRect;	//��ʏ�œ�����͈�
	int			x;			//X���W
	int			y;			//Y���W
	int			moveAdd;	//�ړ���
}JSTATE;

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT	InitJoysticks( HINSTANCE hInstance, HWND hWnd );
void	UninitJoysticks( void );
void	UpdateJoysticks( void );
JSTATE	*GetJoysticksState( void );
bool	GetJoysticksPress( int nKey );
bool	GetJoysticksTrigger( int nKey );
bool	GetJoysticksRelease( int key );
bool	GetJoysticksRepeat( int nKey );

#endif