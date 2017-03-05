#include "main.h"
#include "field.h"
#include "input.h"
//�O���[�o���ϐ�
VERTEX_3D g_Field[4];
LPDIRECT3DTEXTURE9 g_pTextureField =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField =NULL;	//���_�p�b�t�@�ւ̃|�C���^

float g_fLengthField;		//�n�ʂ̑Ίp���̒���
float g_fAngleField;		//�n�ʂ̑Ίp���̊p�x

float g_aMove_Field;
float g_aRot_Field;
FIELD g_aField;
//=============================================================================
//  �֐����@�FInitField
//  �@�\�T�v�F�n�ʂ̏�����
//  �߂�l�@�FHRESULT
//=============================================================================
HRESULT InitField (void)
{
	g_aField.fHeight = 100.0f;		//�n�ʂ̍����̏�����
	g_aField.fWidth = 100.0f;		//�n�ʂ̕����̏�����
	g_aField.g_posField.x = 0.0f;		//�n�ʂ�X�̏�����
	g_aField.g_posField.y = 0.0f;		//�n�ʂ�Y�̏�����
	g_aField.g_posField.z = 0.0f;		//�n�ʂ�Z�̏�����

	g_aField.g_rotField.x = 0.0f;		//�n�ʂ�X�̉�]������
	g_aField.g_rotField.y = 0.0f;		//�n�ʂ�Y�̉�]������
	g_aField.g_rotField.z = 0.0f;		//�n�ʂ�Z�̉�]������

	g_aField.g_sclField.x = 1.0f;		//�n�ʂ�X�̃X�P�[��������
	g_aField.g_sclField.y = 1.0f;		//�n�ʂ�Y�̃X�P�[��������
	g_aField.g_sclField.z = 1.0f;		//�n�ʂ�Z�̃X�P�[��������

	g_aMove_Field = MOVE_FIELD;		//�n�ʂ̈ړ���
	g_aRot_Field = ROT_FIELD;		//��]�̈ړ���
	g_aField.g_posField = D3DXVECTOR3(g_aField.g_posField.x,g_aField.g_posField.y,g_aField.g_posField.z);
	g_aField.g_rotField = D3DXVECTOR3(g_aField.g_rotField.x,g_aField.g_rotField.y,g_aField.g_rotField.z);
	g_aField.g_sclField = D3DXVECTOR3(g_aField.g_sclField.x,g_aField.g_sclField.y,g_aField.g_sclField.z);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//����������
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*14,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffField,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;
	g_pVtxBuffField ->Lock(0,0,(void **)&pVtx,0);		//���_���ւ̃|�C���^���擾
	//�e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\zhi.png",
		&g_pTextureField);

	pVtx[0].pos = D3DXVECTOR3 (g_aField.g_posField.x - g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z);

	pVtx[1].pos = D3DXVECTOR3 (g_aField.g_posField.x - g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z + g_aField.fHeight/2);

	pVtx[2].pos = D3DXVECTOR3 (g_aField.g_posField.x,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z);

	pVtx[3].pos = D3DXVECTOR3 (g_aField.g_posField.x,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z + g_aField.fHeight/2);

	pVtx[4].pos = D3DXVECTOR3 (g_aField.g_posField.x+ g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z);

	pVtx[5].pos = D3DXVECTOR3 (g_aField.g_posField.x+ g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z+ g_aField.fHeight/2);

	pVtx[6].pos = D3DXVECTOR3 (g_aField.g_posField.x+ g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z+ g_aField.fHeight/2);

	pVtx[7].pos = D3DXVECTOR3 (g_aField.g_posField.x- g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z- g_aField.fHeight/2);

	pVtx[8].pos = D3DXVECTOR3 (g_aField.g_posField.x- g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z- g_aField.fHeight/2);

	pVtx[9].pos = D3DXVECTOR3 (g_aField.g_posField.x- g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z);

	pVtx[10].pos = D3DXVECTOR3 (g_aField.g_posField.x,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z-g_aField.fHeight/2);

	pVtx[11].pos = D3DXVECTOR3 (g_aField.g_posField.x,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z);

	pVtx[12].pos = D3DXVECTOR3 (g_aField.g_posField.x+ g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z-g_aField.fHeight/2);

	pVtx[13].pos = D3DXVECTOR3 (g_aField.g_posField.x+ g_aField.fWidth/2,
							   g_aField.g_posField.y,
							   g_aField.g_posField.z);
	//UV�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f );
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f );
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f );
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f );

	//���_�F�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//���_���i�[���[�N
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

	//�@��
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	g_pVtxBuffField ->Unlock();	//LOCK

	return S_OK;

}
//=============================================================================
//  �֐����@�FDrawField
//  �@�\�T�v�F�n�ʂ̕`�揈��
//  �߂�l�@�F
//=============================================================================
void DrawField (void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTrans;
	D3DXMatrixIdentity ( &g_aField.g_mtxWorldField);		//���[���h�}�g���b�N�X�̏�����

	D3DXMatrixScaling ( &mtxScl,g_aField.g_sclField.x,g_aField.g_sclField.y,g_aField.g_sclField.z);
	D3DXMatrixMultiply ( &g_aField.g_mtxWorldField, &g_aField.g_mtxWorldField, &mtxScl);		//�X�P�[���𔽉f

	D3DXMatrixRotationYawPitchRoll ( &mtxRot,g_aField.g_rotField.y,g_aField.g_rotField.x,g_aField.g_rotField.z);
	D3DXMatrixMultiply ( &g_aField.g_mtxWorldField, &g_aField.g_mtxWorldField, &mtxRot);		//��]�𔽉f

	D3DXMatrixTranslation ( &mtxTrans,g_aField.g_posField.y,g_aField.g_posField.y,g_aField.g_posField.z);
	D3DXMatrixMultiply ( &g_aField.g_mtxWorldField, &g_aField.g_mtxWorldField, &mtxTrans);		//�ʒu�𔽉f

	pDevice->SetTransform (D3DTS_WORLD, &g_aField.g_mtxWorldField);		//���[���h�}�g���b�N�X��ݒ�

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h����
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffField,
								0,
								sizeof(VERTEX_3D)
								);
	// ���_�F�t�H�[�}�b�g
	pDevice -> SetFVF ( FVF_VERTEX_3D );

	//�e�N�X�`���̐ݒ�
	pDevice -> SetTexture ( 0, g_pTextureField);

	// �t�F�[�h�̕`��ݒ���e
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
							  0,		// �ŏ��̒��_�̃C���f�b�N�X
							  2+10			// �`�悷��v���~�e�B�u��
							);
}
//=============================================================================
//  �֐����@�FUpdateField
//  �@�\�T�v�F�n�ʂ̍X�V����
//  �߂�l�@�F
//=============================================================================
void UpdateField(void)
{

}
//=============================================================================
//  �֐����@�FUninitField
//  �@�\�T�v�F�v���S���̏I������
//  �߂�l�@�F
//=============================================================================
void UninitField(void)
{
	if(g_pTextureField!=NULL)
	{
		g_pTextureField->Release();
		g_pTextureField=NULL;
	}
	if(g_pVtxBuffField!=NULL)
	{
		g_pVtxBuffField->Release();		//���_�o�b�t�@�̊J��
		g_pVtxBuffField=NULL;
	}
}
FIELD *GetFieldNum(void)
{
	return &g_aField;
}
