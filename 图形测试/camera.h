/*******************************************************************************
* �^�C�g���F �J�����֐�
* �t�@�C�����F camera.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/16
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/

#ifndef _CAMERA_H_
#define _CAMERA_H_
//�}�N����`
#define ANGLE_CAMERA (45.0f)		//���W�A��
#define ASPECT_CAMERA (SCREEN_WIDTH/SCREEN_HEIGHT)		//�A�X�y�N�g��
#define NEAR_Z (10.0f)		//NearZ�l
#define FAR_Z (10000000.0f)		//FarZ�l


//�J�����̍\����
typedef struct
{
	D3DXVECTOR3 posV;		//���_
	D3DXVECTOR3 posR;		//�����_
	D3DXVECTOR3 vecU;		//����ʃx�N�g��
	D3DXMATRIX mtxProjection;		//�v���W�F�N�V�����X�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X

	D3DXVECTOR3 rot;		//����
	float fDistance;		//����
	bool bRotate;	//true�Ȃ王�_�𒆐S�Afalse�Ȃ璍���_�𒆐S
	D3DXVECTOR3 RotCheck;		//check����
	float correction_x;
	float correction_z;
	int wait;
} CAMERA;
//�v���g�^�C�v�錾
void InitCamera (void);
void UninitCamera (void);
void UpdateCamera (void);
void SetCamera (void);
void Autorotation (void);
CAMERA GetCamera(void);
#endif