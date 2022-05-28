#include "SceneSelect.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneGame.h"

/*
ゲームシーン
*/

//	初期設定
SceneSelect::SceneSelect()
{

}

//	初期処理
void SceneSelect::Initia()
{
	static int ZeroX = 32;									//　ボタングループの原点のX座標
	static int MaxmX = (GAME_WIN_WIDTH / 2) - (64 * 5);		//　ステージセレクトボタンの左端のX座標
	static int MaxpX = (GAME_WIN_WIDTH / 2) + (64 * 5);		//　ステージセレクトボタンの右端のX座標
	static int ZeroY = 64;									//　ボタングループの原点のY座標
	static int Gap = 32;									//　ボタン同士の空白距離
	static int SelectStageHeight = 64 * 6;					//　

	pSceneDataLoad->InitiaGame();							//　ゲーム画像の初期処理を行う
	MaxClearStageNo = pSceneDataLoad->MaxStageNo;			//　現在クリアしたステージ番号の代入
	SelectStageNo = pSceneDataLoad->StageSet;					//　選択されたステージ番号を保存

	ColorBase = GetColor(0, 0, 0);							//　黒色
	ColorMain = GetColor(255, 255, 255);					//　白色
	ColorSelect = GetColor(255, 255, 0);					//　黄色

	//　ボタンUIの数だけ繰り返す
	for (int ButtonUINum = 0; ButtonUINum < 5; ButtonUINum++)
	{
		//　代入
		ButtonUI[ButtonUINum].ButtonNo = ButtonUINum;
		ButtonUI[ButtonUINum].ColorBase = ColorBase;
		ButtonUI[ButtonUINum].ColorMain = ColorMain;
		ButtonUI[ButtonUINum].ColorSelect = ColorSelect;
	}

	//	ステージセレクトボタン
	{
		//　X座標, Y座標, 横幅, 縦幅
		ButtonUI[BUTTON_L::StageSelect].PosX = ZeroX + Gap;
		ButtonUI[BUTTON_L::StageSelect].PosY = ZeroY + Gap;
		ButtonUI[BUTTON_L::StageSelect].Width = MaxmX - ButtonUI[StageSelect].PosX - Gap;
		ButtonUI[BUTTON_L::StageSelect].Height = SelectStageHeight;
	}

	//	説明ボタン
	{
		//　X座標, Y座標, 横幅, 縦幅
		ButtonUI[BUTTON_L::Description].PosX = ButtonUI[StageSelect].PosX;
		ButtonUI[BUTTON_L::Description].PosY = ButtonUI[StageSelect].PosY + ButtonUI[StageSelect].Height + Gap;
		ButtonUI[BUTTON_L::Description].Width = ButtonUI[StageSelect].Width;
		ButtonUI[BUTTON_L::Description].Height = ButtonUI[StageSelect].Height / 2;
	}

	//	設定ボタン
	{
		//　X座標, Y座標, 横幅, 縦幅
		ButtonUI[BUTTON_L::Option].PosX = ButtonUI[StageSelect].PosX;
		ButtonUI[BUTTON_L::Option].PosY = ButtonUI[Description].PosY + ButtonUI[Description].Height + Gap;
		ButtonUI[BUTTON_L::Option].Width = (ButtonUI[Description].Width - Gap) / 2;
		ButtonUI[BUTTON_L::Option].Height = ButtonUI[Description].Height;
	}

	//	ゲーム終了ボタン
	{
		//　X座標, Y座標, 横幅, 縦幅
		ButtonUI[BUTTON_L::GameExit].PosX = ButtonUI[Option].PosX + ButtonUI[Option].Width + Gap;
		ButtonUI[BUTTON_L::GameExit].PosY = ButtonUI[Option].PosY;
		ButtonUI[BUTTON_L::GameExit].Width = ButtonUI[Option].Width;
		ButtonUI[BUTTON_L::GameExit].Height = ButtonUI[Option].Height;
	}

	//	ゲームスタートボタン
	{
		//　X座標, Y座標, 横幅, 縦幅
		ButtonUI[4].PosX = MaxpX + Gap;
		ButtonUI[4].PosY = (GAME_WIN_HEIGHT - ButtonUI[StageSelect].Height) / 2;
		ButtonUI[4].Width = ButtonUI[StageSelect].Width;
		ButtonUI[4].Height = ButtonUI[StageSelect].Height;
	}

	SelectOption.pOptionBackGrahandle = &pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackGround];
	SelectOption.pOptionOperation = pSceneOperation;				//	ゲームパッドクラスを参照させる
	SelectOption.pOptionGameUI = pSceneGameUI;					//	ゲームUIクラスを参照させる
	SelectOption.pOptionSE = pSceneSE;							//	音の管理を参照させる
	SelectOption.pOptionUI = pSceneUI;							//	表示UIクラスを参照させる
	SelectOption.pOptionGameDate = pSceneGameData;				//	ゲームセーブデータを参照させる
	SelectOption.pOptionDataLoad = pSceneDataLoad;				//	画像管理クラスを参照させる
	SelectOption.Initia();										//	ポーズ画面の初期処理
}

//	最終処理
void SceneSelect::Final()
{
	//	画像を開放
	pSceneSE->SoundFinal(SOUND_NAME::Wind);
}

//	更新処理
SceneBase* SceneSelect::Update()
{
	//	計算処理を行う
	SceneBase* nextScene = this;

	//　現在のシーンへ
	if (TransitionSet == true)
	{
		//	フェードイン
		if (SceneTransition > 0)
		{
			//	0を下回るまで繰り返す
			SceneTransition -= 10;
			if (SceneTransition < 0)
			{
				SceneTransition = 0;
			}
		}

		//	一般的な処理
		else
		{
			//	画面がアクティブ時に
			if (GetWindowActiveFlag())
			{
				//	基本的な繰り返し処理
				BaseUpdate();
			}
		}
	}

	//	次のシーンへ
	else
	{
		//	フェードアウト
		if (SceneTransition < 255)
		{
			//	255を上回るまで繰り返す
			SceneTransition += 10;
			if (SceneTransition > 255)
			{
				SceneTransition = 255;
			}
		}
		//	次のシーンに遷移
		else
		{
			nextScene = pNextSceneSave;
		}
	}

	//	ここまで
	return nextScene;
}

//	基本的な繰り返し処理
void SceneSelect::BaseUpdate()
{
	//	最初だけ
	if (InitiaBool == false)
	{
		InitiaBool = true;

		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	BGM再生
	}

	//	設定画面の処理
	if (OptionFlag == true)
	{
		//　SelectOption.Updateから返ってきた値が3のとき
		if (SelectOption.Update() == 3)
		{
			//　オプションフラグをfalse
			OptionFlag = false;

			//	更新処理の再生(true)
			SelectOption.TransitionSet = true;
		}
	}
	else
	{
		//	基本的な計算処理
		ButtonReturn = SelectButton();

		//　ボタンUIの数だけ繰り返す
		for (int ButtonUINum = 0; ButtonUINum < 5; ButtonUINum++)
		{
			ButtonUI[ButtonUINum].UpdateBlend();				//　選択されているボタンの色を変える
		}

		//　ボタンの選択肢
		switch (ButtonReturn)
		{
		case 1:	//	ゲームスタートが押された
			//	渡す
			pSceneDataLoad->StageSet = SelectStageNo;			//　選択されたステージを保存
			pNextSceneSave = new SceneGame();					//　ゲームシーンに遷移する
			TransitionSet = false;								//　更新処理を停止
			break;

		case 2:	//	オプションが押された
			OptionFlag = true;									//　オプションフラグをtrue
			SelectOption.Initia();								//　オプションを初期化
			break;

		case 3:	//	ゲーム終了が押された
			//	セーブ

			*pSceneGameExit = true;								//　ゲームを閉じる
			break;

		default:
			break;
		}
	}
}

//	表示処理
void SceneSelect::Draw()
{
	//	設定画面の処理
	if (OptionFlag == true)
	{
		//　オプション画面の描画処理
		SelectOption.Draw();
	}

	else
	{
		//	描画処理を行う
		DrawRotaGraph2(														//	背景の描画
			GAME_WIN_WIDTH / 2												//　画面上での画像の中心のX座標
			, GAME_WIN_HEIGHT												//　画面上での画像の中心のY座標
			, WIN_PL_WIDTH / 4, 0											//　画像上での画像の中心のX座標, Y座標
			, 4, PI															//	サイズと角度
			, pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackGround]			//　表示する画像
			, false, false);												//	表示する画像の透過と反転

		DrawButton();											//　ボタンの表示処理
		DrawSelectStage();										//	ステージを選択の表示処理
		DrawSelectUI();											//　説明用のUI

		if (TransitionSet == true)
		{
			//	フェードイン
			if (SceneTransition > 0)
			{
				pSceneUI->DarkenScreen
				(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//　X座標, Y座標, 横幅, 縦幅
					, GetColor(0, 0, 0), SceneTransition);		//　色, フェードイン
			}
		}
		//	次のシーンへ
		else
		{
			//	フェードアウト
			pSceneUI->DarkenScreen(
				0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//　X座標, Y座標, 横幅, 縦幅
				, GetColor(0, 0, 0), SceneTransition);			//　色, フェードアウト
		}
	}
}

//	ボタンの選択処理
int SceneSelect::SelectButton()
{
	//　1番左側のボタングループ
	if (SelectButtonX == 0)
	{
		//　DOWNキー
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//　選択中の音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//　選択中の音を再生

			SelectButtonL++;								//　1つ下の選択ボタンへ

			//　カーソルが１番下の選択肢のとき
			if (SelectButtonL >= SELECTBUTTON_1Y)
			{
				//　カーソルが1番上の選択肢にいく
				SelectButtonL = 0;
			}
		}

		//　UPキー
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//　選択中の音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//　選択中の音を再生

			SelectButtonL--;								//　1つ上の選択ボタンへ

			//　カーソルが1番上の選択肢のとき
			if (SelectButtonL < 0)
			{
				//　カーソルが1番下の選択肢にいく
				SelectButtonL = 3;
			}
		}

		//　ボタンUIの数だけ繰り返す
		for (int ButtonUINum = 0; ButtonUINum < 4; ButtonUINum++)
		{
			//　1番左側のボタングループが選択中だったら
			if (ButtonUI[ButtonUINum].ButtonNo == SelectButtonL)
			{
				//　選択中のボタングループのフラグをtrueにする
				ButtonUI[ButtonUINum].Valid = true;
			}

			//　1番左側のボタングループが選択中じゃなかったら
			else
			{
				//　選択中のボタングループのフラグをfalseにする
				ButtonUI[ButtonUINum].Valid = false;
			}
		}

		//	左側のボタンの時の判定
		switch (SelectButtonL)
		{
		case BUTTON_L::StageSelect:							//　ステージ選択

			//	RIGHTキーか決定ボタン
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectRight) ||
				pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//　決定音が停止
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//　決定音が再生

				SelectButtonX = 1;							//　カーソルをステージセレクトボタンに移動する
			}
			break;

		case BUTTON_L::Description:							//　操作説明

			//	決定ボタン
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//　決定音が停止
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//　決定音が再生
				SelectButtonX = -1;							//　操作説明画面が出る
			}
			break;

		case BUTTON_L::Option:							//　設定

			//　
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Select);			//　選択中の音が停止
				pSceneSE->SoundPlay(SOUND_NAME::Select);			//　選択中の音を再生
				SelectButtonL = BUTTON_L::GameExit;
			}

			//　
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);			//　決定音が停止
				pSceneSE->SoundPlay(SOUND_NAME::Enter);				//　決定音が再生
				return 2;
			}
			break;

		case BUTTON_L::GameExit:							//　ゲーム終了

			//	LEFTキー
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectLeft))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Select);	//　選択中の音を停止
				pSceneSE->SoundPlay(SOUND_NAME::Select);	//　選択中の音を再生

				SelectButtonL = BUTTON_L::Option;
			}

			//	決定ボタン
			if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
			{
				pSceneSE->SoundFinal(SOUND_NAME::Enter);	//　決定音が停止
				pSceneSE->SoundPlay(SOUND_NAME::Enter);		//　決定音が再生
				return 3;
			}
			break;

		default:
			break;
		}
	}

	//　中央のボタングループ(ステージセレクトボタン)
	else if (SelectButtonX == 1)
	{
		//	中央のステージセレクトボタンのスロット

		//　DOWNキー
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//　選択中の音を停止
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//　選択中の音を再生

			SelectStageNo--;								//　カーソルが1つ前のステージ番号に戻る

			//　カーソルがステージ番号の0を下回ったら
			if (SelectStageNo < 0)
			{
				SelectStageNo = MaxClearStageNo;			//　カーソルを現在クリア済みのMAXステージ番号にする
			}
		}

		//　UPキー
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Select);		//　選択中の音を停止
			pSceneSE->SoundPlay(SOUND_NAME::Select);		//　選択中の音を再生

			SelectStageNo++;								//　カーソルが次のステージ番号にいく

			//　カーソルが現在クリア済みのMAXステージ番号を上回ったら
			if (SelectStageNo > MaxClearStageNo)
			{
				SelectStageNo = 0;							//　カーソルを1番最初のステージ番号にする
			}
		}

		//	決定ボタンかRIGHTキー
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Enter);		//　決定音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Enter);			//　決定音が再生

			SelectButtonX = 2;								//　カーソルをゲームスタートボタンに移動する
			ButtonUI[4].Valid = true;						//　ゲームスタートボタンの選択フラグをtrueにする
		}

		//	LEFTキーか戻る
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectLeft) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//　ジャンプ音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//　ジャンプ音が再生

			SelectButtonX = 0;								//　カーソルを1番左側のボタングループに移動する
		}
	}

	//　1番右側のボタングループ(ゲームスタートボタン)
	else if (SelectButtonX == 2)
	{
		//	ゲームスタートが押された
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Enter);		//　決定音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Enter);			//　決定音が再生
			return 1;										//　case1にいく
		}

		//	LEFTキーか戻る
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectLeft) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//　ジャンプ音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//　ジャンプ音が再生

			SelectButtonX = 1;								//　カーソルを1番右のボタングループに移動する
			ButtonUI[4].Valid = false;						//　ゲームスタートボタンの選択フラグをfalseにする
		}
	}

	//　操作説明画面
	else if (SelectButtonX == -1)
	{
		//　決定ボタンか戻る　
		if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectEnter) ||
			pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			pSceneSE->SoundFinal(SOUND_NAME::Jump);			//　ジャンプ音が停止
			pSceneSE->SoundPlay(SOUND_NAME::Jump);			//　ジャンプ音が再生

			SelectButtonX = 0;								//　カーソルを1番右のボタングループに移動する
		}

	}

	return 0;
}

//	ボタンの表示処理
void SceneSelect::DrawButton()
{
	//　ボタンUIの数だけ繰り返す
	for (int ButtonUINum = 0; ButtonUINum < 5; ButtonUINum++)
	{
		//　操作説明画面を選択時に操作説明のボタンを黄色にする
		ButtonUI[ButtonUINum].Draw((SelectButtonX == -1 && ButtonUINum == Description) || (SelectButtonX > 0 && ButtonUINum == StageSelect));

		//　選択中のボタン
		if (ButtonUI[ButtonUINum].Valid == true)
		{
			//文字の色を黒色にする
			DrawStringToHandle(ButtonUI[ButtonUINum].PosX + 15, ButtonUI[ButtonUINum].PosY + 15,
				ButtonText[ButtonUINum], ButtonUI[ButtonUINum].ColorBase, *pSceneFont[PicUp]);
		}

		//　選択外のボタン
		else
		{
			//文字の色を白色にする
			DrawStringToHandle(ButtonUI[ButtonUINum].PosX + 15, ButtonUI[ButtonUINum].PosY + 15,
				ButtonText[ButtonUINum], ButtonUI[ButtonUINum].ColorMain, *pSceneFont[PicUp]);
		}
	}
}

//	ステージを選択の表示処理
void SceneSelect::DrawSelectStage()
{
	static int CentX = GAME_WIN_WIDTH / 2;					//　画面中央のX座標
	static int CentY = GAME_WIN_HEIGHT / 2;					//　画面中央のY座標
	static int SelectStageWidth = 64 * 10;					//　ステージセレクトボタンの横幅
	static int SelectStageHeight = 64 * 8;					//　ステージセレクトボタンの縦幅

	//	下
	if (SelectStageNo != 0)
	{
		////　背面の色(黒色)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY + SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY + SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorBase, true);

		////　枠の色(白色)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY + SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY + SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorMain, false);

		////　外枠の色(白色)
		//DrawBoxAA(
		//	(float)(CentX - (SelectStageWidth / 2)), (float)(CentY + SelectStageHeight) - (SelectStageHeight / 2),
		//	(float)(CentX + (SelectStageWidth / 2)), (float)(CentY + SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorMain, false, 4);

		pSceneGameUI->DrawMenuWindowPos(
			CentX - (SelectStageWidth / 2), (CentY + SelectStageHeight) - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), (CentY + SelectStageHeight) + (SelectStageHeight / 2),
			4, ColorBase, MENU_TYPE::CenterNone, 180);


		//　文字
		//DrawFormatStringToHandle(CentX, (CentY + SelectStageHeight), ColorMain, *pSceneFont[FONT_SIZE::Big], "No.%d", (SelectStageNo - 1));
		pSceneUI->TextOutlLineFormat(CentX - 10, (CentY + SelectStageHeight), FONT_SIZE::Big, "No.%d", (SelectStageNo - 1), 2, ColorBase, ColorMain);
	}

	//	上
	if (SelectStageNo != (SELECTBUTTON_2Y - 1))
	{
		////　背面の色(黒色)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY - SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorBase, true);

		////　枠の色(白色)
		//DrawBox(
		//	CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
		//	CentX + (SelectStageWidth / 2), (CentY - SelectStageHeight) + (SelectStageHeight / 2),
		//	ColorMain, false);

		pSceneGameUI->DrawMenuWindowPos(
			CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), (CentY - SelectStageHeight) + (SelectStageHeight / 2),
			4, ColorBase, MENU_TYPE::CenterNone, 180);

		//　文字
		//DrawFormatStringToHandle(CentX, (CentY - SelectStageHeight), ColorMain, *pSceneFont[FONT_SIZE::Big], "No.%d", (SelectStageNo + 1));
		pSceneUI->TextOutlLineFormat(CentX - 10, (CentY - SelectStageHeight), FONT_SIZE::Big, "No.%d", (SelectStageNo + 1), 2, ColorBase, ColorMain);

		//　クリア済みのステージ番号よりも上の番号のとき
		if (SelectStageNo + 1 > MaxClearStageNo)
		{
			//　色を暗くする
			pSceneUI->DarkenScreen(
				CentX - (SelectStageWidth / 2), (CentY - SelectStageHeight) - (SelectStageHeight / 2),
				SelectStageWidth, SelectStageHeight, ColorBase, 200);
		}
	}

	{
		//　背面の色を黒色にする
		/*DrawBox(
			CentX - (SelectStageWidth / 2), CentY - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), CentY + (SelectStageHeight / 2),
			ColorBase, true);*/


		pSceneGameUI->DrawMenuWindowPos(
			CentX - (SelectStageWidth / 2), CentY - (SelectStageHeight / 2),
			CentX + (SelectStageWidth / 2), CentY + (SelectStageHeight / 2),
			4, ColorBase, MENU_TYPE::FullDraw, 180);

		//　ステージセレクトボタンまたはゲームスタートボタンのとき
		if (SelectButtonX > 0)
		{
			//　選択中のボタンの枠の色を黄色にする
			DrawBoxAA(
				(float)CentX - (SelectStageWidth / 2), (float)CentY - (SelectStageHeight / 2),
				(float)CentX + (SelectStageWidth / 2), (float)CentY + (SelectStageHeight / 2),
				ColorSelect, false, 2);

			//　文字の色を黄色にする
			//DrawFormatStringToHandle(CentX, CentY, ColorSelect, *pSceneFont[FONT_SIZE::Big], "No.%d", SelectStageNo);
			pSceneUI->TextOutlLineFormat(CentX - 10, CentY, FONT_SIZE::Big, "No.%d", SelectStageNo, 2, ColorSelect, ColorMain);

		}

		//　1番左側のボタングループのとき
		else
		{
			//　ボタンの枠の色を白色にする
			DrawBoxAA(
				(float)CentX - (SelectStageWidth / 2), (float)CentY - (SelectStageHeight / 2),
				(float)CentX + (SelectStageWidth / 2), (float)CentY + (SelectStageHeight / 2),
				ColorMain, false, 2);

			//　文字の色を白色にする
			//DrawFormatStringToHandle(CentX, CentY, ColorMain, *pSceneFont[FONT_SIZE::Big], "No.%d", SelectStageNo);
			pSceneUI->TextOutlLineFormat(CentX - 10, CentY, FONT_SIZE::Big, "No.%d", SelectStageNo, 2, ColorBase, ColorMain);

		}
	}
}

//	説明用のUI
void SceneSelect::DrawSelectUI()
{
	static int UIWidth = GAME_WIN_WIDTH - (64 * 2);			//　UIの横幅
	static int UIHeight = 64;								//　UIの縦幅

	static int UIPosX = 64;									//　UIのX座標
	static int UIPosY = GAME_WIN_HEIGHT - 32 - UIHeight;	//　UIのY座標

	////　説明文の背景
	//DrawBox(UIPosX, UIPosY, UIPosX + UIWidth, UIPosY + UIHeight, ColorBase, true);

	////　説明文を囲っている枠
	//DrawBox(UIPosX, UIPosY, UIPosX + UIWidth, UIPosY + UIHeight, ColorMain, false);

	////　説明文を囲っている外枠
	//DrawBoxAA((float)UIPosX, (float)UIPosY, (float)UIPosX + (float)UIWidth, (float)UIPosY + (float)UIHeight, ColorMain, false, 4);

	pSceneGameUI->DrawMenuWindowOrigin
	(UIPosX, UIPosY, UIWidth, UIHeight, 4, ColorBase, MENU_TYPE::BackTransparency, 180);


	//	ゲームパッドが有効時
	if (pSceneOperation->GamePadReady)
	{
		//　説明文
		DrawStringToHandle(
			UIPosX,
			UIPosY + 15,
			"\"　　\"で選択し\"　　\"で決定\"　　\"でキャンセル", ColorMain, *pSceneFont[PicUp]);

		//	矢印キー(4方向)を表示
		for (int VecSelect = 0; VecSelect < 4; VecSelect++)
		{
			//　矢印キーを表示
			pSceneGameUI->Draw(UIPosX + 48, UIPosY + (UIHeight / 2), 2, UI_PARTS::VecPad, VecSelect);
			pSceneGameUI->Draw(UIPosX + 48, UIPosY + (UIHeight / 2), 2, UI_PARTS::LightVec, VecSelect);
		}

		//　Bボタンを表示
		pSceneGameUI->Draw(UIPosX + 304, UIPosY + (UIHeight / 2), 3, UI_PARTS::Button);
		pSceneGameUI->Draw(UIPosX + 304, UIPosY + (UIHeight / 2), 3, UI_PARTS::B);

		//　Aボタンを表示
		pSceneGameUI->Draw(UIPosX + 516, UIPosY + (UIHeight / 2), 3, UI_PARTS::Button);
		pSceneGameUI->Draw(UIPosX + 516, UIPosY + (UIHeight / 2), 3, UI_PARTS::A);
	}

	//	キーボード操作時
	else
	{
		//　説明文
		DrawStringToHandle(
			UIPosX,
			UIPosY + 15,
			"\"　　　　　　\"で選択し\"　　\"で決定\"　　\"でキャンセル", ColorMain, *pSceneFont[PicUp]);

		//	矢印キー(上方向)を表示
		pSceneGameUI->Draw(UIPosX + 48, UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + 48, UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "↑", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//	矢印キー(下方向)を表示
		pSceneGameUI->Draw(UIPosX + (48 * 2), UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + (48 * 2), UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "↓", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//	矢印キー(右方向)を表示
		pSceneGameUI->Draw(UIPosX + (48 * 3), UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + (48 * 3), UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "→", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//	矢印キー(左方向)を表示
		pSceneGameUI->Draw(UIPosX + (48 * 4), UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + (48 * 4), UIPosY + (UIHeight / 2), FONT_SIZE::PicUp, "←", 1, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//　EnterKeyを表示
		pSceneGameUI->Draw(UIPosX + 436, UIPosY + (UIHeight / 2), 2, UI_PARTS::EnterKey);
		pSceneUI->TextOutlLine(UIPosX + 454, UIPosY + (UIHeight / 2) - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));

		//　SpaceKeyを表示
		pSceneGameUI->Draw(UIPosX + 656, UIPosY + (UIHeight / 2), 3, UI_PARTS::Key);
		pSceneUI->TextOutlLine(UIPosX + 674, UIPosY + (UIHeight / 2), FONT_SIZE::Normal, "Space", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
	}

	//　操作説明ボタンを決定時
	if (SelectButtonX == -1)
	{
		int ManualGraph = 0;									//	説明画像

		//	ゲームパッドが有効時
		if (pSceneOperation->GamePadReady)ManualGraph = pSceneDataLoad->GraphGame[GRAPH::HANDLE::Manual];
		else ManualGraph = pSceneDataLoad->GraphGame[GRAPH::HANDLE::ManualKey];


		//　操作説明画面を表示
		DrawRotaGraph2(
			GAME_WIN_WIDTH / 2, 32								//　画面上での画像の中心のX座標, Y座標
			, 1556 / 2, 0										//　画像上での画像の中心のX座標, Y座標
			, 0.8, 0											//	0.8倍, 角度
			, ManualGraph										//　表示する画像
			, true, false);										//　表示する画像の透過と反転
	}
}