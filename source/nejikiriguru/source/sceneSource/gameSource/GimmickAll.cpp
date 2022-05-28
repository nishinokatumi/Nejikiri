#include "GimmickAll.h"
#include "DxLib.h"

/*------------------------------WMR-------------------------------*/

//　初期処理
GimmickWMR::GimmickWMR()
{

}

//	ギミックの更新処理
void GimmickWMR::Update()
{
	//　WMRのマーク部分の点滅
	GimmickLightNum += GimmickConvequan;

	if (GimmickLightNum > 255 || GimmickLightNum <= 100)
	{
		//　点滅させるために色の変化量を反転させる
		GimmickConvequan = -GimmickConvequan;
	}

	//　判定の引継ぎ
	if (GimmickIsValidOld != GimmickIsValid)
	{
		GimmickIsValidOld = GimmickIsValid;
	}
}

//	ギミックの表示処理
void GimmickWMR::Draw()
{
	float Angle = 0;										//	表示角度

	//	ギミックが縦方向
	if (GimmickVecXorY == 1)
	{
		//	延長部品が必要な時
		if (GimmickSize > 1)
		{
			//	延長部品の表示繰り返し
			for (int size_num = 0; size_num < GimmickSize; size_num++)
			{
				DrawRotaGraph2(
					(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH					//　画面上での画像の中心のX座標
					, ((int)GimmickPos.Y + size_num) * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT	//　画面上での画像の中心のY座標
					, 4, 0																	//　画像上での画像の中心のX座標, Y座標
					, 2, 0																	//	サイズと角度
					, *pGimmickGraNo[GRAPH::WMR_PARTS::Extend]								//	表示する画像
					, true, false);															//	表示する画像の透過と反転
			}

			//	末端部品の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH						//　画面上での画像の中心のX座標
				, ((int)GimmickPos.Y + GimmickSize) * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT		//　画面上での画像の中心のY座標
				, 6, 0																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	末端部品の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH						//　画面上での画像の中心のX座標
				, ((int)GimmickPos.Y) * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT					//　画面上での画像の中心のY座標
				, 6, 0																		//　画像上での画像の中心のX座標, Y座標
				, 2, 0																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転
		}

		//	基本部品の表示
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//　画面上での画像の中心のX座標
			, (int)GimmickCenterPos.Y + WIN_UI_HEIGHT										//　画面上での画像の中心のY座標
			, 6, 16																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRBase]										//	表示する画像
			, true, false);																	//	表示する画像の透過と反転

		//　通電しているかどうか
		if (GimmickIsEnergization == true)
		{
			//　ギミックの色とチャンネルの色が一緒かどうか
			if ((GimmickColor == 0) ||
				(GimmickColor == 1 && GimmickYellow == true) ||
				(GimmickColor == 2 && GimmickBlue == true) ||
				(GimmickColor == 3 && GimmickWhite == true))
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, GimmickLightNum);						//　画像のグラフィックを濃くする

				//	発行部品の表示
				DrawRotaGraph2(
					(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH					//　画面上での画像の中心のX座標
					, (int)GimmickCenterPos.Y + WIN_UI_HEIGHT								//　画面上での画像の中心のY座標
					, 3, 10																	//　画像上での画像の中心のX座標, Y座標
					, 2, Angle																//	サイズと角度
					, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRLight]							//	表示する画像
					, true, false);															//	表示する画像の透過と反転

				SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);								//　普通の画像にする
			}
		}
	}

	//	ギミックが横方向
	else
	{
		Angle = -PI / 2.0f;									//	表示角度を横に

		//	延長部品が必要な時
		if (GimmickSize > 1)
		{
			//	延長部品の表示繰り返し
			for (int size_num = 0; size_num < GimmickSize; size_num++)
			{
				DrawRotaGraph2(
					((int)GimmickPos.X + size_num) * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH		//　画面上での画像の中心のX座標
					, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT					//　画面上での画像の中心のY座標
					, 4, 0																	//　画像上での画像の中心のX座標, Y座標
					, 2, -PI / 2.0															//	サイズと角度
					, *pGimmickGraNo[GRAPH::WMR_PARTS::Extend]								//	表示する画像
					, true, false);															//	表示する画像の透過と反転
			}

			//	末端部品の表示
			DrawRotaGraph2(
				((int)GimmickPos.X + GimmickSize) * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH		//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//　画面上での画像の中心のY座標
				, 6, 0																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI / 2.0f																//	サイズと角度
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	末端部品の表示
			DrawRotaGraph2(
				((int)GimmickPos.X) * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH						//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//　画面上での画像の中心のY座標
				, 6, 0																		//　画像上での画像の中心のX座標, Y座標
				, 2, -PI / 2.0f																//	サイズと角度
				, *pGimmickGraNo[GRAPH::WMR_PARTS::EndPoint]								//	表示する画像
				, true, false);
		}

		//	基本部品の表示
		DrawRotaGraph2(
			(int)GimmickCenterPos.X + WIN_UI_WIDTH										//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 6, 16																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRBase]										//	表示する画像		
			, true, false);																	//	表示する画像の透過と反転

		//　通電しているかどうか
		if (GimmickIsEnergization == true)
		{
			//　ギミックの色とチャンネルの色が一緒かどうか
			if ((GimmickColor == 0) ||
				(GimmickColor == 1 && GimmickYellow == true) ||
				(GimmickColor == 2 && GimmickBlue == true) ||
				(GimmickColor == 3 && GimmickWhite == true))
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, GimmickLightNum);						//　画像のグラフィックを濃くする

				//	発行部品の表示
				DrawRotaGraph2(
					(int)GimmickCenterPos.X + WIN_UI_WIDTH								//　画面上での画像の中心のX座標
					, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT					//　画面上での画像の中心のY座標
					, 3, 10																	//　画像上での画像の中心のX座標, Y座標
					, 2, Angle																//	サイズと角度
					, *pGimmickGraNo[GRAPH::WMR_PARTS::WMRLight]							//	表示する画像
					, true, false);															//	表示する画像の透過と反転

				SetDrawBlendMode(DX_BASEIMAGE_FORMAT_NORMAL, 0);							//　普通の画像にする
			}
		}
	}
}

//　データロードの管理
void GimmickWMR::DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color)
{
	GimmickPos.Set((float)PosX, (float)PosY);				//	座標指定
	GimmickVecXorY = VecXorY;								//	向き指定	X:0	Y:1
	GimmickSize = Size;										//	大きさ
	GimmickColor = Color;									//　色

	//　フラグをオフにする
	GimmickIsEnergization = false;							//　通電しているかどうか
	GimmickIsValid = false;									//　ギミックの反転
	GimmickIsValidOld = false;								//　前回の判定

	//　WMRギミックの向きが横の場合
	if (GimmickVecXorY == 0)
	{
		//　ギミック中心座標を求める
		GimmickCenterPos.Set(
			((GimmickPos.X + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2),
			GimmickPos.Y * MAP_CHIP_SIZE * 2);
	}

	//　WMRギミックの向きが縦の場合
	else
	{
		//　ギミック中心座標を求める
		GimmickCenterPos.Set(
			GimmickPos.X * MAP_CHIP_SIZE * 2,
			((GimmickPos.Y + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2));
	}
}

//　衝突判定
bool GimmickWMR::ReverseMove(int* PLPosX, int* PLPosY, Vector2D PLVec, int PLSize)
{
	//	プレイヤーがギミックに当たっているかの判定
	if (ReverseCheck(*PLPosX + (int)PLVec.X, *PLPosY + (int)PLVec.Y, PLSize))
	{
		Vector2D Difference = Vector2D(0, 0);												//　Differenceに座標(0, 0)を代入

		Difference.Set(GimmickCenterPos.X - *PLPosX, GimmickCenterPos.Y - *PLPosY);			//	中心とプレイヤーの距離を求める

		*PLPosX = (int)GimmickCenterPos.X + (int)Difference.X;								//	プレイヤーの位置を反転させる
		*PLPosY = (int)GimmickCenterPos.Y + (int)Difference.Y;								//	プレイヤーの位置を反転させる
		return true;																		//	判定結果：当たっている
	}
	return false;																			//	判定結果：当たらない
}

//　ギミックの動作処理
bool GimmickWMR::ReverseCheck(int PLPosX, int PLPosY, int PLSize)
{

	//　通電していないとき
	if (GimmickIsEnergization == false)
	{
		//　WMRギミックの反転を無効化
		GimmickIsValid = false;
		return false;
	}

	//	WMRギミックの向きが横の場合
	if (GimmickVecXorY == 0)
	{
		//	ギミックのY軸の判定外だったら外れる
		if ((((int)GimmickPos.Y * MAP_CHIP_SIZE + 8) * 2) < PLPosY ||
			(((int)GimmickPos.Y * MAP_CHIP_SIZE - 8) * 2) > PLPosY)
		{
			GimmickIsValid = false;															//	ギミックの動作受付中
			return false;
		}


		int PLIntXLeft = (int)(PLPosX - (PLSize / 2) + 16) / (MAP_CHIP_SIZE * 2);			//	チップ計算用にした際のYの位置
		int PLIntXRight = (int)(PLPosX + (PLSize / 2) - 16) / (MAP_CHIP_SIZE * 2);			//	チップ計算用にした際のYの位置



		//	ギミックのX軸の判定外だったら外れる
		if ((int)GimmickPos.X > PLIntXLeft || ((int)GimmickPos.X + GimmickSize - 1) < PLIntXRight)
		{
			GimmickIsValid = false;															//	ギミックの動作受付中
			return false;
		}
	}

	//	WMRギミックの向きが縦の場合
	else
	{
		//	ギミックのY軸の判定外だったら外れる
		if ((((int)GimmickPos.X * MAP_CHIP_SIZE + 8) * 2) < PLPosX ||
			(((int)GimmickPos.X * MAP_CHIP_SIZE - 8) * 2) > PLPosX)
		{
			GimmickIsValid = false;															//	ギミックの動作受付中
			return false;
		}


		int PLIntYTop = (int)(PLPosY - ((int)PLSize / 2) - 2) / (MAP_CHIP_SIZE * 2);		//	チップ計算用にした際のYの位置
		int PLIntYBottom = (int)(PLPosY + ((int)PLSize / 2)) / (MAP_CHIP_SIZE * 2);			//	チップ計算用にした際のYの位置



		//	ギミックのX軸の判定外だったら外れる
		if ((int)GimmickPos.Y > PLIntYTop || ((int)GimmickPos.Y + GimmickSize - 1) < PLIntYBottom)
		{
			GimmickIsValid = false;															//	ギミックの動作受付中
			return false;
		}
	}

	//	ここまで
	//	当たっている時

	//　WMRギミックの反転を有効化
	GimmickIsValid = true;

	//　前回の判定がtrueのとき
	if (GimmickIsValidOld == true)
	{
		return false;
	}

	return true;
}

/*------------------------------感圧-------------------------------*/

//　初期処理
GimmickPres::GimmickPres()
{

}

//	ギミックの更新処理
void GimmickPres::Update()
{
	//　判定の引継ぎ
	if (GimmickIsValidOld != GimmickStep)
	{
		GimmickIsValidOld = GimmickStep;
	}
}

//	ギミックの表示処理
void GimmickPres::Draw()
{
	float Angle = 0;										//	表示角度
	const int ButtonDown = 4;								//	ボタンの沈み具合1～4

	//　ギミックが上向き
	if (GimmickVecXorY == 0)
	{
		//　感圧ギミックがオフのとき
		if (GimmickIsValid == false)
		{
			//	ボタン部品の表示
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH												//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 2 * ButtonDown	//　画面上での画像の中心のY座標
				, 16, 5																		//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																	//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転
		}

		//　感圧ギミックがオンのとき
		else
		{
			//	ボタン部品の表示
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH														//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 2 * (ButtonDown - 3)		//　画面上での画像の中心のY座標
				, 16, 5																				//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																			//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]										//	表示する画像
				, true, false);																		//	表示する画像の透過と反転
		}

		//	基本部品の表示
		DrawRotaGraph2(
			GimmickCenterPos + WIN_UI_WIDTH													//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 16, 4																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::PRES_PARTS::PresBase]									//	表示する画像
			, true, false);																	//	表示する画像の透過と反転

		//	基本部品の上から表示
		if (GimmickIsValid == true)
		{
			//	発光部品の表示(左)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH - (2 * 3)									//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//　画面上での画像の中心のY座標
				, 1, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																	//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	発光部品の表示(右)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH + (2 * 3)									//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//　画面上での画像の中心のY座標
				, 1, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																	//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	電波1の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH + 16					//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 18				//　画面上での画像の中心のY座標
				, 16, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																	//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal1]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	電波2の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH + 16					//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 18 - 8			//　画面上での画像の中心のY座標
				, 16, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																	//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal2]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	電波3の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH + 16					//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT - 18 - 8 * 2		//　画面上での画像の中心のY座標
				, 16, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, Angle																	//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal3]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転
		}
	}

	//　ギミックが下向き
	else
	{
		//　感圧ギミックがオフのとき
		if (GimmickIsValid == false)
		{
			//	ボタン部品の表示
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH												//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 2 * ButtonDown	//　画面上での画像の中心のY座標
				, 16, 5																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転
		}

		//　感圧ギミックがオンのとき
		else
		{
			//	ボタン部品の表示
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH														//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 2 * (ButtonDown - 3)		//　画面上での画像の中心のY座標
				, 16, 5																				//　画像上での画像の中心のX座標, Y座標
				, 2, PI																				//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresButton]										//	表示する画像
				, true, false);																		//	表示する画像の透過と反転
		}

		//	基本部品の表示
		DrawRotaGraph2(
			GimmickCenterPos + WIN_UI_WIDTH													//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 16, 4																			//　画像上での画像の中心のX座標, Y座標
			, 2, PI																			//	サイズと角度
			, *pGimmickGraNo[GRAPH::PRES_PARTS::PresBase]									//	表示する画像
			, true, true);																	//	表示する画像の透過と反転

		//	基本部品の上から表示
		if (GimmickIsValid == true)
		{
			//	発光部品の表示(左)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH - (2 * 3)									//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//　画面上での画像の中心のY座標
				, 1, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	発光部品の表示(右)
			DrawRotaGraph2(
				GimmickCenterPos + WIN_UI_WIDTH + (2 * 3)									//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT						//　画面上での画像の中心のY座標
				, 1, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::PresLight]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転

			//	電波1の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH - 16				//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 18				//　画面上での画像の中心のY座標
				, 16, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal1]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転


			//	電波2の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH - 16					//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 18 + 8			//　画面上での画像の中心のY座標
				, 16, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal2]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転


			//	電波3の表示
			DrawRotaGraph2(
				(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH - 16					//　画面上での画像の中心のX座標
				, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT + 18 + 8 * 2		//　画面上での画像の中心のY座標
				, 16, 4																		//　画像上での画像の中心のX座標, Y座標
				, 2, PI																		//	サイズと角度
				, *pGimmickGraNo[GRAPH::PRES_PARTS::Signal3]								//	表示する画像
				, true, false);																//	表示する画像の透過と反転
		}
	}
}

//　データロードの管理
void GimmickPres::DataRoad(int PosX, int PosY, int VecXorY, int Initia, int Color)
{
	GimmickPos.Set((float)PosX, (float)PosY);										//	座標指定
	GimmickVecXorY = VecXorY;														//	向き指定	X:0	Y:1
	GimmickInitia = Initia;															//	初期
	GimmickColor = Color;															//　色

	GimmickCenterPos = (int)((GimmickPos.X + 0.5)* MAP_CHIP_SIZE * 2);				//	ギミック中心座標を求める

	GimmickIsValid = (bool)Initia;													//　ギミックの有効かどうかを初期にする
}

//　ギミックの動作処理
bool GimmickPres::ReverseCheck(int PLPosX, int PLPosY, int PLSize)
{

	int PLIntXLeft = (int)(PLPosX - (PLSize / 2) + 16);						//	チップ計算用にした際のYの位置
	int PLIntXRight = (int)(PLPosX + (PLSize / 2) - 16);						//	チップ計算用にした際のYの位置

		//	ギミックのX軸の判定外だったら外れる
	if (
		((((int)GimmickPos.X * MAP_CHIP_SIZE) + 4) * 2) > PLIntXLeft ||
		((((int)GimmickPos.X * MAP_CHIP_SIZE) + 4 + 24) * 2) < PLIntXRight
		)
	{
		//　感圧ギミックを踏んでいない
		GimmickStep = false;
		return false;
	}

	int PL_int_y_up = (int)(PLPosY - (PLSize / 2));								//	チップ計算用にした際のYの位置
	int PL_int_y_down = (int)(PLPosY + (PLSize / 2));							//	チップ計算用にした際のYの位置

	//　ギミックが上向き
	if (GimmickVecXorY == 0)
	{
		//	ギミックのY軸の判定外だったら外れる
		if (
			(((int)GimmickPos.Y * MAP_CHIP_SIZE) * 2) < PLPosY ||
			(((int)GimmickPos.Y * MAP_CHIP_SIZE - 20) * 2) > PLPosY
			)
		{
			//　感圧ギミックを踏んでいない
			GimmickStep = false;
			return false;
		}
	}

	//　ギミックが下向き
	else
	{
		//	ギミックのY軸の判定外だったら外れる
		if (
			(((int)GimmickPos.Y * MAP_CHIP_SIZE) * 2) > PLPosY ||
			(((int)GimmickPos.Y * MAP_CHIP_SIZE + 20) * 2) < PLPosY
			)
		{
			//　感圧ギミックを踏んでいない
			GimmickStep = false;
			return false;
		}
	}

	//　感圧ギミックを踏んでいる
	GimmickStep = true;

	//　感圧ギミックを踏んでいる ＆ 前回の判定がfalse
	if (GimmickStep == true && GimmickIsValidOld == false)
	{
		GimmickIsValid = !GimmickIsValid;											//	反対にする
		return true;
	}
	return false;
}

/*------------------------------通電-------------------------------*/

//　初期処理
GimmickEner::GimmickEner()
{

}

//	ギミックの表示処理
void GimmickEner::Draw()
{
	//　出力装置
	if (GimmickKind == 0)
	{
		//　出力装置の表示
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 5, 8																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::ENER_PARTS::OutPut]										//	表示する画像
			, true, false);																	//	表示する画像の透過と反転
	}

	//　入力装置
	else
	{
		//	入力装置の表示
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 5, 8																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::ENER_PARTS::InPut]										//	表示する画像
			, true, false);																	//	表示する画像の透過と反転
	}

	//　通電(黄)
	if (GimmickYellow == true)
	{
		//	発光パーツ(黄色)の表示
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 1, 4																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::ENER_PARTS::LightYellow]								//	表示する画像
			, true, false);																	//	表示する画像の透過と反転
	}

	//　通電(青)
	if (GimmickBlue == true)
	{
		//	発光パーツ(青色)の表示
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 1, 4																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::ENER_PARTS::LightBlue]									//	表示する画像
			, true, false);																	//	表示する画像の透過と反転
	}

	//　通電(白)
	if (GimmickWhite == true)
	{
		//	発光パーツ(白色)の表示
		DrawRotaGraph2(
			(int)GimmickPos.X * MAP_CHIP_SIZE * 2 + WIN_UI_WIDTH							//　画面上での画像の中心のX座標
			, (int)GimmickPos.Y * MAP_CHIP_SIZE * 2 + WIN_UI_HEIGHT							//　画面上での画像の中心のY座標
			, 1, 4																			//　画像上での画像の中心のX座標, Y座標
			, 2, Angle																		//	サイズと角度
			, *pGimmickGraNo[GRAPH::ENER_PARTS::LightWhite]									//	表示する画像
			, true, false);																	//	表示する画像の透過と反転
	}
}

//　データロードの管理
void GimmickEner::DataRoad(int PosX, int PosY, int VecXorY, int Size, int Color, int Kind)
{
	GimmickPos.Set((float)PosX, (float)PosY);										//	座標指定
	GimmickVecXorY = VecXorY;														//	向き指定	X:0	Y:1
	GimmickSize = Size;																//	大きさ
	GimmickColor = Color;															//　色
	GimmickKind = Kind;																//　種類

	switch (GimmickVecXorY)
	{
	case 1:		//	下
		Angle = PI;
		break;
	case 2:		//	左
		Angle = PI * (3.0f / 2.0f);
		break;
	case 3:		//	右
		Angle = PI * (1.0f / 2.0f);
		break;
	default:	//	上
		Angle = 0;
		break;
	}

	//　上向きの場合
	if (GimmickVecXorY == 0)
	{
		//	ギミック中心座標を求める
		GimmickCenterPos = (int)((GimmickPos.X + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2);
	}
	else
	{
		//	ギミック中心座標を求める
		GimmickCenterPos = (int)((GimmickPos.Y + ((float)GimmickSize / 2.0f))* MAP_CHIP_SIZE * 2);
	}
}