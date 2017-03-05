#ifndef _FIELD_H_
#define _FIELD_H_
//�}�N����`
#define MOVE_FIELD (7.0f)		//�n�ʂ̈ړ���
#define ROT_FIELD (0.05f)		//��]�̈ړ���
//�n�ʂ̍\����
typedef struct
{
	D3DXVECTOR3 g_posField;
	D3DXVECTOR3 g_rotField;
	D3DXVECTOR3 g_sclField;		//�X�P�[���l
	D3DXMATRIX g_mtxWorldField;		//���[���h�}�g���b�N�X
	float fWidth;		//��
	float fHeight;		//����
} FIELD;
//�v���g�^�C�v�錾
HRESULT InitField (void);
void UninitField (void);
void UpdateField (void);
void DrawField (void);
FIELD *GetFieldNum(void);
#endif