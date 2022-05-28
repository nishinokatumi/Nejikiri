#pragma once
#include "SceneBase.h"
#include "GameSource/SettingSource/CSVHeader.h"

/*
シーンの管理クラス
	シーン遷移するための処理を行う
*/
class SceneManager
{
private:
	// シーン遷移のフェーズを列挙
	enum PHASE
	{
		Run = 0,											//	実行中
		SwitchScene,										//	シーン切り替え
	};

	//	変数
	PHASE				SwitchPhase;									//	シーン遷移のフェーズ
	SceneBase*			pNowScene;										//	現在のシーン
	SceneBase*			pNextScene;										//	遷移先のシーン
	GameData			SceneManagerGameData = GameData();				//	ゲームデータの読み込み
	OperationManager	SceneManagerOperation = OperationManager();		//	操作の管理クラス生成	
	SEManager			SceneManagerSE = SEManager();					//	SE管理生成
	UIDraw				SceneManagerUI = UIDraw();						//	UI用クラス生成
	GameUI				SceneManagerGameUI = GameUI();					//	gameUI用クラス生成
	DataLoadResource	SceneManagerDataLoad = DataLoadResource();		//	データ管理クラス生成
	int					SceneManagerFont[FONT_SIZE::FontLength] = { 0 };//	使用フォント

	// シーン遷移処理
	void SetNextScene();
public:
	bool				SceneManagerGameExit = false;					//	ゲーム終了真偽値

	SceneManager(SceneBase* InitScene);									//	初期設定


	//	シーン管理の処理
	void Initia();														//	初期処理
	void Update();														//	更新処理
	void Draw();														//	表示処理
	void Final();														//	最終処理
};