#ifndef _FIELD_H_
#define _FIELD_H_
//マクロ定義
#define MOVE_FIELD (7.0f)		//地面の移動量
#define ROT_FIELD (0.05f)		//回転の移動量
//地面の構造体
typedef struct
{
	D3DXVECTOR3 g_posField;
	D3DXVECTOR3 g_rotField;
	D3DXVECTOR3 g_sclField;		//スケール値
	D3DXMATRIX g_mtxWorldField;		//ワールドマトリックス
	float fWidth;		//幅
	float fHeight;		//高さ
} FIELD;
//プロトタイプ宣言
HRESULT InitField (void);
void UninitField (void);
void UpdateField (void);
void DrawField (void);
FIELD *GetFieldNum(void);
#endif