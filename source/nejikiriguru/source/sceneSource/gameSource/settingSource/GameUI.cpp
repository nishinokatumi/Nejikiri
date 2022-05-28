#include "GameUI.h"
#include "DxLib.h"

/*
ゲームUIの管理クラス
	ゲームUIを分割し選んで表示する
*/

//	初期設定
GameUI::GameUI()
{
}

//	ゲームUIの処理
void GameUI::Initia(int GameUIGraphNo)
{
	//	部品の数だけ繰り返す
	for (int PartsNum = 0; PartsNum < UILength; PartsNum++)
	{
		//	パーツの切り出し
		GameUIGraph[PartsNum]								//	ギミックの画像配列に代入
			= DerivationGraph(								//	画像の一部を新しい画像に変換
				UIGraphPos[PartsNum][0], UIGraphPos[PartsNum][1],	//	取り出す部分の左上の座標を入力
				UIGraphSize[PartsNum][0], UIGraphSize[PartsNum][1],	//	取り出す部分のXとYのピクセル数を入力
				GameUIGraphNo);								//	取り出す画像を指定

	}

	//	部品の数だけ繰り返す
	for (int PartsNum = 0; PartsNum < UIMenuLength; PartsNum++)
	{
		GameUIFrame[PartsNum]								//	ギミックの画像配列
			= DerivationGraph(								//	画像の一部を新しい画像に変換
				UIFramePos[PartsNum][0], UIFramePos[PartsNum][1],	//	取り出す部分の左上の座標を入力
				UIFrameSize[PartsNum][0], UIFrameSize[PartsNum][1],	//	取り出す部分のXとYのピクセル数を入力
				GameUIGraphNo);								//	取り出す画像を指定
	}

	//	色の取得
	UIColorWhite = GetColor(250, 250, 250);				//	白
	UIColorBlack = GetColor(0, 0, 0);					//	黒
}

//	最終処理
void GameUI::Final()
{
	//	ゲームUIの数分繰り返す
	for (int UINum = 0; UINum < UI_PARTS::UILength; UINum++)
	{
		DeleteGraph(GameUIGraph[UINum]);					//	UIの画像削除
	}
}

//	ゲームの画像を選択し表示する
void GameUI::Draw(int UIPosX, int UIPosY, float Size, int SetUIParts, int VecPadSet)
{
	float Angle = 0;										//	表示角度

	//	方向キーの際に
	if (SetUIParts == UI_PARTS::VecPad || SetUIParts == UI_PARTS::LightVec)
	{
		Angle = PI * (float)VecPadSet / 2.0f;				//	画像の向きを変更
	}

	//	ゲームの画像表示
	DrawRotaGraph2(
		UIPosX, UIPosY,										//	画像の位置
		UIGraphCenterPos[SetUIParts][0], UIGraphCenterPos[SetUIParts][1],	//	中心位置の設定
		Size, Angle,										//	サイズと角度
		GameUIGraph[SetUIParts],							//	表示する画像
		true, false);										//	表示する画像の透過と反転
}

//	ゲーム中の操作説明
void GameUI::DrawpadUI(bool GamePadReady)
{
	//　UIウィンドウの縁の太さ
	const float LineTin = 3.0f;

	//	グラフの拡大度合い
	const int GraphScale = 3;


	//　操作説明
	DrawStringToHandle(
		SpaceAX + (int)LineTin,
		SpaceAY + (int)LineTin,
		"操作説明", UIColorWhite, *pGameUIDraw->FontSet[FONT_SIZE::GameStat]);

	pGameUIDraw->TextOutlLine(
		SpaceAX + (int)LineTin,
		SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
		FONT_SIZE::GameStat, "操作説明", 0,
		2, UIColorWhite, UIColorBlack);


	//　移動
	pGameUIDraw->TextOutlLine(
		SpaceBX + 50 + (int)LineTin,
		SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
		FONT_SIZE::GameStat, ":移動", 0,
		2, UIColorWhite, UIColorBlack);


	//	ゲームパッドが有効時
	if (GamePadReady)
	{
		//　Lスティック
		Draw(SpaceBX + 25, SpaceAY + 20, 1.5f, UI_PARTS::Stick);
		Draw(SpaceBX + 25, SpaceAY + 18, 2, UI_PARTS::L);

		//　Aボタン
		Draw(SpaceCX, SpaceAY + 20, (float)GraphScale, UI_PARTS::Button);
		Draw(SpaceCX, SpaceAY + 20, (float)GraphScale, UI_PARTS::A);

		//　ジャンプ
		pGameUIDraw->TextOutlLine(
			SpaceCX + 24 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":ジャンプ", 0,
			2, UIColorWhite, UIColorBlack);

		//　ポーズ画面へ
		pGameUIDraw->TextOutlLine(
			1170 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, "startボタン:ポーズ", 0,
			2, UIColorWhite, UIColorBlack);
	}
	//	キーボード操作時
	else
	{
		//　ジャンプ
		pGameUIDraw->TextOutlLine(
			SpaceCX + 24 + 180 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":ジャンプ", 0,
			2, UIColorWhite, UIColorBlack);

		//　AKey
		Draw(SpaceBX + (UIGraphCenterPos[UI_PARTS::Key][0] * GraphScale) + 1, SpaceAY + 20, (float)GraphScale, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceBX + 32, SpaceAY + 18, FONT_SIZE::PicUp, "D", 1, 1, UIColorWhite, UIColorBlack);

		//　DKey
		Draw(SpaceBX - (UIGraphCenterPos[UI_PARTS::Key][0] * GraphScale) - 1, SpaceAY + 20, (float)GraphScale, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceBX - 18, SpaceAY + 18, FONT_SIZE::PicUp, "A", 1, 1, UIColorWhite, UIColorBlack);

		//　BKey
		Draw(SpaceBX - (UIGraphCenterPos[UI_PARTS::Key][0] * GraphScale) + 250, SpaceAY + 20, (float)GraphScale, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceBX - 18 + 250, SpaceAY + 18, FONT_SIZE::PicUp, "B", 1, 1, UIColorWhite, UIColorBlack);

		//　SpaceKey
		Draw(SpaceCX + 180, SpaceAY + 18, 3, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceCX + 16 + 180, SpaceAY + 18, FONT_SIZE::Normal, "Space", 5, 1, UIColorWhite, UIColorBlack);

		//　ポーズ画面へ
		Draw(SpaceDX + 180, SpaceAY + 18, 3, UI_PARTS::Key);
		pGameUIDraw->TextOutlLine(SpaceDX + 12 + 180, SpaceAY + 18, FONT_SIZE::Normal, "Esc", 3, 1, UIColorWhite, UIColorBlack);

		//　ポーズ画面へ
		pGameUIDraw->TextOutlLine(
			SpaceDX + 18 + 180 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":ポーズ", 0,
			2, UIColorWhite, UIColorBlack);

		//　減速
		pGameUIDraw->TextOutlLine(
			SpaceBX + 250 + (int)LineTin,
			SpaceAY + (int)LineTin + (SetFontStat[FONT_SIZE::GameStat].Size / 2),
			FONT_SIZE::GameStat, ":減速", 0,
			2, UIColorWhite, UIColorBlack);
	}
}

//	メニューウィンドウを表示する(座標式)
void GameUI::DrawMenuWindowPos(int MenuPosX1, int MenuPosY1, int MenuPosX2, int MenuPosY2, int Size, int BackColor, int MenuType, int Transparency)
{
	//	メニュータイプが透明であれば
	if (MenuType == MENU_TYPE::BackTransparency)
	{
		//	背景のみ指定量で透明に
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Transparency);
		DrawBox(MenuPosX1, MenuPosY1, MenuPosX2, MenuPosY2, BackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//	でなければ
	else
	{
		DrawBox(MenuPosX1, MenuPosY1, MenuPosX2, MenuPosY2, BackColor, true);
	}
	int MenuWidth = MenuPosX2 - MenuPosX1;					//	横幅
	int MenuHeight = MenuPosY2 - MenuPosY1;					//	縦幅

	//	枠の表示上下
	{
		//	上の枠
		DrawRotaGraph3(
			MenuPosX1, MenuPosY1,								//	画面の原点
			0, 0,												//	画像の原点
			(float)Size, (1.0 / 16.0)* MenuWidth,				//	拡大度合
			PI * (float)3 / 2.0f, GameUIFrame[MENU_PARTS::GoldFrame], false, true, false);

		//	上の枠
		DrawRotaGraph3(
			MenuPosX1, MenuPosY2,								//	画面の原点
			4, 0,												//	画像の原点
			(float)Size, (1.0 / 16.0)* MenuWidth,				//	拡大度合
			PI * (float)3 / 2.0f, GameUIFrame[MENU_PARTS::GoldFrame], false, false, false);
	}

	//	メニュータイプが中心部品非表示でありメニューの高さが線の中心部品の大きさよりも大きければ
	if ((MenuType == MENU_TYPE::CenterNone) ||
		(MenuHeight / 2) + (UIFrameSize[MENU_PARTS::GoldFrame][0] * Size) >
		((UIFrameSize[MENU_PARTS::LineCenter][1] / 2) - 4)  * Size)
	{
		//	枠の表示左右
		{
			//	左の枠
			DrawRotaGraph3(
				MenuPosX1, MenuPosY1,								//	画面の原点
				4, 0,												//	画像の原点
				(float)Size, (1.0f / 16.0f)* MenuHeight,			//	拡大度合
				0, GameUIFrame[MENU_PARTS::GoldFrame], false, false, false);

			//	右の枠
			DrawRotaGraph3(
				MenuPosX2, MenuPosY1,								//	画面の原点
				0, 0,												//	画像の原点
				(float)Size, (1.0f / 16.0f)* MenuHeight,			//	拡大度合
				0, GameUIFrame[MENU_PARTS::GoldFrame], false, true, false);

		}

		//	枠の端の表示
		{
			//	左上
			DrawRotaGraph2(
				MenuPosX1, MenuPosY1,							//	画面座標
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	画像中心位置X
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	画像中心位置Y
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

			//	左下
			DrawRotaGraph2(
				MenuPosX1, MenuPosY2,							//	画面座標
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	画像中心位置X
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	画像中心位置Y
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

			//	右上
			DrawRotaGraph2(
				MenuPosX2, MenuPosY1,							//	画面座標
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	画像中心位置X
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	画像中心位置Y
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

			//	右下
			DrawRotaGraph2(
				MenuPosX2, MenuPosY2,							//	画面座標
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][0],//	画像中心位置X
				UIFrameCenterPos[MENU_PARTS::GoldEndoint][1],//	画像中心位置Y
				Size, 0, GameUIFrame[MENU_PARTS::GoldEndoint], true);

		}
	}

	//	枠の中心部品を表示するとき
	if (MenuType != MENU_TYPE::CenterNone)
	{
		//	左
		DrawRotaGraph2(
			MenuPosX1, MenuPosY1 + MenuHeight / 2,			//	画面座標
			UIFrameCenterPos[MENU_PARTS::LineCenter][0] - 1,	//	画像中心位置X
			UIFrameCenterPos[MENU_PARTS::LineCenter][1],	//	画像中心位置Y
			Size, 0, GameUIFrame[MENU_PARTS::LineCenter], true, false);

		//	左
		DrawRotaGraph2(
			MenuPosX2, MenuPosY1 + MenuHeight / 2,			//	画面座標
			UIFrameCenterPos[MENU_PARTS::LineCenter][0] + 1,	//	画像中心位置X
			UIFrameCenterPos[MENU_PARTS::LineCenter][1],	//	画像中心位置Y
			Size, 0, GameUIFrame[MENU_PARTS::LineCenter], true, true);
	}
}