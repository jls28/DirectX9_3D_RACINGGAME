/*------------------------------------------------------------------------------
|	�^�C�g���F		�}�E�X����
|	�t�@�C�����F	mouse.cpp
|	�쐬�ҁF		AT12A244 46 LI HAOSHENG
|	�쐬���F		2016/01/24
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�X�V����:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "input.h"
#include "mouse.h"
#include "cursor.h"

/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�O���[�o���ϐ�
------------------------------------------------------------------------------*/
LPDIRECTINPUTDEVICE8	g_pDevMouse		= NULL;					//IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�}�E�X)
MSTATE					g_Mouse;								//�}�E�X�̃��[�N
DIMOUSESTATE			g_MouseState;							//�}�E�X���
BYTE					g_MouseStateTrigger[ NUM_KEY_MAX ];		//�}�E�X�̏�Ԃ��󂯎�郏�[�N
BYTE					g_MouseStateRelease[ NUM_KEY_MAX ];		//�}�E�X�̏�Ԃ��󂯎�郏�[�N
BYTE					g_MouseStateRepeat[ NUM_KEY_MAX ];		//�}�E�X�̏�Ԃ��󂯎�郏�[�N
int						g_MouseStateRepeatCnt[ NUM_KEY_MAX ];	//�}�E�X�̃��s�[�g�J�E���^

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�}�E�X�̏���������
------------------------------------------------------------------------------*/
HRESULT InitMouse( HINSTANCE hInstance, HWND hWnd )
{
	//IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^���擾
	LPDIRECTINPUT8 pInput = GetpInput();

	if( FAILED( pInput -> CreateDevice( GUID_SysMouse, &g_pDevMouse, NULL ) ) )
	{//�f�o�C�X�I�u�W�F�N�g���쐬
		MessageBox( hWnd, "�}�E�X������܂���I", "�x���I", MB_ICONWARNING );
		return E_FAIL;
	}

	if( g_pDevMouse != NULL )
	{
		if( FAILED( g_pDevMouse -> SetDataFormat( &c_dfDIMouse ) ) )												//�f�[�^�t�H�[�}�b�g�̐ݒ�
		{//�f�[�^�t�H�[�}�b�g��ݒ�
			MessageBox( hWnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return E_FAIL;
		}

		//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		if( FAILED( g_pDevMouse -> SetCooperativeLevel( hWnd, ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) ) )		//�������[�h�̐ݒ�
		{
			MessageBox( hWnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return E_FAIL;
		}

		//�����[�h��ݒ�i���Βl���[�h�ɐݒ�j
		DIPROPDWORD diprop;
		diprop.diph.dwSize			= sizeof( diprop );
		diprop.diph.dwHeaderSize	= sizeof( diprop.diph );
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= DIPROPAXISMODE_REL;	//���Βl���[�h�Őݒ�i��΃��[�h��DIPROPAXISMODE_ABS�j

		if( FAILED( g_pDevMouse -> SetProperty( DIPROP_AXISMODE, &diprop.diph ) ) )
		{
			MessageBox( hWnd, "�����[�h�̐ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return E_FAIL;
		}

		//�}�E�X�\���̂̏�����
		SetRect( &g_Mouse.moveRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );		//�}�E�X�J�[�\���̓����͈�
		g_Mouse.x = SCREEN_CENTER_X;											//�}�E�X�J�[�\���̂w���W��������
		g_Mouse.y = SCREEN_CENTER_Y;											//�}�E�X�J�[�\���̂x���W��������
		g_Mouse.moveAdd = 2;													//�}�E�X�J�[�\���̈ړ��ʂ�ݒ�

		//���͐���J�n
		g_pDevMouse -> Acquire();

		//�J�[�\���̏���������
		InitCursor();
	}

	return S_OK;
}

/*------------------------------------------------------------------------------
|	�}�E�X�̏I������
------------------------------------------------------------------------------*/
void UninitMouse( void )
{
	if( g_pDevMouse != NULL )
	{//�A�N�Z�X���̊J��
		g_pDevMouse -> Unacquire();
		g_pDevMouse -> Release();
		g_pDevMouse = NULL;
	}

	//�J�[�\���̏I������
	UninitCursor();
}

/*------------------------------------------------------------------------------
|	�}�E�X�̍X�V����
------------------------------------------------------------------------------*/
void UpdateMouse( void )
{
	if( g_pDevMouse != NULL )
	{
		BYTE MouseStateOld[ NUM_KEY_MAX ];

		//�O��̃f�[�^��ۑ�
		memcpy( MouseStateOld, g_MouseState.rgbButtons, NUM_KEY_MAX );

		if( SUCCEEDED( g_pDevMouse -> GetDeviceState( sizeof( DIMOUSESTATE ), &g_MouseState ) ) )
		{//�f�o�C�X����f�[�^���擾

			//�}�E�X�̈ړ����X�V
			g_Mouse.x += ( g_MouseState.lX * g_Mouse.moveAdd );
			g_Mouse.y += ( g_MouseState.lY * g_Mouse.moveAdd );

			//��ʊO�`�F�b�N
			if( g_Mouse.x < g_Mouse.moveRect.left )
			{
				g_Mouse.x = g_Mouse.moveRect.left;
			}
			if (g_Mouse.x > g_Mouse.moveRect.right )
			{
				g_Mouse.x = g_Mouse.moveRect.right;
			}
			if (g_Mouse.y < g_Mouse.moveRect.top )
			{
				g_Mouse.y = g_Mouse.moveRect.top;
			}
			if (g_Mouse.y > g_Mouse.moveRect.bottom )
			{
				g_Mouse.y = g_Mouse.moveRect.bottom;
			}

			for( int nCntMouse = 0; nCntMouse < NUM_KEY_MAX; nCntMouse++ )
			{//�f�o�C�X����f�[�^���擾
				g_MouseStateTrigger[ nCntMouse ] = ( MouseStateOld[ nCntMouse ] ^ g_MouseState.rgbButtons[ nCntMouse ] ) & g_MouseState.rgbButtons[ nCntMouse ];
				g_MouseStateRelease[ nCntMouse ] = ( MouseStateOld[ nCntMouse ] ^ g_MouseState.rgbButtons[ nCntMouse ] ) & ~g_MouseState.rgbButtons[ nCntMouse ];
				g_MouseStateRepeat[ nCntMouse ]  = g_MouseStateTrigger[nCntMouse];

				if( g_MouseState.rgbButtons[ nCntMouse ] )
				{
					g_MouseStateRepeatCnt[ nCntMouse ]++;
					if( g_MouseStateRepeatCnt[ nCntMouse ] >= WAIT_COUNT_REPEAT )
					{
						g_MouseStateRepeat[ nCntMouse ] = g_MouseState.rgbButtons[ nCntMouse ];
					}
				}
				else
				{
					g_MouseStateRepeatCnt[ nCntMouse ] = 0;
					g_MouseStateRepeat[ nCntMouse ] = 0;
				}
			}
		}
		else
		{
			//�}�E�X�ւ̃A�N�Z�X�����擾
			g_pDevMouse -> Acquire();
		}

		//�J�[�\���̐ݒ�
		SetCursor( g_Mouse.x, g_Mouse.y );
	}
}

/*------------------------------------------------------------------------------
|	�}�E�X�̃v���X��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetMousePress( int nKey )
{
	return ( g_MouseState.rgbButtons[ nKey ] & 0x80) ? true : false;
}

/*------------------------------------------------------------------------------
|	�}�E�X�̃g���K�[��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetMouseTrigger( int nKey )
{
	return ( g_MouseStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�}�E�X�̃����[�X��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetMouseRelease( int nKey )
{
	return ( g_MouseStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�}�E�X�̃��s�[�g��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetMouseRepeat( int nKey )
{
	return ( g_MouseStateRepeat[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�}�E�X���擾
------------------------------------------------------------------------------*/
MSTATE *GetMouseState( void )
{
	return &g_Mouse;
}