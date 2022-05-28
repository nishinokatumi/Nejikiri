#pragma once
#include "DxLib.h"
#include "SettingSource/Gameinformation.h"
#include "SettingSource/OperationManager.h"
#include "SettingSource/SEManager.h"

/*
プレイヤー管理クラス
	プレイヤーの位置や画像などを動かすためのクラス
*/
class CharaPL
{
private:

	//	変数
	double PLSize = 2;										//	プレイヤーの画像の大きさ普通が１
	double ExtRate = 0;										//	プレイヤーの回転角度：ラジアンで円周率を除く
	int GraphNo = 0;										//	プレイヤー画像の種類ナンバー
	int GraphNow = 0;										//	プレイヤー画像の現在ナンバー
	int Time = 0;											//	現在時刻：画像切り替えで使う
	int VecX = 1;											//	プレイヤーの進む意識の向きX
	int VecY = 1;											//	プレイヤーの重力の向きY
	int Buoyancy = 3;										//	プレイヤーのジャンプの際の浮力
	bool JumpFlag = false;									//	プレイヤーのジャンプの状態
	bool PLToFace = false;									//	プレイヤーの向いている方向 false:右　true:左
	MAP_INFO::Stage NowMapData{ 0 };							//	現在のマップデータ

	//	操作別の処理
	void KeyboardOperation();								//	キーボードでの操作
	void GamePadOperation();									//	ゲームパッドでの操作

	//	プレイヤーとマップの当たり判定処理
	int CharMove(int* pPosX, int* pPosY, int* pDownSP			//	動きによるマップとの当たり判定
		, int MoveX, int MoveY, int Size, bool* pJumpFlag);
	HIT_RESULT MapHitCheck									//	プレイヤーのマップとの当たり判定
	(int PosX, int PosY, int* pMoveX, int* pMoveY);
	int GetChipParam(float ParamX, float ParamY);			//	座標による当たり判定

public:

	//	変数
	int* pPLGraph[GRAPH::PL_GRAPH::PLLength][PL_MAX_GRAPH_WIDTH] = { new int };	//	プレイヤー画像保存配列：コマ数と状態種類から生成
	int PosX = 0;											//	プレイヤーの中心ポジションX
	int PosY = 0;											//	プレイヤーの中心ポジションY
	Vector2D ProgressVec = Vector2D(0, 0);					//	プレイヤーの進行ベクトル
	int PLGamePadNum = 0;									//	ゲームパッドの数

	OperationManager* pPLOperation = new OperationManager();//	プレイヤーを操作できるゲームパッド
	SEManager* pPLSE = new SEManager();						//	プレイヤーの音

	//	初期設定
	CharaPL();												//	クラス生成：Posを0にセット	
	CharaPL(int SetPosX, int SetPosY);						//	クラス生成：Posを指定

	//	プレイヤー処理
	void Vector();											//	ベクトルの処理
	void GraphChange();										//	プレイヤーの画像を変化させる
	void Update();											//	繰り返し実行：プレイヤーの操作の判断と計算
	void Draw();											//	表示処理
	void SetMove();											//	更新処理を段階化	プレイヤーの位置を確認しなおす
	void DataRoad(MAP_INFO::Stage MapData, Vector2D PLPos);	//	ステージ変更時の初期値読み込み
	void PLAnti(int XorY);									//	プレイヤーを反転させる X:0 Y:1
};