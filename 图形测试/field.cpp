#include "main.h"
#include "field.h"
#include "input.h"
//グローバル変数
VERTEX_3D g_Field[4];
LPDIRECT3DTEXTURE9 g_pTextureField =NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField =NULL;	//頂点パッファへのポインタ

float g_fLengthField;		//地面の対角線の長さ
float g_fAngleField;		//地面の対角線の角度

float g_aMove_Field;
float g_aRot_Field;
FIELD g_aField;
//=============================================================================
//  関数名　：InitField
//  機能概要：地面の初期化
//  戻り値　：HRESULT
//=============================================================================
HRESULT InitField (void)
{
	g_aField.fHeight = 100.0f;		//地面の高さの初期化
	g_aField.fWidth = 100.0f;		//地面の幅さの初期化
	g_aField.g_posField.x = 0.0f;		//地面のXの初期化
	g_aField.g_posField.y = 0.0f;		//地面のYの初期化
	g_aField.g_posField.z = 0.0f;		//地面のZの初期化

	g_aField.g_rotField.x = 0.0f;		//地面のXの回転初期化
	g_aField.g_rotField.y = 0.0f;		//地面のYの回転初期化
	g_aField.g_rotField.z = 0.0f;		//地面のZの回転初期化

	g_aField.g_sclField.x = 1.0f;		//地面のXのスケール初期化
	g_aField.g_sclField.y = 1.0f;		//地面のYのスケール初期化
	g_aField.g_sclField.z = 1.0f;		//地面のZのスケール初期化

	g_aMove_Field = MOVE_FIELD;		//地面の移動量
	g_aRot_Field = ROT_FIELD;		//回転の移動量
	g_aField.g_posField = D3DXVECTOR3(g_aField.g_posField.x,g_aField.g_posField.y,g_aField.g_posField.z);
	g_aField.g_rotField = D3DXVECTOR3(g_aField.g_rotField.x,g_aField.g_rotField.y,g_aField.g_rotField.z);
	g_aField.g_sclField = D3DXVECTOR3(g_aField.g_sclField.x,g_aField.g_sclField.y,g_aField.g_sclField.z);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//初期化処理
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*14,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffField,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;
	g_pVtxBuffField ->Lock(0,0,(void **)&pVtx,0);		//頂点情報へのポインタを取得
	//テクスチャの読み込み	
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
	//UV設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f );
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f );
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f );
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f );

	//頂点色設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 128);	//頂点情報格納ワーク
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 128);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 128);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 128);

	//法線
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	g_pVtxBuffField ->Unlock();	//LOCK

	return S_OK;

}
//=============================================================================
//  関数名　：DrawField
//  機能概要：地面の描画処理
//  戻り値　：
//=============================================================================
void DrawField (void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTrans;
	D3DXMatrixIdentity ( &g_aField.g_mtxWorldField);		//ワールドマトリックスの初期化

	D3DXMatrixScaling ( &mtxScl,g_aField.g_sclField.x,g_aField.g_sclField.y,g_aField.g_sclField.z);
	D3DXMatrixMultiply ( &g_aField.g_mtxWorldField, &g_aField.g_mtxWorldField, &mtxScl);		//スケールを反映

	D3DXMatrixRotationYawPitchRoll ( &mtxRot,g_aField.g_rotField.y,g_aField.g_rotField.x,g_aField.g_rotField.z);
	D3DXMatrixMultiply ( &g_aField.g_mtxWorldField, &g_aField.g_mtxWorldField, &mtxRot);		//回転を反映

	D3DXMatrixTranslation ( &mtxTrans,g_aField.g_posField.y,g_aField.g_posField.y,g_aField.g_posField.z);
	D3DXMatrixMultiply ( &g_aField.g_mtxWorldField, &g_aField.g_mtxWorldField, &mtxTrans);		//位置を反映

	pDevice->SetTransform (D3DTS_WORLD, &g_aField.g_mtxWorldField);		//ワールドマトリックスを設定

	// 頂点バッファをデータストリームにバインドする
	pDevice -> SetStreamSource(
								0,
								g_pVtxBuffField,
								0,
								sizeof(VERTEX_3D)
								);
	// 頂点色フォーマット
	pDevice -> SetFVF ( FVF_VERTEX_3D );

	//テクスチャの設定
	pDevice -> SetTexture ( 0, g_pTextureField);

	// フェードの描画設定内容
	pDevice -> DrawPrimitive(
							  D3DPT_TRIANGLESTRIP,		// プリミティブの種類
							  0,		// 最初の頂点のインデックス
							  2+10			// 描画するプリミティブ数
							);
}
//=============================================================================
//  関数名　：UpdateField
//  機能概要：地面の更新処理
//  戻り値　：
//=============================================================================
void UpdateField(void)
{

}
//=============================================================================
//  関数名　：UninitField
//  機能概要：プリゴンの終了処理
//  戻り値　：
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
		g_pVtxBuffField->Release();		//頂点バッファの開放
		g_pVtxBuffField=NULL;
	}
}
FIELD *GetFieldNum(void)
{
	return &g_aField;
}
