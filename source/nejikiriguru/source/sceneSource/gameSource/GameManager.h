#pragma once

#include "CharaPL.h"
#include "DrawMAP.h"
#include "GimmickAll.h"
#include "SettingSource/CSVHeader.h"
#include "SettingSource/GameUI.h"
#include "SettingSource/AllResourceLoad.h"
#include "SettingSource/UIDraw.h"
#include "PauseSG.h"

/*
ゲーム制御クラス
	マップやプレイヤー、ギミック等を作り制御する
	ゲームの基本動作を制御
*/
class GameManager
{
	//	ゲームの状態種類
	enum GAMESTATE
	{
		Normal = 0,												//	通常進行
		Clear,													//	クリア時
		TimeUP,													//	ゲームオーバー時
	};
private:

	//	変数
	DrawMAP GameManagerMap = DrawMAP();						//	マップクラス作成
	UIDraw GameManagerUI;									//	UI用クラス作成
	CSVLoad GameManagerCSV = CSVLoad();						//	読み込みクラス作成

	MAP_INFO::Stage			MapNow;							//	いまのステージデータ

	MAP_INFO::GimmickData GimmiDataNow;						//	いまのギミックデータ

	int GameTime = 0;										//	ゲームの時間
	int GameRemainingTime = 0;								//	ゲームの残り時間
	int GameStartTime = 0;									//	ゲームを始めた時間
	int GameState = 0;										//	ゲームの状態

	//	WMRギミック
	GimmickWMR WMR[GIMMICK_WMR_MAX_NUM] = { GimmickWMR() };

	//	PRESギミック
	GimmickPres Pres[GIMMICK_PRES_MAX_NUM] = { GimmickPres() };

	//	ENERギミック
	GimmickEner Ener[GIMMICK_ENER_MAX_NUM] = { GimmickEner() };

	bool GimmickYellow = false;								//　ギミック(黄)が連動してるか
	bool GimmickBlue = false;								//　ギミック(青)が連動してるか
	bool GimmickWhite = false;								//　ギミック(白)が連動してるか

	bool MoveFlag = false;									//	ゲームの状態を続けるか
	bool LastStageClear = false;							//	最終ステージクリア


	//	処理
	void UpdateNormal();									//	ゲームの通常運行時の処理の更新
	void UpdateClear();										//	ステージクリア時の処理の更新
	void UpdateTimeUP();									//	タイムアップ時の処理の更新
	void DrawNormal();										//	ゲームの通常運行時の表示処理
	void DrawClear();										//	ステージクリア時の表示処理
	void DrawTimeUP();										//	タイムアップ時の表示処理
	void DrawUI();											//	UIの表示処理

public:

	//	変数
	UIDraw*				pGameManagerUI;						//	UI用クラスポインタ作成
	OperationManager*	pGameManagerOperation;				//	ゲームパッドクラスポインタ生成
	GameUI*				pGameManagerGameUI;					//	ゲームUIポインタ生成
	SEManager*			pGameManagerSE;						//	SEポインタ管理生成
	DataLoadResource*	pGameManagerDataLoad;				//	データポインタ生成
	int*				pGameManagerFONT[FONT_SIZE::FontLength];//	使用フォント
	int StageNo = 0;										//	いまのステージ
	int GameStopTime = 0;									//	ゲームを止めた時間
	CharaPL GameManagerPL = CharaPL(200, 200);				//	プレイヤークラス作成


	GameManager();											//	初期処理

	//	処理
	void Initia();											//	初めに読み込みゲームの画像を配列に分割する
	void Update();											//	繰り返し実行：ゲームの操作の判断と計算
	void Draw();											//	表示処理
	void ChangeStage(int NextStageNo);						//	クリア時などにステージの変換を行う

	//	最後のステージをクリアしたか
	bool MAXStageClear()
	{
		return (LastStageClear == true);
	}
};