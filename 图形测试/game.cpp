#include "main.h"
#include "game.h"
#include "input.h"
#include "mouse.h"
#include "keyboard.h"
#include "joystick.h"
#include "cursor.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "debugProc.h"
#include "bullet.h"
#include "time.h"
#include "prop.h"
#include "propshow.h"
#include "propmodel_Group.h"
#include "fade.h"
#include "propmp.h"
#include "propmplife.h"
#include "propmpmax.h"
#include "enemy.h"
#include "propexplosion.h"
#include "modelbody.h"
#include "modelhandL.h"
#include "modelhandR.h"
#include "modelLegL.h"
#include "modelLegR.h"
#include "modelarmL.h"
#include "modelarmR.h"
#include "runleg.h"
#include "obstacle.h"
#include "building_Left.h"
#include "building_Right.h"
#include "money.h"
#include "score.h"
#include "sky.h"
#include "timebg.h"
#include "shop.h"
#include "countdown.h"
#include "boxscore.h"
#include "sound.h"
#include "player.h"
#include "pause.h"
//=============================================================================
//  関数名　：InitGame
//  機能概要：プリゴンの初期化
//  戻り値　：HRESULT
//=============================================================================
void InitGame (void)
{
	PlaySound(SOUND_LABEL_BGM001);
	StopSound(SOUND_LABEL_BGM000);
	//InitSky();
	InitMeshField();
	InitMeshWall();
	//InitPlayer();
	//InitModel();
	InitModelBody();
	//InitModelHandL();
	//InitModelHandR();
	//InitModelLegL();
	//InitModelLegR();
	//InitModelarmL();
	//InitModelarmR();
	//InitRunLeg();
	//InitEnemy();
	InitObstacle();
	InitBuilding_Left();
	InitBuilding_Right();
	InitTime();
	InitBullet();
	InitShadow();
	InitExplosion();
	// エフェクの初期化
	InitEffect();
	InitProp();
	InitMoney();
	InitProw();
	InitPropModel_Group();
	InitPropMp();
	InitPropMpLife();
	InitPropMpMax();
	InitScore();
	InitTimebg();
	InitShop();
	InitCountdown();
	InitPause();
	//InitBoxScore01();
}
//=============================================================================
//  関数名　：UninitGame
//  機能概要：プリゴンの終了処理
//  戻り値　：
//=============================================================================
void UninitGame(void)
{
	//UninitSky();
	UninitMeshField();
	UninitMeshWall();
	//UninitPlayer();
	//UninitModel();
	UninitModelBody();
	//UninitModelHandL();
	//UninitModelHandR();
	//UninitModelLegL();
	//UninitModelLegR();
	//UninitModelarmL();
	//UninitModelarmR();
	//UninitRunLeg();
	//UninitEnemy();
	UninitObstacle();
	UninitBuilding_Left();
	UninitBuilding_Right();
	UninitTime();
	UninitShadow();
	//入力処理の終了処理
	UninitInput();
	UninitExplosion();
	// エフェクトの終了処理
	UninitEffect();
	UninitBullet();
	UninitProp();
	UninitMoney();
	UninitProw();
	UninitPropModel_Group();
	UninitPropMp();
	UninitPropMpLife();
	UninitPropMpMax();
	UninitScore();
	UninitTimebg();
	UninitShop();
	UninitCountdown();
	UninitPause();
	//UninitBoxScore01();
}
//=============================================================================
//  関数名　：DrawGame
//  機能概要：プリゴンの描画処理
//  戻り値　：
//=============================================================================
void DrawGame(void)
{
	//DrawSky();
	DrawMeshField();
	DrawMeshWall();
	//DrawPlayer();
	//DrawModel();
	DrawModelBody();
	//DrawModelHandL();
	//DrawModelHandR();
	//DrawModelLegL();
	//DrawModelLegR();
	//DrawModelarmL();
	//DrawModelarmR();
//	DrawRunLeg();
	//DrawEnemy();
	DrawObstacle();
	DrawBuilding_Left();
	DrawBuilding_Right();
	//カーソル処理の描画
	DrawCursor();
	DrawTime();
	DrawShadow();
	DrawExplosion();
	DrawBullet();
	// エフェクト処理の描画
	DrawEffect();
	DrawProp();
	DrawMoney();
	DrawProw();
	DrawPropModel_Group();
	DrawPropMpMax();
	DrawPropMpLife();
	DrawPropMp();
	DrawScore();
	DrawTimebg();
	DrawShop();
	DrawCountdown();
	DrawPause();
	//DrawBoxScore01();
}
//=============================================================================
//  関数名　：UpdateGame
//  機能概要：プリゴンの更新処理
//  戻り値　：
//=============================================================================
void UpdateGame(void)
{
	PAUSECHECK *pPauseCheck = GetPauseCheck();
	MODE mode;
	mode = GetMode();
	if( GetKeyboardTrigger( DIK_P ) && pPauseCheck->bPauseUse == false)
	{
		pPauseCheck->bPauseUse = true;
	}

	if(pPauseCheck->bPauseUse == false)
	{
	//UpdateSky();
	//UpdateBullet();
	//UpdatePlayer();
	UpdateModelBody();
	//UpdateModelHandL();
	//UpdateModelHandR();
	//UpdateModelLegL();
	//UpdateModelLegR();
	//UpdateModelarmL();
	//UpdateModelarmR();
	//UpdateRunLeg();
	//UpdateModel();
	//UpdateEnemy();
	UpdateObstacle();
	UpdateBuilding_Left();
	UpdateBuilding_Right();
	UpdateLight();
	UpdateMeshField();
	UpdateMeshWall();
	UpdateTime();
	UpdateExplosion();
	// エフェクト処理の更新
	UpdateEffect();
	//UpdateProp();
	UpdateMoney();
	UpdateProw();
	UpdatePropModel_Group();
	UpdatePropMp();
	UpdatePropMpLife();
	UpdatePropMpMax();
	UpdateScore();
	UpdateTimebg();
	UpdateShop();
	UpdateCountdown();

	//UpdateBoxScore01();
	}
	UpdatePause();
	//if(GetKeyboardTrigger(DIK_RETURN) == true)
	//{
	//	SetFade(FADE_OUT,MODE_RANKING);
	//}
}