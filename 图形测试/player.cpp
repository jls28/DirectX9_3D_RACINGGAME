/*******************************************************************************
* �^�C�g���F �v���C���[�`��֐�
* �t�@�C�����F player.cpp
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2016/02/23
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
//2016/02/23 ���f���ǂݍ���
/*******************************************************************************
		�C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "camera.h"
#include "player.h"
#include "keyboard.h"
/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define	TEXTURE_MODEL_HEAD		"data\\MODEL\\model_head.x"	// �ǂݍ��ރ��f����

#define	TEXTURE_MODEL_ARM_L		"data\\MODEL\\model_arm_L.x"	// �ǂݍ��ރ��f����

#define	TEXTURE_MODEL_ARM_R		"data\\MODEL\\model_arm_R.x"	// �ǂݍ��ރ��f����

#define	TEXTURE_MODEL_BODY		"data\\MODEL\\model_body.x"	// �ǂݍ��ރ��f����

#define	TEXTURE_MODEL_LEG_L		"data\\MODEL\\model_leg_L.x"	// �ǂݍ��ރ��f����

#define	TEXTURE_MODEL_LEG_R		"data\\MODEL\\model_leg_R.x"	// �ǂݍ��ރ��f����

#define PLAYER_INERTIA_MOVE	( 0.025f )					//���������W��

#define POSMOVE_PLAYER	( 5.0f )		// �ړ���
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY );

//************************************************************************************************************************************************************************************************
// �O���[�o���ϐ�
//************************************************************************************************************************************************************************************************
PLAYER g_aPlayer[ MAX_PLAYER ];		// ���f���̏��
MODEL aModel[ MAX_MODEL ];
//================================================================================================================================================================================================
// InitPlayer�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
HRESULT InitPlayer( void )
{
	int nNumVertices;	// ���_��
	DWORD sizeFVF;		// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		// ���_���i���_���W�j�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	aModel[ 0 ].nIndexModelDarent = 0;
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_BODY,
								   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
								   pDevice,
								   NULL,
								   &aModel[ 0 ].pBuffMat,		// �}�e���A�����
								   NULL,
								   &aModel[ 0 ].nNumMat,			// �}�e���A����
								   &aModel[ 0 ].pMesh ) ) )		// ���b�V�����
	{
		return E_FAIL;
	}
	aModel[ 1 ].nIndexModelDarent = 1;
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_ARM_L,
								   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
								   pDevice,
								   NULL,
								   &aModel[ 1 ].pBuffMat,		// �}�e���A�����
								   NULL,
								   &aModel[ 1 ].nNumMat,			// �}�e���A����
								   &aModel[ 1 ].pMesh ) ) )		// ���b�V�����
	{
		return E_FAIL;
	}
	aModel[ 2 ].nIndexModelDarent = 2;
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_ARM_R,
								   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
								   pDevice,
								   NULL,
								   &aModel[ 2 ].pBuffMat,		// �}�e���A�����
								   NULL,
								   &aModel[ 2 ].nNumMat,			// �}�e���A����
								   &aModel[ 2 ].pMesh ) ) )		// ���b�V�����
	{
		return E_FAIL;
	}

	aModel[ 3 ].nIndexModelDarent = 3;
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_HEAD,
								   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
								   pDevice,
								   NULL,
								   &aModel[ 3 ].pBuffMat,		// �}�e���A�����
								   NULL,
								   &aModel[ 3 ].nNumMat,			// �}�e���A����
								   &aModel[ 3 ].pMesh ) ) )		// ���b�V�����
	{
		return E_FAIL;
	}

	aModel[ 4 ].nIndexModelDarent = 4;
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_LEG_L,
								   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
								   pDevice,
								   NULL,
								   &aModel[ 4 ].pBuffMat,		// �}�e���A�����
								   NULL,
								   &aModel[ 4 ].nNumMat,			// �}�e���A����
								   &aModel[ 4 ].pMesh ) ) )		// ���b�V�����
	{
		return E_FAIL;
	}
	aModel[ 5 ].nIndexModelDarent = 5;
	// X�t�@�C���̓ǂݍ���
	if( FAILED( D3DXLoadMeshFromX( TEXTURE_MODEL_LEG_R,
								   D3DXMESH_SYSTEMMEM,				// �m�ۂ���o�b�t�@�̃T�C�Y�i�o�C�g�P�ʁj�B�Q�[���ɂ���ĉ����_�Ȃ̂��ς��B����͎l�p������S�B
								   pDevice,
								   NULL,
								   &aModel[ 5 ].pBuffMat,		// �}�e���A�����
								   NULL,
								   &aModel[ 5 ].nNumMat,			// �}�e���A����
								   &aModel[ 5 ].pMesh ) ) )		// ���b�V�����
	{
		return E_FAIL;
	}

	for( int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++ )
	{
		// ���f���̏����ݒ�
		aModel[ nCntModel ].pos = D3DXVECTOR3( 0.0f,  0.0f, 50.0f );
		aModel[ nCntModel ].rot = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		aModel[ nCntModel ].scl = D3DXVECTOR3( 1.0f,  1.0f, 1.0f );
		aModel[ nCntModel ].Max = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		aModel[ nCntModel ].Min = D3DXVECTOR3( 0.0f,  0.0f, 0.0f );
		aModel[ nCntModel ].bUse = true;
		aModel[ nCntModel ].fPosMove = POSMOVE_PLAYER;
		g_aPlayer[0].aIndexParent[0] = 1;
		// �Փ˔���Ŏg�����߂̏���////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// x�t�@�C���̒��_�����擾����B
		nNumVertices = aModel[ nCntModel ].pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y���擾����B
		sizeFVF = D3DXGetFVFVertexSize( aModel[ nCntModel ].pMesh->GetFVF() );

		// �Փ˔���Ŏg�����߂ɁA����x�t�@�C���̒��ň�ԑ傫��x,y,z�̒l�ƁA��ԏ�����x,y,z�̒l���`�F�b�N����B
		aModel[ nCntModel ].pMesh->LockVertexBuffer( D3DLOCK_READONLY, ( void** )&pVtxBuff);
		for( int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++ )
		{
			// ���_�����擾����B
			D3DXVECTOR3 vtx = *( D3DXVECTOR3* )pVtxBuff;

			if( vtx.x < aModel[ nCntModel ].Min.x )		aModel[ nCntModel ].Min.x = vtx.x;		// x�̍ŏ��l�̍X�V
			if( vtx.x > aModel[ nCntModel ].Max.x )		aModel[ nCntModel ].Max.x = vtx.x;		// x�̍ő�l�̍X�V
			if( vtx.y < aModel[ nCntModel ].Min.y )		aModel[ nCntModel ].Min.y = vtx.y;		// y�̍ŏ��l�̍X�V
			if( vtx.y > aModel[ nCntModel ].Max.y )		aModel[ nCntModel ].Max.y = vtx.y;		// y�̍ő�l�̍X�V
			if( vtx.z < aModel[ nCntModel ].Min.z )		aModel[ nCntModel ].Min.z = vtx.z;		// z�̍ŏ��l�̍X�V
			if( vtx.z > aModel[ nCntModel ].Max.z )		aModel[ nCntModel ].Max.z = vtx.z;		// z�̍ő�l�̍X�V

			// ���̒��_�Ɉړ�����B
			pVtxBuff += sizeFVF;
		}
		aModel[ nCntModel ].pMesh->UnlockVertexBuffer();

		// ���f���̔��a�̐ݒ�B��Βl��abs�֐��ŋ��߂�B
		aModel[ nCntModel ].Size.x = ( fabs( aModel[ nCntModel ].Min.x ) + fabs( aModel[ nCntModel ].Max.x ) ) / 2;
		aModel[ nCntModel ].Size.y = ( fabs( aModel[ nCntModel ].Min.y ) + fabs( aModel[ nCntModel ].Max.y ) ) / 2;
		aModel[ nCntModel ].Size.z = ( fabs( aModel[ nCntModel ].Min.z ) + fabs( aModel[ nCntModel ].Max.z ) ) / 2;

		// �Փ˔���̒����̐ݒ�
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
// UninitPlayer�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UninitPlayer( void )
{
	for( int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++ )
	{
		// ���b�V�����̊J��
		if( aModel[ nCntModel ].pMesh != NULL )
		{
			aModel[ nCntModel ].pMesh->Release();
			aModel[ nCntModel ].pMesh = NULL;
		}

		// �o�b�t�@�̊J��
		if( aModel[ nCntModel ].pBuffMat != NULL )
		{
			aModel[ nCntModel ].pBuffMat->Release();
			aModel[ nCntModel ].pBuffMat = NULL;
		}
	}
}

//================================================================================================================================================================================================
// UpdatePlayer�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void UpdatePlayer( void )
{
	// �J�����̍��W�Ȃǎ擾����B
	CAMERA camera = GetCamera();
	//ModelBody�������ړ�
	PlayerMove(
			&camera.rot,	//����
			POSMOVE_PLAYER,				//�ړ���
			DIK_W,				//��{�^��
			DIK_S,			//���{�^��
			DIK_A,			//���{�^��
			DIK_D			//�E�{�^��
	);
}

//================================================================================================================================================================================================
// DrawPlayer�֐�
// ���� void
// �߂�l void
// ���� 
//================================================================================================================================================================================================
void DrawPlayer( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTrans;
	D3DXMATERIAL *pMat;		// �}�e���A�����
	D3DMATERIAL9 matDef;	// �f�t�H���g�̃}�e���A���B���̃}�e���A���̏���ޔ������邽�߂̕ϐ��B

	// ���݂̃}�e���A�������擾����B
	pDevice->GetMaterial( &matDef );

	for( int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++ )
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_aPlayer[ nCntPlayer ].mtxWorld );

		// �X�P�[���𔽉f
		D3DXMatrixScaling( &mtxScl, g_aPlayer[ nCntPlayer ].scl.x, g_aPlayer[ nCntPlayer ].scl.y, g_aPlayer[ nCntPlayer ].scl.z );
		D3DXMatrixMultiply( &g_aPlayer[ nCntPlayer ].mtxWorld, &g_aPlayer[ nCntPlayer ].mtxWorld, &mtxScl );

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll( &mtxRot, g_aPlayer[ nCntPlayer ].rot.y, g_aPlayer[ nCntPlayer ].rot.x, g_aPlayer[ nCntPlayer ].rot.z );	// y,x,z
		D3DXMatrixMultiply( &g_aPlayer[ nCntPlayer ].mtxWorld, &g_aPlayer[ nCntPlayer ].mtxWorld, &mtxRot );

		// �ʒu�𔽉f
		D3DXMatrixTranslation( &mtxTrans, g_aPlayer[ nCntPlayer ].pos.x, g_aPlayer[ nCntPlayer ].pos.y, g_aPlayer[ nCntPlayer ].pos.z );
		D3DXMatrixMultiply( &g_aPlayer[ nCntPlayer ].mtxWorld, &g_aPlayer[ nCntPlayer ].mtxWorld, &mtxTrans );

		// ���[���h�}�g���b�N�X��ݒ�
		pDevice->SetTransform( D3DTS_WORLD, &g_aPlayer[ nCntPlayer ].mtxWorld );

		for (int nCntParts = 0; nCntParts < MAX_PARTS ;nCntParts ++)
		{
			for( int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++ )
			{
				// ���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity( &aModel[ nCntModel ].mtxWorld );

				// �X�P�[���𔽉f
				D3DXMatrixScaling( &mtxScl, aModel[ nCntModel ].scl.x, aModel[ nCntModel ].scl.y, aModel[ nCntModel ].scl.z );
				D3DXMatrixMultiply( &aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld, &mtxScl );

				// ��]�𔽉f
				D3DXMatrixRotationYawPitchRoll( &mtxRot, aModel[ nCntModel ].rot.y, aModel[ nCntModel ].rot.x, aModel[ nCntModel ].rot.z );	// y,x,z
				D3DXMatrixMultiply( &aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld, &mtxRot );

				// �ʒu�𔽉f
				D3DXMatrixTranslation( &mtxTrans, aModel[ nCntModel ].pos.x, aModel[ nCntModel ].pos.y, aModel[ nCntModel ].pos.z );
				D3DXMatrixMultiply( &aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld, &mtxTrans );

				D3DXMatrixMultiply ( &aModel[ nCntModel ].mtxWorld,&aModel[ nCntModel ].mtxWorld, &aModel[ nCntModel ].mtxWorld/*�e���f���̃��[���h�}�g���b�N�X*/ );

				// ���[���h�}�g���b�N�X��ݒ�
				pDevice->SetTransform( D3DTS_WORLD, &aModel[ nCntModel ].mtxWorld );

				// �L���X�g�ϊ�
				pMat = ( D3DXMATERIAL* )aModel[ nCntModel ].pBuffMat->GetBufferPointer();

				for( int nCntMat = 0; nCntMat < ( int )aModel[ nCntModel ].nNumMat; nCntMat++ )
				{
					// �}�e���A���̐ݒ�
					pDevice->SetMaterial( &pMat[ nCntMat ].MatD3D );

					// �e�N�X�`���̐ݒ�
					pDevice->SetTexture( 0, NULL );		// �e�N�X�`����\��Ȃ�
						
					// ���b�V���̕`��
					aModel[ nCntModel ].pMesh->DrawSubset( nCntMat );
				}
			}
		}
	}
	// �}�e���A���������ɖ߂��B�߂��Ȃ��Ǝ��ɕ`�悳���}�e���A�������������Ȃ�B�ԐF�̂܂܁A�Ƃ��B
	pDevice->SetMaterial( &matDef );
}
//================================================================================================================================================================================================
// *GetPlayer�֐�
// ���� void
// �߂�l 
// ���� Player���擾����B
//================================================================================================================================================================================================
PLAYER *GetPlayer( void )
{
	return &g_aPlayer[ 0 ];
}

//================================================================================================================================================================================================
// *GetModel�֐�
// ���� void
// �߂�l 
// ���� Model���擾����B
//================================================================================================================================================================================================
MODEL *GetModel( void )
{
	return &aModel[ 0 ];
}
/*******************************************************************************
* �֐���: �������ړ��֐�
* 
* ����  : D3DXVECTOR3	*pos		//�ʒu
		  D3DXVECTOR3	*rot		//����
		  float			fPosmove	//�ړ���
		  int			UP			//��{�^��
		  int			DOWN			//���{�^��
		  int			LEFT		//���{�^��
		  int			RIGHT		//�E�{�^��
* �߂�l: �i�V
* ����: �i�V
*******************************************************************************/
void PlayerMove( D3DXVECTOR3 *pRot, float fPosMove, int UP_KEY, int DOWN_KEY, int LEFT_KEY, int RIGHT_KEY )
{
	PLAYER *pPlayer = GetPlayer();
	pPlayer -> fPosMove = fPosMove;
	CAMERA pCamera = GetCamera();
	if( GetKeyboardPress( UP_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//����ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E��ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y - D3DX_PI * 0.75f;
		}
		else											//�O�ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}
	else if( GetKeyboardPress( DOWN_KEY ) )
	{
		if( GetKeyboardPress( LEFT_KEY ) )				//�����ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else if( ( GetKeyboardPress( RIGHT_KEY ) ) )	//�E���ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y - D3DX_PI * 0.25f;
		}
		else											//��ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + 0.0f;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}
	else if( GetKeyboardPress( LEFT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//����ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�����ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.25f;
		}
		else											//���ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y + D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y + D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + D3DX_PI * 0.5f;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}
	else if( GetKeyboardPress( RIGHT_KEY ) )
	{
		if( GetKeyboardPress( UP_KEY ) )				//�E��ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.75f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.75f;
		}
		else if( ( GetKeyboardPress( DOWN_KEY ) ) )		//�E���ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.25f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.25f;
		}
		else											//�E�ړ�
		{
			pPlayer -> OldPos.x		-= sinf( pRot -> y - D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldPos.z		-= cosf( pRot -> y - D3DX_PI * 0.5f ) * pPlayer -> fPosMove;
			pPlayer -> OldRot.y	 = pRot -> y + -D3DX_PI * 0.5f;
		}
		pPlayer -> rot.y			 = pPlayer ->OldRot.y;
	}

	//���W���X�V�i�����j
	pPlayer -> pos.x += ( pPlayer->OldPos.x - pPlayer -> pos.x ) * PLAYER_INERTIA_MOVE;
	pPlayer -> pos.z += ( pPlayer->OldPos.z - pPlayer -> pos.z ) * PLAYER_INERTIA_MOVE;
}