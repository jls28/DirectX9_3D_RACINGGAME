#ifndef _LIGHT_H_
#define _LIGHT_H_

//インクルードファイル

//マクロ定義

//構造体
typedef struct
{
	D3DXCOLOR	diffuse;
	D3DXVECTOR3	vecDir;
}LIGHT;


//プロトタイプの宣言
void	InitLight();
void	UninitLight();
void	UpdateLight();
void	DrawLight();
#endif