#pragma once
#include "DxLib.h"
#include "SettingSource/Gameinformation.h"
#include "SettingSource/UIDraw.h"
#include "SettingSource/GameUI.h"
#include "SettingSource/SEManager.h"
#include "OptionSG.h"

/*
一時停止クラス
	ゲームを一時停止しボタンに設定された処理を実行
*/
class PauseSG
{
	//	一時停止画面のボタンの種類
	enum PAUSEBUTTON
	{
		Back = 0,										//	ゲームに戻る
		Retry,											//	リトライする
		Option,											//	設定画面へ
		Select,											//	選択画面へ
		PauseLength										//	総数
	};
private:

	//	変数
	UIButton PauseButton[PauseLength + 1] = { UIButton() };	//	ボタン
	OptionSG PauseOption;

	void SelectButtonDraw(								//	選択ボタンの表示
		int FontNo, const char* PText);
public:

	//	変数
	int* pPauseFont[FONT_SIZE::FontLength];				//	使用フォント
	int* pPauseBackGrahandle;							//	背景画像ハンドル
	int* pPauseGrahandle;								//	タイトル画像ハンドル
	DataLoadResource*	pPauseDataLoad;					//	画像リソースポインタ
	GameUI*				pPauseGameUI;					//	ゲームパッドのUI表示
	OperationManager*	pPauseOperation;				//	ゲームパッドクラスポインタ
	GameData*			pPauseGameData;					//	ゲームセーブデータポインタ
	UIDraw*				pPauseUI;						//	UIの表示
	SEManager*			pPauseSE;						//	効果音クラスポインタ
	int SelectButton = 0;								//	選択中のボタン

	//	初期設定
	PauseSG();											//	初期設定

	//	一時停止画面の処理
	void Initia();										//	一時停止画面の初期処理
	int Update();										//	一時停止画面の更新処理
	void Draw();										//	一時停止画面の表示処理

	void OptionUpdate();

	bool OptionFlag = false;
};