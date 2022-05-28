#pragma once
#include "SettingSource/Gameinformation.h"

/*
WMRの動作クラス
	ワープメビウスリングの判定や表示を行う
	プレイヤーの重力や操作を反転させる
*/
class GimmickWMR
{
private:
	//	変数
	Vector2D GimmickPos = Vector2D(0, 0);					//	ギミックのチップ座標
	Vector2D GimmickCenterPos = Vector2D(0, 0);				//	ギミック中心位置
	int GimmickSize = 0;									//	大きさ
	int GimmickLightNum = 255;								//	ライトのブレンド具合0～255;
	int GimmickConvequan = 10;								//	ライトの変化量
	bool GimmickIsValid = false;							//	ギミックの反転が有効か
	bool GimmickIsValidOld = false;							//	前回の判定

public:
	//	変数
	int* pGimmickGraNo[GRAPH::WMR_PARTS::WMRLength] = { 0 };	//	ギミックの画像ハンドル
	int GimmickVecXorY = 0;									//	ギミックの向き	0:X	1:Y
	bool GimmickIsEnergization = true;						//	通電しているか
	bool GimmickYellow = false;								//	チャンネル黄色
	bool GimmickBlue = false;								//	チャンネル青色
	bool GimmickWhite = false;								//	チャンネル白色
	int GimmickColor = 0;									//　色 　全部点灯:0 黄:1 青:2 白:3


	GimmickWMR();											//	初期設定

	//	WMRの処理
	void Update();											//	ギミックの更新処理
	void Draw();											//	ギミックの表示処理
	void DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color);	//	vecXorY:XかYのプラス方向に伸ばす X:0 Y:1
	bool ReverseMove(int* PLPosX, int* PLPosY, Vector2D PLVec, int PLSize);	//	WMRの中心から反転させる
	bool ReverseCheck(int PLPosX, int PLPosY, int PLSize);	//	反転が有効かどうか
};

/*
感圧の動作クラス
	WMRをONOFF切り替える際に使う
	チャンネルごとに切り替える
*/
class GimmickPres
{
private:
	//	変数
	Vector2D GimmickPos = Vector2D(0, 0);					//	ギミックのチップ座標
	int GimmickCenterPos = 0;								//	ギミック中心位置
	int GimmickInitia = 0;									//	大きさ
	bool GimmickStep = false;								//　感圧板を踏んだか

public:
	//	変数
	int* pGimmickGraNo[GRAPH::PRES_PARTS::PresLength] = { 0 };//	ギミックの画像ハンドル
	int GimmickVecXorY = 0;									//	ギミックの向き	0:X 上向き	1:Y 下向き
	bool GimmickIsEnergization = false;						//	通電している
	bool GimmickIsValid = false;							//	感圧ギミックが有効か
	bool GimmickIsValidOld = false;							//	前回の判定
	bool GimmickYellow = false;								//	チャンネル黄色
	bool GimmickBlue = false;								//	チャンネル青色
	bool GimmickWhite = false;								//	チャンネル白色
	int GimmickColor = 0;									//　色 　全部点灯:0 黄:1 青:2 白:3


	GimmickPres();											//	初期設定

	//	感圧の処理
	void Update();											//	ギミックの更新処理
	void Draw();											//	ギミックの表示処理
	void DataRoad(int PosX, int PosY, int VecXorY, int Initia, int Color);	//	vecXorY:XかYのプラス方向に伸ばす X:0 Y:1
	bool ReverseCheck(int PLPosX, int PLPosY, int PLSize);	//	感圧ギミックが有効かどうか
};

/*
通電の動作クラス
	つながっている感圧とWMRを分かりやすくしたもの
*/
class GimmickEner
{
private:
	//	変数
	Vector2D GimmickPos = Vector2D(0, 0);					//	ギミックのチップ座標
	int GimmickCenterPos = 0;								//	ギミック中心位置
	float Angle = 0;										//	表示角度
	int GimmickSize = 0;									//	大きさ
	int GimmickKind = 0;									//	種類 出力:0 入力:1

public:
	//	変数
	int* pGimmickGraNo[GRAPH::ENER_PARTS::EnerLength] = { 0 };//	ギミックの画像ハンドル
	int GimmickVecXorY = 0;									//	ギミックの向き	0:上 1:下 2:左 3:右
	bool GimmickYellow = false;								//	チャンネル黄色
	bool GimmickBlue = false;								//	チャンネル青色
	bool GimmickWhite = false;								//	チャンネル白色
	int GimmickColor = 0;									//　色 　全部点灯:0 黄:1 青:2 白:3

	GimmickEner();											//	初期設定

	//	通電の処理
	void Draw();											//	ギミックの表示処理
	void DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color, int Kind);	//	vecXorY:XかYのプラス方向に伸ばす X:0 Y:1
};