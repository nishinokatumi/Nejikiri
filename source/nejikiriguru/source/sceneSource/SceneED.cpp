#include "SceneED.h"
#include "SceneSelect.h"

/*
ゲームのエンディング画面クラス
	エンディングアニメーション
*/

//	初期設定
SceneED::SceneED()
{

}

//	初期処理
void SceneED::Initia()
{
	ColorBase = GetColor(0, 0, 0);							//	色を設定(黒)
	ColorMain = GetColor(255, 255, 255);					//	色を設定(白)
	ColorSele = GetColor(255, 255, 0);						//	色を設定(黄色)

	//	背景の1枚目の初めの座標を設定
	BackPos1 = { GAME_WIN_WIDTH / 2,(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y };

	//	背景の2枚目の初めの座標を設定
	BackPos2 = { GAME_WIN_WIDTH / 2 - ED_BACK_MAX_X ,(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y };

	//	背景の3枚目の初めの座標を設定
	BackPos3 = { GAME_WIN_WIDTH / 2 + (-ED_BACK_MAX_X * 2) ,(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y };

	//	MAPの位置の原点を設定
	MapPos = { -ED_BACK_MAX_X * 12 ,-ED_BACK_MAX_Y * 12 };
}

//	最終処理
void SceneED::Final()
{

}

//	更新処理
SceneBase* SceneED::Update()
{
	//	計算処理を行う
	SceneBase* pNextScene = this;

	//	現在のシーンへ
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
				BaseUpdate();								//	更新処理の内容
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
			pNextScene = pNextSceneSave;
		}
	}

	return pNextScene;
}

//	更新処理の内容
void SceneED::BaseUpdate()
{
	//	Escボタンかstartボタンが押されたら
	if (pSceneOperation->GetOperation(OPERATION_CATEGORY::SelectMenu))
	{
		pNextSceneSave = new SceneSelect();					//	選択画面に変更
		TransitionSet = false;								//	更新処理を停止する
	}

	//	現在のコマ数が1200よりも下の際
	if (EDTime < ED_SIZE)
	{
		EDTime++;											//	エンディングタイムをカウントアップ

		//	現在のコマ数が1200よりも上の際
		if (EDTime > ED_SIZE)
		{
			EDTime = ED_SIZE;								//	現在のコマ数をマックス(1200)にする
		}
	}

	//	現在のコマ数が1の際
	if (EDTime == 1)
	{
		pSceneSE->SoundPlay(SOUND_NAME::Wind);				//	音の再生(風の音BGM)
	}


	//	線形補間のアニメーション
	{
		//	背景の1枚目の初めの座標を設定
		KeyFrame(
			{	//	最初の座標 
				GAME_WIN_WIDTH / 2,													//	X座標
				(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y },							//	Y座標
			{	//	最終座標
				GAME_WIN_WIDTH / 2,													//	X座標
				(GAME_WIN_HEIGHT / 2) + (ED_BACK_MAX_Y* BackPosReverse) },			//	Y座標
				&BackPos1,
				0, 500);										//	開始コマ数と最終コマ数

			//	背景の2枚目の初めの座標を設定
		KeyFrame(
			{	//	最初の座標
				GAME_WIN_WIDTH / 2 - ED_BACK_MAX_X ,								//	X座標
				(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y },							//	Y座標
			{	//	最終座標
				GAME_WIN_WIDTH / 2 + (ED_BACK_MAX_X * 4)* BackPosReverse ,			//	X座標
				(GAME_WIN_HEIGHT / 2) + (ED_BACK_MAX_Y)* BackPosReverse },			//	Y座標
				&BackPos2,
				0, 500);										//	開始コマ数と最終コマ数

			//	背景の2枚目の初めの座標を設定
		KeyFrame(
			{	//	最初の座標
				GAME_WIN_WIDTH / 2 + (-ED_BACK_MAX_X * 2) ,							//	X座標
				(GAME_WIN_HEIGHT / 2) - ED_BACK_MAX_Y },							//	Y座標
			{	//	最終座標
				GAME_WIN_WIDTH / 2 + (ED_BACK_MAX_X * 4 * 2)* BackPosReverse ,		//	X座標
				(GAME_WIN_HEIGHT / 2) + (ED_BACK_MAX_Y * BackPosReverse) },			//	Y座標
				&BackPos3,
				0, 500);										//	開始コマ数と最終コマ数

			//	MAPの位置の原点を設定
		KeyFrame(
			{	//	最初の座標
				-ED_BACK_MAX_X * 8 ,												//	X座標
				-ED_BACK_MAX_Y * 8 },												//	Y座標
			{	//	最終座標
				WIN_UI_WIDTH,														//	X座標
				WIN_UI_HEIGHT },													//	Y座標
				&MapPos,
				400, 500);										//	開始コマ数と最終コマ数

			//	WMRの大きさを設定
		KeyFrameFloat(
			1,												//	初期値
			100,											//	最終値
			&EDWMRScale,
			600, 700);										//	開始コマ数と最終コマ数

		//	WMRの濃さを設定
		KeyFrameFloat(
			1,												//	初期値
			0,												//	最終値
			&EDWMRAlpha,
			750, 810);										//	開始コマ数と最終コマ数

		//	クリア文字の位置を設定
		KeyFrame(
			{	//	最初の座標
				0,																	//	X座標
				-100 },																//	Y座標
			{	//	最終座標
				0,																	//	X座標
				GAME_WIN_HEIGHT / 2 },												//	Y座標
				&GameClearPos,
				800, 850);										//	開始コマ数と最終コマ数
	}

	//	現在のコマ数が750以上で処理
	if (EDTime > 750)
	{
		BackAngle = 0;										//	背景画像の角度を正しい向きに
		BackPosReverse = -1;								//	背景画像の位置を正しい場所に
	}
}

//	表示処理
void SceneED::Draw()
{
	//	動く背景演出:縦のみ
	DrawRotaGraph2(
		BackPos1.X, BackPos1.Y,	//	背景の描画
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackSky], false, false);

	//	動く背景演出:遅めに移動
	DrawRotaGraph2(
		BackPos2.X, BackPos2.Y, //	背景の描画
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackBase], true, true);

	//	動く背景演出:遅めに移動
	DrawRotaGraph2(
		(BackPos2.X - (BACK_GRAPH_SIZE_X * 4 * BackPosReverse)), BackPos2.Y, //	背景の描画
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackBase], true, true);


	//	動く背景演出:早く1
	DrawRotaGraph2(
		BackPos3.X, BackPos3.Y, //	背景の描画
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackMove], true, true);

	//	動く背景演出:早く2
	DrawRotaGraph2(
		(BackPos3.X - (BACK_GRAPH_SIZE_X * 4 * BackPosReverse)), BackPos3.Y, //	背景の描画
		BACK_GRAPH_SIZE_X / 2, BACK_GRAPH_SIZE_Y / 2,
		4, PI * ((float)BackAngle / 2.0f),						//	4倍
		pSceneDataLoad->GraphGame[GRAPH::HANDLE::BackMove], true, true);

	//	現在のコマ数が750よりも下で処理する
	if (EDTime < 750)
	{
		//	画面右から塔が映るように5つ重ねて移動させて表示する
		DrawMap(MapPos.X, MapPos.Y, 0);							//	反転用の一番下のマップ表示
		for (int DrawMapNum = 1; DrawMapNum < 5; DrawMapNum++)
		{
			//	同じマップを1マップずつ耐えにずらして4回表示
			DrawMap(MapPos.X, MapPos.Y + (MAP_CHIP_SIZE * 2) * (15 * DrawMapNum), 1);
		}

		//	待機モーションのプレイヤーを表示する
		DrawRotaGraph2(
			MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
			MapPos.Y + (MAP_CHIP_SIZE * 2) * 15,
			16, 32,
			2, 0,
			pSceneDataLoad->GraphPL[GRAPH::PL_GRAPH::Wait][PLGraph], true, true);


		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, (int)(EDWMRAlpha * 255));	//	ブレンドモードを変更して変化する値(だんだん薄く)にする

		//	エンディング用のWMRの表示
		DrawRotaGraph2(
			MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
			MapPos.Y + (MAP_CHIP_SIZE * 2) * 11,
			32, 32,
			2 * EDWMRScale, 0,								//	4倍
			pSceneDataLoad->GraphEDWMR, true, true);

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);		//	ブレンドモードを通常に直す
	}

	//	現在のコマ数が750以上で処理する
	else
	{
		DrawMap(MapPos.X, MapPos.Y, 2);						//	反転したマップの表示
		DrawMap(MapPos.X, MapPos.Y - (MAP_CHIP_SIZE * 2) * 15, 1);	//	世界丸ごと反転したように見せるためマップの一つ上に表示

		//	エンディング用のWMRの濃さが0出ないときに
		if (EDWMRAlpha != 0)
		{
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, (int)(EDWMRAlpha * 255));	//	ブレンドモードを変更して変化する値(だんだん薄く)にする

			//	エンディング用のWMRの表示
			DrawRotaGraph2(
				MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
				MapPos.Y + (MAP_CHIP_SIZE * 2) * 11,
				32, 32,
				2 * EDWMRScale, 0,							//	4倍
				pSceneDataLoad->GraphEDWMR, true, true);

			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);	//	ブレンドモードを通常に直す
		}

		pSceneUI->TextOutlLine(								//	ゲームクリアと上から下ろして表示
			GAME_WIN_WIDTH / 2,								//	画面中央
			GameClearPos.Y,									//	変化する値
			FONT_SIZE::Big, "ゲームクリア", 6,				//	大きいサイズのフォントゲームクリアと表示
			4, ColorMain, ColorBase);						//	アウトラインの幅と色の指定

		//	待機モーションのプレイヤーを表示する
		DrawRotaGraph2(
			MapPos.X + (MAP_CHIP_SIZE * 2) * 10,
			MapPos.Y + (MAP_CHIP_SIZE * 2) * 12,
			16, 32,
			2, 0,
			pSceneDataLoad->GraphPL[GRAPH::PL_GRAPH::Move][0], true, true);

	}



	//	現在のシーンへ
	if (TransitionSet == true)
	{
		//	フェードイン
		if (SceneTransition > 0)
		{
			pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
				GetColor(0, 0, 0), SceneTransition);
		}

	}
	//	次のシーンへ
	else
	{
		//	フェードアウト
		pSceneUI->DarkenScreen(0, 0, GAME_WIN_WIDTH, GAME_WIN_HEIGHT,
			GetColor(0, 0, 0), SceneTransition);
	}
}

//	マップの表示処理
void SceneED::DrawMap(int MapPosX, int MapPosY, int MapNum)
{
	//	マップの描画
	{
		//	マップデータのPosY軸の上から下まで
		for (int PosY = 0; PosY < MAP_HEIGHT; PosY++)
		{
			//	マップデータのPosX軸の左から右まで
			for (int PosX = 0; PosX < MAP_WIDTH; PosX++)
			{
				//	ゴールの針金
				if (PosY == 0 && PosX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	表示する右上のX座標
						, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)							//	表示する右上のY座標
						, 2, 0															//	表示する画像の中心位置()
						, 2, -PI / 2													//	サイズと角度
						, pSceneDataLoad->GraphBlockGimmickWire							//	表示する画像
						, true, false);													//	表示する画像の透過と反転
				}

				//	ゴールの針金
				if (PosY == MAP_HEIGHT - 1 && PosX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	表示する右上のX座標
						, (PosY + 1) * MAP_CHIP_SIZE * 2 + (MapPosY)					//	表示する右上のY座標
						, 2, 0															//	表示する画像の中心位置()
						, 2, -PI / 2													//	サイズと角度
						, pSceneDataLoad->GraphBlockGimmickWire							//	表示する画像
						, true, false);													//	表示する画像の透過と反転
				}



				// ブロックの表示
				if (NowMapData[MapNum].BlockData[PosY][PosX] == GRAPH::BLOCK::Pne)
				{

					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	表示する右上のX座標
						, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)							//	表示する右上のY座標
						, 0, 0															//	表示する画像の中心位置()
						, 2, 0															//	サイズと角度
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::Pne - 1][NowMapData[MapNum].MapPanelNo]	//	表示する画像
						, true, false);													//	表示する画像の透過と反転


					//	ブロックの隣を判断し補助部品を付ける
					{
						if (PosX < MAP_WIDTH - 1 && NowMapData[MapNum].BlockData[PosY][PosX + 1] != 1)	//	ブロック右部
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	表示する右上のX座標
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	表示する右上のY座標
								, 0, 0						//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][3]	//	表示する画像
								, true, false);											//	表示する画像の透過と反転
						}

						if (PosX > 0 && NowMapData[MapNum].BlockData[PosY][PosX - 1] != 1)	//	ブロック右部
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	表示する右上のX座標
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	表示する右上のY座標
								, 0, 0													//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][2]	//	表示する画像
								, true, false);												//	表示する画像の透過と反転
						}

						if (PosY < MAP_HEIGHT - 1 && NowMapData[MapNum].BlockData[PosY + 1][PosX] != 1)	//	ブロック上部
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	表示する右上のX座標
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	表示する右上のY座標
								, 0, 0													//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][1]	//	表示する画像
								, true, false);												//	表示する画像の透過と反転
						}

						if (PosY > 0 && NowMapData[MapNum].BlockData[PosY - 1][PosX] != 1)	//	ブロック下部
						{
							DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)			//	表示する右上のX座標
								, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)					//	表示する右上のY座標
								, 0, 0													//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][0]	//	表示する画像
								, true, false);											//	表示する画像の透過と反転
						}
					}
				}
				else if (NowMapData[MapNum].BlockData[PosY][PosX] == GRAPH::BLOCK::Wal)
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	表示する右上のX座標
						, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)							//	表示する右上のY座標
						, 0, 0															//	表示する左下の座標
						, 2, 0															//	サイズと角度
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::Wal - 1][NowMapData[MapNum].MapWallNo]	//	表示する画像
						, true, false);													//	表示する画像の透過と反転

					//	ブロック右左部
					{
						DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)				//	表示する右上のX座標
							, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)						//	表示する右上のY座標
							, 0, 0														//	表示する左下の座標
							, 2, 0														//	サイズと角度
							, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][2]	//	表示する画像
							, true, false);												//	表示する画像の透過と反転

						DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)				//	表示する右上のX座標
							, PosY * MAP_CHIP_SIZE * 2 + (MapPosY)						//	表示する右上のY座標
							, 0, 0														//	表示する左下の座標
							, 2, 0														//	サイズと角度
							, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][3]	//	表示する画像
							, true, false);												//	表示する画像の透過と反転
					}
				}
			}
		}

		//	マップデータのPosY軸の上から下まで
		for (int PosY = 0; PosY < MAP_HEIGHT + 2; PosY += 16)
		{
			//	マップデータのPosX軸の左から右まで
			for (int PosX = 0; PosX < MAP_WIDTH; PosX += 19)
			{
				DrawRotaGraph2(PosX* MAP_CHIP_SIZE * 2 + (MapPosX)						//	表示する右上のX座標
					, PosY* MAP_CHIP_SIZE * 2 + ((MapPosY)-MAP_CHIP_SIZE * 2)			//	表示する右上のY座標
					, 0, 0																//	表示する左下の座標
					, 2, 0																//	サイズと角度
					, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::Wal - 1][NowMapData[MapNum].MapWallNo]	//	表示する画像
					, true, false);														//	表示する画像の透過と反転

				//	ブロック右左部
				{
					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	表示する右上のX座標
						, PosY * MAP_CHIP_SIZE * 2 + ((MapPosY)-MAP_CHIP_SIZE * 2)		//	表示する右上のY座標
						, 0, 0															//	表示する左下の座標
						, 2, 0															//	サイズと角度
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][2]		//	表示する画像
						, true, false);													//	表示する画像の透過と反転

					DrawRotaGraph2(PosX * MAP_CHIP_SIZE * 2 + (MapPosX)					//	表示する右上のX座標
						, PosY * MAP_CHIP_SIZE * 2 + ((MapPosY)-MAP_CHIP_SIZE * 2)		//	表示する右上のY座標
						, 0, 0															//	表示する左下の座標
						, 2, 0															//	サイズと角度
						, pSceneDataLoad->GraphBlock[GRAPH::BLOCK::AuxiMate - 1][3]		//	表示する画像
						, true, false);													//	表示する画像の透過と反転
				}

			}
		}
	}
}