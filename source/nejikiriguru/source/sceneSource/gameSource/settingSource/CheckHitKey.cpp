/*
キー入力に関する補助関数
DXLibに存在しないので自作

*/
#include "CheckHitKey.h"
#include "DxLib.h"

namespace CheckKey
{
	int DownBuffer[256];	// CheckDownKey用のキーバッファ
	int UpBuffer[256];		// CheckUpKey用のキーバッファ
};

// 指定されたキーが押された瞬間だけ 1 を返す関数
int CheckDownKey(int KeyCode)
{
	// 戻り値用の変数を用意
	int Result = 0;

	// 指定キーの現在の状態を取得
	int KeyState = CheckHitKey(KeyCode);

	// 前回キーが押されておらず、かつ、現在キーが押されていたら「キーを押した瞬間」とする
	if (CheckKey::DownBuffer[KeyCode] == 0 && KeyState == 1)
	{
		Result = 1;
	}

	// 現在のキー状態をバッファに格納
	CheckKey::DownBuffer[KeyCode] = KeyState;

	return Result;
}

// 指定されたキーが離された瞬間だけ 1 を返す関数
int CheckUpKey(int KeyCode)
{
	// 戻り値用の変数を用意
	int Result = 0;

	// 指定キーの現在の状態を取得
	int KeyState = CheckHitKey(KeyCode);

	// 前回キーが押されており、かつ、現在キーが押されていなかったら「キーを離した瞬間」とする
	if (CheckKey::UpBuffer[KeyCode] == 1 && KeyState == 0)
	{
		Result = 1;
	}

	// 現在のキー状態をバッファに格納
	CheckKey::UpBuffer[KeyCode] = KeyState;

	return Result;
}