#ifndef _LIGHT_H_
#define _LIGHT_H_

//�C���N���[�h�t�@�C��

//�}�N����`

//�\����
typedef struct
{
	D3DXCOLOR	diffuse;
	D3DXVECTOR3	vecDir;
}LIGHT;


//�v���g�^�C�v�̐錾
void	InitLight();
void	UninitLight();
void	UpdateLight();
void	DrawLight();
#endif