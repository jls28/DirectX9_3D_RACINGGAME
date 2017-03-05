/*------------------------------------------------------------------------------
|	タイトル：		ジョイスティック処理
|	ファイル名：	joystick.cpp
|	作成者：		AT12A244 46 LI HAOSHENG
|	作成日：		2016/01/24
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	更新履歴:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "input.h"
#include "joystick.h"

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	グローバル変数
------------------------------------------------------------------------------*/
LPDIRECTINPUTDEVICE8	g_pDevJoysticks		= NULL;					//IDirectInputDevice8インターフェースへのポインタ(マウス)
DIDEVCAPS				g_JoysticksCaps;							//ジョイスティックの能力
JSTATE					g_Joysticks;								//ジョイスティックのワーク
DIJOYSTATE				g_JoysticksState;							//ジョイスティックの情報
BYTE					g_JoysticksStateTrigger[ 256 ];		//ジョイスティックの能力の状態を受け取るワーク
BYTE					g_JoysticksStateRelease[ 256 ];		//ジョイスティックの能力の状態を受け取るワーク
BYTE					g_JoysticksStateRepeat[ 256 ];		//ジョイスティックの能力の状態を受け取るワーク
int						g_JoysticksStateRepeatCnt[ 256 ];	//ジョイスティックの能力のリピートカウンタ

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef );

/*------------------------------------------------------------------------------
|	ジョイスティックの初期化処理
------------------------------------------------------------------------------*/
HRESULT InitJoysticks( HINSTANCE hInstance, HWND hWnd )
{
	//IDirectInput8インターフェースへのポインタを取得
	LPDIRECTINPUT8 pInput = GetpInput();

	if( FAILED( pInput -> EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY ) ) )
	{//デバイスを列挙して作成
		MessageBox( hWnd, "ジョイスティックがありません！", "警告！", MB_ICONWARNING );
		return E_FAIL;
	}

	if( g_pDevJoysticks != NULL )
	{
		if( FAILED( g_pDevJoysticks -> SetDataFormat( &c_dfDIJoystick ) ) )												//データフォーマットの設定
		{//データフォーマットを設定
			MessageBox( hWnd, "ジョイスティックのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//協調モードを設定（フォアグラウンド＆非排他モード）
		if( FAILED( g_pDevJoysticks -> SetCooperativeLevel( hWnd, ( DISCL_NONEXCLUSIVE | DISCL_FOREGROUND ) ) ) )		//協調モードの設定
		{
			MessageBox( hWnd, "ジョイスティックの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//コールバック関数を使って各軸のモードを設定
		if( FAILED( g_pDevJoysticks -> EnumObjects( EnumAxesCallback, NULL, DIDFT_AXIS ) ) )
		{
			MessageBox( hWnd, "軸モードの設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//ジョイスティック構造体の初期化
		SetRect( &g_Joysticks.moveRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );		//ジョイスティックの動く範囲
		g_Joysticks.x = SCREEN_CENTER_X;											//ジョイスティックのＸ座標を初期化
		g_Joysticks.y = SCREEN_CENTER_Y;											//ジョイスティックのＹ座標を初期化
		g_Joysticks.moveAdd = 5;													//ジョイスティックの移動量を設定

		//入力制御開始
		g_pDevJoysticks -> Acquire();
	}

	return S_OK;
}

/*------------------------------------------------------------------------------
|	ジョイスティックを列挙する関数
------------------------------------------------------------------------------*/
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext )
{
	//IDirectInput8インターフェースへのポインタを取得
	LPDIRECTINPUT8 pInput = GetpInput();

	//列挙されたジョイスティックへのインターフェイスを取得する。
	if( FAILED( pInput -> CreateDevice( pdidInstance -> guidInstance, &g_pDevJoysticks, NULL ) ) )
	{
		return DIENUM_CONTINUE;
	}

	//ジョイスティックの能力を調べる
	g_JoysticksCaps.dwSize = sizeof( DIDEVCAPS );

	if( FAILED ( g_pDevJoysticks -> GetCapabilities( &g_JoysticksCaps ) ) )
	{//ジョイスティック能力の取得に失敗
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
|	ジョイスティックの軸を列挙する関数
------------------------------------------------------------------------------*/
BOOL CALLBACK EnumAxesCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef )
{
	//軸の値の範囲を設定（-1000～1000）
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
|	ジョイスティックの終了処理
------------------------------------------------------------------------------*/
void UninitJoysticks( void )
{
	if( g_pDevJoysticks != NULL )
	{//アクセス権の開放
		g_pDevJoysticks -> Unacquire();
		g_pDevJoysticks -> Release();
		g_pDevJoysticks = NULL;
	}
}

/*------------------------------------------------------------------------------
|	ジョイスティックの更新処理
------------------------------------------------------------------------------*/
void UpdateJoysticks( void )
{
	if( g_pDevJoysticks != NULL )
	{
		BYTE JoysticksStateOld[ 32 ];

		//前回のデータを保存
		memcpy( JoysticksStateOld, g_JoysticksState.rgbButtons, 32 );

		if( SUCCEEDED( g_pDevJoysticks -> GetDeviceState( sizeof( DIJOYSTATE ), &g_JoysticksState ) ) )
		{//デバイスからデータを取得

			//マウスの移動を更新
			g_Joysticks.x += ( g_JoysticksState.lX / 1000 * g_Joysticks.moveAdd );
			g_Joysticks.y += ( g_JoysticksState.lY / 1000* g_Joysticks.moveAdd );

			//画面外チェック
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
			{//デバイスからデータを取得
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
			//マウスへのアクセス権を取得
			g_pDevJoysticks -> Acquire();
		}
	}
}

/*------------------------------------------------------------------------------
|	ジョイスティックのプレス状態を取得
------------------------------------------------------------------------------*/
bool GetJoysticksPress( int nKey )
{
	return ( g_JoysticksState.rgbButtons[ nKey ] & 0x80) ? true : false;
}

/*------------------------------------------------------------------------------
|	ジョイスティックのトリガー状態を取得
------------------------------------------------------------------------------*/
bool GetJoysticksTrigger( int nKey )
{
	return ( g_JoysticksStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	ジョイスティックのリリース状態を取得
------------------------------------------------------------------------------*/
bool GetJoysticksRelease( int nKey )
{
	return ( g_JoysticksStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	ジョイスティックのリピート状態を取得
------------------------------------------------------------------------------*/
bool GetJoysticksRepeat( int nKey )
{
	return ( g_JoysticksStateRepeat[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	ジョイスティックを取得
------------------------------------------------------------------------------*/
JSTATE *GetJoysticksState( void )
{
	return &g_Joysticks;
}