#include "GameMain.h"
#include "DxLib.h"
#include "sceneSource/SceneManager.h"
#include "sceneSource/SceneTitle.h"


/*
ゲームメインクラス
DXLibやシーン管理クラス等の初期化から後始末や、ゲームのメインループ
*/

GameMain::GameMain()
{
	// DXLib 前処理
	SetMainWindowText("ねじきり");							// ウィンドウタイトル
	SetAlwaysRunFlag(true);									// 非アクティブ時にも動作
	ChangeWindowMode(false);								// Window Mode
	SetGraphMode(GAME_WIN_WIDTH, GAME_WIN_HEIGHT, 32);		// ウィンドウサイズ

	// DXLib初期化
	DxLib_Init();

	// シーン管理クラス作成　タイトルシーンを起動
	GameMainSceneManager = new SceneManager(new SceneTitle());

	// バックスクリーンに描画する
	SetDrawScreen(DX_SCREEN_BACK);

}

//	ゲームを閉じる際の処理
GameMain::~GameMain()
{
	// newしたクラスをdelete
	delete GameMainSceneManager;

	//　シーンクラスを空にする
	GameMainSceneManager = nullptr;

	// DXLib 終了
	DxLib_End();
}

void GameMain::Run()
{
	//	FPS用に使用する時間
	int time = 0;
	
	// 初期化処理　SE等の常に使う物の読み込み
	GameMainSceneManager->Initia();

	// ゲームループ
	while (ProcessMessage() == 0)
	{
		//	FPS用の処理開始時間を取得
		time = GetTickCount();

		// ゲーム終了が呼ばれたら終了
		if ((GameMainSceneManager->SceneManagerGameExit))
		{
			break;
		}

		// 更新処理
		GameMainSceneManager->Update();

		// 描画する
		ClearDrawScreen();
		GameMainSceneManager->Draw();

		// 画面更新
		ScreenFlip();

		//	17超えるまで繰り返して60FPSに固定
		while (GetTickCount() - time < 15);
	}

	// 初期化処理　セーブ等
	GameMainSceneManager->Final();
}