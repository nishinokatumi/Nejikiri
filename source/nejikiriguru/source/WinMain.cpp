#include "DxLib.h"
#include "GameMain.h"
#include "sceneSource/SceneGame.h"
#include "sceneSource/SceneSelect.h"
#include "sceneSource/SceneTitle.h"

/*
WinMain関数
ここがスタート
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ゲームメインクラスの作成
	GameMain gameMain;

	// ゲーム開始　中でゲームループを行う
	gameMain.Run();

	// Run関数を抜けてきたらゲーム終了
	return 0;
};