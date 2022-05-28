#pragma once
#include "SceneBase.h"

/*
タイトル画面クラス
	選択画面への誘導処理を行う
*/
class SceneTitle :public SceneBase
{
private:
	SceneBase* pNextSceneSave = this;						//	次のシーン保存用
	int BackGraph;											//	背景画像ハンドル
	int TittleGraph;										//	タイトル画像ハンドル

public:
	SceneTitle();											//	初期設定

	//	タイトル画面の処理
	void Initia();											//	初期処理
	void Final();											//	最終処理
	SceneBase* Update();									//	更新処理
	void BaseUpdate();										//	更新処理の内容
	void Draw();											//	表示処理
};