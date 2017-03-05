//=============================================================================
//
// エフェクトの処理 [effect.h]
//
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
//*************************************
// エフェクトの種類
//*************************************
enum
{
	EFFECTTYPE_NORMAL = 0,			// 通常エフェクト
	EFFECTTYPE_RANDOMCOLOR,			// ランダムカラーエフェクト
	EFFECTYPE_COLOR,
	EFFECTTYPE_MAX
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife, int nType);

#endif
