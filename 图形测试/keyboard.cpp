/*------------------------------------------------------------------------------
|	タイトル：		キーボード処理
|	ファイル名：	keyboard.cpp
|	作成者：		AT12A244 46 LI HAOSHENG
|	作成日：		2015/06/12
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	更新履歴:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	インクルードファイル
------------------------------------------------------------------------------*/
#include "input.h"
#include "keyboard.h"

/*------------------------------------------------------------------------------
|	マクロ定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	グローバル変数
------------------------------------------------------------------------------*/
LPDIRECTINPUTDEVICE8	g_pDevKeyboard	= NULL;					//IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE					g_KeyState[ NUM_KEY_MAX ];				//キーボードの状態を受け取るワーク
BYTE					g_KeyStateTrigger[ NUM_KEY_MAX ];		//キーボードの状態を受け取るワーク
BYTE					g_KeyStateRelease[ NUM_KEY_MAX ];		//キーボードの状態を受け取るワーク
BYTE					g_KeyStateRepeat[ NUM_KEY_MAX ];		//キーボードの状態を受け取るワーク
int						g_KeyStateRepeatCnt[ NUM_KEY_MAX ];		//キーボードのリピートカウンタ

/*------------------------------------------------------------------------------
|	プロトタイプ宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	キーボードの初期化処理
------------------------------------------------------------------------------*/
HRESULT InitKeyboard( HINSTANCE hInstance, HWND hWnd )
{
	//IDirectInput8インターフェースへのポインタを取得
	LPDIRECTINPUT8 pInput = GetpInput();

	if( FAILED( pInput -> CreateDevice( GUID_SysKeyboard, &g_pDevKeyboard, NULL ) ) )
	{//デバイスオブジェクトを作成
		MessageBox( hWnd, "キーボードがありません！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	if( g_pDevKeyboard != NULL )
	{
		if( FAILED( g_pDevKeyboard -> SetDataFormat( &c_dfDIKeyboard ) ) )											//データフォーマットの設定
		{//データフォーマットを設定
			MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//協調モードを設定（フォアグラウンド＆非排他モード）
		if( FAILED( g_pDevKeyboard -> SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )	//協調モードの設定
		{
			MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
			return E_FAIL;
		}

		//入力制御開始
		g_pDevKeyboard -> Acquire();
	}
	
	return S_OK;
}

/*------------------------------------------------------------------------------
|	キーボードの終了処理
------------------------------------------------------------------------------*/
void UninitKeyboard( void )
{
	if( g_pDevKeyboard != NULL )
	{//アクセス権を開放
		g_pDevKeyboard -> Unacquire();
		g_pDevKeyboard -> Release();
		g_pDevKeyboard = NULL;
	}
}

/*------------------------------------------------------------------------------
|	キーボードの更新処理
------------------------------------------------------------------------------*/
void UpdateKeyboard( void )
{
	if( g_pDevKeyboard != NULL )
	{
		BYTE KeyStateOld[ NUM_KEY_MAX ];

		//前回のデータを保存
		memcpy( KeyStateOld, g_KeyState, NUM_KEY_MAX );

		if( SUCCEEDED( g_pDevKeyboard -> GetDeviceState( sizeof( g_KeyState ), g_KeyState ) ) )
		{//デバイスからデータを取得
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
			//キーボードへのアクセス権を取得
			g_pDevKeyboard -> Acquire();
		}
	}
}

/*------------------------------------------------------------------------------
|	キーボードのプレス状態を取得
------------------------------------------------------------------------------*/
bool GetKeyboardPress( int nKey )
{
	return ( g_KeyState[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	キーボードのトリガー状態を取得
------------------------------------------------------------------------------*/
bool GetKeyboardTrigger( int nKey )
{
	return ( g_KeyStateTrigger[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	キーボードのリリース状態を取得
------------------------------------------------------------------------------*/
bool GetKeyboardRelease( int nKey )
{
	return ( g_KeyStateRelease[ nKey ] & 0x80 ) ? true : false;
}

/*------------------------------------------------------------------------------
|	キーボードのリピート状態を取得
------------------------------------------------------------------------------*/
bool GetKeyboardRepeat( int nKey )
{
	return ( g_KeyStateRepeat[ nKey ] & 0x80 ) ? true : false;
}
