#pragma once
#include "Gameinformation.h"
#include "UIDraw.h"

//	UIの部品
enum UI_PARTS
{
	A = 0,			//　A
	B,				//　B
	X,				//　X
	Y,				//　Y
	L,				//　L
	R,				//　R
	Button,			//　ボタン
	Stick,			//　スティック
	VecPad,			//　方向パッド
	LightVec,		//　方向パッド(発光)
	Trigger,		//　トリガー
	Shoulder,		//　ショルダボタン
	Key,			//	キーボードのキー
	EnterKey,		//	エンターキー
	UILength,		//	部品総数
};

//	Menuの部品
enum MENU_PARTS
{
	GoldFrame = 0,	//	金の枠
	GoldEndoint,	//	金の端点
	LineCenter,		//	枠の中央
	UIMenuLength,	//	部品総数
};

//	Menuの表示種類
enum MENU_TYPE
{
	FullDraw = 0,	//	全表示
	CenterNone,		//	枠中央部品無し
	BackTransparency,//	背景半透明
};

//	UI部品の原点(左上)
static const int UIGraphPos[UI_PARTS::UILength][2] =
{
	{96,32},		//	A
	{112,32},		//	B
	{96,46},		//	X
	{112,46},		//	Y
	{104,0},		//	L
	{104,16},		//	R
	{0,48},			//	ボタン
	{32,32},		//	スティック
	{0,32},			//	方向パッド
	{16,32},		//	方向パッド（発光）
	{64,48},		//	トリガー
	{64,32},		//	ショルダボタン
	{48,0},			//	キーボードのキー
	{64,0}			//	エンターキー
};

//	UI部品の幅(XY)
static const int UIGraphSize[UI_PARTS::UILength][2] =
{
	{16,16},		//	A
	{16,16},		//	B
	{16,16},		//	X
	{16,16},		//	Y
	{16,16},		//	L
	{16,16},		//	R
	{16,16},		//	ボタン
	{32,32},		//	スティック
	{16,10},		//	方向パッド
	{16,10},		//	方向パッド（発光）
	{32,16},		//	トリガー
	{32,16},		//	ショルダボタン
	{16,16},		//	キーボードのキー
	{32,32}			//	エンターキー
};

//	UI部品の中心位置
static const int UIGraphCenterPos[UI_PARTS::UILength][2] =
{
	{8,8},			//	A
	{8,8},			//	B
	{8,8},			//	X
	{8,8},			//	Y
	{8,8},			//	L
	{8,8},			//	R
	{8,8},			//	ボタン
	{16,16},		//	スティック
	{16,5},			//	方向パッド
	{16,5},			//	方向パッド（発光）
	{16,8},			//	トリガー
	{16,8},			//	ショルダボタン
	{8,8},			//	キーボードのキー
	{16,16}			//	エンターキー
};

//	UI部品の原点(左上)
static const int UIFramePos[MENU_PARTS::UIMenuLength][2] =
{
	{0 ,16},			//	GoldFrame
	{0 ,0 },			//	GoldEndoint
	{32,0 },			//	LineCenter
};

//	UI部品の幅(XY)
static const int UIFrameSize[MENU_PARTS::UIMenuLength][2] =
{
	{4 ,16},			//	GoldFrame
	{16,16},			//	GoldEndoint
	{16,32},			//	LineCenter
};

//	UI部品の中心位置
static const int UIFrameCenterPos[MENU_PARTS::UIMenuLength][2] =
{
	{2 ,8 },			//	GoldFrame
	{8 ,8 },			//	GoldEndoint
	{8 ,16},			//	LineCenter
};

enum GameSenenUIPosition
{
	SpaceAX = 360,
	SpaceBX = 630,
	SpaceCX = 900,
	SpaceDX = 1170,
	SpaceAY = 1030,
	SpaceC = 0
};

/*
ゲームUIの管理クラス
	ゲームUIを分割し選んで表示する
*/
class GameUI
{
private:
	int GameUIGraph[UI_PARTS::UILength] = { 0 };			//	ゲームパッドの画像ハンドル
	int GameUIFrame[MENU_PARTS::UIMenuLength] = { 0 };		//	ゲームUIの画像ハンドル

	int FontThrty;											//　フォントサイズ30

	int UIColorWhite;										//	白
	int UIColorBlack;										//	黒

public:
	int*	pGameUIFont[FONT_SIZE::FontLength] = { 0 };		//	使用フォント
	UIDraw* pGameUIDraw = new UIDraw();						//	UI表示管理

	GameUI();												//	初期設定

	//	ゲームUIの処理
	void Initia(int GameUIGraphNo);					    	//	初期処理
	void Final();								    		//	最終処理

	//	ゲームの画像を選択し表示する
	void Draw(int UIPosX, int UIPosY, float Size, int SetUIParts, int VecPadSet = -1);	//	UIの表示処理
	void DrawpadUI(bool GamePadReady);						//	ゲーム中の操作説明

	//	メニューウィンドウを表示する(座標式)PV風になる縦幅(((UIFrameSize[MENU_PARTS::LineCenter][1] - 8) - (UIFrameSize[MENU_PARTS::GoldFrame][0]*2)) * 4)
	void DrawMenuWindowPos(int MenuPosX1, int MenuPosY1, int MenuPosX2, int MenuPosY2, int Size, int BackColor, int MenuType, int Transparency = 0);

	//	メニューウィンドウを表示する(原点式)PV風になる縦幅(((UIFrameSize[MENU_PARTS::LineCenter][1] - 8) - (UIFrameSize[MENU_PARTS::GoldFrame][0]*2)) * 4)
	void DrawMenuWindowOrigin(int MenuPosX, int MenuPosY, int MenuWidth, int MenuHeight, int Size, int BackColor, int MenuType, int Transparency = 0)
	{
		//	原点式から座標式に変換
		DrawMenuWindowPos(MenuPosX, MenuPosY, MenuPosX + MenuWidth, MenuPosY + MenuHeight, Size, BackColor, MenuType, Transparency);
	}

	//	メニューウィンドウを表示する(中心式)PV風になる縦幅(((UIFrameSize[MENU_PARTS::LineCenter][1] - 8) - (UIFrameSize[MENU_PARTS::GoldFrame][0]*2)) * 4)
	void DrawMenuWindowCenter(int MenuCenterPosX, int MenuCenterPosY, int MenuWidth, int MenuHeight, int Size, int BackColor, int MenuType, int Transparency = 0)
	{
		//	中心式から座標式に変換
		DrawMenuWindowPos(MenuCenterPosX - (MenuWidth / 2), MenuCenterPosY - (MenuHeight / 2),
			MenuCenterPosX + (MenuWidth / 2), MenuCenterPosY + (MenuHeight / 2), Size, BackColor, MenuType, Transparency);
	}
};