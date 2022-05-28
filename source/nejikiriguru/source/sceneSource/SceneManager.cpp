#include "SceneManager.h"
#include "SceneBase.h"

/*
シーン管理クラス
シーンの切り替え処理を担う

*/

SceneManager::SceneManager(SceneBase* initScene)
{
	//	今のシーンは空に
	pNowScene = nullptr;

	//	次のシーンに最初のシーンを入れる
	pNextScene = initScene;

	// initSceneで受け取ったシーンを起動する
	SetNextScene();
}

void SceneManager::SetNextScene()
{
	//	アドレス渡し
	pNextScene->pSceneGameExit = &SceneManagerGameExit;
	pNextScene->pSceneOperation = &SceneManagerOperation;
	pNextScene->pSceneGameData = &SceneManagerGameData;
	pNextScene->pSceneUI = &SceneManagerUI;
	pNextScene->pSceneSE = &SceneManagerSE;
	pNextScene->pSceneGameUI = &SceneManagerGameUI;
	pNextScene->pSceneDataLoad = &SceneManagerDataLoad;
	for (int num = 0; num < FontLength; num++)
	{
		pNextScene->pSceneFont[num] = &SceneManagerDataLoad.FontSet[num];
	}

	//	遷移先シーンの初期化
	pNextScene->Initia();

	//	シーン切り替えを行う
	SwitchPhase = SwitchScene;
}

void SceneManager::Initia()
{
	//	ゲームのセーブデータ読み込み
	SceneManagerGameData.Load();

	//	初期化
	int uifghun = LoadGraph("resource/texture/UI32pix.png");
	SceneManagerDataLoad.Initia();

	//	音の管理初期化
	SceneManagerSE.SoundLoad(
		(float)SceneManagerGameData.GameSaveData.SaveSEVolume / 100.0f,
		(float)SceneManagerGameData.GameSaveData.SaveBGMVolume / 100.0f,
		(float)SceneManagerGameData.GameSaveData.SaveUIVolume / 100.0f);
	
	//	ゲームUIの初期化(UI用の画像渡す)
	SceneManagerGameUI.Initia(uifghun);

	//	フォントをすべて取得
	for (int fnum = 0; fnum < FontLength; fnum++)
	{
		SceneManagerUI.FontSet[fnum] = &SceneManagerDataLoad.FontSet[fnum];
	}

	//	UIの情報渡し
	SceneManagerGameUI.pGameUIDraw = &SceneManagerUI;

	//	ゲームパッドの初期設定(一番目のゲームパッドを使用)
	SceneManagerOperation.Initia(DX_INPUT_PAD1);

	//	解放済みステージを読み込む
	SceneManagerDataLoad.MaxStageNo = SceneManagerGameData.GameSaveData.ReleaseStage;

	//	画面を消す
	ClearDrawScreen();
}

void SceneManager::Update()
{
	//	全シーンで使うクラスの更新処理
	SceneManagerOperation.Update();

	//	シーン遷移のフェーズによって処理を切り替える
	switch (SwitchPhase)
	{
		//	実行中
	case PHASE::Run:

		//	現在のシーンの更新処理
		pNextScene = pNowScene->Update();

		//	次のシーンが今のシーンと違っていた場合
		if (pNextScene != pNowScene)
		{
			SetNextScene();
		}
		break;

		//	シーン切り替え
	case PHASE::SwitchScene:
		//	現在実行中のシーンの終了処理と解放を行う
		//	ゲーム開始直後は現在実行中のシーンが存在しないのでif()で囲っている
		if (pNowScene)
		{
			pNowScene->Final();
			delete pNowScene;
			pNowScene = nullptr;
		}

		//	遷移先シーンを現在実行中のシーンにする
		pNowScene = pNextScene;

		//	pNextSceneの所有権をpNowSceneに渡したので、pNextSceneはdeleteしない
		//	pNextSceneのポインタを消すに留める
		pNextScene = nullptr;

		//	フェーズ進行
		SwitchPhase = Run;
		break;
	}

	//	最終的な処理の後に毎回行う処理
	SceneManagerOperation.OldUpdate();
}

void SceneManager::Draw()
{
	//	フェーズ毎に描画するものを切り替える
	switch (SwitchPhase)
	{
	case PHASE::Run:
		if (pNowScene)
		{
			pNowScene->Draw();								//	今の画面の表示処理
		}
		break;
	}
}

void SceneManager::Final()
{
	//	解放済みステージを保存する
	SceneManagerGameData.SaveStageNo(SceneManagerDataLoad.MaxStageNo);

}