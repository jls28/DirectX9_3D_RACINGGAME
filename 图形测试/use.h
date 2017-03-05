/*******************************************************************************
* タイトル：	関数化
* ファイル名：	use.h
* 作成者：		AT12A244 46 LIHAOSHENG
* 作成日：		2015-11-20 18:24:52
********************************************************************************
* 更新履歴：
*******************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#ifndef _USE_H_
#define _USE_H_
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "meshField.h"
#include "meshWall.h"
#include "camera.h"
//プロトタイプの宣言
void MeshFieldVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHFIELD *pField, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float WIDTH, float HEIGHT );
void MeshWallVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHWALL *pWall, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int STATE, float WIDTH, float HEIGHT );
void MeshIdx( LPDIRECT3DINDEXBUFFER9 pIdxBuff, MESH *pMesh );


#endif