#include "UIDraw.h"
#include "DxLib.h"

/*
UIの表示クラス
	多用するUIをまとめて簡単に使えるようにする
*/

//	初期設定
UIDraw::UIDraw()
{
}

//	ボックスで作るウィンドウの表示
void UIDraw::BoxWindow(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor)
{
	//	ボックスの表示
	DrawBox(
		WindowPosX, WindowPosY,								//	ボックス左上
		WindowPosX + WindowWidth, WindowPosY + WindowHeight,//	ボックス右下
		WindowColor, true);									//	色を選択して塗りつぶす
}

//	中空ボックスで作るウィンドウの表示
void UIDraw::BoxLineWindow(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor,
	float WindowLineTin)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);				//	blendモードを切り替え180映す設定をする

	//	テキストボックスの表示
	DrawBox(
		WindowPosX + (int)WindowLineTin,					//	左
		WindowPosY + (int)WindowLineTin,					//	上
		WindowPosX + WindowWidth - (int)WindowLineTin,		//	右
		WindowPosY + WindowHeight - (int)WindowLineTin,		//	下
		GetColor(0, 0, 0), true);							//	黒色を選択して塗りつぶす

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);			//	通常のblendモードを切り替える

	//	テキストボックスの枠の表示
	DrawBoxAA(
		(float)WindowPosX + WindowLineTin,					//	左
		(float)WindowPosY + WindowLineTin,					//	上
		(float)(WindowPosX + WindowWidth) - WindowLineTin,	//	右
		(float)(WindowPosY + WindowHeight) - WindowLineTin,	//	下
		WindowColor, false, WindowLineTin);					//	色を選択して中心を塗りつぶさない
}

//	Textが入るウィンドウを表示
void UIDraw::TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
	float WindowLineTin, int FontType, const char* WindowTextString)
{
	//	文字を入れるためのボックスの右側の位置(文字数分右へ)
	int BoxX = WindowPosX + (SetFontStat[FontType].Size * TextStringNum) + ((15 + (int)WindowLineTin) * 2);

	//	文字を入れるためのボックスの下側の位置
	int BoxY = WindowPosY + SetFontStat[FontType].Size + ((15 + (int)WindowLineTin) * 2);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);				//	blendモードを切り替え180映す設定をする

	//	テキストボックスの表示
	DrawBox(
		WindowPosX, WindowPosY,								//	左上
		BoxX, BoxY,											//	右下(文字数分右へ)
		WindowColor, true);									//	色を選択して塗りつぶす


	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);			//	通常のblendモードを切り替える

	//	テキストボックスの縁の表示
	DrawBoxAA(
		(float)WindowPosX + WindowLineTin,					//	左
		(float)WindowPosY + WindowLineTin,					//	上
		(float)BoxX - WindowLineTin,						//	右(文字数分右へ)
		(float)BoxY - WindowLineTin,						//	下
		StringColor, false, WindowLineTin);					//	色を選択して中心を塗りつぶさない


	//	テキストの表示
	DrawStringToHandle(
		WindowPosX + (int)WindowLineTin + 15,				//	左
		WindowPosY + (int)WindowLineTin + 15,				//	下
		WindowTextString, StringColor, *FontSet[FontType]);	//	色を選択して指定フォントでテキストを表示

}

//	Textが入るウィンドウを表示:複数行
void UIDraw::TextBoxWindow(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
	float WindowLineTin, int FontType, const char* WindowTextString[], int WindowTextNum)
{
	//	文字を入れるためのボックスの右側の位置(文字数分右へ)
	int BoxX = WindowPosX + (SetFontStat[FontType].Size * TextStringNum) + ((15 + (int)WindowLineTin) * 2);

	//	文字を入れるためのボックスの下側の位置(行数分下がる)
	int BoxY = WindowPosY + (SetFontStat[FontType].Size * WindowTextNum) + ((15 + (int)WindowLineTin) * 2);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);				//	blendモードを切り替え180映す設定をする

	//	テキストボックスの表示
	DrawBox(
		WindowPosX, WindowPosY,								//	左上
		BoxX, BoxY,											//	右下(文字数分右へ)
		WindowColor, true);									//	色を選択して塗りつぶす

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);			//	通常のblendモードを切り替える

	//	テキストボックスの縁の表示
	DrawBoxAA(
		(float)WindowPosX + WindowLineTin,					//	左
		(float)WindowPosY + WindowLineTin,					//	上
		(float)BoxX - WindowLineTin,						//	右(文字数分右へ)
		(float)BoxY - WindowLineTin,						//	下
		StringColor, false, WindowLineTin);					//	色を選択して指定フォントでテキストを表示

	//	テキストの表示：行回分
	for (int LineCount = 0; LineCount < WindowTextNum; LineCount++)
	{
		//	テキストの表示
		DrawStringToHandle(
			WindowPosX + (int)WindowLineTin + 10,			//	左
			WindowPosY + (int)WindowLineTin + 10 + (LineCount * SetFontStat[FontType].Size),//	下(行数分下がる)
			WindowTextString[LineCount], StringColor, *FontSet[FontType]);	//	色を選択して指定フォントでテキストを表示
	}
}

//	中心からボックスで作るウィンドウの表示
void UIDraw::BoxWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor)
{
	//	中心からに変換
	BoxWindow(
		WindowPosX - (WindowWidth / 2),						//	左から横幅の半分左に
		WindowPosY - (WindowHeight / 2),					//	上から縦幅の半分上に
		WindowWidth, WindowHeight,							//	縦横それぞれの幅
		WindowColor);										//	色の選択
}

//	中心から中空ボックスで作るウィンドウの表示
void UIDraw::BoxLineWindowCenter(int WindowPosX, int WindowPosY, int WindowWidth, int WindowHeight, int WindowColor, float WindowLineTin)
{
	//	中心からに変換
	BoxLineWindow(
		WindowPosX - (WindowWidth / 2),						//	左から横幅の半分左に
		WindowPosY - (WindowHeight / 2),					//	上から縦幅の半分上に
		WindowWidth, WindowHeight,							//	縦横それぞれの幅
		WindowColor, WindowLineTin);						//	縁の色と幅の選択
}

//	中心からTextが入るウィンドウを表示
void UIDraw::TextBoxWindowCenter(int WindowPosX, int WindowPosY, int TextStringNum, int StringColor, int WindowColor,
	float WindowLineTin, int FontType, const char* WindowTextString)
{
	//	TextBoxWindowと同じように計算
	int BoxX = (SetFontStat[FontType].Size * TextStringNum) + ((15 + (int)WindowLineTin) * 2);

	//	TextBoxWindowと同じように計算
	int BoxY = (SetFontStat[FontType].Size) + ((15 + (int)WindowLineTin) * 2);

	//	中心からに変換
	TextBoxWindow(
		WindowPosX - (BoxX / 2),							//	左から横幅の半分左に
		WindowPosY - (BoxY / 2),							//	上から縦幅の半分上に
		TextStringNum, StringColor,							//	文字数と文字の色
		WindowColor, WindowLineTin,							//	ウィンドウの色とウィンドウの縁の幅
		FontType, WindowTextString);						//	文字の種類とテキスト
}

//	アウトラインがあるテキスト:タイトルや状態を伝えるときなど
void UIDraw::TextOutlLine(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int TextStringNum,
	int OutLineWidth, int StringColor, int OutLineColor)
{
	int FontSize = SetFontStat[FontType].Size;				//	文字の色
	int StringX = StringPosX - (FontSize * TextStringNum / 2);	//	文字の横半分(中心にするため)
	int StringY = StringPosY - (FontSize / 2);				//	文字の縦半分(中心にするため)

	//	アウトカラー表現
	DrawStringToHandle(StringX + OutLineWidth, StringY + OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも右下に表示

	DrawStringToHandle(StringX + OutLineWidth, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも左下に表示

	DrawStringToHandle(StringX - OutLineWidth, StringY + OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも右上に表示

	DrawStringToHandle(StringX - OutLineWidth, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも左上に表示


	DrawStringToHandle(StringX + OutLineWidth, StringY, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも下に表示

	DrawStringToHandle(StringX, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも左に表示

	DrawStringToHandle(StringX - OutLineWidth, StringY, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも上に表示

	DrawStringToHandle(StringX, StringY - OutLineWidth, WindowTextString,
		OutLineColor, *FontSet[FontType]);					//	文字よりも右に表示


	//	文字を表示(中心)
	DrawStringToHandle(StringX, StringY, WindowTextString, StringColor, *FontSet[FontType]);
}

//	アウトラインがあるテキスト右上から:タイトルや状態を伝えるときなど
void UIDraw::TextOutlLineFormat(int StringPosX, int StringPosY, int FontType, const char* WindowTextString, int StringInt,
	int OutLineWidth, int StringColor, int OutLineColor)
{
	//	アウトカラー表現
	DrawFormatStringToHandle(StringPosX + OutLineWidth, StringPosY + OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも右下に表示
	DrawFormatStringToHandle(StringPosX + OutLineWidth, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも左下に表示
	DrawFormatStringToHandle(StringPosX - OutLineWidth, StringPosY + OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも右上に表示
	DrawFormatStringToHandle(StringPosX - OutLineWidth, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも左上に表示



	DrawFormatStringToHandle(StringPosX + OutLineWidth, StringPosY,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも下に表示
	DrawFormatStringToHandle(StringPosX, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも左に表示
	DrawFormatStringToHandle(StringPosX - OutLineWidth, StringPosY,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも上に表示
	DrawFormatStringToHandle(StringPosX, StringPosY - OutLineWidth,
		OutLineColor, *FontSet[FontType], WindowTextString, StringInt);	//	文字よりも右に表示




	//	文字を表示
	DrawFormatStringToHandle(StringPosX, StringPosY, StringColor, *FontSet[FontType], WindowTextString, StringInt);
}

//	ブラックアウト
void UIDraw::DarkenScreen(int WindowPosX, int WindowPosY,
	int WindowWidth, int WindowHeight, int WindowColor, int WindowDarken)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, WindowDarken);					//	αブレンド
	BoxWindow(WindowPosX, WindowPosY, WindowWidth, WindowHeight, WindowColor);	//	指定の色と範囲にボックスで表示
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);						//	基本に戻す
}