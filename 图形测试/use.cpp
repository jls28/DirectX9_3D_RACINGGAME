/*******************************************************************************
* タイトル：	関数化
* ファイル名：	use.cpp`
* 作成者：		AT12A244 46 LIHAOSHENG
* 作成日：		2015-11-20 18:24:52
********************************************************************************
* 更新履歴：2015-11-21 12:12:52 カメラ移動
			2015-11-22 モデル移動
変更前)
カメラの位置 = カメラのターゲットからの相対的位置  + カメラのターゲットの位置
           = モデルの位置                       + カメラのターゲットの位置
変更後)
カメラのターゲットの位置 = カメラのターゲットからの相対的位置  + カメラの位置 
           = モデルの位置                       + カメラの位置
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "use.h"
#include "propmodel_Group.h"
/*******************************************************************************
* グローバル変数
********************************************************************************/


/*******************************************************************************
* 関数名: フィールド頂点の初期化
* 
* 引数  : LPDIRECT3DVERTEXBUFFER9	pVtxBuff		//頂点バッファへのポインタ
		  MESHFIELD					*pField			//フィールドの構造体
		  D3DXVECTOR3				pos				//フィールドの原点位置
		  D3DXVECTOR3				rot				//フィールドの回転
		  D3DXVECTOR3				scl				//フィールドの拡大縮小
		  float						WIDTH			//フィールドの幅
		  int						HEIGHT			//フィールドの高さ

* 戻り値: ナシ
* 説明: ナシ
*******************************************************************************/
void MeshFieldVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHFIELD *pField, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float WIDTH, float HEIGHT )
{
	int nCntFieldSur;		//カウンタの余り

	pField -> pos = pos;	//位置
	pField -> rot = rot;	//向き
	pField -> scl = scl;	//拡大縮小

	//フィールド頂点バッファの初期化
	VERTEX_3D *pVtx;

	pVtxBuff -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	if( pField -> mesh.nNumVtx % 2 == 0 )	//頂点数が偶数だったら
	{
		pField -> mesh.fVtxAdjust = 0.5f;	//頂点座標調整係数
	}
	else									//頂点数が奇数だったら
	{
		pField -> mesh.fVtxAdjust = 0.0f;	//頂点座標調整係数
	}

	for( int nCntMeshFieldVtx = 0; nCntMeshFieldVtx < pField -> mesh.nNumVtx; nCntMeshFieldVtx++ )
	{
		nCntFieldSur = nCntMeshFieldVtx % pField -> mesh.nNumVtxV;

		//頂点座標の設定
		pVtx[ nCntMeshFieldVtx ].pos.x	= ( nCntFieldSur - pField -> mesh.nNumVtxV / 2 + pField -> mesh.fVtxAdjust ) * WIDTH;
		pVtx[ nCntMeshFieldVtx ].pos.y	= 0.0f;
		pVtx[ nCntMeshFieldVtx ].pos.z	=( pField -> mesh.nNumVtxH - pField -> mesh.fVtxAdjust) * HEIGHT;

		//法線の設定
		pVtx[ nCntMeshFieldVtx ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		//頂点カラーの設定
		pVtx[ nCntMeshFieldVtx ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );

		//テクスチャ座標の設定
		pVtx[ nCntMeshFieldVtx ].tex.x	= ( float )nCntFieldSur;
		pVtx[ nCntMeshFieldVtx ].tex.y	= pField -> mesh.fTexAdjust;
		if( nCntFieldSur == pField -> mesh.nNumVtxV - 1 )	//改行
		{
			pField -> mesh.fTexAdjust++;					//テクスチャY座標位置用
			pField -> mesh.nNumVtxH--;						//縦の頂点数
		}
	}

	pField -> fFixedPos = pVtx[ 0 ].pos.z;

	pVtxBuff -> Unlock();
}

/*******************************************************************************
* 関数名: ウォール頂点の初期化
* 
* 引数  : LPDIRECT3DVERTEXBUFFER9	pVtxBuff 		//頂点バッファへのポインタ
		  MESHWALL					*pWall			//ウォールの構造体
		  D3DXVECTOR3				pos				//ウォールの原点位置
		  D3DXVECTOR3				rot				//ウォールの回転
		  D3DXVECTOR3				scl				//ウォールの拡大縮小
		  int						STATE			//ウォールの向き情報
		  float						WIDTH			//ウォールの幅
		  float						HEIGHT			//ウォールの高さ
* 戻り値: ナシ
* 説明: ナシ
*******************************************************************************/
void MeshWallVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHWALL *pWall, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int STATE, float WIDTH, float HEIGHT )
{
	int nCntWallSur;														//カウンタの余り

	pWall -> pos = pos;		//位置
	pWall -> rot = rot;		//回転
	pWall -> scl = scl;		//拡大縮小

	//ウォール頂点バッファの初期化
	VERTEX_3D *pVtx;

	pVtxBuff -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	if( pWall -> mesh.nNumVtxV % 2 == 0 )	//頂点数が偶数だったら
	{
		pWall -> mesh.fVtxAdjust = 0.5f;	//頂点座標調整係数
	}
	else									//頂点数が奇数だったら
	{
		pWall -> mesh.fVtxAdjust = 0.0f;	//頂点座標調整係数
	}

	for( int nCntMeshWallVtx = 0; nCntMeshWallVtx < pWall -> mesh.nNumVtx; nCntMeshWallVtx++ )
	{
		nCntWallSur = nCntMeshWallVtx % pWall -> mesh.nNumVtxV;

		switch( STATE )
		{
		//case WALL_FRONT:
		//	//頂点座標の設定
		//	pVtx[ nCntMeshWallVtx ].pos.x	= ( nCntWallSur - pWall -> mesh.nNumVtxV / 2 + pWall -> mesh.fVtxAdjust ) * WIDTH;
		//	pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
		//	pVtx[ nCntMeshWallVtx ].pos.z	= 0.0f;

		//	//法線の設定
		//	pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		//	break;
		//case WALL_BACK:
		//	//頂点座標の設定
		//	pVtx[ nCntMeshWallVtx ].pos.x	= ( pWall -> mesh.nNumVtxV / 2 - nCntWallSur - pWall -> mesh.fVtxAdjust ) * WIDTH;
		//	pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
		//	pVtx[ nCntMeshWallVtx ].pos.z	= 0.0f;

			//法線の設定
			pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
			break;
		case WALL_LEFT:
			//頂点座標の設定
			pVtx[ nCntMeshWallVtx ].pos.x	= 0.0f;
			pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
			pVtx[ nCntMeshWallVtx ].pos.z	= ( nCntWallSur - pWall -> mesh.nNumVtxV / 2 + pWall -> mesh.fVtxAdjust ) * WIDTH;

			//法線の設定
			pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
			break;
		case WALL_RIGHT:
			//頂点座標の設定
			pVtx[ nCntMeshWallVtx ].pos.x	= 0.0f;
			pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
			pVtx[ nCntMeshWallVtx ].pos.z	= ( pWall -> mesh.nNumVtxV / 2 - nCntWallSur - pWall -> mesh.fVtxAdjust ) * WIDTH;

			//法線の設定
			pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
			break;
		}

		//頂点カラーの設定
		pVtx[ nCntMeshWallVtx ].col			= D3DCOLOR_RGBA( 255, 255, 255, 255 );

		//テクスチャ座標の設定
		pVtx[ nCntMeshWallVtx ].tex.x		= ( float )nCntWallSur;
		pVtx[ nCntMeshWallVtx ].tex.y		= pWall -> mesh.fTexAdjust;

		if( nCntWallSur == pWall -> mesh.nNumVtxV - 1 )		//改行
		{
			pWall -> mesh.fTexAdjust++;						//テクスチャY座標位置
			pWall -> mesh.nNumVtxH--;						//縦の頂点数
		}
	}

	pVtxBuff -> Unlock();
}

/*******************************************************************************
* 関数名: インデックスバッファ頂点の初期化
* 
* 引数  : LPDIRECT3DINDEXBUFFER9	pIdxBuff		//インデックスバッファへのポインタ
		  MESH						*pMesh			//構造体
* 戻り値: ナシ
* 説明: ナシ
*******************************************************************************/
void MeshIdx( LPDIRECT3DINDEXBUFFER9 pIdxBuff, MESH *pMesh )
{
	//インデックスバッファの初期化
	WORD *pIdx;
	pIdxBuff -> Lock( 0, 0, ( void** ) &pIdx, 0 );

	//頂点番号を取得(N型描画用)
	for( int nCntIdx = 0; nCntIdx < pMesh -> nNumIdx; nCntIdx++ )
	{
		if( nCntIdx == pMesh -> nNumVtxV * pMesh -> nMultiple + pMesh -> nNumNullTri )	//縮退ポリゴン頂点を設定し、改行
		{
			//縮退ポリゴン頂点の設定
			if( nCntIdx % 2 == 0 )
			{
				pIdx[ nCntIdx ] = pIdx[ nCntIdx - 1 ];
				pMesh -> nNumNullTri++;													//縮退ポリゴン頂点数が1を加算する
			}
			else
			{
				pIdx[ nCntIdx ] = pMesh -> nNumVtxV + pMesh -> nNumIdxEven;
				pMesh -> nMultiple += 2;
				pMesh -> nNumNullTri++;
			}
		}
		
		//インデックス頂点番号が偶数だったら
		else if( nCntIdx % 2 == 0 )
		{
			pIdx[ nCntIdx ] = pMesh -> nNumVtxV + pMesh -> nNumIdxEven;
			pMesh -> nNumIdxEven++;
		}

		//インデックス頂点番号が奇数だったら
		else
		{
			pIdx[ nCntIdx ] = nCntIdx - pMesh -> nNumIdxEven - pMesh -> nNumNullTri;
		}
	}
	pIdxBuff -> Unlock();
}
