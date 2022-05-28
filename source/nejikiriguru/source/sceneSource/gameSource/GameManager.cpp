#include "GameManager.h"

//　初期処理
GameManager::GameManager()
{
}

//　読み込んだゲームの画像を配列に分割する
void GameManager::Initia()
{
	GameManagerPL.pPLOperation = pGameManagerOperation;			//　ゲームパッドのポインタ生成
	GameManagerPL.pPLSE = pGameManagerSE;					//　SEのポインタ生成
	int GraphNum = 0;										//　画像の数
	int PieceNum = 0;										//　コマの数

	//	WMR
	for (int Num = 0; Num < GIMMICK_WMR_MAX_NUM; Num++)
	{
		//	画像ハンドルポインタ渡し
		for (GraphNum = 0; GraphNum < GRAPH::WMRLength; GraphNum++)
		{
			WMR[Num].pGimmickGraNo[GraphNum] = &pGameManagerDataLoad->GraphGimmickWMR[GraphNum];
		}
	}

	//	感圧
	for (int Num = 0; Num < GIMMICK_PRES_MAX_NUM; Num++)
	{
		//	画像ハンドルポインタ渡し
		for (GraphNum = 0; GraphNum < GRAPH::PresLength; GraphNum++)
		{
			Pres[Num].pGimmickGraNo[GraphNum] = &pGameManagerDataLoad->GraphGimmickPres[GraphNum];
		}
	}

	//	通電
	for (int Num = 0; Num < GIMMICK_ENER_MAX_NUM; Num++)
	{
		//	画像ハンドルポインタ渡し
		for (GraphNum = 0; GraphNum < GRAPH::EnerLength; GraphNum++)
		{
			Ener[Num].pGimmickGraNo[GraphNum] = &pGameManagerDataLoad->GraphGimmickEner[GraphNum];
		}
	}

	//	針金
	GameManagerMap.pGimmickGraph = &pGameManagerDataLoad->GraphBlockGimmickWire;

	//	パネル
	for (GraphNum = 0; GraphNum < GRAPH::BlockLength; GraphNum++)
	{
		//	画像ハンドルポインタ渡し
		for (PieceNum = 0; PieceNum < 4; PieceNum++)
		{
			GameManagerMap.pMapGraph[GraphNum][PieceNum] = &pGameManagerDataLoad->GraphBlock[GraphNum][PieceNum];
		}
	}

	//	プレイヤー
	for (GraphNum = 0; GraphNum < GRAPH::PLLength; GraphNum++)
	{
		//	画像ハンドルポインタ渡し
		for (PieceNum = 0; PieceNum < 4; PieceNum++)
		{
			GameManagerPL.pPLGraph[GraphNum][PieceNum] = &pGameManagerDataLoad->GraphPL[GraphNum][PieceNum];
		}
	}

	StageNo = pGameManagerDataLoad->StageSet;				//　選択したステージを今のステージにセット

	ChangeStage(StageNo);									//	ステージにセット
	GameTime = GetTickCount();								//	時間の読み込み
	GameStartTime = GameTime;								//	最初の時間設定
}

//	繰り返し実行：ゲームの操作の判断と計算
void GameManager::Update()
{
	GameTime = GetTickCount();								//	時間の読み込み



	switch (GameState)
	{
	case GAMESTATE::Normal:									//	ゲームプレイ中
		UpdateNormal();
		break;

	case GAMESTATE::Clear:									//	ステージクリア中
		UpdateClear();
		break;

	case GAMESTATE::TimeUP:									//	タイムアップ中
		UpdateTimeUP();
		break;

	default:
		break;
	}
}

//	表示処理
void GameManager::Draw()
{
	//	下に行くほど画面手前になる

	//	ゲームの基本描画
	{
		//	背景の描画
		DrawRotaGraph2(GAME_WIN_WIDTH / 2					//　画面上での画像の中心のX座標
			, GAME_WIN_HEIGHT / 2 - 64 * 6 + (StageNo * 32)	//　画面上での画像の中心のY座標
			, WIN_PL_WIDTH / 4								//　画像上での画像の中心のX座標
			, WIN_PL_HEIGHT / 4								//　画像上での画像の中心のY座標
			, 4, PI											//	サイズ, 角度
			, pGameManagerDataLoad->GraphGame[GRAPH::HANDLE::BackGround]	//　表示する画像
			, false, false);								//　表示する画像の透過と反転

		GameManagerMap.DrawMap();							//	マップ描画
		GameManagerPL.Draw();								//	プレイヤー描画

		//	WMRギミックの数だけ表示処理を行う
		for (int WMRNum = 0; WMRNum < GimmiDataNow.StageWMRData.GimmickWMRNum; WMRNum++)
		{
			WMR[WMRNum].Draw();
		}

		//	感圧ギミックの数だけ表示処理を行う
		for (int PresNum = 0; PresNum < GimmiDataNow.StagePresData.GimmickPresNum; PresNum++)
		{
			Pres[PresNum].Draw();
		}

		//	通電ギミックの数だけ表示処理を行う
		for (int EnerNum = 0; EnerNum < GimmiDataNow.StageEnerData.GimmickEnerNum; EnerNum++)
		{
			Ener[EnerNum].Draw();
		}
	}

	DrawUI();												//	UIの描画
}

//	UIの表示処理
void GameManager::DrawUI()
{
	int UIColorWhite = GetColor(250, 250, 250);				//白
	int UIColorRed = GetColor(255, 0, 0);                 //赤
	int UIColorBlack = GetColor(0, 0, 0);					//黒

	//	左側	0 ～ WIN_UI_WIDTH
	{

		float LineTin = 3.0f;								//	UIウィンドウの縁の太さ


		//	UIウィンドウの表示
		pGameManagerUI->BoxLineWindow(0, 0, WIN_UI_WIDTH, GAME_WIN_HEIGHT, UIColorWhite, LineTin);


		//	現在の残り時間表示
		//　残り時間が11秒以上だったら時間を白色で表示
		if (GameRemainingTime > 10)
		{
			pGameManagerUI->TextOutlLineFormat(5 + 425 + (int)LineTin,
				5 + (int)LineTin,
				FONT_SIZE::GameStat, "残り時間:%d", GameRemainingTime, 2, UIColorWhite, UIColorBlack);
		}

		//　残り時間が10秒以内だったら時間を赤色で表示
		else
		{
			pGameManagerUI->TextOutlLineFormat(5 + 425 + (int)LineTin,
				5 + (int)LineTin,
				FONT_SIZE::GameStat, "残り時間:%d", GameRemainingTime, 2, UIColorRed, UIColorBlack);
		}

		//	現在のステージ表示
		pGameManagerUI->TextOutlLineFormat(
			5 + 1295 + (int)LineTin,
			50 - 45 + (int)LineTin,
			FONT_SIZE::GameStat, "ステージ:%d", StageNo, 2, UIColorWhite, UIColorBlack);
	}

	//	右側	WIN_UI_WIDTH + WIN_PL_WIDTH ～ GAME_WIN_WIDTH
	{
		float LineTin = 3.0f;								//	UIウィンドウの縁の太さ

		//	UIウィンドウの表示
		pGameManagerUI->BoxLineWindow(WIN_UI_WIDTH + WIN_PL_WIDTH, 0, WIN_UI_WIDTH, GAME_WIN_HEIGHT, UIColorWhite, LineTin);

	}

	//	GameUIの表示
	pGameManagerGameUI->DrawpadUI(pGameManagerOperation->GamePadReady);

	switch (GameState)
	{
	case GAMESTATE::Normal:									//	ゲームプレイ中
		DrawNormal();
		break;

	case GAMESTATE::Clear:									//	ステージクリア中
		DrawClear();
		break;

	case GAMESTATE::TimeUP:									//	タイムアップ中
		DrawTimeUP();
		break;

	default:
		break;
	}
}

//	ゲームの通常運行時の処理の更新
void GameManager::UpdateNormal()
{
	//	ゲームの基本動作
	{
		GameManagerMap.Update();							//	マップの計算処理を行う
		GameManagerPL.Update();								//	プレイヤーの計算処理を行う



		//感圧ギミックの計算処理を行う
		for (int PresNum = 0; PresNum < GimmiDataNow.StagePresData.GimmickPresNum; PresNum++)
		{
			Pres[PresNum].Update();							//	感圧の繰り返し処理

			//	感圧に触れたかどうか
			if (Pres[PresNum].ReverseCheck(GameManagerPL.PosX, GameManagerPL.PosY, (MAP_CHIP_SIZE - 8) * 2))
			{
				pGameManagerSE->SoundFinal(SOUND_NAME::Switch);			//	効果音の停止
				pGameManagerSE->SoundPlay(SOUND_NAME::Switch);			//	効果音の再生

				pGameManagerSE->SoundFinal(SOUND_NAME::Electricity);	//	効果音の停止
				pGameManagerSE->SoundPlay(SOUND_NAME::Electricity);		//	効果音の再生
			}

			//　同じ色のギミックが動作　
			//　ギミック(黄)
			if (Pres[PresNum].GimmickColor == 1)
			{
				if (Pres[PresNum].GimmickIsValid == true)	//	ギミックのスイッチが有効か
				{
					GimmickYellow = true;					//　ギミックが連動している
					Pres[PresNum].GimmickYellow = true;
				}
				else
				{
					GimmickYellow = false;					//　ギミックが連動していない
					Pres[PresNum].GimmickYellow = false;
				}
			}

			//　ギミック(青)
			if (Pres[PresNum].GimmickColor == 2)
			{
				if (Pres[PresNum].GimmickIsValid == true)	//	ギミックのスイッチが有効か
				{
					GimmickBlue = true;						//　ギミックが連動している
					Pres[PresNum].GimmickBlue = true;
				}
				else
				{
					GimmickBlue = false;					//　ギミックが連動していない
					Pres[PresNum].GimmickBlue = false;
				}
			}

			//　ギミック(白)
			if (Pres[PresNum].GimmickColor == 3)
			{
				if (Pres[PresNum].GimmickIsValid == true)	//	ギミックのスイッチが有効か
				{
					GimmickWhite = true;					//　ギミックが連動している
					Pres[PresNum].GimmickWhite = true;
				}
				else
				{
					GimmickWhite = false;					//　ギミックが連動していない
					Pres[PresNum].GimmickWhite = false;
				}
			}
		}

		//通電ギミックの計算処理を行う
		for (int EnerNum = 0; EnerNum < GimmiDataNow.StageEnerData.GimmickEnerNum; EnerNum++)
		{
			//　フラグの受け渡し
			//　ギミック(黄)
			if (Ener[EnerNum].GimmickColor == 1)
				Ener[EnerNum].GimmickYellow = true;

			//　ギミック(黄)が動いていないとき
			else
				Ener[EnerNum].GimmickYellow = false;

			//　ギミック(青)
			if (Ener[EnerNum].GimmickColor == 2)
				Ener[EnerNum].GimmickBlue = true;

			//　ギミック(青)が動いていないとき
			else
				Ener[EnerNum].GimmickBlue = false;

			//　ギミック(白)
			if (Ener[EnerNum].GimmickColor == 3)
				Ener[EnerNum].GimmickWhite = true;

			//　ギミック(白)が動いていないとき
			else
				Ener[EnerNum].GimmickWhite = false;
		}

		//	WMRギミックの計算処理を行う
		for (int WMRNum = 0; WMRNum < GimmiDataNow.StageWMRData.GimmickWMRNum; WMRNum++)
		{
			//　WMRギミックが全部点灯していないとき
			if (WMR[WMRNum].GimmickColor != 0)
			{
				//　同じ色のフラグをオンにして他の2つのフラグをオフにする
				//　ギミック(黄)のとき
				if (WMR[WMRNum].GimmickColor == 1)
				{
					//　ギミック(黄)が連動
					if (GimmickYellow == true)
					{
						//　ギミック(黄)が起動
						WMR[WMRNum].GimmickIsEnergization = true;

						WMR[WMRNum].GimmickYellow = true;
					}

					//　ギミック(黄)が連動していない
					else
					{
						//　ギミック(黄)を停止
						WMR[WMRNum].GimmickIsEnergization = false;
						WMR[WMRNum].GimmickYellow = false;
					}
				}

				//　ギミック(青)のとき
				if (WMR[WMRNum].GimmickColor == 2)
				{
					//　ギミック(青)が連動
					if (GimmickBlue == true)
					{
						//　ギミック(青)が起動
						WMR[WMRNum].GimmickIsEnergization = true;

						WMR[WMRNum].GimmickBlue = true;
					}

					//　ギミック(青)が連動していない
					else
					{
						//　ギミック(青)を停止
						WMR[WMRNum].GimmickIsEnergization = false;
						WMR[WMRNum].GimmickBlue = false;
					}
				}

				//　ギミック(白)のとき
				if (WMR[WMRNum].GimmickColor == 3)
				{
					//　ギミック(白)が連動
					if (GimmickWhite == true)
					{
						//　ギミック(白)が起動
						WMR[WMRNum].GimmickIsEnergization = true;

						WMR[WMRNum].GimmickWhite = true;
					}

					//　ギミック(白)が連動していない
					else
					{
						//　ギミック(白)を停止
						WMR[WMRNum].GimmickIsEnergization = false;
						WMR[WMRNum].GimmickWhite = false;
					}
				}
			}

			//	プレイヤーがWMRに触れたかどうか
			if (WMR[WMRNum].ReverseMove(&GameManagerPL.PosX, &GameManagerPL.PosY, GameManagerPL.ProgressVec, (MAP_CHIP_SIZE - 8) * 2))
			{
				pGameManagerSE->SoundFinal(SOUND_NAME::WMRdown);		//	効果音の停止
				pGameManagerSE->SoundPlay(SOUND_NAME::WMRdown);			//	効果音の再生
				GameManagerPL.PLAnti(WMR[WMRNum].GimmickVecXorY);		//	プレイヤーの向きを反転
			}
			WMR[WMRNum].Update();							//	WMRの繰り返し処理
		}

		GameManagerPL.SetMove();							//	プレイヤーの動きを反映

		//　プレイヤーのY座標が0よりも下のとき
		if (GameManagerPL.PosY < 0)
		{
			pGameManagerSE->SoundFinal(SOUND_NAME::FootStep);			//　歩く音を停止

			GameState = GAMESTATE::Clear;								//	ステージクリア
			pGameManagerSE->SoundFinal(SOUND_NAME::Gole);				//　ゴール音を停止
			pGameManagerSE->SoundPlay(SOUND_NAME::Gole);				//　ゴール音を再生
		}
	}

	//	ゲーム状況判定
	{
		GameTime = GetTickCount();							//	ゲームの時間を読みこむ

		//	一時停止の時間がある場合時間分加算する
		if (GameStopTime > 0)
		{
			GameStartTime += GameStopTime;
			GameStopTime = 0;
		}

		//	残り時間計算:60
		GameRemainingTime = 60 - ((GameTime - GameStartTime) / 1000);


		//	残りの時間がなくなったら
		if (GameRemainingTime <= 0)
		{
			pGameManagerSE->SoundFinal(SOUND_NAME::FootStep);			//　歩く音を停止

			GameState = GAMESTATE::TimeUP;								//	タイムアップ
			pGameManagerSE->SoundFinal(SOUND_NAME::GameOver);			//　ゲームオーバー音を停止
			pGameManagerSE->SoundPlay(SOUND_NAME::GameOver);			//　ゲームオーバー音を再生
		}
	}
}

//	ステージクリア時の処理の更新
void GameManager::UpdateClear()
{
	//	状況の読み込み
	if (MoveFlag == false)
	{
		//　最終ステージではない ＆ まだ次のステージが解放されていなかったら
		if (StageNo < MAP_NUM - 1 && pGameManagerDataLoad->MaxStageNo < StageNo + 1)
		{
			pGameManagerDataLoad->MaxStageNo = (StageNo + 1);			//　次のステージを解放
		}

		GameStartTime = GameTime;							//	最初の時間設定
		MoveFlag = true;									//	Clear状態を有効
	}

	//	スペースキー(Bボタン)か0.5秒後
	if (0.5f < (float)(GameTime - GameStartTime) / 1000.0f
		&& (pGameManagerOperation->GetOperation(OPERATION_CATEGORY::SelectEnter)))
	{
		//　ゴール音が鳴り終わっているかどうか
		if (pGameManagerSE->CheckSE(SOUND_NAME::Gole) == false)
		{
			MoveFlag = false;								//	Clear状態を無効次のステージへ
		}

	}

	//	状態を続けないかクリア状況の10秒後
	if (MoveFlag == false)
	{
		//	ステージ数が限界
		if (StageNo >= MAP_NUM - 1)
		{
			LastStageClear = true;							//　最終ステージの場合 Flagをtrue
			return;
		}
		ChangeStage(StageNo + 1);							//　次のステージへ
	}

}

//	タイムアップ時の処理の更新
void GameManager::UpdateTimeUP()
{

	//	状況の読み込み
	if (MoveFlag == false)
	{
		GameStartTime = GameTime;							//	最初の時間設定
		MoveFlag = true;									//	Clear状態を有効
	}

	//	スペースキー(Bボタン)か0.5秒後
	if (0.5f < (float)(GameTime - GameStartTime) / 1000.0f
		&& (CheckHitKey(KEY_INPUT_SPACE) ||
			pGameManagerOperation->GetOperation(OPERATION_CATEGORY::SelectEnter)))
	{
		MoveFlag = false;									//	Clear状態を無効次のステージへ
	}

	//	状態を続けないかタイムアップ状況の10秒後
	if (MoveFlag == false || 10 < (GameTime - GameStartTime) / 1000)
	{
		ChangeStage(StageNo);								//　リトライ状態にする
		MoveFlag = false;									//　プレイヤーの動きを止める
	}
}

//	ゲームの通常運行時の表示処理
void GameManager::DrawNormal()
{

}

//	ステージクリア時の表示処理
void GameManager::DrawClear()
{
	int Tin = 3;											//　文字の太さ

	//	画面を明るくする
	pGameManagerUI->DarkenScreen(WIN_UI_WIDTH, 0, WIN_PL_WIDTH, GAME_WIN_HEIGHT, GetColor(255, 255, 255), 160);


	//	真ん中にステージクリアと出す
	pGameManagerUI->TextOutlLine(
		GAME_WIN_WIDTH / 2, (GAME_WIN_HEIGHT / 2) - 100,	//　X座標, Y座標
		FONT_SIZE::Big, "ステージクリア", 7, Tin,			//　フォントサイズ, ステージクリア, 文字数, 文字の太さ
		GetColor(250, 250, 250), GetColor(0, 0, 0));		//　文字の色, アウトラインの色

	//	ステージ数が限界
	if (StageNo >= MAP_NUM - 1)
	{
		//　ゴール音が停止すると
		if (pGameManagerSE->CheckSE(SOUND_NAME::Gole) == false)
		{
			//	「Bボタンで次のシーンへ」と表示する
			pGameManagerUI->TextBoxWindowCenter(
				GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 + 40, 10,		//　X座標, Y座標, 文字数
				GetColor(255, 255, 255), GetColor(0, 0, 0),				//　文字の色, WindowColor
				4.0, Normal, "\"　　\"で次のシーンへ");					//　WindowLineの太さ, 文字の種類, テキスト


			//	ゲームパッドが有効あれば
			if (pGameManagerOperation->GamePadReady == true)
			{

				//　BボタンのUIを表示
				pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 50, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::Button);
				pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 50, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::B);
			}
			//	そうでなければ
			else
			{
				//	エンターキー
				pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 50, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::EnterKey);
				pGameManagerUI->TextOutlLine((GAME_WIN_WIDTH / 2) - 50 + 18, GAME_WIN_HEIGHT / 2 + 40 - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
			}
		}
	}

	//	クリア状況の1秒後
	else if (MoveFlag == true && pGameManagerSE->CheckSE(SOUND_NAME::Gole) == false)
	{
		//	「Bボタンで次へ」と表示する
		pGameManagerUI->TextBoxWindowCenter(
			GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 + 40, 6,			//　X座標, Y座標, 文字数
			GetColor(255, 255, 255), GetColor(0, 0, 0),					//　文字の色, WindowColor
			4.0, Normal, "\"　　\"で次へ");								//　WindowLineの太さ, 文字の種類, テキスト



		//	ゲームパッドが有効あれば
		if (pGameManagerOperation->GamePadReady == true)
		{
			//　BボタンのUIを表示
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::Button);
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::B);
		}
		//	そうでなければ
		else
		{
			//	エンターキー
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::EnterKey);
			pGameManagerUI->TextOutlLine((GAME_WIN_WIDTH / 2) - 20 + 18, GAME_WIN_HEIGHT / 2 + 40 - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
		}
	}
}

//	タイムアップ時の表示処理
void GameManager::DrawTimeUP()
{
	int Tin = 3;											//　文字の太さ

	//	画面を暗くする
	pGameManagerUI->DarkenScreen(WIN_UI_WIDTH, 0, WIN_PL_WIDTH, GAME_WIN_HEIGHT, GetColor(0, 0, 0), 200);


	//	真ん中にタイムアップと出す
	pGameManagerUI->TextOutlLine(
		GAME_WIN_WIDTH / 2, (GAME_WIN_HEIGHT / 2) - 100,	//　X座標, Y座標
		FONT_SIZE::Big, "タイムアップ", 6, Tin,				//　フォントサイズ, ステージクリア, 文字数, 文字の太さ
		GetColor(150, 0, 0), GetColor(255, 0, 0));			//　文字の色, アウトラインの色

	//	クリア状況の1秒後
	if (MoveFlag == true && 2 < (GameTime - GameStartTime) / 1000)
	{
		//	「Bボタンで次へ」と表示する
		pGameManagerUI->TextBoxWindowCenter(
			GAME_WIN_WIDTH / 2, GAME_WIN_HEIGHT / 2 + 40, 6,			//　X座標, Y座標, 文字数
			GetColor(255, 255, 255), GetColor(0, 0, 0),					//　文字の色, WindowColor
			4.0, Normal, "\"　　\"で次へ");								//　WindowLineの太さ, 文字の種類, テキスト


		//	ゲームパッドが有効あれば
		if (pGameManagerOperation->GamePadReady == true)
		{
			//　BボタンのUIを表示
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::Button);
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::B);
		}
		//	そうでなければ
		else
		{
			//	エンターキー
			pGameManagerGameUI->Draw((GAME_WIN_WIDTH / 2) - 20, GAME_WIN_HEIGHT / 2 + 40, 2, UI_PARTS::EnterKey);
			pGameManagerUI->TextOutlLine((GAME_WIN_WIDTH / 2) - 20 + 18, GAME_WIN_HEIGHT / 2 + 40 - 12, FONT_SIZE::Normal, "Enter", 5, 1, GetColor(255, 255, 255), GetColor(0, 0, 0));
		}
	}
}

//	クリア時などにステージの変換
void GameManager::ChangeStage(int NextStageNo)
{
	StageNo = NextStageNo;									//	ステージの変更

	//　CSVファイルの読み込み
	GameManagerCSV.StageDataLoad(StageNo, &MapNow, &GimmiDataNow);

	GimmickYellow = false;                                  //　ギミック(黄)が連動してるか
	GimmickBlue = false;									//　ギミック(青)が連動してるか
	GimmickWhite = false;                                   //　ギミック(白)が連動してるか

	GameManagerMap.DataRoad(MapNow, StageNo);				//	マップのデータ読み込み

	Vector2D PLPosSet = Vector2D(96, 928);					//　ゲーム開始時のプレイヤーの座標

	//　最初のステージのとき
	if (StageNo == 0)
	{
		PLPosSet.Set(96, 200);								//　プレイヤーは(96, 200)の座標からスタート
	}

	GameManagerPL.DataRoad(MapNow, PLPosSet);				//	マップのデータ読み込み
	GameManagerPL.ProgressVec.X = 0.1f;						//　ゲーム開始時のプレイヤーの向きを右向きにする

	//　WMRギミックの数だけ繰り返し処理を行う
	for (int Num = 0; Num < GimmiDataNow.StageWMRData.GimmickWMRNum; Num++)
	{
		//	データの読み込み
		WMR[Num].DataRoad(
			GimmiDataNow.StageWMRData.GimmickWMR[Num][0],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][1],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][2],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][3],
			GimmiDataNow.StageWMRData.GimmickWMR[Num][4]);

		//　ゲーム開始時にギミックのフラグを全てオンにする
		if (WMR[Num].GimmickColor == 0) { WMR[Num].GimmickIsEnergization = true; }
	}

	//　感圧ギミックの数だけ繰り返し処理を行う
	for (int Num = 0; Num < GimmiDataNow.StagePresData.GimmickPresNum; Num++)
	{
		//	データの読み込み
		Pres[Num].DataRoad(
			GimmiDataNow.StagePresData.GimmickPres[Num][0],
			GimmiDataNow.StagePresData.GimmickPres[Num][1],
			GimmiDataNow.StagePresData.GimmickPres[Num][2],
			GimmiDataNow.StagePresData.GimmickPres[Num][3],
			GimmiDataNow.StagePresData.GimmickPres[Num][4]);
	}

	//　通電ギミックの数だけ繰り返し処理を行う
	for (int Num = 0; Num < GimmiDataNow.StageEnerData.GimmickEnerNum; Num++)
	{
		//	データの読み込み
		Ener[Num].DataRoad(
			GimmiDataNow.StageEnerData.GimmickEner[Num][0],
			GimmiDataNow.StageEnerData.GimmickEner[Num][1],
			GimmiDataNow.StageEnerData.GimmickEner[Num][2],
			GimmiDataNow.StageEnerData.GimmickEner[Num][3],
			GimmiDataNow.StageEnerData.GimmickEner[Num][4],
			GimmiDataNow.StageEnerData.GimmickEner[Num][5]);
	}



	GameTime = GetTickCount();								//	時間の読み込み
	GameStartTime = GameTime;								//	最初の時間設定
	GameState = GAMESTATE::Normal;							//	通常運行
	GameStopTime = 0;										//　ゲームを止めた時間を0にする
	GameRemainingTime = 60;									//	制限時間
	pGameManagerSE->SoundFinal(SOUND_NAME::Gole);			//	止める
	pGameManagerSE->SoundFinal(SOUND_NAME::GameOver);		//	止める
}