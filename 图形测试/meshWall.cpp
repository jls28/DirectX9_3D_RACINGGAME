#include "main.h"
#include "input.h"
#include "meshField.h"
#include "use.h"

#include "meshWall.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define MESHWALL_TEXTURE_FILE	"data\\TEXTURE\\fence000.jpg"	//�ǃe�N�X�`���t�@�C���ʒu
#define MESHWALL_WIDTH			( 50.0f )						//�E�H�[���̕�
#define MESHWALL_HEIGHT			( 20.0f )						//�E�H�[���̍���

/*******************************************************************************
* �O���[�o���ϐ�
********************************************************************************/
MESHWALL	g_Wall[ WALL_MAX ];									//�E�H�[���\����

/*******************************************************************************
* �֐���: ���b�V���E�H�[���̏������֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
HRESULT InitMeshWall( void )
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	MESHFIELD *pField;
	pField = GetMeshField();

	for( int nCntMeshWall = 0; nCntMeshWall < WALL_MAX; nCntMeshWall++ )
	{
		//���b�V���E�H�[���\���̂̏�����
		g_Wall[ nCntMeshWall ].pTexture = NULL;													//�e�N�X�`���o�b�t�@�ւ̃|�C���^
		g_Wall[ nCntMeshWall ].pIdxBuff = NULL;													//���_�o�b�t�@�ւ̃|�C���^
		g_Wall[ nCntMeshWall ].pIdxBuff = NULL;													//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

		g_Wall[ nCntMeshWall ].mesh.nNumVtxV		= 100;					//���̒��_��
		g_Wall[ nCntMeshWall ].mesh.nNumVtxH		= 2;										//�c�̒��_��

		//�����_��
		g_Wall[ nCntMeshWall ].mesh.nNumVtx			= g_Wall[ nCntMeshWall ].mesh.nNumVtxV * g_Wall[ nCntMeshWall ].mesh.nNumVtxH;

		//�C���f�b�N�X��
		g_Wall[ nCntMeshWall ].mesh.nNumIdx			= ( g_Wall[ nCntMeshWall ].mesh.nNumVtx - g_Wall[ nCntMeshWall ].mesh.nNumVtxV + g_Wall[ nCntMeshWall ].mesh.nNumVtxH - 2 ) * 2;

		g_Wall[ nCntMeshWall ].mesh.nNumBlock		= g_Wall[ nCntMeshWall ].mesh.nNumVtxV - 1;	//�u���b�N��
		g_Wall[ nCntMeshWall ].mesh.nNumPrimitive	= g_Wall[ nCntMeshWall ].mesh.nNumIdx - 2;	//�|���S����
		g_Wall[ nCntMeshWall ].mesh.fTexAdjust		= 0.0f;										//�e�N�X�`��Y���W���炷�W��
		g_Wall[ nCntMeshWall ].mesh.nNumIdxEven		= 0;										//�C���f�b�N�X�o�b�t�@���_�������̐�(�މ��O�p�`���_�ȊO)
		g_Wall[ nCntMeshWall ].mesh.nNumNullTri		= 0;										//�k�ރ|���S�����_�̐�
		g_Wall[ nCntMeshWall ].mesh.nMultiple		= 2;										//�C���f�b�N�X�o�b�t�@�p�W��


		//���_�o�b�t�@�̐���
		if( FAILED ( pDevice -> CreateVertexBuffer(
													sizeof( VERTEX_3D ) * g_Wall[ nCntMeshWall ].mesh.nNumVtx,
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_3D,
													D3DPOOL_MANAGED,
													&g_Wall[ nCntMeshWall ].pVtxBuff,
													NULL
		) ) )
		{
			return E_FAIL;
		}

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile( pDevice, MESHWALL_TEXTURE_FILE, &g_Wall[ nCntMeshWall ].pTexture );
	}
	///*0�Ԗڕǂ̒��_���쐬*/
	//MeshWallVtx(
	//			 g_Wall[ 0 ].pVtxBuff,
	//			&g_Wall[ 0 ],											//�E�H�[���̍\����
	//			D3DXVECTOR3( 0.0f, 0.0f, pField -> fFixedPos ),			//�E�H�[���̒��S�ʒu
	//			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//�E�H�[���̉�]
	//			D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//�E�H�[���̊g��k��
	//			WALL_FRONT,												//�E�H�[���̌������
	//			MESHWALL_WIDTH,											//�E�H�[���̕�
	//			MESHWALL_HEIGHT											//�E�H�[���̍���
	//);
	///*1�Ԗڕǂ̒��_���쐬*/
	//MeshWallVtx(
	//			 g_Wall[ 1 ].pVtxBuff,
	//			&g_Wall[ 1 ],											//�E�H�[���̍\����
	//			D3DXVECTOR3( 0.0f, 0.0f, -( pField -> fFixedPos ) ),	//�E�H�[���̒��S�ʒu
	//			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//�E�H�[���̉�]
	//			D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//�E�H�[���̊g��k��
	//			WALL_BACK,												//�E�H�[���̌������
	//			MESHWALL_WIDTH,												//�E�H�[���̕�
	//			MESHWALL_HEIGHT											//�E�H�[���̍���
	//);
	/*2�Ԗڕǂ̒��_���쐬*/
	MeshWallVtx(
				 g_Wall[ 2 ].pVtxBuff,
				&g_Wall[ 2 ],											//�E�H�[���̍\����
				D3DXVECTOR3(/* -( pField -> fFixedPos )*/TRACK_WIDTH_LEFT, 0.0f, 0.0f ),	//�E�H�[���̒��S�ʒu
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//�E�H�[���̉�]
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//�E�H�[���̊g��k��
				WALL_LEFT,												//�E�H�[���̌������
				MESHWALL_WIDTH,											//�E�H�[���̕�
				MESHWALL_HEIGHT											//�E�H�[���̍���
	);
	/*3�Ԗڕǂ̒��_���쐬*/
	MeshWallVtx(
				 g_Wall[ 3 ].pVtxBuff,
				&g_Wall[ 3 ],											//�E�H�[���̍\����
				D3DXVECTOR3( /*pField -> fFixedPos*/TRACK_WIDTH_RIGHT, 0.0f, 0.0f ),			//�E�H�[���̒��S�ʒu
				D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),						//�E�H�[���̉�]
				D3DXVECTOR3( 1.0f, 1.0f, 1.0f ),						//�E�H�[���̊g��k��
				WALL_RIGHT,												//�E�H�[���̌������
				MESHWALL_WIDTH,											//�E�H�[���̕�
				MESHWALL_HEIGHT											//�E�H�[���̍���
	);

	for( int nCntIdxWall = 0; nCntIdxWall < WALL_MAX; nCntIdxWall++ )
	{
		//�C���f�b�N�X�o�b�t�@���m��
		if( FAILED ( pDevice -> CreateIndexBuffer(
										sizeof( WORD ) * g_Wall[ nCntIdxWall ].mesh.nNumIdx,
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&g_Wall[ nCntIdxWall ].pIdxBuff,
										NULL
		) ) )
		{
			return E_FAIL;
		}

		MeshIdx(
				g_Wall[ nCntIdxWall ].pIdxBuff,	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^�[
				&g_Wall[ nCntIdxWall ].mesh		//�E�H�[���̃��b�V�����
		);
	}

	return S_OK;
}

/*******************************************************************************
* �֐���: ���b�V���E�H�[���̏I���֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UninitMeshWall( void )
{
	for( int nCntMeshWall = 0; nCntMeshWall < WALL_MAX; nCntMeshWall++ )
	{
		if( g_Wall[ nCntMeshWall ].pTexture != NULL )
		{
			g_Wall[ nCntMeshWall ].pTexture -> Release();	//�e�N�X�`���o�b�t�@�̊J��
			g_Wall[ nCntMeshWall ].pTexture = NULL;
		}

		if( g_Wall[ nCntMeshWall ].pVtxBuff != NULL )		//���_�o�b�t�@�̊J��
		{
			g_Wall[ nCntMeshWall ].pVtxBuff -> Release();
			g_Wall[ nCntMeshWall ].pVtxBuff = NULL;
		}

		if( g_Wall[ nCntMeshWall ].pIdxBuff != NULL )		//�C���f�b�N�X�o�b�t�@�̊J��
		{
			g_Wall[ nCntMeshWall ].pIdxBuff -> Release();
			g_Wall[ nCntMeshWall ].pIdxBuff = NULL;
		}
	}
}

/*******************************************************************************
* �֐���: ���b�V���E�H�[���̍X�V�֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UpdateMeshWall( void )
{

}

/*******************************************************************************
* �֐���: ���b�V���E�H�[���̕`��֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void DrawMeshWall( void )
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntMeshWall = 0; nCntMeshWall < WALL_MAX; nCntMeshWall++ )
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_Wall[ nCntMeshWall ].mtx.World );

		//�X�P�[���𔽉f
		D3DXMatrixScaling(
							&g_Wall[ nCntMeshWall ].mtx.Scl,
							g_Wall[ nCntMeshWall ].scl.x,
							g_Wall[ nCntMeshWall ].scl.y,
							g_Wall[ nCntMeshWall ].scl.z
		);
		D3DXMatrixMultiply(
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.Scl
		);

		//��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(
							&g_Wall[ nCntMeshWall ].mtx.Rot,
							g_Wall[ nCntMeshWall ].rot.y,
							g_Wall[ nCntMeshWall ].rot.x,
							g_Wall[ nCntMeshWall ].rot.z
		);
		D3DXMatrixMultiply(
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.Rot
		);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(
							&g_Wall[ nCntMeshWall ].mtx.Trans,
							g_Wall[ nCntMeshWall ].pos.x,
							g_Wall[ nCntMeshWall ].pos.y,
							g_Wall[ nCntMeshWall ].pos.z
		);
		D3DXMatrixMultiply(
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.World,
							&g_Wall[ nCntMeshWall ].mtx.Trans
		);

		//���[���h�}�g���b�N�X��ݒ�
		pDevice -> SetTransform( D3DTS_WORLD, &g_Wall[ nCntMeshWall ].mtx.World );

		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
		pDevice -> SetStreamSource( 0, g_Wall[ nCntMeshWall ].pVtxBuff, 0, sizeof( VERTEX_3D ) );

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
		pDevice -> SetIndices( g_Wall[ nCntMeshWall ].pIdxBuff );

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice -> SetFVF( FVF_VERTEX_3D );

		//�e�N�X�`���̐ݒ�
		pDevice -> SetTexture( 0, g_Wall[ nCntMeshWall ].pTexture );

		//�|���S���̕`��
		pDevice -> DrawIndexedPrimitive(
										D3DPT_TRIANGLESTRIP,
										0,
										0,
										g_Wall[ nCntMeshWall ].mesh.nNumVtx,					//���_��
										0,
										g_Wall[ nCntMeshWall ].mesh.nNumPrimitive			//�v���~�e�B�u��
		);
	}
}

/*******************************************************************************
* �֐���: GetMeshWall
*******************************************************************************/
MESHWALL *GetMeshWall( void )
{
	return &g_Wall[ 0 ];
}