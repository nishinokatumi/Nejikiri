#pragma once
#include "SceneSource/GameSource/SettingSource/Gameinformation.h"

class SceneManager;

/*
ゲームの環境クラス
	DXLibでゲームを動かすための設定を行う
*/
class GameMain
{
private:
	SceneManager* GameMainSceneManager;						//	シーン管理クラス
public:
	static const int WinWidth = GAME_WIN_WIDTH;				//	ウィンドウの幅 Default 640
	static const int WinHeight = GAME_WIN_HEIGHT;			//	ウィンドウの高さ Default 480

	GameMain();												//	初期設定
	~GameMain();											//	ゲームを閉じる際の処理
	void Run();												//	ゲームを走らせる
};