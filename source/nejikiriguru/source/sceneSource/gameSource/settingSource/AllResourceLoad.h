#pragma once
#include "Gameinformation.h"

//	画像データの相対パス
static const char* GraphPath[GRAPH::HANDLE::GameLength] =
{
	"resource/texture/background.png",							//	ゲーム背景画像
	"resource/texture/backbase.png",						//	ゲーム分割背景基礎画像
	"resource/texture/backmove.png",						//	ゲーム分割背景近場画像
	"resource/texture/backsky.png",							//	ゲーム分割背景夕空画像
	"resource/texture/panel32pix.png",						//	ブロックの画像
	"resource/texture/gimmick32pix.png",					//	ギミックの画像
	"resource/texture/player32pix.png",						//	プレイヤーの画像
	"resource/texture/titlelog.png",						//	タイトルロゴ画像
	"resource/texture/ui32pix.png",							//	ゲームパッドUI画像
	"resource/texture/manualpad.png",							//	操作説明画像
	"resource/texture/manualkey.png"						//	操作説明画像キーボード操作
};

//	ギミックそれぞれの部品の数
static const int GimmickGraphSetNum[3] =
{ GRAPH::WMRLength,GRAPH::PresLength,GRAPH::EnerLength };

//	画像を分割するギミックの情報設定
struct GimmickGraphStat
{
	int GraphPosX = 0;										//	画像の参照する右の値
	int GraphPosY = 0;										//	画像の参照する上の値
	int GraphWidth = 0;										//	画像の参照する横幅の値
	int GraphHeight = 0;									//	画像の参照する縦幅の値
};

//	画像を分割するWMRギミックの情報
static const GimmickGraphStat GimmickWMRGraphStatSet[GRAPH::WMRLength] =
{
	{ 0, 0,12,32},											//	基本部品
	{16, 6, 6,20},											//	発光部品
	{24, 0, 8,32},											//	延長部品
	{ 0,32,12, 6}											//	端点部品
};

//	画像を分割する感圧ギミックの情報
static const GimmickGraphStat GimmickPresGraphStatSet[GRAPH::PresLength] =
{
	{32,28,32, 4},											//	基本部品
	{48, 4, 2, 4},											//	発光部品
	{32,16,32, 5},											//	ボタン部品
	{48,32,16, 8},											//	電波1
	{32,32,16, 8},											//	電波2
	{16,32,16, 8}											//	電波3
};

//	画像を分割する通電ギミックの情報
static const GimmickGraphStat GimmickEnerGraphStatSet[GRAPH::EnerLength] =
{
	{35, 0,10, 8},											//	出力装置
	{35, 8,10, 8},											//	入力装置
	{48, 4, 2, 4},											//	発光部品(黄色)
	{48, 8, 2, 4},											//	発光部品(青色)
	{48,12, 2, 4}											//	発光部品(白色)
};


/*
画像リソース管理クラス
	画像を読み込みハンドルにして保存し
	このクラスを参照して使用してもらう
*/
class DataLoadResource
{
private:
	bool FinalGameGraph = false;								//	ゲームをせずに終わったとき用の判定

public:

	//	変数
	/*----------------------画像------------------------*/
	int GraphGame[GRAPH::HANDLE::GameLength] = { 0 };				//	ゲームの画像
	int GraphPL[GRAPH::PL_GRAPH::PLLength][PL_MAX_GRAPH_WIDTH] = { 0 };	//	プレイヤーの画像
	int GraphBlock[GRAPH::BLOCK::BlockLength - 1][4] = { 0 };		//	ブロックの画像
	int GraphBlockGimmickWire = 0;								//	ステージ上下の針金の画像
	int GraphEDWMR = 0;											//	エンディングで使用する専用WMRの画像
	int	GraphGimmickWMR[GRAPH::WMR_PARTS::WMRLength] = { 0 };		//	WMRの画像
	int GraphGimmickPres[GRAPH::PRES_PARTS::PresLength] = { 0 };	//	感圧の画像
	int GraphGimmickEner[GRAPH::ENER_PARTS::EnerLength] = { 0 };	//	通電の画像

	/*----------------------文字------------------------*/
	int FontSet[FONT_SIZE::FontLength] = { 0 };				//	使用フォント

	int MaxStageNo = 0;										//	解放済み最大のステージ番号
	int StageSet = 0;										//	選択したステージ

	DataLoadResource() {}									//	初期設定

	//	画像リソース管理クラスの処理
	void Initia();											//	初めに読み込み画像を配列にセットする
	void InitiaGame()										//	ゲーム初期処理まとめ 
	{
		//	一度も読み込んでない
		if (FinalGameGraph == false) {

			InitiaPL();										//	プレイヤーの画像ロード
			InitiaBlock();									//	ブロックの画像ロード
			InitiaGimmick();								//	ギミックの画像ロード
			FinalGameGraph = true;							//	ゲームの画像はロードした。
		}
	}
	void InitiaPL();										//	初めに読み込みPL画像を配列にセットする
	void InitiaBlock();										//	初めに読み込みブロック画像を配列にセットする
	void InitiaGimmick();									//	初めに読み込みギミック画像を配列にセットする
	void InitiaGimmickSet(int GimmickNo, int PartsNo);		//	初めに読み込みギミック画像を配列にセットする
	void Final();											//	最後に読み込んだすべての画像を消す
};