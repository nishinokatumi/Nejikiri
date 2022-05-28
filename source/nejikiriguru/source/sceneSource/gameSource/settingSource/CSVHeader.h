#pragma once
#include "DxLib.h"
#include "Gameinformation.h"
#include <stdio.h>
#include <string.h>

#define	MAP_WIDTH_NUM		20								//	マップチップの横の数
#define	MAP_HEIGHT_NUM		15								//	マップチップの縦の数
#define CSV_MAX_COMMA	19									//	ステージCSVフォルダのカンマの最大数
#define	CSV_STAGE_NUM	27

static const char* CSVFilePath = "resource/csvdata/stage_%d.csv";	//	読み込むCSVファイルの相対パス
static const char* GameFile = "resource/GameData.dat";		//	読み込むDatファイルの相対パス

//	ゲームのセーブデータの構造体
struct GameSaveData
{
	int ReleaseStage = 0;									//	解放済みのステージの番号
	int SaveSEVolume = 100;										//	効果音の設定
	int SaveBGMVolume = 100;									//	背景音の設定
	int SaveUIVolume = 100;										//	システム音の設定
};

/*
ステージの読み込みクラス
	CSVファイルからステージデータ(ブロックの配置や種類・ギミックの配置や情報)を読み込む
*/
class CSVLoad
{
public:
	CSVLoad() {};											//	初期設定

	//	ステージのデータをCSVファイルから読み込みポインタで値を渡す
	void StageDataLoad(int StageNo, MAP_INFO::Stage* pStageData, MAP_INFO::GimmickData* pGimmickData);
};

/*
ステージの書き込みクラス
	CSVファイルにステージデータ(ブロックの配置や種類・ギミックの配置や情報)を書き込む
*/
class CSVWrite
{
public:
	CSVWrite() {};											//	初期設定

	//	ステージのデータをCSVファイルに合わせて書き込む
	void StageDataWrite(int StageNo, MAP_INFO::Stage StageData, MAP_INFO::GimmickData GimmickData);
};

/*
ステージの読み込みクラス
	datファイルからゲームのセーブデータを処理する
*/
class GameData
{
private:
	bool LoadDone = false;									//	ゲームのセーブデータを読み込み済みかどうか
	bool LoadDoneSE = false;								//	音の設定を読み込み済みかどうか

public:
	GameSaveData GameSaveData = { 0 };						//	ゲームのセーブデータ

	GameData() {};											//	初期設定

	void Load();											//	datファイルからセーブデータを読み込む
	void SaveStageNo(int SetNo);							//	datファイルにゲームのセーブデータを書き込む
	void SaveSoundVolume(int SEVolume, int BGMVolume, int UIVolume);	//	datファイルに音のセーブデータを書き込む
	void LoadSoundVolume(int* pSEVolume, int* pBGMVolume, int* pUIVolume);	//	音量セーブデータ代入
};