/*******************************************************************************
* �^�C�g���F	�֐���
* �t�@�C�����F	use.h
* �쐬�ҁF		AT12A244 46 LIHAOSHENG
* �쐬���F		2015-11-20 18:24:52
********************************************************************************
* �X�V�����F
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#ifndef _USE_H_
#define _USE_H_
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "meshField.h"
#include "meshWall.h"
#include "camera.h"
//�v���g�^�C�v�̐錾
void MeshFieldVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHFIELD *pField, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float WIDTH, float HEIGHT );
void MeshWallVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHWALL *pWall, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int STATE, float WIDTH, float HEIGHT );
void MeshIdx( LPDIRECT3DINDEXBUFFER9 pIdxBuff, MESH *pMesh );


#endif