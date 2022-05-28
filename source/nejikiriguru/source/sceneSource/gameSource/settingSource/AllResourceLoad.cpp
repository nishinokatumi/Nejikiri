#include "AllResourceLoad.h"
#include "DxLib.h"


/*
画像リソース管理クラス
	画像を読み込みハンドルにして保存し
	このクラスを参照して使用してもらう
*/

//	初めに読み込み画像を配列にセットする
void DataLoadResource::Initia()
{
	//	フォントをフォントの種類分読み込み設定する
	for (int FontNum = 0; FontNum < FontLength; FontNum++)
	{
		FontSet[FontNum] =
			CreateFontToHandle(
				0,											//	デフォルトのフォントを使う
				SetFontStat[FontNum].Size,					//	フォントの大きさを設定する
				SetFontStat[FontNum].Thick,					//	フォントの太さを設定する
				DX_FONTTYPE_NORMAL);						//	ノーマルフォント
	}

	//	画像の枚数だけ繰り返す
	for (int GraphNum = 0; GraphNum < GRAPH::HANDLE::GameLength; GraphNum++)
	{
		GraphGame[GraphNum] = LoadGraph(GraphPath[GraphNum]);	//	画像の読み込み
	}
}

//	初めに読み込みPL画像を配列にセットする
void DataLoadResource::InitiaPL()
{
	//	画像の左側から処理：横の画像個数回
	for (int GraphNumX = 0; GraphNumX < GRAPH::PL_GRAPH::PLLength; GraphNumX++)
	{
		//	画像の上側から処理：縦の画像個数回
		for (int GraphNumY = 0; GraphNumY < 4; GraphNumY++)
		{
			GraphPL[GraphNumX][GraphNumY]					//	プレイヤーの画像配列に代入
				= DerivationGraph(							//	画像の一部を新しい画像に変換
					PL_GRAPH_SIZE * GraphNumX,				//	取り出す部分の左の座標を入力
					PL_GRAPH_SIZE * GraphNumY,				//	取り出す部分の上の座標を入力
					PL_GRAPH_SIZE, PL_GRAPH_SIZE,			//	取り出す部分のXとYのピクセル数を入力
					GraphGame[GRAPH::HANDLE::PLHandle]);	//	取り出す画像を指定
		}
	}
}

//	初めに読み込みブロック画像を配列にセットする
void DataLoadResource::InitiaBlock()
{
	//	画像の上側から処理：縦の画像個数回
	for (int GraphNumY = 0; GraphNumY < GRAPH::BLOCK::BlockLength; GraphNumY++)
	{
		//	画像の左側から処理：横の画像個数回
		for (int GraphNumX = 0; GraphNumX < PL_MAX_GRAPH_WIDTH; GraphNumX++)
		{

			GraphBlock[GraphNumY][GraphNumX]				//	ブロックの画像配列に代入
				= DerivationGraph(							//	画像の一部を新しい画像に変換
					MAP_CHIP_SIZE * GraphNumX,				//	取り出す部分の左の座標を入力
					MAP_CHIP_SIZE * GraphNumY,				//	取り出す部分の上の座標を入力
					MAP_CHIP_SIZE, MAP_CHIP_SIZE,			//	取り出す部分のXとYのピクセル数を入力
					GraphGame[GRAPH::HANDLE::PanelHandle]);	//	取り出す画像を指定
		}
	}
	//	針金の読み込み
	GraphBlockGimmickWire = DerivationGraph(
		64, 0, 4, 32,
		GraphGame[GRAPH::HANDLE::GimmickHandle]);

	//	エンディング用WMRの読み込み
	GraphEDWMR = DerivationGraph(
		0, 64, 64, 64,
		GraphGame[GRAPH::HANDLE::GimmickHandle]);
}

//	初めに読み込みギミック画像を配列にセットする
void DataLoadResource::InitiaGimmick()
{
	//	WMR 感圧 通電の３回
	for (int GimmickGraphNum = 0; GimmickGraphNum < 3; GimmickGraphNum++)
	{
		//	WMR 感圧 通電それぞれのパーツの数分
		for (int GimmickPartsNum = 0; GimmickPartsNum < GimmickGraphSetNum[GimmickGraphNum]; GimmickPartsNum++)
		{
			InitiaGimmickSet(GimmickGraphNum, GimmickPartsNum);	//	画像を読み込む
		}
	}
}

//	初めに読み込みギミック画像を配列にセットする
void DataLoadResource::InitiaGimmickSet(int GimmickNo, int PartsNo)
{
	//	WMR切り出し
	if (GimmickNo == 0)
	{
		GraphGimmickWMR[PartsNo] = DerivationGraph(			//	切り出したものを代入
			GimmickWMRGraphStatSet[PartsNo].GraphPosX,		//	右の値
			GimmickWMRGraphStatSet[PartsNo].GraphPosY,		//	上の値
			GimmickWMRGraphStatSet[PartsNo].GraphWidth,		//	横幅の値
			GimmickWMRGraphStatSet[PartsNo].GraphHeight,	//	縦幅の値
			GraphGame[GRAPH::HANDLE::GimmickHandle]);		//	切り出す画像
	}

	//	感圧切り出し
	else if (GimmickNo == 1)
	{
		GraphGimmickPres[PartsNo] = DerivationGraph(		//	切り出したものを代入
			GimmickPresGraphStatSet[PartsNo].GraphPosX,		//	右の値
			GimmickPresGraphStatSet[PartsNo].GraphPosY,	//	上の値
			GimmickPresGraphStatSet[PartsNo].GraphWidth,	//	横幅の値
			GimmickPresGraphStatSet[PartsNo].GraphHeight,	//	縦幅の値
			GraphGame[GRAPH::HANDLE::GimmickHandle]);		//	切り出す画像
	}

	//	通電切り出し
	else if (GimmickNo == 2)
	{
		GraphGimmickEner[PartsNo] = DerivationGraph(		//	切り出したものを代入
			GimmickEnerGraphStatSet[PartsNo].GraphPosX,		//	右の値
			GimmickEnerGraphStatSet[PartsNo].GraphPosY,		//	上の値
			GimmickEnerGraphStatSet[PartsNo].GraphWidth,	//	横幅の値
			GimmickEnerGraphStatSet[PartsNo].GraphHeight,	//	縦幅の値
			GraphGame[GRAPH::HANDLE::GimmickHandle]);		//	切り出す画像
	}
}

//	最後に読み込んだすべての画像を消す
void DataLoadResource::Final()
{
	int GraphNum = 0;										//	画像の数
	int PieceNum = 0;										//	コマ数

	//	画像の数だけ処理する
	for (GraphNum = 0; GraphNum < GRAPH::HANDLE::GameLength; GraphNum++)
	{
		DeleteGraph(GraphGame[GraphNum]);
	}

	//	文字の数だけ処理する
	for (GraphNum = 0; GraphNum < FONT_SIZE::FontLength; GraphNum++)
	{
		DeleteFontToHandle(FontSet[GraphNum]);
	}

	//	ゲームをプレイしていたら
	if (FinalGameGraph)
	{
		//	プレイヤーの画像の数だけ処理する
		for (GraphNum = 0; GraphNum < GRAPH::PL_GRAPH::PLLength; GraphNum++)
		{
			//	コマの数だけ処理する
			for (PieceNum = 0; PieceNum < 4; PieceNum++)
			{
				DeleteGraph(GraphPL[GraphNum][PieceNum]);
			}
		}

		//	ブロックの画像の数だけ処理する
		for (GraphNum = 0; GraphNum < GRAPH::BLOCK::BlockLength; GraphNum++)
		{
			//	コマの数だけ処理する
			for (PieceNum = 0; PieceNum < 4; PieceNum++)
			{
				DeleteGraph(GraphBlock[GraphNum][PieceNum]);
			}
		}

		DeleteGraph(GraphBlockGimmickWire);					//	ワイヤーを処理
		DeleteGraph(GraphEDWMR);							//	エンディング用のWMRを処理

		//	ギミックの数だけ処理
		for (int GimmickGraphNum = 0; GimmickGraphNum < 3; GimmickGraphNum++)
		{
			//	部品の数だけ処理
			for (GraphNum = 0; GraphNum < GimmickGraphSetNum[GimmickGraphNum]; GraphNum++)
			{
				if (GimmickGraphNum == 0)DeleteGraph(GraphGimmickWMR[GraphNum]);		//	WMR
				else if (GimmickGraphNum == 1)DeleteGraph(GraphGimmickPres[GraphNum]);	//	感圧
				else if (GimmickGraphNum == 2)DeleteGraph(GraphGimmickEner[GraphNum]);	//	通電
			}
		}
	}
}