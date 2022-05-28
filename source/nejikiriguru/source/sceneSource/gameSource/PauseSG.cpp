#include "PauseSG.h"
#include "DxLib.h"

//	初期設定
PauseSG::PauseSG()
{

}

//	一時停止画面の初期処理
void PauseSG::Initia()
{
	static int ColorBase = GetColor(0, 0, 0);							//　黒色
	static int ColorMain = GetColor(255, 255, 255);						//　白色
	static int ColorSelect = GetColor(255, 255, 0);						//　黄色

	static int PauseButtonPosX = GAME_WIN_WIDTH / 2;					//　PauseButtonのX座標
	static int PauseButtonPosY = GAME_WIN_HEIGHT / 2;					//　PauseButtonのY座標

	static int PauseButtonWidth = 200;									//　PauseButtonの横幅
	static int PauseButtonHeight = 30;									//　PauseButtonの縦の長さ

	//　ボタンの数だけ繰り返す
	for (int Num = 0; Num < PAUSEBUTTON::PauseLength; Num++)
	{
		PauseButton[Num].ButtonNo = Num;								//　ボタンの番号
		PauseButton[Num].ColorBase = ColorBase;							//　ボタンの色(黒)
		PauseButton[Num].ColorMain = ColorMain;							//　ボタンの色(白)
		PauseButton[Num].ColorSelect = ColorSelect;						//　ボタンの色(黄)
	}

	//	ステージセレクトボタン
	{
		PauseButton[PAUSEBUTTON::Back].PosX = PauseButtonPosX;			//　X座標
		PauseButton[PAUSEBUTTON::Back].PosY = PauseButtonPosY;			//　Y座標
		PauseButton[PAUSEBUTTON::Back].Width = PauseButtonWidth;		//　ボタンの大きさ(横)
		PauseButton[PAUSEBUTTON::Back].Height = PauseButtonHeight;		//　ボタンの大きさ(縦)
	}

	//	説明ボタン
	{
		PauseButton[PAUSEBUTTON::Retry].PosX = PauseButtonPosX;			//　X座標
		PauseButton[PAUSEBUTTON::Retry].PosY = PauseButtonPosY + 100;	//　Y座標
		PauseButton[PAUSEBUTTON::Retry].Width = PauseButtonWidth;		//　ボタンの大きさ(横)
		PauseButton[PAUSEBUTTON::Retry].Height = PauseButtonHeight;		//　ボタンの大きさ(縦)
	}

	//	設定ボタン
	{
		PauseButton[PAUSEBUTTON::Option].PosX = PauseButtonPosX;		//　X座標
		PauseButton[PAUSEBUTTON::Option].PosY = PauseButtonPosY + 200;	//　Y座標
		PauseButton[PAUSEBUTTON::Option].Width = PauseButtonWidth;		//　ボタンの大きさ(横)
		PauseButton[PAUSEBUTTON::Option].Height = PauseButtonHeight;	//　ボタンの大きさ(縦)
	}

	//	ゲーム終了ボタン
	{
		PauseButton[PAUSEBUTTON::Select].PosX = PauseButtonPosX + 585;	//　X座標
		PauseButton[PAUSEBUTTON::Select].PosY = PauseButtonPosY + 400;	//　Y座標
		PauseButton[PAUSEBUTTON::Select].Width = PauseButtonWidth;		//　ボタンの大きさ(横)
		PauseButton[PAUSEBUTTON::Select].Height = PauseButtonHeight;	//　ボタンの大きさ(縦)
	}

	PauseOption.pOptionBackGrahandle = pPauseBackGrahandle;
	PauseOption.pOptionOperation = pPauseOperation;				//	ゲームパッドクラスを参照させる
	PauseOption.pOptionGameUI = pPauseGameUI;					//	ゲームUIクラスを参照させる
	PauseOption.pOptionSE = pPauseSE;							//	音の管理を参照させる
	PauseOption.pOptionUI = pPauseUI;							//	表示UIクラスを参照させる
	PauseOption.pOptionDataLoad = pPauseDataLoad;				//	画像管理クラスを参照させる
	PauseOption.pOptionGameDate = pPauseGameData;				//	ゲームセーブデータを参照させる
	PauseOption.Initia();									//	ポーズ画面の初期処理

}

//	一時停止画面の更新処理
int PauseSG::Update()
{
	//	設定画面の処理
	if (OptionFlag == true)
	{
		//　PauseOption.Updateから返ってきた値が3のとき
		if (PauseOption.Update() == 3)
		{
			//　オプションフラグをfalse
			OptionFlag = false;

			//	更新処理の再生(true)
			PauseOption.TransitionSet = true;
		}
	}

	//	一時停止画面の処理
	else
	{
		//　ボタンの数だけ繰り返す
		for (int ButtonNum = 0; ButtonNum < PAUSEBUTTON::PauseLength; ButtonNum++)
		{
			//	ボタンの選択非選択の動的な色の変化
			PauseButton[ButtonNum].UpdateBlend();

			//　ボタンが選択中だったら
			if (PauseButton[ButtonNum].ButtonNo == SelectButton)
			{
				//　ボタン選択中のフラグをtrueにする
				PauseButton[ButtonNum].Valid = true;
			}

			//　ボタンが選択中じゃなかったら
			else
			{
				//　ボタン選択中のフラグをfalseにする
				PauseButton[ButtonNum].Valid = false;
			}
		}

		//　DOWNキー
		if (pPauseOperation->GetOperation(OPERATION_CATEGORY::SelectDown))
		{
			pPauseSE->SoundFinal(SOUND_NAME::Select);			//	効果音の停止
			pPauseSE->SoundPlay(SOUND_NAME::Select);			//	効果音の再生

			SelectButton++;										//　次の選択ボタンへ

			//　カーソルが最後の選択肢のとき
			if (SelectButton >= PAUSEBUTTON::PauseLength)
			{
				//　カーソルが1番最初の選択肢にいく
				SelectButton = 0;
			}
		}

		//　UPキー
		if (pPauseOperation->GetOperation(OPERATION_CATEGORY::SelectUP))
		{
			pPauseSE->SoundFinal(SOUND_NAME::Select);			//	効果音の停止
			pPauseSE->SoundPlay(SOUND_NAME::Select);			//	効果音の再生
			SelectButton--;										//　1個前の選択ボタンへ

			//　カーソルが最初の選択肢のとき
			if (SelectButton < 0)
			{
				//　カーソルが1番最後の選択肢にいく
				SelectButton = PAUSEBUTTON::PauseLength - 1;
			}
		}


		//	決定ボタン
		if (pPauseOperation->GetOperation(OPERATION_CATEGORY::SelectEnter))
		{
			pPauseSE->SoundFinal(SOUND_NAME::Enter);			//	効果音の停止
			pPauseSE->SoundPlay(SOUND_NAME::Enter);				//	効果音の再生
			//　1ゲームに戻る
			//　2リトライ
			//　3設定画面
			//　4タイトル

			if (SelectButton == PAUSEBUTTON::Option)
			{
				PauseOption.Initia();							//	設定画面初期化
			}

			return (SelectButton + 1);							//　選択されたボタンの処理を行う
		}


	}
	return 0;												//　処理をしない
}

//	一時停止画面の表示処理
void PauseSG::Draw()
{
	if (OptionFlag == true)
	{
		PauseOption.Draw();
	}

	else
	{
		// シーン内の描画処理を行う
		DrawRotaGraph2(											//	背景の描画
			GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 - 64		//　画面上での画像の中心のX座標
			, WIN_PL_WIDTH / 4, WIN_PL_HEIGHT / 4				//　画面上での画像の中心のY座標
			, 3.5, 0											//	サイズ, 角度
			, *pPauseBackGrahandle, false, false);				//	表示する画像, 表示する画像の透過, 反転

		int Tin = 4;											//　文字の太さ

		const char* TextString[PAUSEBUTTON::PauseLength] =		//	テキストの内容 : Back
		{
			{"            Back"},
			{"            Retry"},
			{"            Option"},
			{"      Select"}
		};

		//　ボタンの数だけ繰り返す
		for (int Num = 0; Num < PAUSEBUTTON::PauseLength; Num++)
		{
			//	選択ボタンの表示
			SelectButtonDraw(Num, TextString[Num]);
		}
	}
}

//	選択ボタンの表示
void PauseSG::SelectButtonDraw(int FontNo, const char* pText)
{
	//　ボタンの表示処理
	PauseButton[FontNo].Draw(false);

	//　選択中
	if (PauseButton[FontNo].Valid)
	{
		DrawStringToHandle(
			PauseButton[FontNo].PosX						//　文字列を描画する起点座標(X座標)
			, PauseButton[FontNo].PosY + 1					//　文字列を描画する起点座標(Y座標)
			, pText, PauseButton[FontNo].ColorBase			//　描画する文字列のポインタ, 文字の色
			, *pPauseFont[FONT_SIZE::Normal]				//　描画する文字列
		);
	}

	//　選択外
	else
	{
		DrawStringToHandle(
			PauseButton[FontNo].PosX						//　文字列を描画する起点座標(X座標)
			, PauseButton[FontNo].PosY + 1					//　文字列を描画する起点座標(Y座標)
			, pText, PauseButton[FontNo].ColorMain			//　描画する文字列のポインタ, 文字の色
			, *pPauseFont[FONT_SIZE::Normal]				//　描画する文字列
		);
	}
}

//　設定画面の処理
void PauseSG::OptionUpdate()
{
	if (OptionFlag == true)
		PauseOption.Update();
}