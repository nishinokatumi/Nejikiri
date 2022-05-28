#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneSelect.h"

/*
タイトルシーン
*/

//	初期設定
SceneTitle::SceneTitle()
{

}

//	初期処理
void SceneTitle::Initia()
{
}

//	最終処理
void SceneTitle::Final()
{
	pSceneSE->SoundFinal(SOUND_NAME::Wind);					//	音の停止(風の音BGM)
}

//	初期処理
SceneBase* SceneTitle::Update()
{
	// シーン内の計算処理
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
			//	画面がアクティブ時に
			if (GetWindowActiveFlag())
			{
				BaseUpdate();								//	基本的な更新処理
			}
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
void SceneTitle::BaseUpdate()
{
	//	最初だけ
	if (InitiaBool == false)
	{
		InitiaBool = true;
		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	音の再生(風の音BGM)
	}

	// Zキーが押されたらゲームシーンに遷移するCheckDownKey(KEY_INPUT_RETURN) || (pSceneGamePad->OneButton(XINPUT_BUTTON_B))
	if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
	{
		pSceneSE->SoundFinal(SOUND_NAME::Enter);			//	音の停止(決定)
		pSceneSE->SoundPlay(SOUND_NAME::Enter);				//	音の再生(決定)
		pNextSceneSave = new SceneSelect();					//	次のシーンを選択画面に
		TransitionSet = false;								//	次のシーンへ
	}
}

//	表示処理
void SceneTitle::Draw()
{
	// シーン内の描画処理を行う

	//	背景の描画
	DrawRotaGraph2(
		GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 64,		//	表示する座標
		WIN_PL_WIDTH / 4, WIN_PL_HEIGHT / 4,				//	画像の半分の位置
		3.5, 0,												//	3.5倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackGround], false, false);

	//	背景の描画
	DrawRotaGraph2(
		GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 200,		//	表示する座標
		96, 34,												//	画像の半分の位置
		4, 0,												//	4倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::TitlLogo], true, false);

	int Tin = 4;											//	ウィンドウの縁の幅
	int WindowBoxY = GAME_WIN_HEIGHT / 2 + 128;					//	ウィンドウの位置Y


	//	”B”で次へと表示
	pSceneUI->TextBoxWindowCenter(
		GAME_WIN_WIDTH / 2, WindowBoxY, 15,		//	座標と文字数
		GetColor(255, 255, 255), GetColor(0, 0, 0),			//	文字の色,ウィンドウの色
		(float)Tin, FONT_SIZE::PicUp, "　　\"　　　\"で次へ");	//	ウィンドウの縁の幅,文字の種類,テキスト

	//	ゲームパッドが有効時
	if (pSceneOperation->GamePadReady)
	{
		//	Bボタンの表示
		pSceneGameUI->Draw(GAME_WIN_WIDTH / 2 - 88, WindowBoxY, 3, UI_PARTS::Button);
		pSceneGameUI->Draw(GAME_WIN_WIDTH / 2 - 88, WindowBoxY, 3, UI_PARTS::B);
	}

	//	キーボード操作時
	else
	{
		//　EnterKeyを表示
		pSceneGameUI->Draw(GAME_WIN_WIDTH / 2 - 88, WindowBoxY, 2, UI_PARTS::EnterKey);
		pSceneUI->TextOutlLine(GAME_WIN_WIDTH / 2 - (88 - 18), WindowBoxY - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
	}

	//	現在のシーンへ
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