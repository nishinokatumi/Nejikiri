#pragma once
#include "DxLib.h"
#include "CheckHitKey.h"

/*
ゲームパッドクラス
ゲームパッドの機能が使用できる
*/

#define THUMB_MAX 32767										//	スティックの最大値
#define THUMB_MIN -32768									//	スティックの最小値
#define TRIGGER_MAX 255										//	トリガーの最大値

/*
ゲームパッドの管理クラス
	ゲームパッドの情報管理
	XInputのゲームパッドのみ使える
*/
class GamePad
{
private:
	XINPUT_STATE OldGamePadData = { 0 };					//	ゲームパッドの過去の入力データ
	int GamePadNo = 0;										//	プレイヤーの操作できるゲームパッド

public:
	XINPUT_STATE GamePadData;								//	ゲームパッドの入力データ

	float Joystick[2][2] = { 0.0f };						//	ジョイスティックの値-1～1まで 0:右 1:左0:X 1:Y 
	float Trigger[2] = { 0 };								//	トリガーの値0～255まで 0:右 1:左
	bool GamePadReady = false;								//	ゲームパッドが有効か

	GamePad();												//	初期設定

	//	ゲームパッドの処理
	void Initia(int InputType);								//	初期処理
	void Update();											//	更新処理
	void OldUpdate();										//	過去の更新処理
	bool Button(int XinSet);								//	指定ボタンが有効か確認
	bool OneButton(int XinSet);								//	指定ボタンが一回押されたか確認
	void Vibrat(int Power, int Time, int RorL);				//	振動処理:Power:300～1000	RorL 1:右 0:左
};