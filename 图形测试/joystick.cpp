/*------------------------------------------------------------------------------
|	�^�C�g���F		�W���C�X�e�B�b�N����
|	�t�@�C�����F	joystick.cpp
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
#include "joystick.h"

/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�O���[�o���ϐ�
------------------------------------------------------------------------------*/
LPDIRECTINPUTDEVICE8	g_pDevJoysticks		= NULL;					//IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�}�E�X)
DIDEVCAPS				g_JoysticksCaps;							//�W���C�X�e�B�b�N�̔\��
JSTATE					g_Joysticks;								//�W���C�X�e�B�b�N�̃��[�N
DIJOYSTATE				g_JoysticksState;							//�W���C�X�e�B�b�N�̏��
BYTE					g_JoysticksStateTrigger[ 256 ];		//�W���C�X�e�B�b�N�̔\�͂̏�Ԃ��󂯎�郏�[�N
BYTE					g_JoysticksStateRelease[ 256 ];		//�W���C�X�e�B�b�N�̔\�͂̏�Ԃ��󂯎�郏�[�N
BYTE					g_JoysticksStateRepeat[ 256 ];		//�W���C�X�e�B�b�N�̔\�͂̏�Ԃ��󂯎�郏�[�N
int						g_JoysticksStateRepeatCnt[ 256 ];	//�W���C�X�e�B�b�N�̔\�͂̃��s�[�g�J�E���^

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef );

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̏���������
------------------------------------------------------------------------------*/
HRESULT InitJoysticks( HINSTANCE hInstance, HWND hWnd )
{
	//IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^���擾
	LPDIRECTINPUT8 pInput = GetpInput();

	if( FAILED( pInput -> EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY ) ) )
	{//�f�o�C�X��񋓂��č쐬
		MessageBox( hWnd, "�W���C�X�e�B�b�N������܂���I", "�x���I", MB_ICONWARNING );
		return E_FAIL;
	}

	if( g_pDevJoysticks != NULL )
	{
		if( FAILED( g_pDevJoysticks -> SetDataFormat( &c_dfDIJoystick ) ) )												//�f�[�^�t�H�[�}�b�g�̐ݒ�
		{//�f�[�^�t�H�[�}�b�g��ݒ�
			MessageBox( hWnd, "�W���C�X�e�B�b�N�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return E_FAIL;
		}

		//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		if( FAILED( g_pDevJoysticks -> SetCooperativeLevel( hWnd, ( DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) ) )		//�������[�h�̐ݒ�
		{
			MessageBox( hWnd, "�W���C�X�e�B�b�N�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return E_FAIL;
		}

		//�R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
		if( FAILED( g_pDevJoysticks -> EnumObjects( EnumAxesCallback, NULL, DIDFT_AXIS ) ) )
		{
			MessageBox( hWnd, "�����[�h�̐ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING );
			return E_FAIL;
		}

		//�W���C�X�e�B�b�N�\���̂̏�����
		SetRect( &g_Joysticks.moveRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );		//�W���C�X�e�B�b�N�̓����͈�
		g_Joysticks.x = SCREEN_CENTER_X;											//�W���C�X�e�B�b�N�̂w���W��������
		g_Joysticks.y = SCREEN_CENTER_Y;											//�W���C�X�e�B�b�N�̂x���W��������
		g_Joysticks.moveAdd = 5;													//�W���C�X�e�B�b�N�̈ړ��ʂ�ݒ�

		//���͐���J�n
		g_pDevJoysticks -> Acquire();
	}

	return S_OK;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N��񋓂���֐�
------------------------------------------------------------------------------*/
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext )
{
	//IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^���擾
	LPDIRECTINPUT8 pInput = GetpInput();

	//�񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
	if( FAILED( pInput -> CreateDevice( pdidInstance -> guidInstance, &g_pDevJoysticks, NULL ) ) )
	{
		return DIENUM_CONTINUE;
	}

	//�W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	g_JoysticksCaps.dwSize = sizeof( DIDEVCAPS );

	if( FAILED ( g_pDevJoysticks -> GetCapabilities( &g_JoysticksCaps ) ) )
	{//�W���C�X�e�B�b�N�\�͂̎擾�Ɏ��s
		if( g_pDevJoysticks != NULL )
			{
				g_pDevJoysticks  -> Release();
				g_pDevJoysticks = NULL;
			}
		return DIENUM_CONTINUE;
	}

	return DIENUM_STOP;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̎���񋓂���֐�
------------------------------------------------------------------------------*/
BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
{
	//���̒l�͈̔͂�ݒ�i-1000�`1000�j
	DIPROPRANGE diprg;
	ZeroMemory( &diprg, sizeof( diprg ) );
	diprg.diph.dwSize		= sizeof( diprg ); 
	diprg.diph.dwHeaderSize	= sizeof( diprg.diph ); 
	diprg.diph.dwObj		= lpddoi -> dwType;
	diprg.diph.dwHow		= DIPH_BYID;
	diprg.lMin				= -1000;
	diprg.lMax				= +1000;

	if( FAILED( g_pDevJoysticks -> SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̏I������
------------------------------------------------------------------------------*/
void UninitJoysticks( void )
{
	if( g_pDevJoysticks != NULL )
	{//�A�N�Z�X���̊J��
		g_pDevJoysticks -> Unacquire();
		g_pDevJoysticks -> Release();
		g_pDevJoysticks = NULL;
	}
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̍X�V����
------------------------------------------------------------------------------*/
void UpdateJoysticks( void )
{
	if( g_pDevJoysticks != NULL )
	{
		BYTE JoysticksStateOld[ 32 ];

		//�O��̃f�[�^��ۑ�
		memcpy( JoysticksStateOld, g_JoysticksState.rgbButtons, 32 );

		if( SUCCEEDED( g_pDevJoysticks -> GetDeviceState( sizeof( DIJOYSTATE ), &g_JoysticksState ) ) )
		{//�f�o�C�X����f�[�^���擾

			//�}�E�X�̈ړ����X�V
			g_Joysticks.x += ( g_JoysticksState.lX / 1000 * g_Joysticks.moveAdd );
			g_Joysticks.y += ( g_JoysticksState.lY / 1000* g_Joysticks.moveAdd );

			//��ʊO�`�F�b�N
			if( g_Joysticks.x < g_Joysticks.moveRect.left )
			{
				g_Joysticks.x = g_Joysticks.moveRect.left;
			}
			if (g_Joysticks.x > g_Joysticks.moveRect.right )
			{
				g_Joysticks.x = g_Joysticks.moveRect.right;
			}
			if (g_Joysticks.y < g_Joysticks.moveRect.top )
			{
				g_Joysticks.y = g_Joysticks.moveRect.top;
			}
			if (g_Joysticks.y > g_Joysticks.moveRect.bottom )
			{
				g_Joysticks.y = g_Joysticks.moveRect.bottom;
			}

			for( int nCntJoysticks = 0; nCntJoysticks < 32; nCntJoysticks++ )
			{//�f�o�C�X����f�[�^���擾
				g_JoysticksStateTrigger[ nCntJoysticks ] = ( JoysticksStateOld[ nCntJoysticks ] ^ g_JoysticksState.rgbButtons[ nCntJoysticks ] ) & g_JoysticksState.rgbButtons[ nCntJoysticks ];
				g_JoysticksStateRelease[ nCntJoysticks ] = ( JoysticksStateOld[ nCntJoysticks ] ^ g_JoysticksState.rgbButtons[ nCntJoysticks ] ) & ~g_JoysticksState.rgbButtons[ nCntJoysticks ];
				g_JoysticksStateRepeat[ nCntJoysticks ]  = g_JoysticksStateTrigger[nCntJoysticks];

				if( g_JoysticksState.rgbButtons[ nCntJoysticks ] )
				{
					g_JoysticksStateRepeatCnt[ nCntJoysticks ]++;
					if( g_JoysticksStateRepeatCnt[ nCntJoysticks ] >= WAIT_COUNT_REPEAT )
					{
						g_JoysticksStateRepeat[ nCntJoysticks ] = g_JoysticksState.rgbButtons[ nCntJoysticks ];
					}
				}
				else
				{
					g_JoysticksStateRepeatCnt[ nCntJoysticks ] = 0;
					g_JoysticksStateRepeat[ nCntJoysticks ] = 0;
				}
			}
		}
		else
		{
			//�}�E�X�ւ̃A�N�Z�X�����擾
			g_pDevJoysticks -> Acquire();
		}
	}
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̃v���X��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetJoysticksPress( int nKey )
{
	return ( g_JoysticksState.rgbButtons[ nKey ] & 0x80) ? true : false;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̃g���K�[��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetJoysticksTrigger( int nKey )
{
	return ( g_JoysticksStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̃����[�X��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetJoysticksRelease( int nKey )
{
	return ( g_JoysticksStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N�̃��s�[�g��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetJoysticksRepeat( int nKey )
{
	return ( g_JoysticksStateRepeat[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�W���C�X�e�B�b�N���擾
------------------------------------------------------------------------------*/
JSTATE *GetJoysticksState( void )
{
	return &g_Joysticks;
}