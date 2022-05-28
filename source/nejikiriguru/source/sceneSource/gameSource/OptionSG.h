#pragma once
#include "DxLib.h"
#include "SettingSource/OperationManager.h"
#include "SettingSource/Gameinformation.h"
#include "SettingSource/UIDraw.h"
#include "SettingSource/GameUI.h"
#include "SettingSource/SEManager.h"
#include "SettingSource/AllResourceLoad.h"
#include "SettingSource/CSVHeader.h"

#define CENTER_SCREEN_POS_X			(GAME_WIN_WIDTH / 2)	//　画面中央のX座標
#define CENTER_SCREEN_POS_Y			(GAME_WIN_HEIGHT / 2)	//　画面中央のY座標

#define BACK_GROUND_FRAME_WIDTH		1280					//　OptionTabの横幅
#define BACK_GROUND_FRAME_HEIGHT	640						//　OptionTabの縦の長さ

#define OPTION_TAB_WIDTH			400						//　OptionTabの横幅
#define OPTION_TAB_HEIGHT			60						//　OptionTabの縦の長さ
#define OPTION_CLOSE_TAB			50						//　閉じるボタンの大きさ
#define SAVE_WIDTH					100
#define SAVE_HEIGHT					50

#define VOLUME_BAR_WIDTH			600						//　音量バーの横幅
#define VOLUME_BAR_HEIGHT			24						//　音量バーの縦幅

#define VOLUME_BUTTON_WIDTH			100						//　音量ボタンの横幅
#define VOLUME_BUTTON_HEIGHT		50						//　音量ボタンの縦幅

#define OPRATION_BUTTON_WIDTH		300						//　操作設定ボタンの横幅
#define OPRATION_BUTTON_HEIGHT		40						//　操作設定ボタンの縦幅

#define TRIVIABOX_SIDE				10						//　TRIVIABOXの１辺

#define PERCENT_MAX					100						//	バーのマックス


/*
一時停止クラス
	ゲームを一時停止しボタンに設定された処理を実行
*/
class OptionSG
{
	//　オプションタブの種類
	enum OPTION_TAB
	{
		VolumeSetting = 0,									//　音量設定
		Operation,											//　操作設定
		OptionClose,										//　×(閉じる)
		OptionTabLength										//　総数
	};

	//	一時停止画面のボタンの種類
	enum VOLUME_BUTTON
	{
		BGM = 0,											//	ゲームに戻る
		SE,													//	リトライする
		UI,													//	設定画面へ
		Save,												//　保存
		VolumeButtonLength									//	総数
	};

	//　操作設定のボタンの種類
	enum OPRATION_BUTTON
	{
		ArrowKeyJump = 0,
		ArrowKeyMove,
		OprationButtonLength
	};

	//　豆知識の種類
	enum TRIVIA
	{
		Trivia0 = 0,
		Trivia1,
		Trivia2,
		Trivia3,
		Trivia4,
		Trivia5,
		Trivia6,
		Trivia7,
		Trivia8,
		Trivia9,
		TriviaLength
	};


private:
	const int TabButtonMaxNum[OPTION_TAB::OptionTabLength] =	//	オプションタブそれぞれのボタンの最大数
	{ VOLUME_BUTTON::VolumeButtonLength,OPRATION_BUTTON::OprationButtonLength,0 };

	const int ColorBase = GetColor(0, 0, 0);				//　黒色
	const int ColorMain = GetColor(255, 255, 255);			//　白色
	const int ColorSelect = GetColor(255, 255, 0);			//　黄色

	const char* TabTextString[OPTION_TAB::OptionTabLength] =				//	タブのテキストの内容
	{
		{"     音量"},
		{"     操作"},
		{"×"}
	};

	const char* VolumeTextString[VOLUME_BUTTON::VolumeButtonLength] =		//	音量設定のテキストの内容
	{
		{"BGM"},
		{"SE"},
		{"UI"},
		{"保存"},
	};

	const char* OprationTextString[OPRATION_BUTTON::OprationButtonLength] =	//	操作設定のテキストの内容
	{
		{"ジャンプ操作変更"},
		{"移動操作変更"},
	};

	const char* TriviaTextString[TRIVIA::TriviaLength] =	//	豆知識の内容
	{
		{"     真上にジャンプしてる最中に"},
		{"移動キーを押してもジャンプ移動できるよ"},

		{"ステージ24"},
		{"正解のルートは１つではない!?"},

		{"ステージ10"},
		{"スタート位置から"},
		{"Dキーをずっと押していると…"},

		{"このゲームには様々な攻略法がある。"},
		{"全クリ後もどんな攻略法があるのか"},
		{"いろんなステージで試してみよう！"},
	};

	//	変数
	int SelectTab = 0;										//	選択中のタブ
	int SelectButtons = 0;									//	選択中のボタン番号
	int VolumeBar[VolumeButtonLength - 1];					//　音量バーの配列
	int VolumePercent[VolumeButtonLength - 1];				//　音量バーの割合
	int Percent = 100;										//　割合
	int CountSave = 0;										//　表示時間のカウント
	int CountDraw = 1;										//　閉じる画面で描画されてる画面の表示時間のカウント
	int DrawNum = 0;										//　閉じる画面で描画されてる画面の番号
	int TriviaNum = 0;										//　豆知識の番号

	bool SaveFlag = false;									//　保存されたかどうか
	bool* pOperationSetting[OprationButtonLength] = { new bool };			//	操作設定の内容

	UIButton OptionTab[OptionTabLength + 1] = { UIButton() };				//	タブ
	UIButton VolumeButton[VolumeButtonLength + 1] = { UIButton() };			//	音量設定ボタン
	UIButton OprationButton[OprationButtonLength + 1] = { UIButton() };		//	操作設定ボタン



	bool InitiaBool = false;								//	初めの処理
	int ReturningSave = 0;									//　親の画面に返す値
	int	SceneTransition = 255;								//	画面遷移のフェードインフェードアウト0~255

	void SelectTabDraw(										//	選択タブの表示
		int FontNo, const char* PText);

	void VolumeButtonDraw(									//	音量設定ボタンの表示
		int FontNo, const char* PText);

	void OprationButtonDraw(								//	操作設定ボタンの表示
		int FontNo, const char* PText);

public:

	//	変数
	int* pOptionFont[FONT_SIZE::FontLength];				//	使用フォント
	int* pOptionBackGrahandle;								//	背景画像ハンドル
	int* pOptionGrahandle;									//	タイトル画像ハンドル
	DataLoadResource*	pOptionDataLoad;
	GameUI*				pOptionGameUI;						//	ゲームパッドのUI表示
	OperationManager*	pOptionOperation;					//	ゲームパッドクラスポインタ
	UIDraw*				pOptionUI;							//	UIの表示
	SEManager*			pOptionSE;							//	効果音クラスポインタ
	GameData*			pOptionGameDate;					//	ゲームセーブデータポインタ
	bool TransitionSet = true;								//	更新処理の再生(true)と停止(false)
	OptionSG();												//	初期設定

	//	一時停止画面の処理
	void Initia();											//	一時停止画面の初期処理
	void TabButton();										//	ボタンの更新処理
	void Draw();											//	一時停止画面の表示処理
	void VolumeDraw();										//　音量設定画面の描画処理
	void OperationDraw();									//　操作設定画面の描画処理
	void CloseDraw();										//　閉じるボタンの画面の描画処理
	int Update();											//	一時停止画面の更新処理

	//	設定読み込み0～100
	void LoadOption()
	{
		VolumePercent[SE] = pOptionGameDate->GameSaveData.SaveSEVolume;				//	音量を適用
		VolumePercent[BGM] = pOptionGameDate->GameSaveData.SaveBGMVolume;			//	音量を適用
		VolumePercent[UI] = pOptionGameDate->GameSaveData.SaveUIVolume;				//	音量を適用
		pOperationSetting[ArrowKeyJump] = &pOptionOperation->ArrowKeyJumpActive;	//	十字キーによるジャンプが有効か
		pOperationSetting[ArrowKeyMove] = &pOptionOperation->ArrowKeyMoveActive;	//	十字キーによる移動が有効か
		SelectTab = OPTION_TAB::VolumeSetting;										//	タブカーソル音声
		SelectButtons = 0;															//	ボタン選択タブ
	}
};