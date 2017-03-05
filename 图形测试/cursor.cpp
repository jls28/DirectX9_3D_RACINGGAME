/*------------------------------------------------------------------------------
|	�^�C�g���F		�J�[�\���̏���
|	�t�@�C�����F	cursor.cpp
|	�쐬�ҁF		AT12A244 46 LI HAOSHENG
|	�쐬���F		2016/01/24
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�X�V����:
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
|	�C���N���[�h�t�@�C��
------------------------------------------------------------------------------*/
#include "main.h"
#include "input.h"

#include "cursor.h"

/*------------------------------------------------------------------------------
|	�}�N����`
------------------------------------------------------------------------------*/
#define	CURSOR_TEXTURE_FILE	"data\\TEXTURE\\cursor000.png"	//�J�[�\���̃e�N�X�`���t�@�C���ʒu

/*------------------------------------------------------------------------------
|	�O���[�o���ϐ�
------------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9			g_pTextureCursor = NULL;		//�e�N�X�`���|���S���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffCursor = NULL;		//���_�o�b�t�@�ւ̃|�C���^
CURSOR						g_Cursor;						//�J�[�\���̃��[�N

/*------------------------------------------------------------------------------
|	�v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT	MakeVertexCursor( LPDIRECT3DDEVICE9 pDevice );
void SetVertexCursor( void );

/*------------------------------------------------------------------------------
|	����������
------------------------------------------------------------------------------*/
HRESULT InitCursor( void )
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�J�[�\���\���̂̏�����
	g_Cursor.bUse = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
								pDevice,
								CURSOR_TEXTURE_FILE,	//�e�N�X�`���t�@�C���ʒu
								&g_pTextureCursor		//�e�N�X�`���o�b�t�@�ւ̃|�C���^
	);

	//���_���̍쐬
	MakeVertexCursor( pDevice );

	return S_OK;
}

/*------------------------------------------------------------------------------
|	�I������
------------------------------------------------------------------------------*/
void UninitCursor( void )
{
	// ���b�V�����̊J��
		if( g_pTextureCursor != NULL )
		{
			g_pTextureCursor->Release();
			g_pTextureCursor = NULL;
		}

		// �o�b�t�@�̊J��
		if( g_pVtxBuffCursor != NULL )
		{
			g_pVtxBuffCursor->Release();
			g_pVtxBuffCursor = NULL;
		}
}

/*------------------------------------------------------------------------------
|	�`�揈��
------------------------------------------------------------------------------*/
void DrawCursor( void )
{
	//�f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource( 0, g_pVtxBuffCursor, 0, sizeof( VERTEX_2D ) );

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	// �����_�[�X�e�[�g�̐ݒ�iz�e�X�g�j
	pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	pDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL );
	pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );		//z�l�̍X�V

	// �����_�[�X�e�[�g�̐ݒ�i�A���t�@�e�X�g�j
	pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );				// �A���t�@�l�𔻒肵�āA�Y���̃s�N�Z����`�悷��悤�ɂ���B
	pDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATER );			// ���̒l���A���t�@�l���傫����Ε`�悷��B
	pDevice->SetRenderState( D3DRS_ALPHAREF, 200 );						// �A���t�@�l�B0�œ����ȕ����B

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture( 0, g_pTextureCursor );

	if( g_Cursor.bUse == true )
	{//�J�[�\���g�p���Ȃ�
		//�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON );
	}
}

/*------------------------------------------------------------------------------
|	���_�o�b�t�@���쐬
------------------------------------------------------------------------------*/
HRESULT MakeVertexCursor( LPDIRECT3DDEVICE9 pDevice )
{
	//���_�o�b�t�@�̐���
	if( FAILED ( pDevice -> CreateVertexBuffer
	(
		sizeof( VERTEX_2D ) * 4,	//���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,						//�g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					//���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pVtxBuffCursor,					//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL								//NULL�ɐݒ�
	) ) )
	{
		return E_FAIL;
	}

//���_�o�b�t�@�̒��g�𖄂߂�
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffCursor -> Lock( 0, 0, ( void** ) &pVtx, 0 );

	//���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( - CURSOR_WIDTH / 2, - CURSOR_HEIGHT / 2, 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3(   CURSOR_WIDTH / 2, - CURSOR_HEIGHT / 2, 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( - CURSOR_WIDTH / 2,   CURSOR_HEIGHT / 2, 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3(   CURSOR_WIDTH / 2,   CURSOR_HEIGHT / 2, 0.0f );

	//rhw�̐ݒ�
	pVtx[ 0 ].rhw =
	pVtx[ 1 ].rhw =
	pVtx[ 2 ].rhw =
	pVtx[ 3 ].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[ 0 ].col =
	pVtx[ 1 ].col =
	pVtx[ 2 ].col =
	pVtx[ 3 ].col = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	//�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

	//���_�f�[�^���A�����b�N����
	g_pVtxBuffCursor -> Unlock();

	return S_OK;
}

/*------------------------------------------------------------------------------
|	���_���W�ݒ�
------------------------------------------------------------------------------*/
void SetVertexCursor( void )
{
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffCursor -> Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3( g_Cursor.x - CURSOR_WIDTH * 0.5f, g_Cursor.y - CURSOR_HEIGHT * 0.5f, 0.0f );
	pVtx[1].pos = D3DXVECTOR3( g_Cursor.x + CURSOR_WIDTH * 0.5f, g_Cursor.y - CURSOR_HEIGHT * 0.5f, 0.0f );
	pVtx[2].pos = D3DXVECTOR3( g_Cursor.x - CURSOR_WIDTH * 0.5f, g_Cursor.y + CURSOR_HEIGHT * 0.5f, 0.0f );
	pVtx[3].pos = D3DXVECTOR3( g_Cursor.x + CURSOR_WIDTH * 0.5f, g_Cursor.y + CURSOR_HEIGHT * 0.5f, 0.0f );

	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffCursor -> Unlock();
}

/*------------------------------------------------------------------------------
|	�J�[�\���ݒ�
------------------------------------------------------------------------------*/
void SetCursor( int x, int y )
{
	CURSOR *pCursor = &g_Cursor;
	if( pCursor -> bUse == true )
	{
		//�ʒu��ݒ�
		pCursor -> x = x;
		pCursor -> y = y;
		SetVertexCursor();
	}
}
