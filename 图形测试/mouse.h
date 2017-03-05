/*------------------------------------------------------------------------------
|	�^�C�g���F		�}�E�X�����̃w�b�_�[
|	�t�@�C�����F	mouse.cpp
|	�쐬�ҁF		AT12A244 46 LI HAOSHENG
|	�쐬���F		2016/01/24
------------------------------------------------------------------------------*/
#ifndef _MOUSE_H_
#define _MOUSE_H_

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/
//�}�E�X�{�^���̗񋓌^
typedef enum
{
	DIM_LEFT		= 0,		//�}�E�X���{�^��
	DIM_RIGHT,					//�}�E�X�E�{�^��
	DIM_CENTER,					//�}�E�X���{�^��
	DIM_MAX
}MOUSE_BUTTONS;

//�}�E�X�|�C���^���̍\����
typedef struct
{
	RECT		moveRect;	//��ʏ�œ�����͈�
	int			x;			//X���W
	int			y;			//Y���W
	int			moveAdd;	//�ړ���
}MSTATE;

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT	InitMouse( HINSTANCE hInstance, HWND hWnd );
void	UninitMouse( void );
void	UpdateMouse( void );
MSTATE	*GetMouseState( void );
bool	GetMousePress( int nKey );
bool	GetMouseTrigger( int nKey );
bool	GetMouseRelease( int key );
bool	GetMouseRepeat( int nKey );

#endif