#include "SceneGame.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneED.h"
/*
ゲームシーン
*/

//	初期設定
SceneGame::SceneGame()
{

}

//	初期処理
void SceneGame::Initia()
{
	//	ポインタ引継ぎ
	SceneGameManager.pGameManagerOperation = pSceneOperation;	//	ゲームパッドクラスを参照させる
	SceneGameManager.pGameManagerGameUI = pSceneGameUI;		//	ゲームUIクラスを参照させる
	SceneGameManager.pGameManagerSE = pSceneSE;				//	音の管理クラスを参照させる
	SceneGameManager.pGameManagerUI = pSceneUI;				//	表示UIクラスを参照させる
	SceneGameManager.pGameManagerDataLoad = pSceneDataLoad;	//	リソース管理クラスを参照させる

	//	文字の数だけ処理
	for (int Num = 0; Num < FONT_SIZE::FontLength; Num++)
	{
		//	文字データを参照させる
		SceneGameManager.pGameManagerFONT[Num] = &pSceneDataLoad->FontSet[Num];
		ScenePause.pPauseFont[Num] = &pSceneDataLoad->FontSet[Num];
	}

	//	背景画像を参照させる
	ScenePause.pPauseBackGrahandle = &pSceneDataLoad->GraphGame[GRAPH::BackGround];
	ScenePause.pPauseOperation = pSceneOperation;				//	ゲームパッドクラスを参照させる
	ScenePause.pPauseGameUI = pSceneGameUI;					//	ゲームUIクラスを参照させる
	ScenePause.pPauseSE = pSceneSE;							//	音の管理を参照させる
	ScenePause.pPauseUI = pSceneUI;							//	表示UIクラスを参照させる
	ScenePause.pPauseDataLoad = pSceneDataLoad;				//	画像管理クラスを参照させる
	ScenePause.pPauseGameData = pSceneGameData;				//	ゲームセーブデータを参照させる
	ScenePause.Initia();									//	ポーズ画面の初期処理

	SceneGameManager.Initia();								//	ゲームマネージャ初期処理
	NowStat = PlayGame;										//	プレイゲーム状態にする
}

//	最終処理
void SceneGame::Final()
{
	pSceneSE->SoundFinal(SOUND_NAME::Wind);					//	音の停止(風の音BGM)
}

//	更新処理
SceneBase* SceneGame::Update()
{
	//	計算処理を行う
	SceneBase* pNextScene = this;

	//	現在のシーンへ
	if (TransitionSet == true)
	{
		//	フェードイン
		if (SceneTransition > 0)
		{
			//	0を下回るまで繰り返す
			SceneTransition -= 10;
			if (SceneTransition < 0)
			{
				SceneTransition = 0;
			}
		}

		//	一般的な処理
		else
		{
			BaseUpdate();											//	更新処理の内容
		}

	}
	//	次のシーンへ
	else
	{
		//	フェードアウト
		if (SceneTransition < 255)
		{
			//	255を上回るまで繰り返す
			SceneTransition += 10;
			if (SceneTransition > 255)
			{
				SceneTransition = 255;
			}
		}
		//	次のシーンに遷移
		else
		{
			pNextScene = pNextSceneSave;
		}
	}

	return pNextScene;
}

//	更新処理の内容
void SceneGame::BaseUpdate()
{
	//	最初だけ
	if (InitiaBool == false)
	{
		InitiaBool = true;
		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	音の再生(風の音BGM)
	}

	//	スタートボタンが押されたらポーズメニューに遷移する
	if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectMenu))
	{
		//	ポーズ画面の時にゲーム画面に
		if (NowStat == PauseScene)
		{
			NowStat = PlayGame;								//	プレイゲーム状態にする
			SceneGameManager.GameStopTime = TimePause - TimeStart;	//	一時停止しても制限時間が減らないようにする

			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//	音の停止(ジャンプ)
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//	音の再生(ジャンプ)
		}
		//	ゲーム画面の時にポーズ画面に
		else {
			//	今の画面がプレイゲームの時
			if (NowStat == PlayGame)
			{
				ScenePause.SelectButton = 0;					//	ボタンの選択位置初期化
				TimeStart = GetTickCount();					//	始める時間の初期化

				//	効果音の停止(ループを防ぐ)
				pSceneSE->SoundFinal(SOUND_NAME::Jump);		//	音の停止(ジャンプ)
				pSceneSE->SoundFinal(SOUND_NAME::FootStep);	//	音の停止(歩く音)
				pSceneSE->SoundFinal(SOUND_NAME::Timelimit);//	音の停止(制限時間)

				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//	音の停止(決定)
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//	音の再生(決定)
			}
			NowStat = PauseScene;							//	一時停止状態にする
		}
	}

	//	画面が非アクティブ時に
	if (!(GetWindowActiveFlag()))
	{
		//	今の画面がプレイゲームの時
		if (NowStat == PlayGame)
		{
			ScenePause.SelectButton = 0;
			TimeStart = GetTickCount();

			//	効果音の停止(ループを防ぐ)
			pSceneSE->SoundFinal(SOUND_NAME::Jump);		//	音の停止(ジャンプ)
			pSceneSE->SoundFinal(SOUND_NAME::FootStep);	//	音の停止(ジャンプ)
			pSceneSE->SoundFinal(SOUND_NAME::Timelimit);//	音の停止(ジャンプ)

			pSceneSE->SoundFinal(SOUND_NAME::Enter);	//	音の停止(ジャンプ)
			pSceneSE->SoundPlay(SOUND_NAME::Enter);			//	音の停止(ジャンプ)
		}
		NowStat = PauseScene;								//	一時停止状態にする
	}

	//	今の画面がプレイゲームの時
	if (NowStat == PlayGame)
	{
		SceneGameManager.Update();							//	ゲームマネージャーの更新処理

		//	最後のステージをクリアしたら
		if (SceneGameManager.MAXStageClear())
		{
			pNextSceneSave = new SceneED();					//	ゲームエンディング画面へ
			TransitionSet = false;							//	次の画面へ
		}

	}

	//	ポーズ画面の時にゲーム画面に
	else if (NowStat == PauseScene)
	{
		TimePause = GetTickCount();							//	一時停止している現在時間の更新
		int Set = ScenePause.Update();						//	一時停止画面の更新処理

		//	一時停止画面から帰ってきた値が以下の値の時の処理
		switch (Set)
		{
		case 1: //　ゲームに戻る
			NowStat = PlayGame;								//	プレイゲーム状態にする
			SceneGameManager.GameStopTime = (TimePause - TimeStart);	//	ゲームを止めた時間を代入
			break;

		case 2: //　リトライ
			NowStat = PlayGame;								//	プレイゲーム状態にする
			SceneGameManager.ChangeStage(SceneGameManager.StageNo);		//	ゲームを止めた時間を代入
			break;

		case 3: //　設定画面

			ScenePause.OptionFlag = true;
			break;

		case 4: //　選択シーン
			pNextSceneSave = new SceneSelect();				//	選択画面へ
			TransitionSet = false;							//	次の画面へ
			break;

		default:
			break;
		}
	}
}

//	表示処理
void SceneGame::Draw()
{
	//	描画処理を行う

	//	今の画面がプレイゲームの時
	if (NowStat == PlayGame)
	{
		SceneGameManager.Draw();								//	ゲームマネージャーの表示処理
	}

	//	ポーズ画面の時にゲーム画面に
	else if (NowStat == PauseScene)
	{
		ScenePause.Draw();									//	一時停止画面の表示処理
	}

	//	現在の画面へ
	if (TransitionSet == true)
	{
		//	フェードイン
		if (SceneTransition > 0)
		{
			pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
				GetColor(0, 0, 0), SceneTransition);
		}

	}
	//	次のシーンへ
	else
	{
		//	フェードアウト
		pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
			GetColor(0, 0, 0), SceneTransition);
	}
}