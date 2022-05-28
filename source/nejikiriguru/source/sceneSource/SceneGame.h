#pragma once
#include "SceneBase.h"
#include "GameSource/GameManager.h"
#include "GameSource/PauseSG.h"

/*
ゲーム画面クラス
	ゲーム画面や一時停止画面の処理と表示を行う
*/

//	ゲームの状態
enum SCENE_GAME_STAT
{
	PlayGame = 0,											//	プレイゲーム
	PauseScene,												//	一時停止
	OptionScene,
};

class SceneGame : public SceneBase
{
private:
	//	変数
	SceneBase* pNextSceneSave = this;						//	次のシーン保存用
	GameManager SceneGameManager = GameManager();			//	ゲームマネージャークラス
	PauseSG	ScenePause = PauseSG();							//	一時停止クラス
	int TimeStart = 0;										//	始めの時間
	int TimePause = 0;										//	一時停止した時間

public:
	SceneGame();											//	初期設定

	//	ゲーム画面の処理
	void Initia();											//	初期処理
	void Final();											//	最終処理
	SceneBase* Update();									//	更新処理
	void BaseUpdate();										//	更新処理の内容
	void Draw();											//	表示処理

	int NowStat = 0;										//	現在の状態(一時停止かゲームプレイか)
	int SeleStage = 0;										//	選択しているステージ
};