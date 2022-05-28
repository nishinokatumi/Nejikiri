#pragma once
#pragma once
#include "SceneBase.h"
#include "GameSource/OptionSG.h"

#define SELECTBUTTON_X 3									//	ボタングループ
#define SELECTBUTTON_1Y 4									//	ボタンの横の数
#define SELECTBUTTON_2Y 27									//	ボタンの横の数
#define SELECTBUTTON_3Y 1									//	ボタンの横の数

/*
選択画面クラス
	ゲームのステージを選択する処理を行う
*/
class SceneSelect :public SceneBase
{
	enum BUTTON_L
	{
		StageSelect = 0,									//	ステージ選択
		Description,										//	操作説明
		Option,												//	設定
		GameExit,											//	ゲーム終了
	};
private:
	SceneBase* pNextSceneSave = this;						//	次のシーン保存用
	int BackGraph = 0;										//	背景画像ハンドル
	int TitleGraph = 0;										//	タイトル画像ハンドル
	int ColorBase = 0;										//	基本的な色(黒)
	int ColorMain = 0;										//	基本的な色(白)
	int ColorSelect = 0;									//	基本的な色(黄)
	UIButton ButtonUI[5] = { UIButton() };						//	選択シーンのボタン5つ
	const char* ButtonText[5] =								//	ボタンのテキスト
	{
		"StageSelect",
		"操作説明",
		"設定",
		"EXIT",
		"GameStart"
	};
	int MaxClearStageNo = 0;								//	クリアしているステージの最大値
	int SelectStageNo = 0;									//	選択しているステージの番号
	int ButtonReturn = 0;									//	ボタンの処理でシーン遷移する際の値
	int SelectButtonX = 0;									//	選択しているボタングループ
	int SelectButtonL = 0;									//	選択している左側のボタン

	//	選択画面の処理
	int SelectButton();										//	ボタンの選択処理
	void DrawButton();										//	ボタンの表示処理
	void DrawSelectStage();									//	ステージを選択の表示処理
	void DrawSelectUI();									//	説明用のUI

	OptionSG SelectOption;									//	設定画面
	bool OptionFlag = false;								//	設定画面かどうか

public:
	SceneSelect();											//	初期設定

	//	選択画面の処理
	void Initia();											//	初期処理
	SceneBase* Update();									//	更新処理
	void BaseUpdate();										//	更新処理の内容
	void Draw();											//	表示処理
	void Final();											//	最終処理

};