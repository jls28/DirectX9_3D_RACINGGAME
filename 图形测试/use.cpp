/*******************************************************************************
* �^�C�g���F	�֐���
* �t�@�C�����F	use.cpp`
* �쐬�ҁF		AT12A244 46 LIHAOSHENG
* �쐬���F		2015-11-20 18:24:52
********************************************************************************
* �X�V�����F2015-11-21 12:12:52 �J�����ړ�
			2015-11-22 ���f���ړ�
�ύX�O)
�J�����̈ʒu = �J�����̃^�[�Q�b�g����̑��ΓI�ʒu  + �J�����̃^�[�Q�b�g�̈ʒu
           = ���f���̈ʒu                       + �J�����̃^�[�Q�b�g�̈ʒu
�ύX��)
�J�����̃^�[�Q�b�g�̈ʒu = �J�����̃^�[�Q�b�g����̑��ΓI�ʒu  + �J�����̈ʒu 
           = ���f���̈ʒu                       + �J�����̈ʒu
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "use.h"
#include "propmodel_Group.h"
/*******************************************************************************
* �O���[�o���ϐ�
********************************************************************************/


/*******************************************************************************
* �֐���: �t�B�[���h���_�̏�����
* 
* ����  : LPDIRECT3DVERTEXBUFFER9	pVtxBuff		//���_�o�b�t�@�ւ̃|�C���^
		  MESHFIELD					*pField			//�t�B�[���h�̍\����
		  D3DXVECTOR3				pos				//�t�B�[���h�̌��_�ʒu
		  D3DXVECTOR3				rot				//�t�B�[���h�̉�]
		  D3DXVECTOR3				scl				//�t�B�[���h�̊g��k��
		  float						WIDTH			//�t�B�[���h�̕�
		  int						HEIGHT			//�t�B�[���h�̍���

* �߂�l: �i�V
* ����: �i�V
*******************************************************************************/
void MeshFieldVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHFIELD *pField, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, float WIDTH, float HEIGHT )
{
	int nCntFieldSur;		//�J�E���^�̗]��

	pField -> pos = pos;	//�ʒu
	pField -> rot = rot;	//����
	pField -> scl = scl;	//�g��k��

	//�t�B�[���h���_�o�b�t�@�̏�����
	VERTEX_3D *pVtx;

	pVtxBuff -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	if( pField -> mesh.nNumVtx % 2 == 0 )	//���_����������������
	{
		pField -> mesh.fVtxAdjust = 0.5f;	//���_���W�����W��
	}
	else									//���_�������������
	{
		pField -> mesh.fVtxAdjust = 0.0f;	//���_���W�����W��
	}

	for( int nCntMeshFieldVtx = 0; nCntMeshFieldVtx < pField -> mesh.nNumVtx; nCntMeshFieldVtx++ )
	{
		nCntFieldSur = nCntMeshFieldVtx % pField -> mesh.nNumVtxV;

		//���_���W�̐ݒ�
		pVtx[ nCntMeshFieldVtx ].pos.x	= ( nCntFieldSur - pField -> mesh.nNumVtxV / 2 + pField -> mesh.fVtxAdjust ) * WIDTH;
		pVtx[ nCntMeshFieldVtx ].pos.y	= 0.0f;
		pVtx[ nCntMeshFieldVtx ].pos.z	=( pField -> mesh.nNumVtxH - pField -> mesh.fVtxAdjust) * HEIGHT;

		//�@���̐ݒ�
		pVtx[ nCntMeshFieldVtx ].nor	= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

		//���_�J���[�̐ݒ�
		pVtx[ nCntMeshFieldVtx ].col	= D3DCOLOR_RGBA( 255, 255, 255, 255 );

		//�e�N�X�`�����W�̐ݒ�
		pVtx[ nCntMeshFieldVtx ].tex.x	= ( float )nCntFieldSur;
		pVtx[ nCntMeshFieldVtx ].tex.y	= pField -> mesh.fTexAdjust;
		if( nCntFieldSur == pField -> mesh.nNumVtxV - 1 )	//���s
		{
			pField -> mesh.fTexAdjust++;					//�e�N�X�`��Y���W�ʒu�p
			pField -> mesh.nNumVtxH--;						//�c�̒��_��
		}
	}

	pField -> fFixedPos = pVtx[ 0 ].pos.z;

	pVtxBuff -> Unlock();
}

/*******************************************************************************
* �֐���: �E�H�[�����_�̏�����
* 
* ����  : LPDIRECT3DVERTEXBUFFER9	pVtxBuff 		//���_�o�b�t�@�ւ̃|�C���^
		  MESHWALL					*pWall			//�E�H�[���̍\����
		  D3DXVECTOR3				pos				//�E�H�[���̌��_�ʒu
		  D3DXVECTOR3				rot				//�E�H�[���̉�]
		  D3DXVECTOR3				scl				//�E�H�[���̊g��k��
		  int						STATE			//�E�H�[���̌������
		  float						WIDTH			//�E�H�[���̕�
		  float						HEIGHT			//�E�H�[���̍���
* �߂�l: �i�V
* ����: �i�V
*******************************************************************************/
void MeshWallVtx( LPDIRECT3DVERTEXBUFFER9 pVtxBuff, MESHWALL *pWall, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, int STATE, float WIDTH, float HEIGHT )
{
	int nCntWallSur;														//�J�E���^�̗]��

	pWall -> pos = pos;		//�ʒu
	pWall -> rot = rot;		//��]
	pWall -> scl = scl;		//�g��k��

	//�E�H�[�����_�o�b�t�@�̏�����
	VERTEX_3D *pVtx;

	pVtxBuff -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	if( pWall -> mesh.nNumVtxV % 2 == 0 )	//���_����������������
	{
		pWall -> mesh.fVtxAdjust = 0.5f;	//���_���W�����W��
	}
	else									//���_�������������
	{
		pWall -> mesh.fVtxAdjust = 0.0f;	//���_���W�����W��
	}

	for( int nCntMeshWallVtx = 0; nCntMeshWallVtx < pWall -> mesh.nNumVtx; nCntMeshWallVtx++ )
	{
		nCntWallSur = nCntMeshWallVtx % pWall -> mesh.nNumVtxV;

		switch( STATE )
		{
		//case WALL_FRONT:
		//	//���_���W�̐ݒ�
		//	pVtx[ nCntMeshWallVtx ].pos.x	= ( nCntWallSur - pWall -> mesh.nNumVtxV / 2 + pWall -> mesh.fVtxAdjust ) * WIDTH;
		//	pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
		//	pVtx[ nCntMeshWallVtx ].pos.z	= 0.0f;

		//	//�@���̐ݒ�
		//	pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		//	break;
		//case WALL_BACK:
		//	//���_���W�̐ݒ�
		//	pVtx[ nCntMeshWallVtx ].pos.x	= ( pWall -> mesh.nNumVtxV / 2 - nCntWallSur - pWall -> mesh.fVtxAdjust ) * WIDTH;
		//	pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
		//	pVtx[ nCntMeshWallVtx ].pos.z	= 0.0f;

			//�@���̐ݒ�
			pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
			break;
		case WALL_LEFT:
			//���_���W�̐ݒ�
			pVtx[ nCntMeshWallVtx ].pos.x	= 0.0f;
			pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
			pVtx[ nCntMeshWallVtx ].pos.z	= ( nCntWallSur - pWall -> mesh.nNumVtxV / 2 + pWall -> mesh.fVtxAdjust ) * WIDTH;

			//�@���̐ݒ�
			pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
			break;
		case WALL_RIGHT:
			//���_���W�̐ݒ�
			pVtx[ nCntMeshWallVtx ].pos.x	= 0.0f;
			pVtx[ nCntMeshWallVtx ].pos.y	= ( pWall -> mesh.nNumVtxH - 1 ) * HEIGHT;
			pVtx[ nCntMeshWallVtx ].pos.z	= ( pWall -> mesh.nNumVtxV / 2 - nCntWallSur - pWall -> mesh.fVtxAdjust ) * WIDTH;

			//�@���̐ݒ�
			pVtx[ nCntMeshWallVtx ].nor		= D3DXVECTOR3( -1.0f, 0.0f, 0.0f );
			break;
		}

		//���_�J���[�̐ݒ�
		pVtx[ nCntMeshWallVtx ].col			= D3DCOLOR_RGBA( 255, 255, 255, 255 );

		//�e�N�X�`�����W�̐ݒ�
		pVtx[ nCntMeshWallVtx ].tex.x		= ( float )nCntWallSur;
		pVtx[ nCntMeshWallVtx ].tex.y		= pWall -> mesh.fTexAdjust;

		if( nCntWallSur == pWall -> mesh.nNumVtxV - 1 )		//���s
		{
			pWall -> mesh.fTexAdjust++;						//�e�N�X�`��Y���W�ʒu
			pWall -> mesh.nNumVtxH--;						//�c�̒��_��
		}
	}

	pVtxBuff -> Unlock();
}

/*******************************************************************************
* �֐���: �C���f�b�N�X�o�b�t�@���_�̏�����
* 
* ����  : LPDIRECT3DINDEXBUFFER9	pIdxBuff		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		  MESH						*pMesh			//�\����
* �߂�l: �i�V
* ����: �i�V
*******************************************************************************/
void MeshIdx( LPDIRECT3DINDEXBUFFER9 pIdxBuff, MESH *pMesh )
{
	//�C���f�b�N�X�o�b�t�@�̏�����
	WORD *pIdx;
	pIdxBuff -> Lock( 0, 0, ( void** ) &pIdx, 0 );

	//���_�ԍ����擾(N�^�`��p)
	for( int nCntIdx = 0; nCntIdx < pMesh -> nNumIdx; nCntIdx++ )
	{
		if( nCntIdx == pMesh -> nNumVtxV * pMesh -> nMultiple + pMesh -> nNumNullTri )	//�k�ރ|���S�����_��ݒ肵�A���s
		{
			//�k�ރ|���S�����_�̐ݒ�
			if( nCntIdx % 2 == 0 )
			{
				pIdx[ nCntIdx ] = pIdx[ nCntIdx - 1 ];
				pMesh -> nNumNullTri++;													//�k�ރ|���S�����_����1�����Z����
			}
			else
			{
				pIdx[ nCntIdx ] = pMesh -> nNumVtxV + pMesh -> nNumIdxEven;
				pMesh -> nMultiple += 2;
				pMesh -> nNumNullTri++;
			}
		}
		
		//�C���f�b�N�X���_�ԍ���������������
		else if( nCntIdx % 2 == 0 )
		{
			pIdx[ nCntIdx ] = pMesh -> nNumVtxV + pMesh -> nNumIdxEven;
			pMesh -> nNumIdxEven++;
		}

		//�C���f�b�N�X���_�ԍ������������
		else
		{
			pIdx[ nCntIdx ] = nCntIdx - pMesh -> nNumIdxEven - pMesh -> nNumNullTri;
		}
	}
	pIdxBuff -> Unlock();
}
