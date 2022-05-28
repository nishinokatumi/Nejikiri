#include "DrawMAP.h"


/*
マップの表時処理クラス
マップの画像を加工してチップで表示するクラス

*/

//	初期設定
DrawMAP::DrawMAP()
{

}

//	繰り返し実行：パネルの操作の判断と計算
void DrawMAP::Update()
{

}

//	表示処理
void DrawMAP::DrawMap()
{
	//	マップの描画
	{
		//	マップデータのMapY軸の上から下まで
		for (int MapY = 0; MapY < MAP_HEIGHT; MapY++)
		{
			//	マップデータのMapX軸の左から右まで
			for (int MapX = 0; MapX < MAP_WIDTH; MapX++)
			{
				//	ゴールの針金
				if (MapY == 0 && MapX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	表示する右上のX座標
						, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)					//	表示する右上のY座標
						, 2, 0															//	表示する画像の中心位置()
						, 2, -PI / 2													//	サイズと角度
						, *pGimmickGraph												//	表示する画像
						, true, false);													//	表示する画像の透過と反転
				}

				//	ゴールの針金
				if (MapY == MAP_HEIGHT - 1 && MapX < MAP_WIDTH - 1)
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	表示する右上のX座標
						, (MapY + 1) * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)				//	表示する右上のY座標
						, 2, 0															//	表示する画像の中心位置()
						, 2, -PI / 2													//	サイズと角度
						, *pGimmickGraph												//	表示する画像
						, true, false);													//	表示する画像の透過と反転
				}



				// ブロックの表示
				if (NowMapData.BlockData[MapY][MapX] == GRAPH::BLOCK::Pne)
				{

					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	表示する右上のX座標
						, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)					//	表示する右上のY座標
						, 0, 0															//	表示する画像の中心位置()
						, 2, 0															//	サイズと角度
						, *pMapGraph[GRAPH::BLOCK::Pne - 1][NowMapData.MapPanelNo]		//	表示する画像
						, true, false);													//	表示する画像の透過と反転


					//	ブロックの隣を判断し補助部品を付ける
					{
						if (MapX < MAP_WIDTH - 1 && NowMapData.BlockData[MapY][MapX + 1] != 1)	//ブロック右部
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	表示する右上のX座標
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	表示する右上のY座標
								, 0, 0						//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][3]				//	表示する画像
								, true, false);											//	表示する画像の透過と反転
						}

						if (MapX > 0 && NowMapData.BlockData[MapY][MapX - 1] != 1)		//	ブロック右部
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	表示する右上のX座標
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	表示する右上のY座標
								, 0, 0						//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][2]				//	表示する画像
								, true, false);											//	表示する画像の透過と反転
						}

						if (MapY < MAP_HEIGHT - 1 && NowMapData.BlockData[MapY + 1][MapX] != 1)	//	ブロック上部
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	表示する右上のX座標
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	表示する右上のY座標
								, 0, 0						//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][1]				//	表示する画像
								, true, false);											//	表示する画像の透過と反転
						}

						if (MapY > 0 && NowMapData.BlockData[MapY - 1][MapX] != 1)		//	ブロック下部
						{
							DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)	//	表示する右上のX座標
								, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)			//	表示する右上のY座標
								, 0, 0													//	表示する左下の座標
								, 2, 0													//	サイズと角度
								, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][0]				//	表示する画像
								, true, false);											//	表示する画像の透過と反転
						}
					}
				}
				else if (NowMapData.BlockData[MapY][MapX] == GRAPH::BLOCK::Wal)
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)			//	表示する右上のX座標
						, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)					//	表示する右上のY座標
						, 0, 0															//	表示する左下の座標
						, 2, 0															//	サイズと角度
						, *pMapGraph[GRAPH::BLOCK::Wal - 1][NowMapData.MapWallNo]		//	表示する画像
						, true, false);													//	表示する画像の透過と反転

					//	ブロック右左部
					{
						DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)		//	表示する右上のX座標
							, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)				//	表示する右上のY座標
							, 0, 0														//	表示する左下の座標
							, 2, 0														//	サイズと角度
							, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][2]					//	表示する画像
							, true, false);												//	表示する画像の透過と反転

						DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)		//	表示する右上のX座標
							, MapY * MAP_CHIP_SIZE * 2 + (WIN_UI_HEIGHT)				//	表示する右上のY座標
							, 0, 0														//	表示する左下の座標
							, 2, 0														//	サイズと角度
							, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][3]					//	表示する画像
							, true, false);												//	表示する画像の透過と反転
					}
				}
			}
		}

		//	上下の壁の端の処理
		for (int MapY = 0; MapY < MAP_HEIGHT + 2; MapY += 16)
		{
			if (MapY >= 16 && MapNo == 0)break;
			//	マップデータのMapY軸の上から下まで

			//	左右の壁の端の処理
			for (int MapX = 0; MapX < MAP_WIDTH; MapX += 19)
			{
				//	マップデータのMapX軸の左から右まで
				DrawRotaGraph2(MapX* MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)					//	表示する右上のX座標
					, MapY* MAP_CHIP_SIZE * 2 + ((WIN_UI_HEIGHT)-MAP_CHIP_SIZE * 2)		//	表示する右上のY座標
					, 0, 0																//	表示する左下の座標
					, 2, 0																//	サイズと角度
					, *pMapGraph[GRAPH::BLOCK::Wal - 1][NowMapData.MapWallNo]			//	表示する画像
					, true, false);														//	表示する画像の透過と反転

				//	ブロック右左部
				{
					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)				//	表示する右上のX座標
						, MapY * MAP_CHIP_SIZE * 2 + ((WIN_UI_HEIGHT)-MAP_CHIP_SIZE * 2)	//	表示する右上のY座標
						, 0, 0															//	表示する左下の座標
						, 2, 0															//	サイズと角度
						, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][2]						//	表示する画像
						, true, false);													//	表示する画像の透過と反転

					DrawRotaGraph2(MapX * MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)				//	表示する右上のX座標
						, MapY * MAP_CHIP_SIZE * 2 + ((WIN_UI_HEIGHT)-MAP_CHIP_SIZE * 2)	//	表示する右上のY座標
						, 0, 0															//	表示する左下の座標
						, 2, 0															//	サイズと角度
						, *pMapGraph[GRAPH::BLOCK::AuxiMate - 1][3]						//	表示する画像
						, true, false);													//	表示する画像の透過と反転
				}

			}
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			//	ブレンドモード変更指定の数値180の濃さ

		//	赤い針金にするために赤い四角を被せる
		DrawBox(MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)
			, ((WIN_UI_HEIGHT)) - 4
			, (MAP_WIDTH - 1)*MAP_CHIP_SIZE * 2 + (WIN_UI_WIDTH)
			, ((WIN_UI_HEIGHT)) + 4, GetColor(255, 0, 0), true);

		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);		//	ブレンドモード変更通常に
	}
}

//	ステージ変更時の初期値読み込み
void DrawMAP::DataRoad(MAP_INFO::Stage MapData, int MapDataNo)
{
	NowMapData = MapData;					//	表示するステージデータを読み込み
	MapNo = MapDataNo;							//	表示するステージナンバー読み込み
}