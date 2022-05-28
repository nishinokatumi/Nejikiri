#pragma once
#include "DxLib.h"
#include "GameSource/SettingSource/Gameinformation.h"
#include "GameSource/SettingSource/CSVHeader.h"
#include "GameSource/SettingSource/GameUI.h"
#include "GameSource/SettingSource/OperationManager.h"
#include "GameSource/SettingSource/SEManager.h"
#include "GameSource/SettingSource/UIDraw.h"
#include "GameSource/SettingSource/CheckHitKey.h"
#include "GameSource/SettingSource/AllResourceLoad.h"

/*
シーン基底クラス
*/
class SceneBase
{
public:
	SceneBase() {};														//	初期設定
	virtual ~SceneBase() {};											//	消す際の処理

	virtual void Initia() = 0;											//	シーンの初期処理
	virtual void Final() = 0;											//	シーンの最終処理
	virtual SceneBase* Update() = 0;									//	シーンの更新処理
	virtual void Draw() = 0;											//	シーンの表示処理

	bool*				pSceneGameExit = new bool;						//	ゲーム終了真偽値ポインタ生成
	UIDraw*				pSceneUI = new UIDraw;							//	UI用クラスポインタ作成
	GameData*			pSceneGameData = new GameData;					//	ゲームのセーブデータポインタ生成
	OperationManager*	pSceneOperation = new OperationManager;			//	操作管理クラスポインタ作成
	SEManager*			pSceneSE = new SEManager;						//	SEポインタ生成
	GameUI*				pSceneGameUI = new GameUI;						//	ゲームUIクラスポインタ生成
	DataLoadResource*	pSceneDataLoad = new DataLoadResource;			//	データ管理ポインタ生成
	int*				pSceneFont[FONT_SIZE::FontLength] = { new int };//	使用フォント

protected:
	bool InitiaBool = false;											//	初めの処理
	bool TransitionSet = true;											//	更新処理の再生(true)と停止(false)
	int	SceneTransition = 255;											//	画面遷移のフェードインフェードアウト0~255
};