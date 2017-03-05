/*------------------------------------------------------------------------------
|	タイトル：		マウス処理
|	ファイル名：	mouse.cpp
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
#include "mouse.h"
#include "cursor.h"

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	グローバル変数
------------------------------------------------------------------------------*/
LPDIRECTINPUTDEVICE8	g_pDevMouse		= NULL;					//IDirectInputDevice8インターフェースへのポインタ(マウス)
MSTATE					g_Mouse;								//マウスのワーク
DIMOUSESTATE			g_MouseState;							//マウス情報
BYTE					g_MouseStateTrigger[ NUM_KEY_MAX ];		//マウスの状態を受け取るワーク
BYTE					g_MouseStateRelease[ NUM_KEY_MAX ];		//マウスの状態を受け取るワーク
BYTE					g_MouseStateRepeat[ NUM_KEY_MAX ];		//マウスの状態を受け取るワーク
int						g_MouseStateRepeatCnt[ NUM_KEY_MAX ];	//マウスのリピートカウンタ

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	マウスの初期化処理
------------------------------------------------------------------------------*/
HRESULT InitMouse( HINSTANCE hInstance, HWND hWnd )
{
	//IDirectInput8インターフェースへのポインタを取得
	LPDIRECTINPUT8 pInput = GetpInput();

	if( FAILED( pInput -> CreateDevice( GUID_SysMouse, &g_pDevMouse, NULL ) ) )
	{//デバイスオブジェクトを作成
		MessageBox( hWnd, "マウスがありません！", "警告！", MB_ICONWARNING );
		return E_FAIL;
	}

	if( g_pDevMouse != NULL )
	{
		if( FAILED( g_pDevMouse -> SetDataFormat( &c_dfDIMouse ) ) )												//データフォーマットの設定
		{//データフォーマットを設定
			MessageBox( hWnd, "マウスのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//協調モードを設定（フォアグラウンド＆非排他モード）
		if( FAILED( g_pDevMouse -> SetCooperativeLevel( hWnd, ( DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) ) )		//協調モードの設定
		{
			MessageBox( hWnd, "マウスの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//軸モードを設定（相対値モードに設定）
		DIPROPDWORD diprop;
		diprop.diph.dwSize			= sizeof( diprop );
		diprop.diph.dwHeaderSize	= sizeof( diprop.diph );
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= DIPROPAXISMODE_REL;	//相対値モードで設定（絶対モードはDIPROPAXISMODE_ABS）

		if( FAILED( g_pDevMouse -> SetProperty( DIPROP_AXISMODE, &diprop.diph ) ) )
		{
			MessageBox( hWnd, "軸モードの設定できませんでした。", "警告！", MB_ICONWARNING );
			return E_FAIL;
		}

		//マウス構造体の初期化
		SetRect( &g_Mouse.moveRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );		//マウスカーソルの動く範囲
		g_Mouse.x = SCREEN_CENTER_X;											//マウスカーソルのＸ座標を初期化
		g_Mouse.y = SCREEN_CENTER_Y;											//マウスカーソルのＹ座標を初期化
		g_Mouse.moveAdd = 2;													//マウスカーソルの移動量を設定

		//入力制御開始
		g_pDevMouse -> Acquire();

		//カーソルの初期化処理
		InitCursor();
	}

	return S_OK;
}

/*------------------------------------------------------------------------------
|	マウスの終了処理
------------------------------------------------------------------------------*/
void UninitMouse( void )
{
	if( g_pDevMouse != NULL )
	{//アクセス権の開放
		g_pDevMouse -> Unacquire();
		g_pDevMouse -> Release();
		g_pDevMouse = NULL;
	}

	//カーソルの終了処理
	UninitCursor();
}

/*------------------------------------------------------------------------------
|	マウスの更新処理
------------------------------------------------------------------------------*/
void UpdateMouse( void )
{
	if( g_pDevMouse != NULL )
	{
		BYTE MouseStateOld[ NUM_KEY_MAX ];

		//前回のデータを保存
		memcpy( MouseStateOld, g_MouseState.rgbButtons, NUM_KEY_MAX );

		if( SUCCEEDED( g_pDevMouse -> GetDeviceState( sizeof( DIMOUSESTATE ), &g_MouseState ) ) )
		{//デバイスからデータを取得

			//マウスの移動を更新
			g_Mouse.x += ( g_MouseState.lX * g_Mouse.moveAdd );
			g_Mouse.y += ( g_MouseState.lY * g_Mouse.moveAdd );

			//画面外チェック
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
			{//デバイスからデータを取得
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
			//マウスへのアクセス権を取得
			g_pDevMouse -> Acquire();
		}

		//カーソルの設定
		SetCursor( g_Mouse.x, g_Mouse.y );
	}
}

/*------------------------------------------------------------------------------
|	マウスのプレス状態を取得
------------------------------------------------------------------------------*/
bool GetMousePress( int nKey )
{
	return ( g_MouseState.rgbButtons[ nKey ] & 0x80) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスのトリガー状態を取得
------------------------------------------------------------------------------*/
bool GetMouseTrigger( int nKey )
{
	return ( g_MouseStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスのリリース状態を取得
------------------------------------------------------------------------------*/
bool GetMouseRelease( int nKey )
{
	return ( g_MouseStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスのリピート状態を取得
------------------------------------------------------------------------------*/
bool GetMouseRepeat( int nKey )
{
	return ( g_MouseStateRepeat[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	マウスを取得
------------------------------------------------------------------------------*/
MSTATE *GetMouseState( void )
{
	return &g_Mouse;
}