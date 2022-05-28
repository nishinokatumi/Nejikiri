#include "GamePad.h"

/*
ゲームパッドクラス
ゲームパッドの機能が使用できる
*/

//	初期設定
GamePad::GamePad()
{

}

//	初期処理
void GamePad::Initia(int InputType)
{
	//	ゲームパッドがある場合
	if (GetJoypadNum() != 0)
	{
		GamePadReady = true;								//	ゲームパッド有効
		GamePadNo = InputType;								//	ゲームパッドの番号を設定
		SetJoypadDeadZone(GamePadNo, 0.25);					//	ゲームパッドの反応しない部分を設定
	}
}

//	更新処理
void GamePad::Update()
{
	GamePadReady = (GetJoypadNum() != 0);					//	ゲームパッドが有効かどうか調べ代入する

	//	ゲームパッドが無効の時何もしない
	if (!GamePadReady)return;


	GetJoypadXInputState(GamePadNo, &GamePadData);			//	ゲームパッドデータの更新

	//	ジョイスティックの値入力	-1.0～1.0
	Joystick[0][0] = ((float)GamePadData.ThumbRX / (float)THUMB_MAX);	//	右スティックのX量
	Joystick[0][1] = -((float)GamePadData.ThumbRY / (float)THUMB_MAX);	//	右スティックのY量
	Joystick[1][0] = ((float)GamePadData.ThumbLX / (float)THUMB_MAX);	//	左スティックのX量
	Joystick[1][1] = -((float)GamePadData.ThumbLY / (float)THUMB_MAX);	//	左スティックのY量

	//	トリガーの値入力	0.0～1.0
	Trigger[0] = ((float)GamePadData.RightTrigger / (float)TRIGGER_MAX);//	右トリガー
	Trigger[1] = ((float)GamePadData.LeftTrigger / (float)TRIGGER_MAX);	//	左トリガー
}

//	過去の更新処理
void GamePad::OldUpdate()
{
	//	ゲームパッドが無効の時何もしない
	if (!GamePadReady)return;

	OldGamePadData = GamePadData;							//	データを更新する
}

//	指定ボタンが有効か確認
bool GamePad::Button(int XinSet)
{
	//	ゲームパッドが無効の時何もしない
	if (!GamePadReady)return false;

	return GamePadData.Buttons[XinSet];						//	指定のボタンが押されていればtrue
}

//	指定ボタンが一回押されたか確認
bool GamePad::OneButton(int XinSet)
{
	//	ゲームパッドが無効の時何もしない
	if (!GamePadReady)return false;

	//	過去のボタンが有効の時は抜ける
	if (OldGamePadData.Buttons[XinSet])return false;

	//	過去が無効で現在が有効の時にtrue
	return GamePadData.Buttons[XinSet];
}

//	振動処理:Power:300～1000	RorL 1:右 0:左
void GamePad::Vibrat(int Power, int Time, int RorL)
{
	//	ゲームパッドが無効の時何もしない
	if (!GamePadReady)return;

	int SetPower = 0;										//	振動量

	//	1000よりも上にされたら
	if (Power >= 1000)
	{
		SetPower = 1000;									//	1000で確定する
	}

	//	300よりも上なら
	else if (Power >= 300)
	{
		SetPower = Power;									//	そのまま設定する(300よりも下だと対して振動しないため)
	}

	StartJoypadVibration(GamePadNo, SetPower, Time, RorL);	//	振動し始める
}