/*******************************************************************************
* �^�C�g���F �����L���O����
* �t�@�C�����F ranking.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/23
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include <stdio.h>
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"
#include "fade.h"
#include "score.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define	TEXTURE_SCORE	"data\\TEXTURE\\score.png"	// �ǂݍ��ރe�N�X�`���t�@�C����


/*******************************************************************************
* �O���[�o���ϐ�
********************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;					//�����L���O�X�R�A�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankingScore = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRankingScore[ RANKINGSCORE_MAX ][ RANKING_MAX ];	//�����L���O�X�R�A�̈ʒu
RANKING *g_pRanking = NULL;											//�����L���O�ւ̃|�C���^
int g_nRankingScoreDigits[ RANKINGSCORE_MAX ][ RANKING_MAX ];		//�����L���O�X�R�A�̌��̐����i�[���[�N
int g_nNumRanking = RANKING_MAX;									//�����L���O�̑���
int nCnt;															//�����p�ϐ�
bool g_RankingUpdateUse;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

/*******************************************************************************
* �֐���: InitRanking
*******************************************************************************/
HRESULT InitRanking( void )
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice, TEXTURE_SCORE, &g_pTextureRankingScore );

	g_RankingUpdateUse = false;

	// ���_���̍쐬
	MakeVertexRanking(pDevice);
	return S_OK;
}

/*******************************************************************************
* �֐���: UninitRanking
*******************************************************************************/
void UninitRanking( void )
{

	if( g_pTextureRankingScore != NULL )
	{
		g_pTextureRankingScore -> Release();	//�����L���O�X�R�A�e�N�X�`���̊J��
		g_pTextureRankingScore = NULL;
	}

	if( g_pVtxBuffRankingScore != NULL )
	{
		g_pVtxBuffRankingScore -> Release();	//���_�o�b�t�@�̊J��
		g_pVtxBuffRankingScore = NULL;
	}
}

/*******************************************************************************
* �֐���: UpdateRanking
*******************************************************************************/
void UpdateRanking( void )
{
	VERTEX_2D *pVtx;

	g_pVtxBuffRankingScore -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	RANKING *pRanking = g_pRanking;

	for( int nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++ )
	{
		for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX; nCntRankingScore++, pVtx+=4)
		{

			g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] = pRanking -> nScore % Powi( 10, RANKINGSCORE_MAX - nCntRankingScore ) / Powi( 10, RANKINGSCORE_MAX - nCntRankingScore - 1 );

			pVtx[ 0 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f );
			pVtx[ 0 ].tex.y = 0.0f;

			pVtx[ 1 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f + 0.10f );
			pVtx[ 1 ].tex.y = 0.0f;
		 
			pVtx[ 2 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f );
			pVtx[ 2 ].tex.y = 1.0f;

			pVtx[ 3 ].tex.x = float( g_nRankingScoreDigits[ nCntRankingScore ][ nCntRanking ] * 0.10f + 0.10f );
			pVtx[ 3 ].tex.y = 1.0f;
		}
		pRanking++;
	}

	g_pVtxBuffRankingScore -> Unlock();
}

/*******************************************************************************
* �֐���: DrawRanking
*******************************************************************************/
void DrawRanking( void )
{
	//�f�o�C�X�̃Q�b�^�[
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource( 0, g_pVtxBuffRankingScore, 0, sizeof( VERTEX_2D ) );

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//�����L���O�X�R�A�e�N�X�`���̐ݒ�
	pDevice -> SetTexture( 0, g_pTextureRankingScore );

	for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX * RANKING_MAX; nCntRankingScore++ )
	{
		//�����L���O�X�R�A�̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, nCntRankingScore * 4, 2 );
	}
}	

//=============================================================================
// �f�[�^�����o��
//=============================================================================
void SaveRanking( void )
{
	FILE *pFile;

	if( g_RankingUpdateUse )
	{
		/*pFile = fopen( RANKING_FILE, "wb" );*/
		fopen_s( &pFile, RANKING_FILE, "wb" );

		if( pFile )
		{
			// �v���C���[���̏����o��
			fwrite( &g_nNumRanking, 4, 1, pFile );

			// �v���C���[�f�[�^�̏�������
			fwrite( g_pRanking, sizeof( RANKING ), g_nNumRanking, pFile);

			fclose( pFile );
			g_RankingUpdateUse = false;
		}
	}
}

//=============================================================================
// �f�[�^�ǂݍ���
//=============================================================================
void LoadRanking( void )
{
	FILE *pFile;

	// �t�@�C���I�[�v��
	/*pFile = fopen( RANKING_FILE, "rb" );*/
	fopen_s( &pFile, RANKING_FILE, "rb" );

	if( pFile )
	{
		// �ǂݍ���
		fread( &g_nNumRanking, 4, 1, pFile );

		if( g_pRanking )
		{
			free( g_pRanking );
			g_pRanking = NULL;
		}
		g_pRanking = ( RANKING * ) malloc ( sizeof( RANKING ) * g_nNumRanking );

		// �v���C���[�f�[�^�̏�������
		fread( g_pRanking, sizeof( RANKING ), g_nNumRanking, pFile );
		
		// �t�@�C���N���[�Y
		fclose( pFile );
	}
	else
	{
		if( g_pRanking )
		{
			free( g_pRanking );
			g_pRanking = NULL;
		}
		g_pRanking = ( RANKING * ) malloc ( sizeof( RANKING ) * g_nNumRanking );

		RANKING *pRanking = g_pRanking;

		for( int nCntRanking = 0; nCntRanking < g_nNumRanking; nCntRanking++ )
		{
			pRanking -> nScore = 500 - 100 * nCntRanking;
			pRanking++;
		}
	}
}

void CompareRanking( void )
{
	SCORE *pScore;
	RANKING *pRanking = g_pRanking;
	pScore = GetScore();

	for( int nCntRanking = 0; nCntRanking < g_nNumRanking; nCntRanking++ )
	{
		if( pScore -> g_nScore >= ( pRanking + ( nCntRanking ) ) -> nScore )
		{
			for( int nCntCompare = 4; nCntCompare > nCntRanking; nCntCompare-- )
			{
				( pRanking + ( nCntCompare ) ) -> nScore = ( pRanking + ( nCntCompare - 1 ) ) -> nScore;
			}
			( pRanking  + ( nCntRanking ) ) -> nScore = pScore -> g_nScore;
			g_RankingUpdateUse = true;
			pScore ->g_nScore = 0;

			VERTEX_2D *pVtx;
			g_pVtxBuffRankingScore -> Lock( 0, 0, ( void** ) &pVtx, 0 );

			for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX ; nCntRankingScore++ ,pVtx+=4)
			{
				//���_�J���[�̐ݒ�(�F�ς��)
				pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
				pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
				pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
				pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 0, 0, 255 );
			}

			break;
		}
	}
}
/*******************************************************************************
* �֐���: HRESULT Powi
*******************************************************************************/
HRESULT Powi( int x, int y )
{
	return ( int )( powf( ( float )x, ( float )y ) );
}
//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�̐���
	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * ( RANKINGSCORE_MAX * RANKING_MAX + 2 ) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRankingScore, NULL ) ) )
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffRankingScore -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	for( int nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++ )
	{
		for( int nCntRankingScore = 0; nCntRankingScore < RANKINGSCORE_MAX; nCntRankingScore++, pVtx+=4 )
		{
			g_posRankingScore[ nCntRankingScore ][ nCntRanking ] = D3DXVECTOR3( RANKINGSCORE_POSX + RANKINGSCORE_WIDTH * nCntRankingScore, RANKINGSCORE_POSY + RANKINGSCORE_HEIGHT * nCntRanking, 0.0f );

			//���_���W�̏�����
			pVtx[ 0 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x - RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 0 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y - RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 0 ].pos.z = 0.0f;

			pVtx[ 1 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x + RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 1 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y - RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 1 ].pos.z = 0.0f;

			pVtx[ 2 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x - RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 2 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y + RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 2 ].pos.z = 0.0f;

			pVtx[ 3 ].pos.x = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].x + RANKINGSCORE_WIDTH * 0.50f;
			pVtx[ 3 ].pos.y = g_posRankingScore[ nCntRankingScore ][ nCntRanking ].y + RANKINGSCORE_HEIGHT * 0.50f;
			pVtx[ 3 ].pos.z = 0.0f;

			//���_���W�̐ݒ�
			pVtx[ 0 ].pos = D3DXVECTOR3( pVtx[ 0 ].pos.x, pVtx[ 0 ].pos.y, pVtx[ 0 ].pos.z );
			pVtx[ 1 ].pos = D3DXVECTOR3( pVtx[ 1 ].pos.x, pVtx[ 1 ].pos.y, pVtx[ 1 ].pos.z );
			pVtx[ 2 ].pos = D3DXVECTOR3( pVtx[ 2 ].pos.x, pVtx[ 2 ].pos.y, pVtx[ 2 ].pos.z );
			pVtx[ 3 ].pos = D3DXVECTOR3( pVtx[ 3 ].pos.x, pVtx[ 3 ].pos.y, pVtx[ 3 ].pos.z );

			pVtx[ 0 ].rhw = 1.0f;
			pVtx[ 1 ].rhw = 1.0f;
			pVtx[ 2 ].rhw = 1.0f;
			pVtx[ 3 ].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[ 0 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 1 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 2 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
			pVtx[ 3 ].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

			//�e�N�X�`�����W�̐ݒ�
			pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
			pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
			pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
			pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );
		}
	}
	g_pVtxBuffRankingScore -> Unlock();

	return S_OK;
}