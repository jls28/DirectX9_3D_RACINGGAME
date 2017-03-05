/********************************************************************************
* タイトル　04
* ファイル名　main.cpp
* 作成者 AT11D243 36 李昊盛
* 作成日 2015/06/04
*
********************************************************************************/
/*******************************************************************************
* インクルードファイル
******************************************************************************/
#include "main.h"
#include <stdio.h>
#include "fade.h"
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "result.h"
#include "titlebg.h"
#include "resultbg.h"
#include "press.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "debugProc.h"
#include "bullet.h"
#include "time.h"
#include "prop.h"
#include "propshow.h"
#include "propmodel_Group.h"
#include "propmp.h"
#include "propmplife.h"
#include "propmpmax.h"
#include "enemy.h"
#include "propexplosion.h"
#include "modelbody.h"
#include "modelhandL.h"
#include "modelhandR.h"
#include "modellegL.h"
#include "modellegR.h"
#include "modelarmL.h"
#include "modelarmR.h"
#include "runleg.h"
#include "obstacle.h"
#include "building_Left.h"
#include "building_Right.h"
#include "money.h"
#include "score.h"
#include "sky.h"
#include "timebg.h"
#include "shop.h"
#include "countdown.h"
#include "boxscore.h"
#include "skip.h"
#include "skipbg0.h"
#include "skipbg.h"
#include "skipbg2.h"
#include "rule.h"
#include "rule2.h"
#include "result2.h"
#include "sound.h"
#include "player.h"
#include "rankingmode.h"
#include "pause.h"
/*******************************************************************************
* プロトタイプの宣言
********************************************************************************/
LRESULT	CALLBACK WndProc( HWND hWnd , UINT uMsg ,WPARAM wParam ,LPARAM lParam );
HRESULT	Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow );
void	Uninit();
void	Update();
void	Draw();
void	DrawFPS();

/*******************************************************************************
* グローバル変数
********************************************************************************/
MODE g_mode = MODE_TITLE;		//現在のモード
LPDIRECT3D9			g_pD3D			= NULL;		//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9	g_pD3DDevice	= NULL;		//Direct3Dデバイスへのポインタ
int					g_nCountFPS;				//FPSカウンタ

LPD3DXFONT			g_pFont		= NULL;		//フォントへのポインタ

/*******************************************************************************
* 関数名: main
* 引数:
* 戻り値:
* 説明:
*******************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrewInstance, LPSTR lpCmdLine, int nCmdShow )
{
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	timeBeginPeriod( 1 );

	dwFrameCount	=
	dwCurrentTime	= 0;
	dwExecLastTime	=
	dwFPSLastTime	= timeGetTime();

	WNDCLASSEX wcex = { 
						sizeof( WNDCLASSEX ),
						CS_CLASSDC,
						WndProc,
						0,
						0,
						hInstance,
						NULL,
						LoadCursor( NULL, IDC_ARROW ),
						( HBRUSH )( COLOR_WINDOW + 1 ),
						NULL,
						"Window",
						NULL, };

	HWND hWnd;
	MSG  msg;
	RegisterClassEx( &wcex );

	hWnd = CreateWindowEx(
							0,
							"window",
							"課題",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							SCREEN_WIDTH,
							SCREEN_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL );

	if( FAILED ( Init( hInstance, hWnd, TRUE ) ) )				//初期化処理
	{
		return -1;
	}

	ShowWindow( hWnd ,nCmdShow );
	UpdateWindow( hWnd );

	while( 1 )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 )	//Windowsの処理
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else												//メッセージの翻訳と送出
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else													//DirectXの処理
		{
			dwCurrentTime = timeGetTime();

			if( ( dwCurrentTime - dwFPSLastTime ) >= 500 )
			{
				g_nCountFPS		= ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );
				dwFPSLastTime	= dwCurrentTime;
				dwFrameCount	= 0;
			}

			if( ( dwCurrentTime - dwExecLastTime ) >= ( 1000 / 60 ) )
			{
				dwExecLastTime	= dwCurrentTime;
				Update();										//更新処理
				Draw();											//描画処理
				dwFrameCount++;
			}
		}
	}
	Uninit();													//終了処理

	UnregisterClass( "Window" ,wcex.hInstance );

	timeEndPeriod( 1 );

	return ( int )msg.wParam;
}

/*******************************************************************************
* 関数名: WndProc
*******************************************************************************/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg ,WPARAM wParam ,LPARAM lParam )
{
	int nID;
	switch( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );					//"WN_QUIT"メッセージを返す
		break;

	case WM_CLOSE:
		nID = MessageBox( hWnd, "終了しますか。", "終了メッセージ", MB_YESNO );
		if( nID == IDYES )
		{
			DestroyWindow( hWnd );				//ウインドウを破棄する
		}
		return 0;
		break;

	case WM_KEYDOWN:							//キーが押したら
		switch( wParam )
		{
			case VK_ESCAPE:						//ESCキー
				nID = MessageBox( hWnd, "終了しますか。", "終了メッセージ", MB_YESNO );
				if( nID == IDYES )
				{
					DestroyWindow( hWnd );		//ウインドウを破棄する
				}
				break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

/*******************************************************************************
* 関数名: Init
*******************************************************************************/
HRESULT Init( HINSTANCE hInstance, HWND hWnd, BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );										//Direct3Dオブジェクトの生成

	if( g_pD3D == NULL )
	{
		return E_FAIL;
	}

	if( FAILED ( g_pD3D -> GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )		//ディスプレイモードを取得
	{
		return E_FAIL;
	}

	ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	d3dpp.BackBufferWidth				= SCREEN_WIDTH;						//画面の幅
	d3dpp.BackBufferHeight				= SCREEN_HEIGHT;					//画面の高
	d3dpp.BackBufferFormat				= d3ddm.Format;						//バックバッファの形式
	d3dpp.BackBufferCount				= 1;								//バックバッファの数
	d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil		= TRUE;								//デプスバッファとステンツルバッファの生成
	d3dpp.AutoDepthStencilFormat		= D3DFMT_D16;						//デプスバッファとして16ビットを使用
	d3dpp.Windowed						= bWindow;	
   // d3dpp.Windowed = false;		//全画面
	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval			= D3DPRESENT_INTERVAL_DEFAULT;

  //  d3dpp.Windowed = false;
  //  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  ////d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
  //  d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	//Direct3Dデバイスの生成
	if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice ) ) )
	{
		if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice ) ) )
		{
			if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice ) ) )
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice -> SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	g_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	g_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	g_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	//サンプラーステートの設定
	g_pD3DDevice -> SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	g_pD3DDevice -> SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	g_pD3DDevice -> SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );	//テクスチャ( U値 )繰り返す設定
	g_pD3DDevice -> SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );	//テクスチャ( V値 )繰り返す設定

	//テクスチャステージステートの設定
	g_pD3DDevice -> SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	g_pD3DDevice -> SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	g_pD3DDevice -> SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_CURRENT );

	D3DXCreateFont( g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont );
	InitSound(hWnd);
	//入力処理の初期化処理
	InitFade();
	InitInput( hInstance, hWnd);
	InitCamera();
	InitLight();
	#ifdef _DEBUG
	InitDebugProc();
	#endif

	SetMode(g_mode);
	return S_OK;
}

/*******************************************************************************
* 関数名: Uninit
*******************************************************************************/
void Uninit( void )
{

	#ifdef _DEBUG
	UninitDebugProc();
	#endif
	if( g_pD3DDevice != NULL )
	{
		g_pD3DDevice -> Release();		//デバイスの開放
		g_pD3DDevice = NULL;
	}

	if( g_pD3D != NULL )
	{
		g_pD3D -> Release();			//オブジェクトの開放
		g_pD3D = NULL;
	}

#ifdef _DEBUG
	if( g_pFont != NULL )
	{
		g_pFont -> Release();
		g_pFont = NULL;
	}
#endif
	UninitSound();
	UninitInput();
	UninitKeyboard();
	UninitCamera();
	UninitLight();
	UninitFade();
}

/*******************************************************************************
* 関数名: Update
*******************************************************************************/
void Update( void )
{

#ifdef _DEBUG
	UpdateDebugProc();
#endif
	switch(g_mode)
		{
		case MODE_TITLE:
			UpdateTitle();
			break;

		case MODE_SKIP:
			UpdateSkip();
			break;

		case MODE_RULE:
			UpdateRule();
			break;

		case MODE_RULE2:
			UpdateRule2();
			break;

		case MODE_GAME:
			UpdateGame();
			break;

		case MODE_RANKING:
			UpdateRankingMode();
			break;

		case MODE_RESULT:
			UpdateResult();
			break;

		case MODE_RESULT2:
			UpdateResult2();
			break;
		default:
		break;
		}

	if(g_mode == MODE_TITLE)
	{
		if(GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT,MODE_GAME);
		}
	}

	if(g_mode == MODE_GAME)
	{
		if(GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT,MODE_RANKING);
		}
	}

	if(g_mode == MODE_RANKING)
	{
		if(GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT,MODE_RESULT);
		}
	}

	if(g_mode == MODE_RESULT)
	{
		if(GetKeyboardTrigger(DIK_RETURN))
		{
			SetFade(FADE_OUT,MODE_TITLE);
		}
	}
	//入力処理の更新処理
	UpdateInput();
	UpdateFade();
	UpdateCamera();
}

/*******************************************************************************
* 関数名: Draw
*******************************************************************************/
void Draw( void )
{
	//画面クリア
	g_pD3DDevice -> Clear( 0, NULL, ( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ), D3DCOLOR_RGBA( 255, 255, 0, 0 ), 1.0f, 0 );

	if( SUCCEEDED( g_pD3DDevice ->BeginScene() ) )			//成功したら、描画開始
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_SKIP:
			DrawSkip();
			break;

		case MODE_RULE:
			DrawRule();
			break;

		case MODE_RULE2:
			DrawRule2();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RANKING:
			DrawRankingMode();
			break;

		case MODE_RESULT:
			DrawResult();
			break;


		case MODE_RESULT2:
			DrawResult2();
			break;
		default:
		break;
		}
	DrawFade();
	SetCamera();
	DrawLight();

#ifdef _DEBUG
		DrawFPS();										//FPS描画処理
		DrawDebugProc();									//Debug描画処理
#endif

		g_pD3DDevice -> EndScene();							//描画終了
	}

	g_pD3DDevice -> Present( NULL, NULL, NULL, NULL );		//バックバッファをフロントバッファの切替
}

/*******************************************************************************
* 関数名: GetDevice
*******************************************************************************/
LPDIRECT3DDEVICE9 GetDevice( void )
{
	return g_pD3DDevice;
}

/*******************************************************************************
* 関数名: DrawFPS
*******************************************************************************/
void DrawFPS( void )
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char aStr[ 256 ];

	wsprintf( &aStr[ 0 ], "FPS:%d\n", g_nCountFPS );

	//テキスト描画
	g_pFont -> DrawText( NULL, &aStr[ 0 ], -1, &rect, DT_RIGHT,  D3DCOLOR_RGBA( 255, 255, 255, 255 ) );
}
//=============================================================================
//  関数名　：SetMode
//  機能概要：
//  戻り値　：
//=============================================================================
void SetMode(MODE mode)
{
	switch(g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_SKIP:
		UninitSkip();
		break;

	case MODE_RULE:
		UninitRule();
		break;

	case MODE_RULE2:
		UninitRule2();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RANKING:
		UninitRankingMode();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	case MODE_RESULT2:
		UninitResult2();
		break;
	default:
	break;
	}

	switch(mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_SKIP:
		InitSkip();
		break;

	case MODE_RULE:
		InitRule();
		break;

	case MODE_RULE2:
		InitRule2();
		break;	

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RANKING:
		InitRankingMode();
		LoadRanking();
		CompareRanking();
		SaveRanking();
		LoadRanking();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_RESULT2:
		InitResult2();
		break;

	default:
	break;
	}
	g_mode = mode;
}
//=============================================================================
//  関数名　：MODE GetMode(void)
//  機能概要：
//  戻り値　：g_mode
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}
