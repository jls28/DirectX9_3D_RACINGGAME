/*******************************************************************************
* �^�C�g���F �f�o�b�N�̏���
* �t�@�C�����F debugProc.h
* �쐬�ҁF AT12A244 46 LIHAOSHENG
* �쐬���F 2015/11/30
*******************************************************************************/

/*******************************************************************************
* �X�V�����F
*******************************************************************************/
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_
//�v���g�^�C�v�̐錾
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void DrawDebugProc(void);
void UpdateDebugProc(void);
void PrintDebugProc (char *fmt,...);
#endif