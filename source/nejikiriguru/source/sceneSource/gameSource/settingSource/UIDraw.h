#pragma once
#include "Gameinformation.h"
#include "DxLib.h"


/*
UIの表示クラス
	多用するUIをまとめて簡単に使えるようにする
*/
class UIDraw
{
public:
	/*----------------------文字------------------------*/
	int* FontSet[FONT_SIZE::FontLength] = { new int };		//	使用フォント 

	UIDraw();												//	初期設定

	//	ボックスで作るウィンドウの表示
	void BoxWindow(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor);

	//	中空ボックスで作るウィンドウの表示
	void BoxLineWindow(int WindowPosX, int WindowPosY, int WindowWidth,
		int WindowHeight, int WindowColor, float WindowLineTin);

	//	Textが入るウィンドウを表示
	void TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
		float WindowLineTin, int FontType, const char* WindowTextString);

	//	Textが入るウィンドウを表示:複数行
	void TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
		float WindowLineTin, int FontType, const char* WindowTextString[], int WindowTextNum);

	//	中心からボックスで作るウィンドウの表示
	void BoxWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor);

	//	中心から中空ボックスで作るウィンドウの表示
	void BoxLineWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor,
		float WindowLineTin);

	//	中心からTextが入るウィンドウを表示
	void TextBoxWindowCenter(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
		float WindowLineTin, int FontType, const char* WindowTextString);

	//	アウトラインがあるテキスト:タイトルや状態を伝えるときなど
	void TextOutlLine(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int TextStringNum, int OutLineWidth, int StringColor, int OutLineColor);

	//	アウトラインがあるテキスト右上から:タイトルや状態を伝えるときなど
	void TextOutlLineFormat(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int StringInt, int OutLineWidth, int StringColor, int OutLineColor);

	//	ブラックアウト
	void DarkenScreen(int WindowPosX, int WindowPosY,
		int WindowWidth, int WindowHeight,
		int WindowColor, int WindowDarken);
};

#define PLUSPER 20											//	ボタン色切り替えの変化量

/*
ボタンの処理表示クラス
	ボタンの動的選択等の表示表現の処理などを行う
*/
class UIButton :public UIDraw
{
public:
	bool Valid = false;										//	ボタン選択中
	int ButtonNo = 0;										//	ボタンのナンバー
	int PosX = 0;											//	ボタン左の座標
	int PosY = 0;											//	ボタン上の座標
	int Width = 0;											//	ボタン横幅
	int Height = 0;											//	ボタン縦幅
	int ColorBase = 0;										//	ボタン色(非選択時)
	int ColorSelect = 0;									//	ボタン色(選択済み)
	int ColorMain = 0;										//	ボタン色(選択時)

	int ColorPercent = 0;									//	重ねる色のパーセント0～255
	int Perplus = 0;										//	パーセントを変える値


	UIButton() {}											//	初期設定

	//	ボタンの選択非選択の動的な色の変化
	void UpdateBlend()
	{
		Perplus = 0;										//	変化しない際に余計な処理をしないために0にする

		//	有効の時
		if (Valid)
		{
			//	色がすでに最大でなければ
			if (ColorPercent < 255)
			{
				Perplus = PLUSPER;							//	変化量を設定
			}

			//	色がすでに最大であれば
			else
			{
				ColorPercent = 255;							//	重ねる色を最大値に設定
			}
		}

		//	無効の時
		else
		{
			//	色がすでに最小でなければ
			if (ColorPercent > 0)
			{
				Perplus = -PLUSPER;							//	変化量を設定
			}

			//	色がすでに最小であれば
			else
			{
				ColorPercent = 0;							//	重ねる色を最大値に設定
			}
		}

		//	変化量が変わっていれば
		if (Perplus != 0)
		{
			ColorPercent += Perplus;						//	変化の処理をする
		}
	}

	//	ボタンの表示　sele:選択済みの論理値
	void Draw(bool Sele)
	{
		int WindowLineTin = 4;								//	ウィンドウの線の太さ

		//	ボタンのボックス
		DrawBox(
			PosX, PosY,
			PosX + Width, PosY + Height,
			ColorBase, true);

		//	理論値が有効だった場合
		if (Sele)
		{
			//	ボックスを選択済みの色に
			DrawBox(
				PosX, PosY,
				PosX + Width, PosY + Height,
				ColorSelect, true);
		}

		//	理論値が無効だった場合
		else
		{
			//	blendモードを切り替えどの位映すか設定する
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, ColorPercent);

			//	ボックスに選択色を被せる
			DrawBox(
				PosX, PosY,
				PosX + Width, PosY + Height,
				ColorMain, true);

			//	通常のblendモードを切り替える
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		//	テキストボックスの縁の表示
		DrawBoxAA((float)PosX, (float)PosY,
			(float)(PosX + Width), (float)(PosY + Height),
			ColorMain, false, (float)WindowLineTin);
	}
};