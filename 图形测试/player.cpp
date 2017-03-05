/*******************************************************************************
* タイトル： プレイヤー描画関数
* ファイル名： player.cpp
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2016/02/23
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
//2016/02/23 モデル読み込み
/*******************************************************************************
		インクルードファイル
*******************************************************************************/
#include "main.h"
#include "camera.h"
#include "player.h"
#include "keyboard.h"
/*******************************************************************************
* マクロ定義
*******************************************************************************/
#define	TEXTURE_MODEL_HEAD		"data\\MODEL\\model_head.x"	// 読み込むモデル名

#define	TEXTURE_MODEL_ARM_L		"data\\MODEL\\model_arm_L.x"	// 読み込むモデル名

#define	TEXTURE_MODEL_ARM_R		"data\\MODEL\\model_arm_R.x"	// 読み込むモデル名

#define	TEXTURE_MODEL_BODY		"data\\MODEL\\model_body.x"	// 読み込むモデル名

#define	TEXTURE_MODEL_LEG_L		"data\\MODEL\\model_leg_L.x"	// 読み込むモデル名

#define	TEXTURE_MODEL_LEG_R		"data\\MODEL\\model_leg_R.x"	// 読み込むモデル名

#define PLAYER_INERTIA_MOVE	( 0.025f )					//慣性調整係数

#define POSMOVE_PLAYER	( 5.0f )		// 移動量
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void PlayerMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY );

//************************************************************************************************************************************************************************************************
// グローバル変数
//************************************************************************************************************************************************************************************************
PLAYER g_aPlayer[ MAX_PLAYER ];		// モデルの情報
MODEL aModel[ MAX_MODEL ];
//================================================================================================================================================================================================
// InitPlayer関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
HRESULT InitPlayer( void )
{
	int nNumVertices;	// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点情報（頂点座標）へのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	aModel[ 0 ].nIndexModelDarent = 0;
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_BODY,
								   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
								   pDevice,
								   NULL,
								   &aModel[ 0 ].pBuffMat,		// マテリアル情報
								   NULL,
								   &aModel[ 0 ].nNumMat,			// マテリアル数
								   &aModel[ 0 ].pMesh ) ) )		// メッシュ情報
	{
		return E_FAIL;
	}
	aModel[ 1 ].nIndexModelDarent = 1;
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_ARM_L,
								   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
								   pDevice,
								   NULL,
								   &aModel[ 1 ].pBuffMat,		// マテリアル情報
								   NULL,
								   &aModel[ 1 ].nNumMat,			// マテリアル数
								   &aModel[ 1 ].pMesh ) ) )		// メッシュ情報
	{
		return E_FAIL;
	}
	aModel[ 2 ].nIndexModelDarent = 2;
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_ARM_R,
								   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
								   pDevice,
								   NULL,
								   &aModel[ 2 ].pBuffMat,		// マテリアル情報
								   NULL,
								   &aModel[ 2 ].nNumMat,			// マテリアル数
								   &aModel[ 2 ].pMesh ) ) )		// メッシュ情報
	{
		return E_FAIL;
	}

	aModel[ 3 ].nIndexModelDarent = 3;
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_HEAD,
								   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
								   pDevice,
								   NULL,
								   &aModel[ 3 ].pBuffMat,		// マテリアル情報
								   NULL,
								   &aModel[ 3 ].nNumMat,			// マテリアル数
								   &aModel[ 3 ].pMesh ) ) )		// メッシュ情報
	{
		return E_FAIL;
	}

	aModel[ 4 ].nIndexModelDarent = 4;
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_LEG_L,
								   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
								   pDevice,
								   NULL,
								   &aModel[ 4 ].pBuffMat,		// マテリアル情報
								   NULL,
								   &aModel[ 4 ].nNumMat,			// マテリアル数
								   &aModel[ 4 ].pMesh ) ) )		// メッシュ情報
	{
		return E_FAIL;
	}
	aModel[ 5 ].nIndexModelDarent = 5;
	// Xファイルの読み込み
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_LEG_R,
								   D3DXMESH_SYSTEMMEM,				// 確保するバッファのサイズ（バイト単位）。ゲームによって何頂点なのか変わる。今回は四角だから４。
								   pDevice,
								   NULL,
								   &aModel[ 5 ].pBuffMat,		// マテリアル情報
								   NULL,
								   &aModel[ 5 ].nNumMat,			// マテリアル数
								   &aModel[ 5 ].pMesh ) ) )		// メッシュ情報
	{
		return E_FAIL;
	}

	for( int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++ )
	{
		// モデルの初期設定
		aModel[ nCntModel ].pos = D3DXVECTOR3( 0.0f,  0.0f, 50.0f );
		aModel[ nCntModel ].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		aModel[ nCntModel ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		aModel[ nCntModel ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		aModel[ nCntModel ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		aModel[ nCntModel ].bUse = true;
		aModel[ nCntModel ].fPosMove = POSMOVE_PLAYER;
		g_aPlayer[0].aIndexParent[0] = 1;
		// 衝突判定で使うための処理////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// xファイルの頂点数を取得する。
		nNumVertices = aModel[ nCntModel ].pMesh->GetNumVertices();

		// 頂点フォーマットのサイズを取得する。
		sizeFVF = D3DXGetFVFVertexSize( aModel[ nCntModel ].pMesh->GetFVF() );

		// 衝突判定で使うために、そのxファイルの中で一番大きいx,y,zの値と、一番小さいx,y,zの値をチェックする。
		aModel[ nCntModel ].pMesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// 頂点情報を取得する。
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < aModel[ nCntModel ].Min.x )		aModel[ nCntModel ].Min.x = vtx.x;		// xの最小値の更新
			if( vtx.x > aModel[ nCntModel ].Max.x )		aModel[ nCntModel ].Max.x = vtx.x;		// xの最大値の更新
			if( vtx.y < aModel[ nCntModel ].Min.y )		aModel[ nCntModel ].Min.y = vtx.y;		// yの最小値の更新
			if( vtx.y > aModel[ nCntModel ].Max.y )		aModel[ nCntModel ].Max.y = vtx.y;		// yの最大値の更新
			if( vtx.z < aModel[ nCntModel ].Min.z )		aModel[ nCntModel ].Min.z = vtx.z;		// zの最小値の更新
			if( vtx.z > aModel[ nCntModel ].Max.z )		aModel[ nCntModel ].Max.z = vtx.z;		// zの最大値の更新

			// 次の頂点に移動する。
			pVtxBuff += sizeFVF;
		}
		aModel[ nCntModel ].pMesh->UnlockVertexBuffer();

		// モデルの半径の設定。絶対値をabs関数で求める。
		aModel[ nCntModel ].Size.x = ( fabs( aModel[ nCntModel ].Min.x ) + fabs( aModel[ nCntModel ].Max.x ) ) / 2;
		aModel[ nCntModel ].Size.y = ( fabs( aModel[ nCntModel ].Min.y ) + fabs( aModel[ nCntModel ].Max.y ) ) / 2;
		aModel[ nCntModel ].Size.z = ( fabs( aModel[ nCntModel ].Min.z ) + fabs( aModel[ nCntModel ].Max.z ) ) / 2;

		// 衝突判定の長さの設定
		if( aModel[ nCntModel ].Size.x < aModel[ nCntModel ].Size.z )
		{
			aModel[ nCntModel ].Collisoin = aModel[ nCntModel ].Size.z;
		}
		else
		{
			aModel[ nCntModel ].Collisoin = aModel[ nCntModel ].Size.x;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	for( int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++ )
	{
		g_aPlayer[nCntPlayer].pos = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		g_aPlayer[nCntPlayer].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		g_aPlayer[nCntPlayer].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		g_aPlayer[nCntPlayer].nNumParts = 60;
		g_aPlayer[nCntPlayer].fPosMove = POSMOVE_PLAYER;
	}
	return S_OK;
}

//================================================================================================================================================================================================
// UninitPlayer関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UninitPlayer( void )
{
	for( int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++ )
	{
		// メッシュ情報の開放
		if( aModel[ nCntModel ].pMesh != NULL )
		{
			aModel[ nCntModel ].pMesh->Release();
			aModel[ nCntModel ].pMesh = NULL;
		}

		// バッファの開放
		if( aModel[ nCntModel ].pBuffMat != NULL )
		{
			aModel[ nCntModel ].pBuffMat->Release();
			aModel[ nCntModel ].pBuffMat = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdatePlayer関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void UpdatePlayer( void )
{
	// カメラの座標など取得する。
	CAMERA camera = GetCamera();
	//ModelBody八方向移動
	PlayerMove(
			&camera.rot,	//向き
			POSMOVE_PLAYER,				//移動量
			DIK_W,				//上ボタン
			DIK_S,			//下ボタン
			DIK_A,			//左ボタン
			DIK_D			//右ボタン
	);
}

//================================================================================================================================================================================================
// DrawPlayer関数
// 引数 void
// 戻り値 void
// 説明 
//================================================================================================================================================================================================
void DrawPlayer( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// マテリアル情報
	D3DMATERIAL9 matDef;	// デフォルトのマテリアル。今のマテリアルの情報を退避させるための変数。

	// 現在のマテリアル情報を取得する。
	pDevice->GetMaterial( &matDef );

	for( int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++ )
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_aPlayer[ nCntPlayer ].mtxWorld );

		// スケールを反映
		D3DXMatrixScaling( &mtxScl, g_aPlayer[ nCntPlayer ].scl.x, g_aPlayer[ nCntPlayer ].scl.y, g_aPlayer[ nCntPlayer ].scl.z );
		D3DXMatrixMultiply( &g_aPlayer[ nCntPlayer ].mtxWorld, &g_aPlayer[ nCntPlayer ].mtxWorld, &mtxScl );

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aPlayer[ nCntPlayer ].rot.y, g_aPlayer[ nCntPlayer ].rot.x, g_aPlayer[ nCntPlayer ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aPlayer[ nCntPlayer ].mtxWorld, &g_aPlayer[ nCntPlayer ].mtxWorld, &mtxRot );

		// 位置を反映
		D3DXMatrixTranslation( &mtxTrans, g_aPlayer[ nCntPlayer ].pos.x, g_aPlayer[ nCntPlayer ].pos.y, g_aPlayer[ nCntPlayer ].pos.z );
		D3DXMatrixMultiply( &g_aPlayer[ nCntPlayer ].mtxWorld, &g_aPlayer[ nCntPlayer ].mtxWorld, &mtxTrans );

		// ワールドマトリックスを設定
		pDevice->SetTransform( D3DTS_WORLD, &g_aPlayer[ nCntPlayer ].mtxWorld );

		for (int nCntParts = 0; nCntParts < MAX_PARTS ;nCntParts ++)
		{
			for( int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++ )
			{
				// ワールドマトリックスの初期化
				D3DXMatrixIdentity( &aModel[ nCntModel ].mtxWorld );

				// スケールを反映
				D3DXMatrixScaling( &mtxScl, aModel[ nCntModel ].scl.x, aModel[ nCntModel ].scl.y, aModel[ nCntModel ].scl.z );
				D3DXMatrixMultiply( &aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld, &mtxScl );

				// 回転を反映
				D3DXMatrixRotationYawPitchRoll( &mtxRot, aModel[ nCntModel ].rot.y, aModel[ nCntModel ].rot.x, aModel[ nCntModel ].rot.z );	// y,x,z
				D3DXMatrixMultiply( &aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld, &mtxRot );

				// 位置を反映
				D3DXMatrixTranslation( &mtxTrans, aModel[ nCntModel ].pos.x, aModel[ nCntModel ].pos.y, aModel[ nCntModel ].pos.z );
				D3DXMatrixMultiply( &aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld, &mtxTrans );

				D3DXMatrixMultiply ( &aModel[ nCntModel ].mtxWorld,&aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld/*親モデルのワールドマトリックス*/ );

				// ワールドマトリックスを設定
				pDevice->SetTransform( D3DTS_WORLD, &aModel[ nCntModel ].mtxWorld );

				// キャスト変換
				pMat = ( D3DXMATERIAL* )aModel[ nCntModel ].pBuffMat->GetBufferPointer();

				for( int nCntMat = 0; nCntMat < ( int )aModel[ nCntModel ].nNumMat; nCntMat++ )
				{
					// マテリアルの設定
					pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

					// テクスチャの設定
					pDevice->SetTexture( 0, NULL );		// テクスチャを貼らない
						
					// メッシュの描画
					aModel[ nCntModel ].pMesh->DrawSubset( nCntMat );
				}
			}
		}
	}
	// マテリアル情報を元に戻す。戻さないと次に描画されるマテリアルがおかしくなる。赤色のまま、とか。
	pDevice->SetMaterial( &matDef );
}
//================================================================================================================================================================================================
// *GetPlayer関数
// 引数 void
// 戻り値 
// 説明 Playerを取得する。
//================================================================================================================================================================================================
PLAYER *GetPlayer( void )
{
	return &g_aPlayer[ 0 ];
}

//================================================================================================================================================================================================
// *GetModel関数
// 引数 void
// 戻り値 
// 説明 Modelを取得する。
//================================================================================================================================================================================================
MODEL *GetModel( void )
{
	return &aModel[ 0 ];
}
/*******************************************************************************
* 関数名: 八方向移動関数
* 
* 引数  : D3DXVECTOR3	*pos		//位置
		  D3DXVECTOR3	*rot		//向き
		  float			fPosmove	//移動量
		  int			UP			//上ボタン
		  int			DOWN			//下ボタン
		  int			LEFT		//左ボタン
		  int			RIGHT		//右ボタン
* 戻り値: ナシ
* 説明: ナシ
*******************************************************************************/
void PlayerMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	PLAYER *pPlayer = GetPlayer();
	pPlayer -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左上移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右上移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
		}
		else											//前移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//左下移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//右下移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
		}
		else											//後移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + 0.0f;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//左上移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//左下移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else											//左移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//右上移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//右下移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
		}
		else											//右移動
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}

	//座標を更新（慣性）
	pPlayer -> pos.x += ( pPlayer->OldPos.x - pPlayer -> pos.x ) * PLAYER_INERTIA_MOVE;
	pPlayer -> pos.z += ( pPlayer->OldPos.z - pPlayer -> pos.z ) * PLAYER_INERTIA_MOVE;
}