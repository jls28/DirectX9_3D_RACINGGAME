#include "main.h"

#include "light.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
#define LIGHT_MAX ( 4 )

/*******************************************************************************
* �O���[�o���ϐ�
********************************************************************************/
D3DLIGHT9	g_aLight[ LIGHT_MAX ];		//���C�g���
LIGHT		g_Light[ LIGHT_MAX ];		//���̕����ƌ��̋����̍\����

/*******************************************************************************
* �֐���: ���C�g�̏������֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void InitLight( void )
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXVECTOR3 vecDir[ LIGHT_MAX ];

	g_Light[ 0 ].diffuse	= D3DXCOLOR( 0.8f, 0.8f, 0.8f, 1.0f );
	g_Light[ 1 ].diffuse	= D3DXCOLOR( 0.75f, 0.75f, 0.75f, 1.0f );
	g_Light[ 2 ].diffuse	= D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f );
	g_Light[ 3 ].diffuse	= D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	g_Light[ 0 ].vecDir		= D3DXVECTOR3( 2.0f, -1.0f, -1.0f );
	g_Light[ 1 ].vecDir		= D3DXVECTOR3( -1.0f, -1.0f, 1.0f );
	g_Light[ 2 ].vecDir		= D3DXVECTOR3( 0.0f, -1.0f, -2.0f );
	g_Light[ 3 ].vecDir		= D3DXVECTOR3( 1.0f, 400.0f, -2.0f );

	for( int nCntLight = 0; nCntLight < LIGHT_MAX; nCntLight++ )
	{
		ZeroMemory( &g_aLight[ nCntLight ],sizeof( D3DLIGHT9 ) );

		//���s����
		g_aLight[ nCntLight ].Type		= D3DLIGHT_DIRECTIONAL;

		//�g�U��
		g_aLight[ nCntLight ].Diffuse	= g_Light[ nCntLight ].diffuse;

		//���̕���
		vecDir[ nCntLight ]				= g_Light[ nCntLight ].vecDir;

		//���K��
		D3DXVec3Normalize( ( D3DXVECTOR3 * ) &g_aLight[ nCntLight ].Direction, &vecDir[ nCntLight ] );

		//���C�g�̐ݒ�
		pDevice -> SetLight( nCntLight, &g_aLight[ nCntLight ] );

		//���C�g��L������
		pDevice -> LightEnable( nCntLight, TRUE );
	}
}

/*******************************************************************************
* �֐���: ���C�g�̏I���֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UninitLight( void )
{
}

/*******************************************************************************
* �֐���: ���C�g�̍X�V�֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void UpdateLight( void )
{
}

/*******************************************************************************
* �֐���: ���C�g�̕`��֐�
* 
* ����  : �i�V
* �߂�l: �i�V
* ����  : �i�V
*******************************************************************************/
void DrawLight( void )
{
}