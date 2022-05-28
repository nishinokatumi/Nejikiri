#pragma once
#include "GamePad.h"
#include "CheckHitKey.h"

//	操作の種類
enum class OPERATION_CATEGORY
{
	CharaUP = 0,											//	キャラ移動:上
	CharaDown,												//	キャラ移動:下
	CharaLeft,												//	キャラ移動:左
	CharaRight,												//	キャラ移動:右
	CharaDash,												//	キャラ移動:走る
	CharaJump,												//	キャラ移動:ジャンプ
	SelectUP,												//	選択移動:上
	SelectDown,												//	選択移動:下
	SelectLeft,												//	選択移動:左
	SelectRight,											//	選択移動:右
	SelectEnter,											//	選択決定
	SelectCancel,											//	選択取り消し
	SelectMenu,												//	選択メニュー
	SelectSkip,												//　音量調整時のゲージスキップ
	OperationLength											//	総数
};

//	操作管理クラス
class OperationManager :public GamePad
{
public:
	OperationManager() {}									//	初期処理

	bool ArrowKeyJumpActive = true;							//	十字キーによるジャンプが有効か
	bool ArrowKeyMoveActive = true;							//	十字キーによる移動が有効か


	//	操作処理
	bool GetOperation(OPERATION_CATEGORY Set) {

		bool Returning = false;								//	返す値を定義		

		//	操作の種類によって判定変更
		switch (Set)
		{
		case OPERATION_CATEGORY::CharaUP:					//	キャラ移動上
			Returning = ArrowKeyJumpActive && (CheckHitKey(KEY_INPUT_UP) || Button(XINPUT_BUTTON_DPAD_UP) ||
				CheckHitKey(KEY_INPUT_W));
			break;
		case OPERATION_CATEGORY::CharaDown:					//	キャラ移動下
			Returning = ArrowKeyJumpActive && (CheckHitKey(KEY_INPUT_DOWN) || Button(XINPUT_BUTTON_DPAD_DOWN) ||
				CheckHitKey(KEY_INPUT_S));
			break;
		case OPERATION_CATEGORY::CharaLeft:					//	キャラ移動左
			Returning = ((ArrowKeyMoveActive && (CheckHitKey(KEY_INPUT_LEFT) || Button(XINPUT_BUTTON_DPAD_LEFT))) ||
				CheckHitKey(KEY_INPUT_A));
			break;
		case OPERATION_CATEGORY::CharaRight:				//	キャラ移動右
			Returning = ((ArrowKeyMoveActive && (CheckHitKey(KEY_INPUT_RIGHT) || Button(XINPUT_BUTTON_DPAD_RIGHT))) ||
				CheckHitKey(KEY_INPUT_D));
			break;
		case OPERATION_CATEGORY::CharaDash:					//	キャラダッシュ
			Returning = (CheckHitKey(KEY_INPUT_B) || Button(XINPUT_BUTTON_B));
			break;
		case OPERATION_CATEGORY::CharaJump:					//	キャラジャンプ
			Returning = (CheckDownKey(KEY_INPUT_SPACE) || OneButton(XINPUT_BUTTON_A));
			break;
		case OPERATION_CATEGORY::SelectUP:					//	選択上
			Returning = (CheckDownKey(KEY_INPUT_UP) || OneButton(XINPUT_BUTTON_DPAD_UP));
			break;
		case OPERATION_CATEGORY::SelectDown:				//	選択下
			Returning = (CheckDownKey(KEY_INPUT_DOWN) || OneButton(XINPUT_BUTTON_DPAD_DOWN));
			break;
		case OPERATION_CATEGORY::SelectLeft:				//	選択左
			Returning = (CheckDownKey(KEY_INPUT_LEFT) || OneButton(XINPUT_BUTTON_DPAD_LEFT));
			break;
		case OPERATION_CATEGORY::SelectRight:				//	選択右
			Returning = (CheckDownKey(KEY_INPUT_RIGHT) || OneButton(XINPUT_BUTTON_DPAD_RIGHT));
			break;
		case OPERATION_CATEGORY::SelectEnter:				//	選択決定
			Returning = (CheckDownKey(KEY_INPUT_RETURN) || OneButton(XINPUT_BUTTON_B));
			break;
		case OPERATION_CATEGORY::SelectCancel:				//	選択取り消し
			Returning = (CheckDownKey(KEY_INPUT_SPACE) || OneButton(XINPUT_BUTTON_A));
			break;
		case OPERATION_CATEGORY::SelectMenu:				//	選択メニュー
			Returning = (CheckDownKey(KEY_INPUT_ESCAPE) || OneButton(XINPUT_BUTTON_START));
			break;
		case OPERATION_CATEGORY::SelectSkip:				//	選択をスキップ
			Returning = (CheckHitKey(KEY_INPUT_LSHIFT));
		default:
			break;
		}
		return Returning;									//	判定結果を返す
	}
};

