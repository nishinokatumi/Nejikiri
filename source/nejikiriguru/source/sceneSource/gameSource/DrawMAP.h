#pragma once
#include "DxLib.h"
#include "SettingSource/Gameinformation.h"


/*
マップの表示クラス
	マップデータ(CSVから変換したもの)を読み込み画像として表示
	見た目の表示が基本
*/
class DrawMAP
{
private:

	//	変数
	int MapPosX = 0;										//	マップの原点の位置X
	int MapPosY = 0;										//	マップの原点の位置Y
	int MapNo = 0;											//	表示するステージナンバー
	MAP_INFO::Stage NowMapData = { 0 };						//	現在のステージのマップデータ

public:
	//	変数
	int* pMapGraph[GRAPH::BLOCK::BlockLength - 1][4] = { 0 };	//	画像取り分け用配列
	int* pGimmickGraph = 0;									//	ギミック画像取り分け用

	DrawMAP();												//	初期設定

	//	処理
	void Update();											//	繰り返し実行：パネルの操作の判断と計算
	void DrawMap();											//	表示処理
	void DataRoad(MAP_INFO::Stage MapData, int MapDataNo);	//	ステージ変更時の初期値読み込み
};