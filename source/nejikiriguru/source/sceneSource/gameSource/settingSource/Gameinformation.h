#pragma once
#include "Vector2D.h"
//ゲームプログラムの定数・形

// ウィンドウのサイズ
#define GAME_WIN_WIDTH	1920								//	ゲームの画面サイズ:横
#define GAME_WIN_HEIGHT	1080								//	ゲームの画面サイズ:縦

#define WIN_PL_WIDTH		1280								//	プレイ画面サイズ:横
#define WIN_PL_HEIGHT		960									//	プレイ画面サイズ:縦
#define MAP_CHIP_SIZE 	32									//	一つのチップのサイズ
#define MAP_NUM			27									//	ステージ数

#define MAP_WIDTH		(WIN_PL_WIDTH / (MAP_CHIP_SIZE*2))	//	マップの横幅
#define MAP_HEIGHT		(WIN_PL_HEIGHT / (MAP_CHIP_SIZE*2))	//	マップの縦幅
#define	WIN_UI_WIDTH		((GAME_WIN_WIDTH - WIN_PL_WIDTH)/2)		//	UIの横幅
#define	WIN_UI_HEIGHT		((GAME_WIN_HEIGHT - WIN_PL_HEIGHT)/2)		//	UIの縦幅

//	プレイヤーの設定
#define PL_MAX_GRAPH_WIDTH 4									//	プレイヤーテクスチャーの動作最大数(X)
#define PL_MAX_GRAPH_HEIGHT 4									//	プレイヤーテクスチャーの動きの数(Y)
#define PL_GRAPH_SIZE 32										//	プレイヤーテクスチャーの一辺ピクセル数

#define PL_MOV_SPEED 6										//	プレイヤーの動く速さ
#define PL_GRAPHVITY	32										//	プレイヤーの重力値(場合により-を付けて使う)


#define GIMMICK_WMR_MAX_NUM 12								//	WMRの最大数
#define GIMMICK_PRES_MAX_NUM 3								//	WMRの最大数
#define GIMMICK_ENER_MAX_NUM 6								//	WMRの最大数

//	画像などの列挙型の名前空間
namespace GRAPH
{
	//	画像ハンドル
	enum HANDLE
	{
		BackGround = 0,										//	バックスクリーン画像
		BackBase,											//	バックスクリーン建物画像
		BackMove,											//	バックスクリーン近い建物画像
		BackSky,											//	バックスクリーン空画像
		PanelHandle,										//	パネル画像
		GimmickHandle,										//	ギミック画像
		PLHandle,											//	キャラ画像
		TitlLogo,											//	タイトルロゴ
		GamePadUI,											//	ゲームパッド画像
		Manual,												//	説明画像
		ManualKey,											//	説明画像キーボード操作
		GameLength,											//	列挙数
	};

	//	プレイヤーの画像の状態種類
	enum PL_GRAPH
	{
		Wait = 0,											//	待機
		Move,												//	移動
		Jump,												//	跳躍
		Action,												//	行動
		PLLength,											// 列挙数
	};

	// マップ画像の列挙
	enum BLOCK
	{
		Ear = 0,											// 空白
		Pne,												// パネル
		Wal,												// 壁
		AuxiMate,											// 補助材
		BlockLength,										// 列挙数
	};

	//	WMRの部品
	enum WMR_PARTS
	{
		WMRBase = 0,										//	基本部品
		WMRLight,											//	発光部品
		Extend,												//	延長部品
		EndPoint,											//	端点部品
		WMRLength,											//	部品総数
	};

	//	PRESの部品
	enum PRES_PARTS
	{
		PresBase = 0,										//	基本部品
		PresLight,											//	発光部品
		PresButton,											//	ボタン部品
		Signal1,											//　電波1
		Signal2,											//　電波2
		Signal3,											//　電波3
		PresLength											//	部品総数
	};

	//　ENERの部品
	enum ENER_PARTS
	{
		OutPut = 0,											//　出力装置
		InPut,												//　入力装置
		LightYellow,										//	発光部品(黄色)
		LightBlue,											//	発光部品(青色)
		LightWhite,											//	発光部品(白色)
		EnerLength											//	部品総数
	};
}


//	マップの型の名前空間
namespace MAP_INFO
{
	// ステージの構造体
	struct Stage
	{
		int MapPanelNo;										//	パネルの種類
		int MapWallNo;										//	壁の種類
		int BlockData[MAP_HEIGHT][MAP_WIDTH];					// マップ
	};
	//	WMRギミックの構造体
	struct GimmickDataWMR
	{
		int GimmickWMRNum;									//	WMRの数
		int GimmickWMR[GIMMICK_WMR_MAX_NUM][5];				//	WMRのデータ　現在のギミックの設定情報 X:Y:縦横:長さ:チャンネル
	};

	//	感圧ギミックの構造体
	struct GimmickDataPres
	{
		int GimmickPresNum;									//	感圧の数
		int GimmickPres[GIMMICK_PRES_MAX_NUM][5];			//	感圧のデータ　現在のギミックの設定情報 X:Y:上下:初期値:チャンネル
	};

	//	通電ギミックの構造体
	struct GimmickDataEner
	{
		int GimmickEnerNum;									//	通電の数
		int GimmickEner[GIMMICK_ENER_MAX_NUM][6];			//	通電のデータ　現在のギミックの設定情報 X:Y:向き:サイズ:チャンネル:種類
	};

	//	ギミックの構造体をまとめた構造体
	struct GimmickData
	{
		GimmickDataWMR	StageWMRData;						//	ステージのWMRのデータ
		GimmickDataPres StagePresData;						//	ステージの感圧のデータ
		GimmickDataEner StageEnerData;						//	ステージの通電のデータ
	};
}


//	プレイヤーが当たった方向
enum class HIT_RESULT
{
	None = 0,												// 当たらなかった
	Left,													// 左辺に当たった
	Right,													// 右辺に当たった
	Top,													// 上辺に当たった
	Bottom,													// 下辺に当たった
};

//	フォントの種類
enum FONT_SIZE
{
	Normal = 0,												//	通常サイズのフォント
	PicUp,													//	少し目立たせるサイズのフォント
	Big,													//	大きいサイズのフォント
	GameStat,												//	情報を書くサイズのフォント
	Tab,													//	タブ文字数
	Explanation,											//　説明
	FontLength,												//	列挙数
};

//	フォントの情報の構造体
struct FontStat
{
	int Size;												//	大きさ
	int Thick;												//	フォントの太さ
};

//	フォントの情報
const FontStat SetFontStat[FONT_SIZE::FontLength] =
{
	{16,-1},												//	ノーマル
	{32,-1},												//	目立たせ
	{128,5},												//	大きく
	{40,-1},												//	情報を書く
	{55,-1},												//	タブ文字
	{24,-1},												//　説明
};