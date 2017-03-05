/*******************************************************************************
* タイトル： デバックの処理
* ファイル名： debugProc.h
* 作成者： AT12A244 46 LIHAOSHENG
* 作成日： 2015/11/30
*******************************************************************************/

/*******************************************************************************
* 更新履歴：
*******************************************************************************/
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_
//プロトタイプの宣言
HRESULT InitDebugProc(void);
void UninitDebugProc(void);
void DrawDebugProc(void);
void UpdateDebugProc(void);
void PrintDebugProc (char *fmt,...);
#endif