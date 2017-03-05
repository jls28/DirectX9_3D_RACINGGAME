/*------------------------------------------------------------------------------
|	�^�C�g���F		�L�[�{�[�h����
|	�t�@�C�����F	keyboard.cpp
|	�쐬�ҁF		AT12A244 46 LI HAOSHENG
|	�쐬���F		2015/06/12
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�X�V����:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "input.h"
#include "keyboard.h"

/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�O���[�o���ϐ�
------------------------------------------------------------------------------*/
LPDIRECTINPUTDEVICE8	g_pDevKeyboard	= NULL;					//IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
BYTE					g_KeyState[ NUM_KEY_MAX ];				//�L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_KeyStateTrigger[ NUM_KEY_MAX ];		//�L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_KeyStateRelease[ NUM_KEY_MAX ];		//�L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_KeyStateRepeat[ NUM_KEY_MAX ];		//�L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
int						g_KeyStateRepeatCnt[ NUM_KEY_MAX ];		//�L�[�{�[�h�̃��s�[�g�J�E���^

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̏���������
------------------------------------------------------------------------------*/
HRESULT InitKeyboard( HINSTANCE hInstance, HWND hWnd )
{
	//IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^���擾
	LPDIRECTINPUT8 pInput = GetpInput();

	if( FAILED( pInput -> CreateDevice( GUID_SysKeyboard, &g_pDevKeyboard, NULL ) ) )
	{//�f�o�C�X�I�u�W�F�N�g���쐬
		MessageBox( hWnd, "�L�[�{�[�h������܂���I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	if( g_pDevKeyboard != NULL )
	{
		if( FAILED( g_pDevKeyboard -> SetDataFormat( &c_dfDIKeyboard ) ) )											//�f�[�^�t�H�[�}�b�g�̐ݒ�
		{//�f�[�^�t�H�[�}�b�g��ݒ�
			MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//�������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		if( FAILED( g_pDevKeyboard -> SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )	//�������[�h�̐ݒ�
		{
			MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
			return E_FAIL;
		}

		//���͐���J�n
		g_pDevKeyboard -> Acquire();
	}
	
	return S_OK;
}

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̏I������
------------------------------------------------------------------------------*/
void UninitKeyboard( void )
{
	if( g_pDevKeyboard != NULL )
	{//�A�N�Z�X�����J��
		g_pDevKeyboard -> Unacquire();
		g_pDevKeyboard -> Release();
		g_pDevKeyboard = NULL;
	}
}

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̍X�V����
------------------------------------------------------------------------------*/
void UpdateKeyboard( void )
{
	if( g_pDevKeyboard != NULL )
	{
		BYTE KeyStateOld[ NUM_KEY_MAX ];

		//�O��̃f�[�^��ۑ�
		memcpy( KeyStateOld, g_KeyState, NUM_KEY_MAX );

		if( SUCCEEDED( g_pDevKeyboard -> GetDeviceState( sizeof( g_KeyState ), g_KeyState ) ) )
		{//�f�o�C�X����f�[�^���擾
			for( int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++ )
			{
				g_KeyStateTrigger[ nCntKey ] = ( KeyStateOld[nCntKey] ^ g_KeyState[ nCntKey ] ) & g_KeyState[ nCntKey ];
				g_KeyStateRelease[ nCntKey ] = ( KeyStateOld[nCntKey] ^ g_KeyState[ nCntKey ] ) & ~g_KeyState[ nCntKey ];
				g_KeyStateRepeat[ nCntKey ]  = g_KeyStateTrigger[nCntKey];

				if( g_KeyState[ nCntKey ] )
				{
					g_KeyStateRepeatCnt[ nCntKey ]++;
					if( g_KeyStateRepeatCnt[ nCntKey ] >= WAIT_COUNT_REPEAT )
					{
						g_KeyStateRepeat[ nCntKey ] = g_KeyState[ nCntKey ];
					}
				}
				else
				{
					g_KeyStateRepeatCnt[ nCntKey ] = 0;
					g_KeyStateRepeat[ nCntKey ] = 0;
				}
			}
		}
		else
		{
			//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
			g_pDevKeyboard -> Acquire();
		}
	}
}

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̃v���X��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetKeyboardPress( int nKey )
{
	return ( g_KeyState[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̃g���K�[��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetKeyboardTrigger( int nKey )
{
	return ( g_KeyStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̃����[�X��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetKeyboardRelease( int nKey )
{
	return ( g_KeyStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	�L�[�{�[�h�̃��s�[�g��Ԃ��擾
------------------------------------------------------------------------------*/
bool GetKeyboardRepeat( int nKey )
{
	return ( g_KeyStateRepeat[ nKey ] & 0x80 ) ? true : false;
}
