#include "OptionSG.h"
#include "PauseSG.h"
#include "DxLib.h"

//	初期設定
OptionSG::OptionSG()
{

}

//	一時停止画面の初期処理
void OptionSG::Initia()
{
	//	タブボタン初期処理
	{
		//　タブの数だけ繰り返す
		for (int Num = 0; Num < OPTION_TAB::OptionTabLength; Num++)
		{
			OptionTab[Num].ButtonNo = Num;								//　ボタンの番号
			OptionTab[Num].ColorBase = ColorBase;						//　ボタンの色(黒)
			OptionTab[Num].ColorMain = ColorMain;						//　ボタンの色(白)
			OptionTab[Num].ColorSelect = ColorSelect;					//　ボタンの色(黄)
		}

		//	選択タブ
		//	音量設定
		{
			OptionTab[OPTION_TAB::VolumeSetting].PosX = (CENTER_SCREEN_POS_X - OPTION_TAB_WIDTH) - 5;		//　X座標
			OptionTab[OPTION_TAB::VolumeSetting].PosY = CENTER_SCREEN_POS_Y - 300;							//　Y座標
			OptionTab[OPTION_TAB::VolumeSetting].Width = OPTION_TAB_WIDTH;									//　ボタンの大きさ(横)
			OptionTab[OPTION_TAB::VolumeSetting].Height = OPTION_TAB_HEIGHT;								//　ボタンの大きさ(縦)
		}

		//	操作設定
		{
			OptionTab[OPTION_TAB::Operation].PosX = CENTER_SCREEN_POS_X + 5;								//　X座標
			OptionTab[OPTION_TAB::Operation].PosY = CENTER_SCREEN_POS_Y - 300;								//　Y座標
			OptionTab[OPTION_TAB::Operation].Width = OPTION_TAB_WIDTH;										//　ボタンの大きさ(横)
			OptionTab[OPTION_TAB::Operation].Height = OPTION_TAB_HEIGHT;									//　ボタンの大きさ(縦)
		}

		//	×(閉じる)
		{
			OptionTab[OPTION_TAB::OptionClose].PosX = (CENTER_SCREEN_POS_X + 5) + OPTION_TAB_WIDTH + 10;	//　X座標
			OptionTab[OPTION_TAB::OptionClose].PosY = CENTER_SCREEN_POS_Y - 300 + 10;						//　Y座標
			OptionTab[OPTION_TAB::OptionClose].Width = OPTION_CLOSE_TAB;									//　ボタンの大きさ(横)
			OptionTab[OPTION_TAB::OptionClose].Height = OPTION_CLOSE_TAB;									//　ボタンの大きさ(縦)
		}
	}
	
	//	音量設定ボタン初期処理
	{
		//　ボタンの数だけ繰り返す
		for (int Num = 0; Num < VOLUME_BUTTON::VolumeButtonLength; Num++)
		{
			VolumeButton[Num].ButtonNo = Num + 1;								//　ボタンの番号
			VolumeButton[Num].ColorBase = ColorBase;							//　ボタンの色(黒)
			VolumeButton[Num].ColorMain = ColorMain;							//　ボタンの色(白)
			VolumeButton[Num].ColorSelect = ColorSelect;						//　ボタンの色(黄)
		}

		//	音量設定ボタン
		//	BGM
		{
			VolumeButton[VOLUME_BUTTON::BGM].PosX = CENTER_SCREEN_POS_X - 450;	//　X座標
			VolumeButton[VOLUME_BUTTON::BGM].PosY = CENTER_SCREEN_POS_Y;		//　Y座標
			VolumeButton[VOLUME_BUTTON::BGM].Width = VOLUME_BUTTON_WIDTH;		//　ボタンの大きさ(横)
			VolumeButton[VOLUME_BUTTON::BGM].Height = VOLUME_BUTTON_HEIGHT;		//　ボタンの大きさ(縦)
		}

		//	SE
		{
			VolumeButton[VOLUME_BUTTON::SE].PosX = CENTER_SCREEN_POS_X - 450;	//　X座標
			VolumeButton[VOLUME_BUTTON::SE].PosY = CENTER_SCREEN_POS_Y + 100;	//　Y座標
			VolumeButton[VOLUME_BUTTON::SE].Width = VOLUME_BUTTON_WIDTH;		//　ボタンの大きさ(横)
			VolumeButton[VOLUME_BUTTON::SE].Height = VOLUME_BUTTON_HEIGHT;		//　ボタンの大きさ(縦)
		}

		//	UI
		{
			VolumeButton[VOLUME_BUTTON::UI].PosX = CENTER_SCREEN_POS_X - 450;	//　X座標
			VolumeButton[VOLUME_BUTTON::UI].PosY = CENTER_SCREEN_POS_Y + 200;	//　Y座標
			VolumeButton[VOLUME_BUTTON::UI].Width = VOLUME_BUTTON_WIDTH;		//　ボタンの大きさ(横)
			VolumeButton[VOLUME_BUTTON::UI].Height = VOLUME_BUTTON_HEIGHT;		//　ボタンの大きさ(縦)
		}

		//	Save
		{
			VolumeButton[VOLUME_BUTTON::Save].PosX = CENTER_SCREEN_POS_X + 400;	//　X座標
			VolumeButton[VOLUME_BUTTON::Save].PosY = CENTER_SCREEN_POS_Y + 300;	//　Y座標
			VolumeButton[VOLUME_BUTTON::Save].Width = SAVE_WIDTH;				//　ボタンの大きさ(横)
			VolumeButton[VOLUME_BUTTON::Save].Height = SAVE_HEIGHT;				//　ボタンの大きさ(縦)
		}
	}
	
	//	操作設定ボタン初期処理
	{
		//　ボタンの数だけ繰り返す
		for (int Num = 0; Num < OPRATION_BUTTON::OprationButtonLength; Num++)
		{
			OprationButton[Num].ButtonNo = Num + 1;								//　ボタンの番号
			OprationButton[Num].ColorBase = ColorBase;							//　ボタンの色(黒)
			OprationButton[Num].ColorMain = ColorMain;							//　ボタンの色(白)
			OprationButton[Num].ColorSelect = ColorSelect;						//　ボタンの色(黄)
		}

		//	音量設定ボタン
		//	ジャンプ操作変更
		{
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].PosX = CENTER_SCREEN_POS_X - 500;		//　X座標
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].PosY = CENTER_SCREEN_POS_Y + 50;		//　Y座標
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].Width = OPRATION_BUTTON_WIDTH;		//　ボタンの大きさ(横)
			OprationButton[OPRATION_BUTTON::ArrowKeyJump].Height = OPRATION_BUTTON_HEIGHT;		//　ボタンの大きさ(縦)
		}

		//	移動操作変更
		{
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].PosX = CENTER_SCREEN_POS_X - 500;		//　X座標
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].PosY = CENTER_SCREEN_POS_Y + 270;		//　Y座標
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].Width = OPRATION_BUTTON_WIDTH;		//　ボタンの大きさ(横)
			OprationButton[OPRATION_BUTTON::ArrowKeyMove].Height = OPRATION_BUTTON_HEIGHT;		//　ボタンの大きさ(縦)
		}
	}

	//	仮置き
	LoadOption();
}

//　一時停止画面の更新処理
int OptionSG::Update()
{
	int Returning = 0;										//　親の画面に返す値を0にする

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

		//	画面がアクティブ時に
		if (GetWindowActiveFlag())
		{
			ReturningSave = 0;								//　親の画面に返す値を0にする

			//	基本的な繰り返し処理
			TabButton();

			if (ReturningSave == 3)
				TransitionSet = false;						//	更新処理の停止(false)
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
			Returning = ReturningSave;
		}
	}

	//	ここまで
	return Returning;
}

//	ボタンの更新処理
void OptionSG::TabButton()
{
	//	タブの更新処理
	//　タブの数だけ繰り返す
	for (int TabNum = 0; TabNum < OPTION_TAB::OptionTabLength; TabNum++)
	{
		//	ボタンの選択非選択の動的な色の変化
		OptionTab[TabNum].UpdateBlend();

		//　ボタンが選択中だったら
		if (OptionTab[TabNum].ButtonNo == SelectTab)
		{
			//　ボタン選択中のフラグをtrueにする
			OptionTab[TabNum].Valid = true;
		}

		//　ボタンが選択中じゃなかったら
		else
		{
			//　ボタン選択中のフラグをfalseにする
			OptionTab[TabNum].Valid = false;
		}
	}

	//	ボタンの処理：タブが閉じる以外
	if (SelectTab != OPTION_TAB::OptionClose)
	{
		//	ボタンの更新処理
		//　ボタンの数だけ繰り返す
		for (int ButtonNum = 0; ButtonNum < TabButtonMaxNum[SelectTab]; ButtonNum++)
		{
			//	オプションタブが音量設定の時
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	ボタンの選択非選択の動的な色の変化
				VolumeButton[ButtonNum].UpdateBlend();

				//　ボタンが選択中だったら
				if (VolumeButton[ButtonNum].ButtonNo == SelectButtons)
				{
					//　ボタン選択中のフラグをtrueにする
					VolumeButton[ButtonNum].Valid = true;
				}

				//　ボタンが選択中じゃなかったら
				else
				{
					//　ボタン選択中のフラグをfalseにする
					VolumeButton[ButtonNum].Valid = false;
				}
			}

			//	オプションタブが音量設定の時
			if (SelectTab == OPTION_TAB::Operation)
			{
				//	ボタンの選択非選択の動的な色の変化
				OprationButton[ButtonNum].UpdateBlend();

				//　ボタンが選択中だったら
				if (OprationButton[ButtonNum].ButtonNo == SelectButtons)
				{
					//　ボタン選択中のフラグをtrueにする
					OprationButton[ButtonNum].Valid = true;
				}

				//　ボタンが選択中じゃなかったら
				else
				{
					//　ボタン選択中のフラグをfalseにする
					OprationButton[ButtonNum].Valid = false;
				}
			}
		}
	}

	
	//	選択の上
	if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
	{
		//	選択ボタンを上へ
		SelectButtons--;
		if (SelectButtons < 0)
		{
			SelectButtons = TabButtonMaxNum[SelectTab];		//	ボタンを1番下に
		}
		pOptionSE->SoundFinal(SOUND_NAME::Select);			//	効果音の停止
		pOptionSE->SoundPlay(SOUND_NAME::Select);			//	効果音の再生
	}

	//	選択の下
	if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
	{
		//	選択ボタンを下へ
		SelectButtons++;
		if (SelectButtons > TabButtonMaxNum[SelectTab])
		{
			SelectButtons = 0;								//	ボタンを1番上に
		}
		pOptionSE->SoundFinal(SOUND_NAME::Select);			//	効果音の停止
		pOptionSE->SoundPlay(SOUND_NAME::Select);			//	効果音の再生
	}



	//	選択ボタンがタブの時
	if (SelectButtons == 0)
	{
		//	選択の左
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectLeft))
		{
			pOptionSE->SoundFinal(SOUND_NAME::Select);		//	効果音の停止
			pOptionSE->SoundPlay(SOUND_NAME::Select);		//	効果音の再生
			//	選択タブを左へ
			SelectTab--;
			if (SelectTab < 0)
			{
				SelectTab = OPTION_TAB::OptionTabLength -1;	//	タブを1番右に
			}

			SaveFlag = false;								//　保存完了のテロップを非表示にする
		}

		//	選択の右
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
		{
			pOptionSE->SoundFinal(SOUND_NAME::Select);		//	効果音の停止
			pOptionSE->SoundPlay(SOUND_NAME::Select);		//	効果音の再生
			//	選択タブを左へ
			SelectTab++;
			if (SelectTab >= OPTION_TAB::OptionTabLength)
			{
				SelectTab = 0;								//	タブを1番左に
			}

			SaveFlag = false;								//　保存完了のテロップを非表示にする
		}

		//	決定キー選択
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			pOptionSE->SoundFinal(SOUND_NAME::Enter);		//	効果音の停止
			pOptionSE->SoundPlay(SOUND_NAME::Enter);		//	効果音の再生

			//	閉じるタブの時
			if (SelectTab == OPTION_TAB::OptionClose)
			{
				ReturningSave = 3;							//	設定画面から切り替え
			}

			//	それ以外
			else
			{
				SelectButtons = 1;							//	選択部をタブの一番最初に設定
			}
		}

		//	取り消しキー選択
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			ReturningSave = 3;								//	設定画面から切り替え
			pOptionSE->SoundFinal(SOUND_NAME::Jump);		//	効果音の停止
			pOptionSE->SoundPlay(SOUND_NAME::Jump);			//	効果音の再生
		}
	}

	//	それ以外の時
	else
	{
		//	選択の左
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectLeft))
		{
			//　音量設定
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	ボタン選択部がバーの時
				if (SelectButtons == VOLUME_BUTTON::BGM + 1 || SelectButtons == VOLUME_BUTTON::SE + 1
					|| SelectButtons == VOLUME_BUTTON::UI + 1)
				{
					pOptionSE->SoundFinal(SOUND_NAME::Select);			//	効果音の停止
					pOptionSE->SoundPlay(SOUND_NAME::Select);			//	効果音の再生

					//　音量調整時にゲージスキップする
					if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectSkip))
					{
						VolumePercent[SelectButtons - 1] -= 10;			//	指定音量割合を10ずつ減少させる
					}

					else
					{
						VolumePercent[SelectButtons - 1]--;				//	指定音量割合を1ずつ減少させる
					}

					//	指定音量割合が0未満であれば
					if (VolumePercent[SelectButtons - 1] < 0)
					{
						VolumePercent[SelectButtons - 1] = 0;			//	0に直す
					}
				}
			}
		}

		//	選択の右
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectRight))
		{
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	ボタン選択部がバーの時
				if (SelectButtons == VOLUME_BUTTON::BGM + 1 || SelectButtons == VOLUME_BUTTON::SE + 1
					|| SelectButtons == VOLUME_BUTTON::UI + 1)
				{
					pOptionSE->SoundFinal(SOUND_NAME::Select);			//	効果音の停止
					pOptionSE->SoundPlay(SOUND_NAME::Select);			//	効果音の再生

					//　音量調整時にゲージスキップする
					if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectSkip))
					{
						VolumePercent[SelectButtons - 1] += 10;			//	指定音量割合を減少させる
					}

					else
					{
						VolumePercent[SelectButtons - 1]++;				//	指定音量割合を上昇させる
					}

					//	指定音量割合が100より多いのであれば
					if (VolumePercent[SelectButtons - 1] > PERCENT_MAX)
					{
						VolumePercent[SelectButtons - 1] = PERCENT_MAX;	//	100に直す
					}
				}
			}
		}

		//	取り消しキー選択
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectCancel))
		{
			SelectButtons = 0;									//	選択部をタブに設定
			pOptionSE->SoundFinal(SOUND_NAME::Jump);			//	効果音の停止
			pOptionSE->SoundPlay(SOUND_NAME::Jump);				//	効果音の再生
		}

		//	決定キー選択
		if (pOptionOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			//　音量設定
			if (SelectTab == OPTION_TAB::VolumeSetting)
			{
				//	ボタン選択部がSaveの時
				if (SelectButtons == VOLUME_BUTTON::Save + 1)
				{
					//	保存する
					pOptionGameDate->SaveSoundVolume(
						VolumePercent[VOLUME_BUTTON::SE],
						VolumePercent[VOLUME_BUTTON::BGM],
						VolumePercent[VOLUME_BUTTON::UI]);

					//　音量を適応する
					pOptionSE->SettingVolume(
						(float)VolumePercent[VOLUME_BUTTON::SE] / 100.0f,
						(float)VolumePercent[VOLUME_BUTTON::BGM] / 100.0f,
						(float)VolumePercent[VOLUME_BUTTON::UI] / 100.0f);

					SaveFlag = true;							//　保存した
					CountSave = 0;								//　保存完了のテロップの表示時間を初期化

					pOptionSE->SoundFinal(SOUND_NAME::Enter);	//	効果音の停止
					pOptionSE->SoundPlay(SOUND_NAME::Enter);	//	効果音の再生

				}
			}

			//　操作設定
			else if (SelectTab == OPTION_TAB::Operation)
			{
				pOptionSE->SoundFinal(SOUND_NAME::Enter);		//	効果音の停止
				pOptionSE->SoundPlay(SOUND_NAME::Enter);		//	効果音の再生

				//　操作設定の有無の切り替え
				*pOperationSetting[SelectButtons - 1] =! *pOperationSetting[SelectButtons - 1];

			}
		}
	}


	//	音声設定の時
	if (SelectTab == OPTION_TAB::VolumeSetting)
	{
		//　3回繰り返す
		for (int BarNo = 0; BarNo < VOLUME_BUTTON::VolumeButtonLength - 1; BarNo++)
		{
			//	音量バーの長さ設定
			VolumeBar[BarNo] = (VOLUME_BAR_WIDTH / 100) * (VolumePercent[BarNo]);
		}
	}
}

//	一時停止画面の表示処理
void OptionSG::Draw()
{
	// シーン内の描画処理を行う
	DrawRotaGraph2(											//	背景の描画
		GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 64		//　画面上での画像の中心のX座標
		, WIN_PL_WIDTH / 4, WIN_PL_HEIGHT / 4				//　画面上での画像の中心のY座標
		, 3.5, 0											//	サイズ, 角度
		, *pOptionBackGrahandle, false, false);				//	表示する画像, 表示する画像の透過, 反転

	int ColorGray = GetColor(160, 160, 160);				//　灰色

		//　背景枠
	pOptionGameUI->DrawMenuWindowPos(
		CENTER_SCREEN_POS_X - (BACK_GROUND_FRAME_WIDTH / 2),			//　左上のX座標
		CENTER_SCREEN_POS_Y - (BACK_GROUND_FRAME_HEIGHT / 2) + 113,		//　左上のY座標
		CENTER_SCREEN_POS_X + (BACK_GROUND_FRAME_WIDTH / 2),			//　右下のX座標
		CENTER_SCREEN_POS_Y + (BACK_GROUND_FRAME_HEIGHT / 2) + 113,		//　右下のY座標
		8, ColorGray, 0);												//　サイズ, 色, タイプ

	//　タイトル枠
	pOptionGameUI->DrawMenuWindowOrigin(
		CENTER_SCREEN_POS_X - 250, CENTER_SCREEN_POS_Y - 150,			//　左上のX座標, Y座標
		500, 64,														//　横幅, 縦幅
		4, ColorBase,													//　サイズ, 色
		MENU_TYPE::FullDraw);											//　表示種類, 背景の透明度


//　ボタンの数だけ繰り返す
	for (int Num = 0; Num < OPTION_TAB::OptionTabLength; Num++)
	{
		//	選択ボタンの表示
		SelectTabDraw(Num, TabTextString[Num]);
	}


	switch (SelectTab)
	{
	case 0:	//　音量設定

		//　ボタンの数だけ繰り返す
		for (int Num = 0; Num < VOLUME_BUTTON::VolumeButtonLength; Num++)
		{
			//	選択ボタンの表示
			VolumeButtonDraw(Num, VolumeTextString[Num]);
		}

		VolumeDraw();										//　音量設定画面の描画処理
		break;

	case 1:	//　操作設定

		//　ボタンの数だけ繰り返す
		for (int Num = 0; Num < OPRATION_BUTTON::OprationButtonLength; Num++)
		{
			//	選択ボタンの表示
			OprationButtonDraw(Num, OprationTextString[Num]);
		}

		OperationDraw();									//　操作設定画面の描画処理
		break;

	case 2:	//　閉じる
		CloseDraw();										//　閉じるボタンの画面の描画処理
		break;

	default:
		break;
	}


	if (TransitionSet == true)
	{
		//	フェードイン
		if (SceneTransition > 0)
		{
			pOptionUI->DarkenScreen
			(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//　X座標, Y座標, 横幅, 縦幅
				, GetColor(0, 0, 0), SceneTransition);		//　色, フェードイン
		}
	}

	//	次のシーンへ
	else
	{
		//	フェードアウト
		pOptionUI->DarkenScreen(
			0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT			//　X座標, Y座標, 横幅, 縦幅
			, GetColor(0, 0, 0), SceneTransition);			//　色, フェードアウト
	}
}

//　音量設定の表示
void OptionSG::VolumeDraw()
{
	//　タイトル文字
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 66, CENTER_SCREEN_POS_Y - 135,				//　左上のX座標, Y座標
		"音量設定", ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　表示する文字, 色

	//　ボタンの数だけ繰り返す
	for (int VolumeButtonNum = 0; VolumeButtonNum < VOLUME_BUTTON::VolumeButtonLength - 1; VolumeButtonNum++)
	{
		//　音量設定の説明
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 200, CENTER_SCREEN_POS_Y - 40,			//　左上のX座標, Y座標
			"←　→　で１,　+　Shiftキーで10移動", ColorBase,				//　表示する文字, 色
			*pOptionUI->FontSet[FONT_SIZE::Explanation]);					//　フォントの種類　


		//　BGMゲージの枠の色(黒色)
		DrawBox(
			CENTER_SCREEN_POS_X + (VOLUME_BAR_WIDTH / 2) + 1,										//　左上のX座標
			(CENTER_SCREEN_POS_Y + 13 + (VolumeButtonNum * 100)) - 1,								//　左上のY座標
			CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2) - 1,										//　右下のX座標
			(CENTER_SCREEN_POS_Y + 13 + (VOLUME_BAR_HEIGHT / 4) * 3 + VolumeButtonNum * 100) + 1,	//　右下のY座標
			ColorBase, true);																		//　色, 塗りつぶすかどうか


		//　BGMゲージの色(黒色)
		DrawBox(
			CENTER_SCREEN_POS_X + (VOLUME_BAR_WIDTH / 2),											//　左上のX座標
			CENTER_SCREEN_POS_Y + 13 + (VolumeButtonNum * 100),										//　左上のY座標
			CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2),											//　右上のX座標
			CENTER_SCREEN_POS_Y + 13 + (VOLUME_BAR_HEIGHT / 4) * 3 + VolumeButtonNum * 100,			//　右上のY座標
			ColorBase, true);																		//　色, 塗りつぶすかどうか

		//　BGMゲージの色(黄色)
		DrawBox(
			CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2),											//　左上のX座標
			CENTER_SCREEN_POS_Y + 13 + (VolumeButtonNum * 100),										//　左上のY座標
			(CENTER_SCREEN_POS_X - (VOLUME_BAR_WIDTH / 2)) + VolumeBar[VolumeButtonNum],			//　右上のX座標
			CENTER_SCREEN_POS_Y + 13 + (VOLUME_BAR_HEIGHT / 4) * 3 + VolumeButtonNum * 100,			//　右上のY座標
			ColorSelect, true);																		//　色, 塗りつぶすかどうか


		//　音量の数値の枠(白色)
		DrawBox(
			CENTER_SCREEN_POS_X + 350 - 3,								//　左上のX座標
			CENTER_SCREEN_POS_Y + (VolumeButtonNum * 100) - 3,			//　左上のY座標
			CENTER_SCREEN_POS_X + 450 + 3,								//　右上のX座標
			CENTER_SCREEN_POS_Y + 50 + (VolumeButtonNum * 100) + 3,		//　右上のY座標
			ColorMain, true);											//　色, 塗りつぶすかどうか

		//　音量の数値の背景(黒色)
		DrawBox(
			CENTER_SCREEN_POS_X + 350,									//　左上のX座標
			CENTER_SCREEN_POS_Y + (VolumeButtonNum * 100),				//　左上のY座標
			CENTER_SCREEN_POS_X + 450,									//　右上のX座標
			CENTER_SCREEN_POS_Y + 50 + (VolumeButtonNum * 100),			//　右上のY座標
			ColorBase, true);											//　色, 塗りつぶすかどうか

		//　音量の数値の表示
		pOptionUI->TextOutlLineFormat(
			CENTER_SCREEN_POS_X + 380,									//　左上のX座標
			CENTER_SCREEN_POS_Y + (VolumeButtonNum * 100) + 5,			//　左上のY座標
			FONT_SIZE::GameStat,										//　フォントタイプ
			"%d", VolumePercent[VolumeButtonNum], 2,					//　表示する文字のポインタ, 表示する文字, サイズ
			ColorMain, ColorBase);										//　色, アウトラインの色
	
		//　保存され,テロップの表示カウントが500以下のときに表示
		if (SaveFlag && CountSave <= 500)
		{
			//　枠
			pOptionGameUI->DrawMenuWindowOrigin(
				CENTER_SCREEN_POS_X - 200, CENTER_SCREEN_POS_Y + 305,			//　左下のX座標, Y座標
				400, 80,														//　横幅, 縦幅
				2, ColorBase,													//　サイズ, 色
				MENU_TYPE::CenterNone);											//　表示種類, 背景の透明度

			//　保存完了のテロップ
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 100, CENTER_SCREEN_POS_Y + 328,			//　左上のX座標, Y座標
				"保存しました", ColorMain,										//　表示する文字, 色
				*pOptionUI->FontSet[FONT_SIZE::PicUp]);							//　フォントの種類
		
			CountSave++;									//　表示する時間のカウント

			if (CountSave == 500)							//　表示時間が終わったら
				SaveFlag = false;							//　保存完了のテロップを非表示にする
		}

	}

}

//　操作設定の表示
void OptionSG::OperationDraw()
{
	//　タイトル文字
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 65, CENTER_SCREEN_POS_Y - 135,			//　左上のX座標, Y座標
		"操作設定", ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);	//　表示する文字, 色, フォントの種類

	//　2回繰り返す
	for (int BackGroundNum = 0; BackGroundNum < OPRATION_BUTTON::OprationButtonLength; BackGroundNum++)
	{
		pOptionGameUI->DrawMenuWindowOrigin(
			CENTER_SCREEN_POS_X - 150,									//　左下のX座標
			CENTER_SCREEN_POS_Y - 24 + (BackGroundNum * 230),			//　左下のY座標
			700, 180,													//　横幅, 縦幅
			2, ColorBase,												//　サイズ, 色
			MENU_TYPE::CenterNone);										//　表示種類
	}

	//　説明
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 26,			//　左上のX座標, Y座標
		"Wキー,↑キー(反転時：Sキー,↓キー)での",						//　表示する文字
		ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);				//　色, フォントの種類

	//　説明
	if (*pOperationSetting[ArrowKeyJump])
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 76,		//　左上のX座標, Y座標
			"ジャンプ操作を有効化しました。",							//　表示する文字
			ColorSelect, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　色, フォントの種類
	}

	//　説明
	else
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 76,		//　左上のX座標, Y座標
			"ジャンプ操作を無効化しました。",							//　表示する文字
			ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);			//　色, フォントの種類
	}

	//　説明
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 256,			//　左上のX座標, Y座標
		"←→キーでの",													//　表示する文字
		ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);				//　色, フォントの種類

	//　説明
	if (*pOperationSetting[ArrowKeyMove])
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 306,		//　左上のX座標, Y座標
			"移動操作を有効化しました。",								//　表示する文字
			ColorSelect, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　色, フォントの種類
	}
	
	//　説明
	else
	{
		DrawStringToHandle(
			CENTER_SCREEN_POS_X - 130, CENTER_SCREEN_POS_Y + 306,		//　左上のX座標, Y座標
			"移動操作を無効化しました。",								//　表示する文字
			ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);			//　色, フォントの種類
	}

}

//　閉じるボタンの画面の描画処理
void OptionSG::CloseDraw()
{
	if (CountDraw <= 1200)
		CountDraw++;										//　閉じる画面で描画されてる画面の表示時間のカウント
	else
		CountDraw = 1;

	//　タイトル文字
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 66, CENTER_SCREEN_POS_Y - 135,				//　左上のX座標, Y座標
		" 閉じる", ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　表示する文字, 色

	//　このゲームの豆知識
	DrawStringToHandle(
		CENTER_SCREEN_POS_X - 160, CENTER_SCREEN_POS_Y - 40,								//　左上のX座標, Y座標
		" ちょっとした豆知識", ColorBase, *pOptionUI->FontSet[FONT_SIZE::PicUp]);			//　表示する文字, 色, フォントタイプ

	//　枠
	pOptionGameUI->DrawMenuWindowOrigin(
		CENTER_SCREEN_POS_X - 400, CENTER_SCREEN_POS_Y + 40,			//　左下のX座標, Y座標
		800, 320,														//　横幅, 縦幅
		2, ColorBase,													//　サイズ, 色
		MENU_TYPE::CenterNone);											//　表示種類, 背景の透明度

	//　豆知識の数
	for (int TriviaBoxNum = 0; TriviaBoxNum < 4; TriviaBoxNum++)
	{
		//　白い箱
		DrawBox(
			CENTER_SCREEN_POS_X - 120 + (TriviaBoxNum * 80),								//　左上のX座標
			CENTER_SCREEN_POS_Y + 100,														//　左上のY座標
			(CENTER_SCREEN_POS_X - 120 + (TriviaBoxNum * 80)) - TRIVIABOX_SIDE,				//　右上のX座標
			(CENTER_SCREEN_POS_Y + 100) - TRIVIABOX_SIDE,									//　右上のY座標
			ColorMain, true);																//　色, 塗りつぶすかどうか

	//　黄色い箱
		DrawBox(
			CENTER_SCREEN_POS_X - 120 + (TriviaNum * 80),									//　左上のX座標
			CENTER_SCREEN_POS_Y + 100,														//　左上のY座標
			(CENTER_SCREEN_POS_X - 120 + (TriviaNum * 80)) - TRIVIABOX_SIDE,				//　右上のX座標
			(CENTER_SCREEN_POS_Y + 100) - TRIVIABOX_SIDE,									//　右上のY座標
			ColorSelect, true);																//　色, 塗りつぶすかどうか

	}

	//　カウント　0～300
	if ((0 < CountDraw) && (CountDraw <= 300))
	{
		//　豆知識だけ繰り返す
		for (int TriviaNum = 0; TriviaNum < 2; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 320, CENTER_SCREEN_POS_Y + 170 + (TriviaNum * 50),			//　左上のX座標, Y座標
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　表示する文字, 色, フォントタイプ
		}

		TriviaNum = 0;										//　豆知識の番号：0
	}

	//　カウント　300～600
	else if ((300 < CountDraw) && (CountDraw <= 600))
	{
		//　豆知識だけ繰り返す
		for (int TriviaNum = 2; TriviaNum < 4; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 240, CENTER_SCREEN_POS_Y + 170 + ((TriviaNum - 2) * 50),		//　左上のX座標, Y座標
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　表示する文字, 色, フォントタイプ
		}

		TriviaNum = 1;										//　豆知識の番号：1
	}

	//　カウント　600～900
	else if ((600 < CountDraw) && (CountDraw <= 900))
	{
		//　豆知識だけ繰り返す
		for (int TriviaNum = 4; TriviaNum < 7; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 240, CENTER_SCREEN_POS_Y + 160 + ((TriviaNum - 4) * 50),		//　左上のX座標, Y座標
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　表示する文字, 色, フォントタイプ
		}

		TriviaNum = 2;										//　豆知識の番号：2
	}

	//　カウント　900～1200
	else if ((900 < CountDraw) && (CountDraw <= 1200))
	{
		//　豆知識だけ繰り返す
		for (int TriviaNum = 7; TriviaNum < OptionSG::TriviaLength; TriviaNum++)
		{
			DrawStringToHandle(
				CENTER_SCREEN_POS_X - 280, CENTER_SCREEN_POS_Y + 160 + ((TriviaNum - 7) * 50),		//　左上のX座標, Y座標
				TriviaTextString[TriviaNum], ColorMain, *pOptionUI->FontSet[FONT_SIZE::PicUp]);		//　表示する文字, 色, フォントタイプ
		}

		TriviaNum = 3;										//　豆知識の番号：3
	}

}

//	選択タブの表示
void OptionSG::SelectTabDraw(int FontNo, const char* pText)
{
	//　ボタンの表示処理
	OptionTab[FontNo].Draw(SelectButtons != 0 && FontNo == SelectTab);

	//　選択中
	if (OptionTab[FontNo].Valid)
	{
		DrawStringToHandle(
			OptionTab[FontNo].PosX							//　文字列を描画する起点座標(X座標)
			, OptionTab[FontNo].PosY + 1					//　文字列を描画する起点座標(Y座標)
			, pText, OptionTab[FontNo].ColorBase			//　描画する文字列のポインタ, 文字の色
			, *pOptionUI->FontSet[FONT_SIZE::Tab]			//　描画する文字列
		);
	}

	//　選択外
	else
	{
		DrawStringToHandle(
			OptionTab[FontNo].PosX							//　文字列を描画する起点座標(X座標)
			, OptionTab[FontNo].PosY + 1					//　文字列を描画する起点座標(Y座標)
			, pText, OptionTab[FontNo].ColorMain			//　描画する文字列のポインタ, 文字の色
			, *pOptionUI->FontSet[FONT_SIZE::Tab]			//　描画する文字列
		);
	}

}

//	音量ボタンの表示
void OptionSG::VolumeButtonDraw(int FontNo, const char* pText)
{
	//　ボタンの表示処理
	VolumeButton[FontNo].Draw(false);

	//　選択中
	if (VolumeButton[FontNo].Valid)
	{
		DrawStringToHandle(
			VolumeButton[FontNo].PosX						//　文字列を描画する起点座標(X座標)
			, VolumeButton[FontNo].PosY + 1					//　文字列を描画する起点座標(Y座標)
			, pText, VolumeButton[FontNo].ColorBase			//　描画する文字列のポインタ, 文字の色
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//　描画する文字列
		);
	}

	//　選択外
	else
	{
		DrawStringToHandle(
			VolumeButton[FontNo].PosX						//　文字列を描画する起点座標(X座標)
			, VolumeButton[FontNo].PosY + 1					//　文字列を描画する起点座標(Y座標)
			, pText, VolumeButton[FontNo].ColorMain			//　描画する文字列のポインタ, 文字の色
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//　描画する文字列
		);
	}
}

//　操作設定ボタンの表示
void OptionSG::OprationButtonDraw(int FontNo, const char* pText)
{
	//　ボタンの表示処理
	OprationButton[FontNo].Draw(false);

	//　選択中
	if (OprationButton[FontNo].Valid)
	{
		DrawStringToHandle(
			OprationButton[FontNo].PosX						//　文字列を描画する起点座標(X座標)
			, OprationButton[FontNo].PosY + 1				//　文字列を描画する起点座標(Y座標)
			, pText, OprationButton[FontNo].ColorBase		//　描画する文字列のポインタ, 文字の色
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//　描画する文字列
		);
	}

	//　選択外
	else
	{
		DrawStringToHandle(
			OprationButton[FontNo].PosX						//　文字列を描画する起点座標(X座標)
			, OprationButton[FontNo].PosY + 1				//　文字列を描画する起点座標(Y座標)
			, pText, OprationButton[FontNo].ColorMain		//　描画する文字列のポインタ, 文字の色
			, *pOptionUI->FontSet[FONT_SIZE::PicUp]			//　描画する文字列
		);
	}

}